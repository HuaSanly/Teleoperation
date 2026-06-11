#include "udp/fec_v2.hpp"

#include "udp/gf256.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <mutex>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"

namespace trb::udp
{
    namespace
    {
        bool parseIntAfterColon(const std::string &text, size_t &pos, int &out)
        {
            const size_t colon = text.find(':', pos);
            if (colon == std::string::npos)
            {
                return false;
            }
            size_t index = colon + 1;
            while (index < text.size() && (text[index] == ' ' || text[index] == '\t' || text[index] == '\r' || text[index] == '\n'))
            {
                ++index;
            }
            bool negative = false;
            if (index < text.size() && text[index] == '-')
            {
                negative = true;
                ++index;
            }
            if (index >= text.size() || text[index] < '0' || text[index] > '9')
            {
                return false;
            }
            long value = 0;
            while (index < text.size() && text[index] >= '0' && text[index] <= '9')
            {
                value = value * 10 + (text[index] - '0');
                ++index;
            }
            out = static_cast<int>(negative ? -value : value);
            pos = index;
            return true;
        }

        const std::vector<uint8_t> &getCoef(uint8_t k, uint8_t r)
        {
            struct Cache
            {
                std::mutex mutex;
                std::unordered_map<uint32_t, std::vector<uint8_t>> values;
            };
            static Cache cache;

            const uint32_t key = (static_cast<uint32_t>(k) << 8) | static_cast<uint32_t>(r);
            {
                std::lock_guard<std::mutex> lock(cache.mutex);
                auto it = cache.values.find(key);
                if (it != cache.values.end())
                {
                    return it->second;
                }
            }

            std::vector<uint8_t> coef(static_cast<size_t>(k) * static_cast<size_t>(r), 0);
            for (uint8_t row = 0; row < r; ++row)
            {
                for (uint8_t column = 0; column < k; ++column)
                {
                    const uint8_t x = column;
                    const uint8_t y = static_cast<uint8_t>(0x80u + row);
                    coef[static_cast<size_t>(row) * static_cast<size_t>(k) + static_cast<size_t>(column)] = gf256::inv(static_cast<uint8_t>(x ^ y));
                }
            }

            std::lock_guard<std::mutex> lock(cache.mutex);
            auto [it, inserted] = cache.values.emplace(key, std::move(coef));
            (void)inserted;
            return it->second;
        }

        void prepareGroupCoefficients(uint16_t total_fragments,
                                      uint8_t groups,
                                      uint8_t r_per_group,
                                      std::vector<uint8_t> &k_by_group,
                                      std::vector<const std::vector<uint8_t> *> &coef_by_group)
        {
            k_by_group.assign(groups, 0);
            coef_by_group.assign(groups, nullptr);
            for (uint8_t group = 0; group < groups; ++group)
            {
                uint8_t k_group = 0;
                for (uint32_t index = group; index < total_fragments; index += groups)
                {
                    ++k_group;
                }
                k_by_group[group] = k_group;
                if (k_group > 0)
                {
                    coef_by_group[group] = &getCoef(k_group, r_per_group);
                }
            }
        }
    } // namespace

    bool FecV2::getParams(uint8_t table_id, uint16_t total_fragments, uint8_t &groups, uint8_t &r_per_group) const
    {
        groups = 0;
        r_per_group = 0;
        if (table_id == 0 || table_id != 1 || total_fragments >= 256)
        {
            return false;
        }
        const auto &fec_table = table();
        if (!fec_table.loaded)
        {
            return false;
        }
        groups = fec_table.groups_by_n[static_cast<size_t>(total_fragments)];
        r_per_group = fec_table.r_by_n[static_cast<size_t>(total_fragments)];
        return groups > 0 && r_per_group > 0;
    }

    void FecV2::buildParity(const uint8_t *data,
                            size_t size,
                            uint16_t total_fragments,
                            uint8_t groups,
                            uint8_t r_per_group,
                            size_t symbol_bytes,
                            std::vector<std::vector<uint8_t>> &out_parity) const
    {
        out_parity.clear();
        if (!data || size == 0 || groups == 0 || r_per_group == 0 || symbol_bytes == 0)
        {
            return;
        }

        const size_t parity_count = static_cast<size_t>(groups) * static_cast<size_t>(r_per_group);
        out_parity.resize(parity_count);
        std::vector<uint8_t *> out_payloads;
        out_payloads.reserve(parity_count);
        for (auto &payload : out_parity)
        {
            payload.resize(symbol_bytes);
            out_payloads.push_back(payload.data());
        }

        buildParityInto(data, size, total_fragments, groups, r_per_group, symbol_bytes, out_payloads);
    }

