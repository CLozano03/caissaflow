#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

// Bitboard is a 64-bit integer representing the chessboard
// Each bit corresponds to a square on the board and indicates presence of one
// unique type piece for that bitboard.
typedef uint64_t Bitboard;

enum Color { WHITE, BLACK, BOTH };
enum Piece { P, N, B, R, Q, K, p, n, b, r, q, k };
enum CastlingRights { WK = 1, WQ = 2, BK = 4, BQ = 8 };

// Enum for each square on the chessboard
enum Square : int {
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
  no_sq
};

#endif
