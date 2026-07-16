#pragma once

#include "bitboard.h"
#include "types.h"
#include <string>

// Holds game state information
struct StateInfo {
  int enpassant = no_sq;
  CastlingRights castle_rights = NO_CASTLING;
  int rule50_counter;
  StateInfo *previous;
};

class Position {
public:
  static void init();
  Position() = default;
  Position(const Position &) = delete;
  Position &operator=(const Position &) = delete;

  // 12 Bitboards. 1 for each piece type
  Bitboard bitboards[12];

  // 3 Bitboards for occupancies (
  //  occupancies[0] = All white pieces
  //  occupancies[1] = All black pieces
  //  occupancies[2] = All pieces (White | Black)
  // )
  Bitboard occupancies[3];

  // Loads a FEN position (Forsyth-Edwards Notation)
  void set_pos(const std::string_view fen);

  friend std::ostream &operator<<(std::ostream &os, const Position &pos);

  Color side_to_move() const;
  bool is_square_attacked(Square square, Color side, const Position &pos);

  bool has_repeated() const;
  int rule50_count() const;
  CastlingRights castle_rights() const;
  Square en_passant_square() const { return enpassant; }

private:
  // Auxiliary method to reset the board state
  void reset();

  // Auxiliary method to update occupancies based on piece bitboards
  void update_occupancies();

  // Game state variables
  StateInfo *st;
  StateInfo setupState; // State by default when no pointer is given
  Color sideToMove;     // Current turn (WHITE o BLACK)
  Square enpassant;     // Square for en passant target
};

inline Color Position::side_to_move() const { return sideToMove; }
inline int Position::rule50_count() const { return st->rule50_counter; }
inline CastlingRights Position::castle_rights() const {
  return st->castle_rights;
}

// TODO: Implement repetition detection using a hash of the position and a
// history of previous positions. For now, we return false as a placeholder.
inline bool Position::has_repeated() const { return false; }

// Overload << operator for visual_board to print the board
std::ostream &operator<<(std::ostream &os, const Position &pos);
