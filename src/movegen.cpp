#include "movegen.h"
#include "attacks.h"
#include "bitboard.h"
#include "position.h"

// Precomputed ranks to quickly check for promotions
const Bitboard RANK_7 = 0x00FF000000000000ULL;
const Bitboard RANK_2 = 0x000000000000FF00ULL;

// Helper to add pawn moves efficiently (handles promotions vs normal moves)
template <GenType Type>
void add_pawn_move(Square from, Square to, MoveList &list) {
  // If capture logic needed for Quiescence, handle flags inside make

  // Check for promotion: White on Rank 8 (0-7 -> 56-63), Black on Rank 1 (0-7)
  // Note: 'to' is the target square.
  bool is_promo = (to >= a8 && to <= h8) || (to >= a1 && to <= h1);

  if (is_promo) {
    // Generate all 4 promotion types
    // If Type == GenType::CAPTURES, we usually still generate Q promotion
    list.add(Move::make<PROMOTION>(from, to, QUEEN));
    list.add(Move::make<PROMOTION>(from, to, ROOK));
    list.add(Move::make<PROMOTION>(from, to, BISHOP));
    list.add(Move::make<PROMOTION>(from, to, KNIGHT));
  } else {
    // Normal Move
    // If Type == GenType::CAPTURES, this function shouldn't be called for
    // non-capture pushes, but the caller handles that logic.
    list.add(Move::make<NORMAL>(from, to));
  }
}

// ============================================================================
// MAIN GENERATION
// ============================================================================

template <GenType Type>
void MoveGen::generate(const Position &pos, MoveList &list) {
  list.reset(); // Always reset the list first
  Color us = static_cast<Color>(pos.side_to_move());

  generate_pawn_moves<Type>(pos, list, us);

  generate_castling_moves<Type>(pos, list, us);

  // 3. Generate Moves for Pieces (N, B, R, Q, K)
  generate_piece_moves<Type>(pos, list, us);
}

// Instantiate templates so linker finds them
template void MoveGen::generate<GenType::ALL_MOVES>(const Position &pos, MoveList &);
template void MoveGen::generate<GenType::CAPTURES>(const Position &pos,
                                                   MoveList &);

// ============================================================================
// IMPLEMENTATION DETAILS
// ============================================================================

template <GenType Type>
void MoveGen::generate_piece_moves(const Position &pos, MoveList &list,
                                   Color us) {
  Color them = (us == WHITE) ? BLACK : WHITE;
  Bitboard enemy_pieces = pos.occupancies[them];
  Bitboard valid_targets =
      (Type == GenType::CAPTURES) ? enemy_pieces : ~pos.occupancies[us];

  // Piece definitions matching your enum Piece: P, N, B, R, Q, K ...
  // N=1, B=2, R=3, Q=4, K=5. (White)
  // n=7, b=8, r=9, q=10, k=11. (Black)
  int offset = (us == WHITE) ? 0 : 6;

  for (int p = N; p <= K; p++) {
    // Cast int to Piece enum for array access
    Piece piece_type = static_cast<Piece>(p + offset);
    Bitboard bb = pos.bitboards[piece_type];

    while (bb) {
      Square from = static_cast<Square>(lsb(bb));
      pop_bit(bb); // Use the fast pop_bit(bb) version

      Bitboard attacks = 0ULL;

      // Generate attacks using your existing attack functions
      // Assuming signatures in attacks.h match standard
      switch (p) {
      case N:
        attacks = Attacks::get_knight_attacks(from);
        break;
      case B:
        attacks = Attacks::get_bishop_attacks(from, pos.occupancies[BOTH]);
        break;
      case R:
        attacks = Attacks::get_rook_attacks(from, pos.occupancies[BOTH]);
        break;
      case Q:
        attacks = Attacks::get_bishop_attacks(from, pos.occupancies[BOTH]) |
                  Attacks::get_rook_attacks(from, pos.occupancies[BOTH]);
        break;
      case K:
        attacks = Attacks::get_king_attacks(from);
        break;
      }

      attacks &= valid_targets;

      while (attacks) {
        Square to = static_cast<Square>(lsb(attacks));
        pop_bit(attacks);

        // Note: We use Move::make<NORMAL> even for captures.
        // The 'MoveType' enum in standard engines usually handles 'CAPTURE'
        // flags internally or deduce them. But given your API:
        list.add(Move::make<NORMAL>(from, to));

        // OPTIONAL IMPROVEMENT:
        // If you want to flag captures explicitly in the Move integer,
        // you need a CAPTURE flag in MoveType and check 'get_bit(enemy_pieces,
        // to)'.
      }
    }
  }
}

