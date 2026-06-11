#include "udp/gf256.hpp"

#include <array>

namespace trb::udp::gf256
{

    namespace
    {
        // Primitive polynomial: x^8 + x^4 + x^3 + x^2 + 1 (0x11D)
        constexpr uint16_t kPrimPoly = 0x11D;

        struct Tables
        {
            std::array<uint8_t, 256> log{}; // log[0] unused
            std::array<uint8_t, 512> exp{}; // exp extended for fast wrap
            std::array<std::array<uint8_t, 256>, 256> mul_lut{};
            bool ready{false};

            void init()
            {
                // Build exp/log tables with generator 0x02.
                // exp[i] = alpha^i, log[alpha^i] = i.
                uint16_t x = 1;
                for (int i = 0; i < 255; ++i)
                {
                    exp[i] = static_cast<uint8_t>(x);
                    log[static_cast<uint8_t>(x)] = static_cast<uint8_t>(i);

                    x <<= 1;
                    if (x & 0x100)
                    {
                        x ^= kPrimPoly;
                    }
                }

                // Duplicate exp table so we can index exp[logA+logB] without mod.
                for (int i = 255; i < 512; ++i)
                {
                    exp[i] = exp[i - 255];
                }

                for (int coef = 0; coef < 256; ++coef)
                {
                    for (int value = 0; value < 256; ++value)
                    {
                        if (coef == 0 || value == 0)
                        {
                            mul_lut[coef][value] = 0;
                            continue;
                        }
                        mul_lut[coef][value] = exp[static_cast<uint16_t>(log[coef]) + static_cast<uint16_t>(log[value])];
                    }
                }

                ready = true;
            }
        };

        inline Tables &tables()
        {
            static Tables t;
            if (!t.ready)
            {
                t.init();
            }
            return t;
        }

    } // namespace

    uint8_t mul(uint8_t a, uint8_t b)
    {
        auto &t = tables();
        return t.mul_lut[a][b];
    }

    uint8_t inv(uint8_t a)
    {
        if (a == 0)
            return 0;
        auto &t = tables();
        // a^{-1} = exp(255 - log(a)) in GF(256)
        const uint16_t la = t.log[a];
        return t.exp[255u - la];
    }

    uint8_t pow(uint8_t a, uint16_t e)
    {
        if (e == 0)
            return 1;
        if (a == 0)
            return 0;

        auto &t = tables();
        const uint16_t la = t.log[a];
        const uint32_t idx = (static_cast<uint32_t>(la) * static_cast<uint32_t>(e)) % 255u;
        return t.exp[idx];
    }

    void mulAdd(uint8_t coef, const uint8_t *src, uint8_t *dst, size_t bytes)
    {
        if (coef == 0 || bytes == 0)
            return;

        if (coef == 1)
        {
            for (size_t i = 0; i < bytes; ++i)
            {
                dst[i] ^= src[i];
            }
            return;
        }

        auto &t = tables();
        const auto &lut = t.mul_lut[coef];

        for (size_t i = 0; i < bytes; ++i)
        {
            dst[i] ^= lut[src[i]];
        }
    }

}
