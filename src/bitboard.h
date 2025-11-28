#ifndef BITBOARD_H
#define BITBOARD_H

#include "types.h"

using Bitboard = uint64_t;

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

// Pop bit is the same as removing a piece from 'sq'. AND with NOT operation.
inline void pop_bit(Bitboard &bitboard, int sq) {
  (bitboard) &= ~(1ULL << (sq));
}

void print_bitboard(Bitboard bitboard);

#endif
