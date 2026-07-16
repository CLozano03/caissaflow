#pragma once

#include "types.h"
#include <string>

// This constants help to prevent wrap-around when calculating piece attacks
// Don't think too much about their values, just trust that they work :)
constexpr Bitboard not_a_file = 0xfefefefefefefefeULL;
constexpr Bitboard not_h_file = 0x7f7f7f7f7f7f7f7fULL;
constexpr Bitboard not_ab_file = 0xfcfcfcfcfcfcfcfcULL;
constexpr Bitboard not_gh_file = 0x3f3f3f3f3f3f3f3fULL;

// Get bit is the same as checking if there is a piece on 'sq'. AND operation.
inline int get_bit(Bitboard bitboard, int sq) {
  return (bitboard & (1ULL << sq)) ? 1 : 0;
}

// Set bit is the same as putting a piece on 'sq'. OR operation.
inline void set_bit(Bitboard &bitboard, int sq) {
  (bitboard) |= (1ULL << (sq));
}

inline void pop_bit(Bitboard &bitboard, int sq) { bitboard &= ~(1ULL << sq); }

inline void pop_bit(Bitboard &bitboard) { bitboard &= (bitboard - 1); }

// Returns the least significant bit in a non-zero bitboard.
inline int lsb(uint64_t bb) {
  assert(bb);

#if defined(__GNUC__) || defined(__clang__)
  return __builtin_ctzll(bb);
#elif defined(_MSC_VER)
#ifdef _WIN64 // MSVC, WIN64

  unsigned long idx;
  _BitScanForward64(&idx, b);
  return Square(idx);

#else // MSVC, WIN32
  unsigned long idx;

  if (b & 0xffffffff) {
    _BitScanForward(&idx, int32_t(b));
    return Square(idx);
  } else {
    _BitScanForward(&idx, int32_t(b >> 32));
    return Square(idx + 32);
  }
#endif
#else
#error "Compiler not supported."
#endif
}

// Returns the most significant bit in a non-zero bitboard.
inline Square msb(Bitboard b) {
  assert(b);

#if defined(__GNUC__) // GCC, Clang, ICX

  return Square(63 ^ __builtin_clzll(b));

#elif defined(_MSC_VER)
#ifdef _WIN64 // MSVC, WIN64

  unsigned long idx;
  _BitScanReverse64(&idx, b);
  return Square(idx);

#else // MSVC, WIN32

  unsigned long idx;

  if (b >> 32) {
    _BitScanReverse(&idx, int32_t(b >> 32));
    return Square(idx + 32);
  } else {
    _BitScanReverse(&idx, int32_t(b));
    return Square(idx);
  }
#endif
#else // Compiler is neither GCC nor MSVC compatible
#error "Compiler not supported."
#endif
}

// Struct for visualizing bitboards in tests
struct visual_bb {
  Bitboard bb;
  visual_bb(Bitboard b) : bb(b) {}
};
// Overload << operator for easy printing of Visual struct
std::ostream &operator<<(std::ostream &os, const visual_bb &v);

void print_bitboard(Bitboard bitboard);
