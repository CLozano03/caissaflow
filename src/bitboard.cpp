#include "bitboard.h"
#include <iostream>

void print_bitboard(Bitboard bitboard) {
  std::cout << "\n";

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {

      // Map: square = (7 - rank) * 8 + file
      int square = (7 - rank) * 8 + file;

      if (!file)
        std::cout << "  " << 8 - rank << "  ";

      std::cout << (get_bit(bitboard, square) ? 1 : 0) << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\n     a b c d e f g h\n\n";
  std::cout << " Bitboard: " << bitboard << "\n\n";
}
