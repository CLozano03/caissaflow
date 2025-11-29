#include "bitboard.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Visual &v) {
  os << "\n";
  for (int rank = 7; rank >= 0; rank--) {
    for (int file = 0; file < 8; file++) {
      int square = rank * 8 + file;

      if (!file)
        os << "  " << rank + 1 << "  ";

      if (get_bit(v.bb, square))
        os << " 1";
      else
        os << " 0";
    }
    os << "\n";
  }
  os << "\n      a b c d e f g h\n\n";
  return os;
}

void print_bitboard(Bitboard bitboard) {
  std::cout << Visual(bitboard) << "\n";
}

//
// void print_bitboard(Bitboard bitboard) {
//
//   std::cout << "\n";
//
//   for (int rank = 0; rank < 8; rank++) {
//     for (int file = 0; file < 8; file++) {
//
//       // Map: square = (7 - rank) * 8 + file
//       int sq = (7 - rank) * 8 + file;
//       Square square = static_cast<Square>(sq);
//
//       if (!file)
//         std::cout << "  " << 8 - rank << "  ";
//
//       std::cout << (get_bit(bitboard, square) ? 1 : 0) << " ";
//     }
//     std::cout << "\n";
//   }
//
//   std::cout << "\n     a b c d e f g h\n\n";
//   std::cout << " Bitboard: " << bitboard << "\n\n";
// }
