#pragma once

#include <cstddef>
#include <cstdint>

namespace trb::udp::gf256
{

// GF(256) arithmetic using primitive polynomial 0x11D.
// Addition is XOR; multiplication is table-based for speed.

uint8_t mul(uint8_t a, uint8_t b);

// Multiplicative inverse in GF(256). Returns 0 for input 0.
uint8_t inv(uint8_t a);

// a^e in GF(256). By convention: 0^0 = 1.
uint8_t pow(uint8_t a, uint16_t e);

// dst[i] ^= coef * src[i] in GF(256)
void mulAdd(uint8_t coef, const uint8_t *src, uint8_t *dst, size_t bytes);

} // namespace trb::udp::gf256
