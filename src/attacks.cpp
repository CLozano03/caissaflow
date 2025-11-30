#include "attacks.h"
#include "magic_data.h"

namespace Attacks {

// Arrays for storing precomputed attacks
Bitboard pawn_attacks[2][64];
Bitboard knight_attacks[64];
Bitboard king_attacks[64];

Bitboard bishop_masks[64];
Bitboard rook_masks[64];
Bitboard bishop_attacks[64][512];
Bitboard rook_attacks[64][4096];

const int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7,
    5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7,
    7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

const int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

Bitboard mask_pawn_attacks(Color side, Square square) {
  Bitboard b = 1ULL << square;

  Bitboard white_attacks = ((b << 7) & not_h_file) | ((b << 9) & not_a_file);
  Bitboard black_attacks = ((b >> 7) & not_a_file) | ((b >> 9) & not_h_file);

  return (white_attacks & -(side == WHITE)) |
         (black_attacks & -(side == BLACK));
}

Bitboard mask_knight_attacks(Square square) {
  Bitboard attacks = 0ULL;
  Bitboard bitboard = 0ULL;
  set_bit(bitboard, square);

  // NNE (+17)
  if ((bitboard << 17) & not_a_file)
    attacks |= (bitboard << 17);
  // SSE (-15)
  if ((bitboard >> 15) & not_a_file)
    attacks |= (bitboard >> 15);
  // NNW (+15)
  if ((bitboard << 15) & not_h_file)
    attacks |= (bitboard << 15);
  // SSW (-17)
  if ((bitboard >> 17) & not_h_file)
    attacks |= (bitboard >> 17);
  // NEE (+10)
  if ((bitboard << 10) & not_ab_file)
    attacks |= (bitboard << 10);
  // SWW (-10)
  if ((bitboard >> 10) & not_gh_file)
    attacks |= (bitboard >> 10);
  // NWW (+6)
  if ((bitboard << 6) & not_gh_file)
    attacks |= (bitboard << 6);
  // SEE (-6)
  if ((bitboard >> 6) & not_ab_file)
    attacks |= (bitboard >> 6);

  return attacks;
}

Bitboard mask_king_attacks(Square square) {
  Bitboard attacks = 0ULL;
  Bitboard bitboard = 0ULL;
  set_bit(bitboard, square);

  if (bitboard >> 1 & not_h_file)
    attacks |= (bitboard >> 1);
  if (bitboard >> 9 & not_h_file)
    attacks |= (bitboard >> 9);
  if (bitboard << 7 & not_h_file)
    attacks |= (bitboard << 7);

  if (bitboard << 1 & not_a_file)
    attacks |= (bitboard << 1);
  if (bitboard << 9 & not_a_file)
    attacks |= (bitboard << 9);
  if (bitboard >> 7 & not_a_file)
    attacks |= (bitboard >> 7);

  if (bitboard >> 8)
    attacks |= (bitboard >> 8);
  if (bitboard << 8)
    attacks |= (bitboard << 8);

  return attacks;
}

Bitboard mask_bishop_attacks(Square square) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8; // target rank
  int tf = square % 8; // target file

  for (r = tr + 1, f = tf + 1; r < 7 && f < 7; r++, f++)
    set_bit(attacks, r * 8 + f);
  for (r = tr - 1, f = tf + 1; r > 0 && f < 7; r--, f++)
    set_bit(attacks, r * 8 + f);
  for (r = tr + 1, f = tf - 1; r < 7 && f > 0; r++, f--)
    set_bit(attacks, r * 8 + f);
  for (r = tr - 1, f = tf - 1; r > 0 && f > 0; r--, f--)
    set_bit(attacks, r * 8 + f);

  return attacks;
}

Bitboard bishop_attacks_on_the_fly(Square square, Bitboard block) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;

  for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  return attacks;
}

Bitboard mask_rook_attacks(Square square) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;

  // File and rank attacks, stopping before edges
  for (r = tr + 1; r < 7; r++)
    set_bit(attacks, r * 8 + tf);
  for (r = tr - 1; r > 0; r--)
    set_bit(attacks, r * 8 + tf);
  for (f = tf + 1; f < 7; f++)
    set_bit(attacks, tr * 8 + f);
  for (f = tf - 1; f > 0; f--)
    set_bit(attacks, tr * 8 + f);

  return attacks;
}

Bitboard rook_attacks_on_the_fly(Square square, Bitboard block) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;

  for (r = tr + 1; r <= 7; r++) {
    set_bit(attacks, r * 8 + tf);
    if (get_bit(block, r * 8 + tf))
      break;
  }
  for (r = tr - 1; r >= 0; r--) {
    set_bit(attacks, r * 8 + tf);
    if (get_bit(block, r * 8 + tf))
      break;
  }
  for (f = tf + 1; f <= 7; f++) {
    set_bit(attacks, tr * 8 + f);
    if (get_bit(block, tr * 8 + f))
      break;
  }
  for (f = tf - 1; f >= 0; f--) {
    set_bit(attacks, tr * 8 + f);
    if (get_bit(block, tr * 8 + f))
      break;
  }
  return attacks;
}

Bitboard set_occupancy(int index, int bits_in_mask, Bitboard attack_mask) {
  Bitboard occupancy = 0ULL;
  for (int count = 0; count < bits_in_mask; count++) {
    Square square = static_cast<Square>(
        __builtin_ctzll(attack_mask)); // Count trailing zeros

    pop_bit(attack_mask, square);

    if (index & (1 << count)) {
      set_bit(occupancy, square);
    }
  }
  return occupancy;
}

void init() {

  // Pawn attacks
  for (Square square = SQUARE_ZERO; square < SQUARE_NB; ++square) {
    pawn_attacks[WHITE][square] = mask_pawn_attacks(WHITE, square);
    pawn_attacks[BLACK][square] = mask_pawn_attacks(BLACK, square);
  }

  // Leaper jumps
  for (Square square = SQUARE_ZERO; square < SQUARE_NB; ++square) {
    knight_attacks[square] = mask_knight_attacks(square);
    king_attacks[square] = mask_king_attacks(square);
  }

  for (Square square = SQUARE_ZERO; square < SQUARE_NB; ++square) {
    bishop_masks[square] = mask_bishop_attacks(square);
    rook_masks[square] = mask_rook_attacks(square);

    // Initialize bishop attack tables
    int bishop_bits = bishop_relevant_bits[square];
    int bishop_occupancy_indices = (1 << bishop_bits); // 2^bits

    for (int index = 0; index < bishop_occupancy_indices; index++) {
      Bitboard occupancy =
          set_occupancy(index, bishop_bits, bishop_masks[square]);

      int magic_index =
          (occupancy * bishop_magics[square]) >> (64 - bishop_bits);

      bishop_attacks[square][magic_index] =
          bishop_attacks_on_the_fly(square, occupancy);
    }

    // Initialize rook attack tables
    int rook_bits = rook_relevant_bits[square];
    int rook_occupancy_indices = (1 << rook_bits);

    for (int index = 0; index < rook_occupancy_indices; index++) {
      Bitboard occupancy = set_occupancy(index, rook_bits, rook_masks[square]);
      int magic_index = (occupancy * rook_magics[square]) >> (64 - rook_bits);
      rook_attacks[square][magic_index] =
          rook_attacks_on_the_fly(square, occupancy);
    }
  }
}
} // namespace Attacks
