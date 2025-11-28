#ifndef ATTACKS_H
#define ATTACKS_H

#include "bitboard.h"

namespace Attacks {

extern Bitboard bishop_masks[64];
extern Bitboard rook_masks[64];
extern Bitboard bishop_attacks[64][512]; // 512 = 2^9
extern Bitboard rook_attacks[64][4096];  // 4096 = 2^12

// Magic numbers
extern const uint64_t bishop_magics[64];
extern const uint64_t rook_magics[64];
extern const int bishop_relevant_bits[64];
extern const int rook_relevant_bits[64];

// Magic attack retrieval
static inline Bitboard get_bishop_attacks(int square, Bitboard occupancy) {
  occupancy &= bishop_masks[square];
  occupancy *= bishop_magics[square];
  occupancy >>= (64 - bishop_relevant_bits[square]); // Shift to get the index
  return bishop_attacks[square][occupancy];
}

static inline Bitboard get_rook_attacks(int square, Bitboard occupancy) {
  occupancy &= rook_masks[square];
  occupancy *= rook_magics[square];
  occupancy >>= (64 - rook_relevant_bits[square]);
  return rook_attacks[square][occupancy];
}

// Leaper attacks (knight and king)
extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];

static inline Bitboard get_knight_attacks(int square) {
  return knight_attacks[square];
}

static inline Bitboard get_king_attacks(int square) {
  return king_attacks[square];
}

Bitboard mask_knight_attacks(int square);
Bitboard mask_king_attacks(int square);

Bitboard mask_bishop_attacks(int square);
Bitboard bishop_attacks_on_the_fly(int square, Bitboard block);
Bitboard mask_rook_attacks(int square);
Bitboard rook_attacks_on_the_fly(int square, Bitboard block);

void init();

} // namespace Attacks

#endif
