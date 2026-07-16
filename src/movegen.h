#pragma once

#include "position.h"

// stage-based move generation
enum class GenType : uint8_t { ALL_MOVES, CAPTURES, QUIETS, CHECKS};

struct MoveList {
  Move moves[256];
  int count;

  void reset() { count = 0; }

  void add(Move m) { moves[count++] = m; }
  Move *begin() { return moves; }
  Move *end() { return moves + count; }
};

class MoveGen {
public:
  template <GenType Type>
  static void generate(const Position &pos, MoveList &list);

private:
  template <GenType Type>
  static void generate_pawn_moves(const Position &pos, MoveList &list,
                                  Color us);

  template <GenType Type>
  static void generate_castling_moves(const Position &pos, MoveList &list,
                                      Color us);

  // No pawn or castling moves
  template <GenType Type>
  static void generate_piece_moves(const Position &pos, MoveList &list,
                                   Color us);
};
