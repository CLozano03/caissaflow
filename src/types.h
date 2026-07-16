#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

// Bitboard is a 64-bit integer representing the chessboard
// Each bit corresponds to a square on the board and indicates presence of one
// unique type piece for that bitboard.
using Bitboard = uint64_t;
using Key = uint64_t;

// A simple linear congruential generator for pseudo-random keys, used for
// Zobrist hashing
constexpr Key zhash(uint64_t seed) {
  return seed * 6364136223846793005ULL + 1442695040888963407ULL;
}

enum Color : std::int8_t { WHITE, BLACK, COLOR_NB = 2 };
static constexpr int BOTH = COLOR_NB;

enum Piece { P, N, B, R, Q, K, p, n, b, r, q, k };
enum PieceType : std::int8_t {
  NO_PIECE,
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING,
  PIECE_TYPE_NB
};

enum CastlingRights : std::int8_t {
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

enum MoveType : uint8_t { NORMAL = 0, PROMOTION, EN_PASSANT, CASTLING };

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

// A move needs 16 bits to be stored:
// bit  0- 5: destination square (from 0 to 63)
// bit  6-11: origin square (from 0 to 63)
// bit 12-13: promotion piece type - 2 (from KNIGHT-2 to QUEEN-2)
// bit 14-15: special move flag: promotion (1), en passant (2), castling (3)
// NOTE: en passant bit is set only when a pawn can be captured
class Move {
public:
  Move() = default;
  constexpr explicit Move(uint16_t d) : data(d) {}

  // Constructor for normal moves (no promotion, no special flags)
  constexpr Move(Square from, Square to) : data((from << 6) + to) {}

  template <MoveType T>
  static constexpr Move make(Square from, Square to, PieceType pt = KNIGHT) {
    return Move((T << 14) + ((pt - KNIGHT) << 12) + (from << 6) + to);
  }

  constexpr bool is_ok() const {
    return none().data != data && null().data != data;
  }
  static constexpr Move null() { return Move(65); }
  static constexpr Move none() { return Move(0); }

  // Getters
  constexpr Square from_sq() const {
    // assert(is_ok());
    return Square((data >> 6) & 0x3F);
  }
  constexpr Square to_sq() const {
    // assert(is_ok());
    return Square(data & 0x3F);
  }
  constexpr MoveType type_of() const {
    return static_cast<MoveType>((data >> 14) & 0xF);
  }
  constexpr PieceType promo_piece() const {
    assert(type_of() == PROMOTION);
    return static_cast<PieceType>(((data >> 12) & 0x3) + KNIGHT);
  }

  bool operator==(const Move &other) const { return data == other.data; }
  bool operator!=(const Move &other) const { return data != other.data; }
  constexpr explicit operator bool() const { return data != 0; }

  inline std::uint16_t raw() const { return data; }

  struct MoveHash {
    std::size_t operator()(const Move &m) const { return zhash(m.data); }
  };

protected:
  std::uint16_t data;
};


// Printing a move in algebraic notation (e.g., e2e4, e7e8q for promotion)
inline std::ostream &operator<<(std::ostream &os, const Move &m) {
  Square from = m.from_sq();
  Square to = m.to_sq();

  auto to_coords = [](Square sq) mutable -> std::string {
    char file = 'a' + (sq % 8);
    char rank = '1' + (sq / 8);
    return {file, rank};
  };

  os << to_coords(from) << to_coords(to);

  if (!(m.type_of() == PROMOTION)) {
    return os;
  }

  PieceType promo = m.promo_piece();
  std::string promo_str = (promo == KNIGHT)   ? "n"
                          : (promo == BISHOP) ? "b"
                          : (promo == ROOK)   ? "r"
                          : (promo == QUEEN)  ? "q"
                                              : "?";
  return os << promo_str;
}
