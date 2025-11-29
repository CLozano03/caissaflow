#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

// Bitboard is a 64-bit integer representing the chessboard
// Each bit corresponds to a square on the board and indicates presence of one
// unique type piece for that bitboard.
typedef uint64_t Bitboard;
using Bitboard = uint64_t;

enum Color : int8_t { WHITE, BLACK, COLOR_NB = 2 };
static constexpr int BOTH = COLOR_NB;

enum Piece { P, N, B, R, Q, K, p, n, b, r, q, k };

enum CastlingRights : int8_t {
  NO_CASTLING,
  WHITE_OO,
  WHITE_OOO = WHITE_OO << 1,
  BLACK_OO = WHITE_OO << 2,
  BLACK_OOO = WHITE_OO << 3,

  KING_SIDE = WHITE_OO | BLACK_OO,
  QUEEN_SIDE = WHITE_OOO | BLACK_OOO,
  WHITE_CASTLING = WHITE_OO | WHITE_OOO,
  BLACK_CASTLING = BLACK_OO | BLACK_OOO,
  ANY_CASTLING = WHITE_CASTLING | BLACK_CASTLING,

  CASTLING_RIGHT_NB = 16
};

// Enum for each square on the chessboard
enum Square : int8_t {
  a1,
  b1,
  c1,
  d1,
  e1,
  f1,
  g1,
  h1,
  a2,
  b2,
  c2,
  d2,
  e2,
  f2,
  g2,
  h2,
  a3,
  b3,
  c3,
  d3,
  e3,
  f3,
  g3,
  h3,
  a4,
  b4,
  c4,
  d4,
  e4,
  f4,
  g4,
  h4,
  a5,
  b5,
  c5,
  d5,
  e5,
  f5,
  g5,
  h5,
  a6,
  b6,
  c6,
  d6,
  e6,
  f6,
  g6,
  h6,
  a7,
  b7,
  c7,
  d7,
  e7,
  f7,
  g7,
  h7,
  a8,
  b8,
  c8,
  d8,
  e8,
  f8,
  g8,
  h8,
  no_sq,

  SQUARE_ZERO = 0,
  SQUARE_NB = 64
};

inline Square &operator++(Square &s) {
  s = static_cast<Square>(static_cast<int>(s) + 1);
  return s;
}

inline Square operator++(Square &s, int) {
  Square temp = s;
  ++s;
  return temp;
}

#endif