template <GenType Type>
void MoveGen::generate_pawn_moves(const Position &pos, MoveList &list,
                                  Color us) {
  Color them = (us == WHITE) ? BLACK : WHITE;
  Bitboard enemy_pieces = pos.occupancies[them];

  // Pawn definitions
  Bitboard pawns = pos.bitboards[(us == WHITE) ? P : p];
  Square ep_square = static_cast<Square>(
      pos.en_passant_square()); // Ensure this is int/Square in Board

  // DIRECTION CONSTANTS
  // White moves UP (index decreases? No, usually A1=0, H8=63 -> Index
  // INCREASES) Wait, check Square enum: a1=0, h8=63. So White moves +8, Black
  // moves -8.
  int direction = (us == WHITE) ? 8 : -8;

  // --- PAWN PUSHES (Quiet) ---
  if (Type != GenType::CAPTURES) {
    Bitboard single_push = 0ULL;
    Bitboard double_push = 0ULL;

    if (us == WHITE) {
      // Shift North (+8) and check empty
      single_push = (pawns << 8) & ~pos.occupancies[BOTH];
      // Shift North again (+16) from Rank 3 (index 16-23) to Rank 4
      // Logic: (single_push on rank 3) << 8 AND empty
      double_push =
          ((single_push & 0x0000000000FF0000ULL) << 8) & ~pos.occupancies[BOTH];
    } else {
      // Shift South (-8) >> 8
      single_push = (pawns >> 8) & ~pos.occupancies[BOTH];
      double_push =
          ((single_push & 0x0000FF0000000000ULL) >> 8) & ~pos.occupancies[BOTH];
    }

    while (single_push) {
      Square to = static_cast<Square>(lsb(single_push));
      pop_bit(single_push);
      Square from = static_cast<Square>(to - direction);
      add_pawn_move<Type>(from, to, list);
    }

    while (double_push) {
      Square to = static_cast<Square>(lsb(double_push));
      pop_bit(double_push);
      Square from = static_cast<Square>(to - (direction * 2));
      // Double push is always NORMAL (no promo), but creates En Passant
      // opportunity (Handled in make_move, not here)
      list.add(Move::make<NORMAL>(from, to));
    }
  }

  // --- PAWN GenType::CAPTURES ---
  Bitboard attacks = 0ULL;

  // Iterate twice: Left capture and Right capture
  // Simplification: Iterate pawns and use lookup tables
  // BUT efficient way is bit shifting the whole board

  for (int side = 0; side < 2; side++) {
    // side 0 = Attack Left (White: +7, Black: -9)
    // side 1 = Attack Right (White: +9, Black: -7)
    // Note: Needs strict file checking to avoid wrapping A-file to H-file

    Bitboard capturers = 0ULL;

    if (us == WHITE) {
      if (side == 0)
        capturers = (pawns << 7) & 0x7F7F7F7F7F7F7F7FULL; // Not H file
      else
        capturers = (pawns << 9) & 0xFEFEFEFEFEFEFEFEULL; // Not A file
    } else {
      if (side == 0)
        capturers = (pawns >> 9) & 0x7F7F7F7F7F7F7F7FULL; // Not H file
      else
        capturers = (pawns >> 7) & 0xFEFEFEFEFEFEFEFEULL; // Not A file
    }

    // 1. Normal Captures
    Bitboard valid_captures = capturers & enemy_pieces;
    while (valid_captures) {
      Square to = static_cast<Square>(lsb(valid_captures));
      pop_bit(valid_captures);

      // Calculate 'from' square based on shift
      int shift_diff =
          (us == WHITE) ? (side == 0 ? 7 : 9) : (side == 0 ? -9 : -7);
      Square from = static_cast<Square>(to - shift_diff);

      add_pawn_move<Type>(from, to, list);
    }

    // 2. En Passant Captures
    if (ep_square != no_sq) {
      // Check if any of our computed attacks land on the En Passant square
      if ((capturers & (1ULL << ep_square))) {
        // Determine 'from'
        int shift_diff =
            (us == WHITE) ? (side == 0 ? 7 : 9) : (side == 0 ? -9 : -7);
        Square from = static_cast<Square>(ep_square - shift_diff);

        // Add Move
        list.add(Move::make<EN_PASSANT>(from, ep_square));
      }
    }
  }
}

template <GenType Type>
void MoveGen::generate_castling_moves(const Position &pos, MoveList &list,
                                      Color us) {

  if (!pos.castle_rights())
    return;
  // Castling logic requires checking:
  // 1. Rights (pos.castle)
  // 2. Path is empty
  // 3. Squares are not attacked (needs is_square_attacked helper)
  //
  int rights = pos.castle_rights();
  int my_rights = rights & (us == WHITE ? WHITE_CASTLING : BLACK_CASTLING);
  if (!my_rights)
    return;

  if (us == WHITE) {
    // Kingside (e1 -> g1)
    if (pos.castle_rights() & WHITE_OO) {
      if (!get_bit(pos.occupancies[BOTH], f1) &&
          !get_bit(pos.occupancies[BOTH], g1)) {

        // TODO: Ensure is_square_attacked is implemented in attacks.h
        if (!Attacks::is_square_attacked(e1, BLACK, pos) &&
            !Attacks::is_square_attacked(f1, BLACK, pos)) {
          list.add(Move::make<CASTLING>(e1, g1));
        }
        // Temporary for testing without attacks check:
        // list.add(Move::make<CASTLING>(e1, g1));
      }
    }
    // Queenside (e1 -> c1)
    if (pos.castle_rights() & WHITE_OOO) {
      if (!get_bit(pos.occupancies[BOTH], d1) &&
          !get_bit(pos.occupancies[BOTH], c1) &&
          !get_bit(pos.occupancies[BOTH], b1)) {

        if (!Attacks::is_square_attacked(e1, BLACK, pos) &&
            !Attacks::is_square_attacked(d1, BLACK, pos)) {
          list.add(Move::make<CASTLING>(e1, c1));
        }
        list.add(Move::make<CASTLING>(e1, c1));
      }
    }
  } else {
    // BLACK Logic (Mirror)
    // Kingside (e8 -> g8)
    if (pos.castle_rights() & BLACK_OO) {
      if (!get_bit(pos.occupancies[BOTH], f8) &&
          !get_bit(pos.occupancies[BOTH], g8)) {
        list.add(Move::make<CASTLING>(e8, g8));
      }
    }
    // Queenside (e8 -> c8)
    if (pos.castle_rights() & BLACK_OOO) {
      if (!get_bit(pos.occupancies[BOTH], d8) &&
          !get_bit(pos.occupancies[BOTH], c8) &&
          !get_bit(pos.occupancies[BOTH], b8)) {
        list.add(Move::make<CASTLING>(e8, c8));
      }
    }
  }
}
