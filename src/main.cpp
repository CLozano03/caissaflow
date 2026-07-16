#include "attacks.h"
// #include "movegen.h"
#include "position.h"
#include "types.h"
#include <iostream>

#include <bitset>

std::string START_FEN =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
std::string MID_FEN = "6k1/r3p1bp/p3R1p1/1p1B3n/3P3r/5P2/PPP4P/5RK1 w - - 1 24";

int main() {

  Attacks::init();

  Position init_pos;
  init_pos.set_pos(START_FEN);

  Position main_pos;
  main_pos.set_pos(MID_FEN);

  std::cout << init_pos << std::endl;
  std::cout << main_pos << std::endl;

  Move m = Move(Square::e2, Square::e4);
  Move m2 = Move::make<PROMOTION>(Square::e7, Square::e8, PieceType::QUEEN);

  std::cout << m << std::endl;
  std::cout << "Move Type: " << static_cast<int>(m.type_of()) << std::endl;
  std::cout << m2 << std::endl;
  std::cout << "Move Type: " << static_cast<int>(m2.type_of()) << std::endl;


  std::cout << "holaaaa" << std::endl;

  return 0;
}
