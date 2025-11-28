#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"
#include "types.h"
#include <string>

class Board {
public:
  // 12 Bitboards. 1 for each piece type
  Bitboard bitboards[12];

  // 3 Bitboards for occupancies (
  //  occupancies[0] = All white pieces
  //  occupancies[1] = All black pieces
  //  occupancies[2] = All pieces (White | Black)
  // )
  Bitboard occupancies[3];

  // Game state variables
  int side;      // Current turn (WHITE o BLACK)
  int enpassant; // Square index for en passant target
  int castle;    // Bit mask for castling rights

  // Constructor. Initializes empty board
  Board();

  // Loads a FEN position (Forsyth-Edwards Notation)
  void parse_fen(const std::string_view fen);

  // Prints the board to console
  void print();

private:
  // Auxiliary method to reset the board state
  void reset();

  // Auxiliary method to update occupancies based on piece bitboards
  void update_occupancies();
};

#endif
