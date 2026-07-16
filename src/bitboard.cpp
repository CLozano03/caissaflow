#include "bitboard.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const visual_bb &v) {
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

  os << " Bitboard: " << v.bb << "\n";

  return os;
}

void print_bitboard(Bitboard bitboard) {
  std::cout << visual_bb(bitboard) << "\n";
}