    void FecV2::buildParityInto(const uint8_t *data,
                                size_t size,
                                uint16_t total_fragments,
                                uint8_t groups,
                                uint8_t r_per_group,
                                size_t symbol_bytes,
                                const std::vector<uint8_t *> &out_payloads) const
    {
        if (!data || size == 0 || groups == 0 || r_per_group == 0 || symbol_bytes == 0)
        {
            return;
        }

        const size_t parity_count = static_cast<size_t>(groups) * static_cast<size_t>(r_per_group);
        if (out_payloads.size() < parity_count)
        {
            return;
        }

        std::vector<uint8_t> k_by_group;
        std::vector<const std::vector<uint8_t> *> coef_by_group;
        prepareGroupCoefficients(total_fragments, groups, r_per_group, k_by_group, coef_by_group);

        for (uint8_t parity = 0; parity < r_per_group; ++parity)
        {
            for (uint8_t group = 0; group < groups; ++group)
            {
                const size_t parity_index = static_cast<size_t>(parity) * static_cast<size_t>(groups) + static_cast<size_t>(group);
                uint8_t *parity_payload = out_payloads[parity_index];
                if (!parity_payload)
                {
                    continue;
                }
                std::fill(parity_payload, parity_payload + symbol_bytes, 0);

                const uint8_t k_group = k_by_group[group];
                const auto *coef_ptr = coef_by_group[group];
                if (k_group == 0 || !coef_ptr)
                {
                    continue;
                }

                const uint8_t *coef_row = coef_ptr->data() + static_cast<size_t>(parity) * static_cast<size_t>(k_group);
                uint8_t local_index = 0;
                for (uint32_t source_index = group; source_index < total_fragments; source_index += groups)
                {
                    const size_t offset = static_cast<size_t>(source_index) * symbol_bytes;
                    const size_t chunk_size = offset < size ? std::min(symbol_bytes, size - offset) : 0;
                    if (chunk_size > 0)
                    {
                        gf256::mulAdd(coef_row[local_index], data + offset, parity_payload, chunk_size);
                    }
                    ++local_index;
                }
            }
        }
    }

    bool FecV2::loadTableFromJsonText(const std::string &text, V2FecTable &out) const
    {
        out.groups_by_n.fill(0);
        out.r_by_n.fill(0);
        size_t pos = 0;
        int parsed = 0;
        while (true)
        {
            const size_t n_key = text.find("\"n\"", pos);
            if (n_key == std::string::npos)
            {
                break;
            }
            pos = n_key + 3;

            int n = 0;
            if (!parseIntAfterColon(text, pos, n))
            {
                break;
            }
            const size_t group_key = text.find("\"groupCount\"", pos);
            if (group_key == std::string::npos)
            {
                break;
            }
            pos = group_key + 12;
            int group_count = 0;
            if (!parseIntAfterColon(text, pos, group_count))
            {
                break;
            }
            const size_t parity_key = text.find("\"parityCount\"", pos);
            if (parity_key == std::string::npos)
            {
                break;
            }
            pos = parity_key + 13;
            int parity_count = 0;
            if (!parseIntAfterColon(text, pos, parity_count))
            {
                break;
            }

            if (n >= 0 && n < 256)
            {
                out.groups_by_n[static_cast<size_t>(n)] = parity_count > 0 ? static_cast<uint8_t>(std::clamp(group_count, 0, 255)) : 0;
                out.r_by_n[static_cast<size_t>(n)] = parity_count > 0 ? static_cast<uint8_t>(std::clamp(parity_count, 0, 255)) : 0;
            }
            ++parsed;
        }
        if (parsed <= 0)
        {
            RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.udp.fec"), "FEC table JSON parsed 0 entries; disabling FEC table");
            return false;
        }
        return true;
    }

    bool FecV2::loadTableFromJsonFile(const std::string &path, V2FecTable &out) const
    {
        std::ifstream input(path);
        if (!input.is_open())
        {
            return false;
        }
        std::string text((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
        if (text.empty() || !loadTableFromJsonText(text, out))
        {
            return false;
        }
        out.source_path = path;
        return true;
    }

    bool FecV2::loadTableOnce(V2FecTable &out) const
    {
        std::vector<std::filesystem::path> candidates;
        for (const auto &filename : {"UDP_VIDEO_FEC_TABLE_V1.json", "UDP_VIDEO_FEC_TABLE_V1(1).json"})
        {
            candidates.emplace_back(std::filesystem::path("config") / filename);
            candidates.emplace_back(std::filesystem::path("teleop_robot_bridge") / "config" / filename);
            candidates.emplace_back(std::filesystem::path("src") / "teleop_robot_bridge" / "config" / filename);
            candidates.emplace_back(std::filesystem::path(__FILE__).parent_path().parent_path().parent_path() / "config" / filename);
        }

        for (const auto &candidate : candidates)
        {
            if (loadTableFromJsonFile(candidate.string(), out))
            {
                out.loaded = true;
                return true;
            }
        }
        out.loaded = false;
        return false;
    }

    const FecV2::V2FecTable &FecV2::table() const
    {
        static V2FecTable fec_table;
        static std::once_flag once;
        static std::atomic<bool> logged{false};
        std::call_once(once, [this]() { loadTableOnce(fec_table); });

        if (!logged.exchange(true))
        {
            const auto logger = rclcpp::get_logger("teleop_robot_bridge.udp.fec");
            if (fec_table.loaded)
            {
                RCLCPP_INFO(logger, "Loaded FEC table from %s", fec_table.source_path.c_str());
            }
            else
            {
                RCLCPP_WARN(logger, "Failed to load FEC table JSON; FEC will be disabled");
            }
        }
        return fec_table;
    }

} // namespace trb::udp
