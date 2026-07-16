#include "position.h"
#include <cstring>
#include <iostream>
#include <sstream>

const char *square_to_coordinates[] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "a2", "b2", "c2",
    "d2", "e2", "f2", "g2", "h2", "a3", "b3", "c3", "d3", "e3", "f3",
    "g3", "h3", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a5",
    "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a6", "b6", "c6", "d6",
    "e6", "f6", "g6", "h6", "a7", "b7", "c7", "d7", "e7", "f7", "g7",
    "h7", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"};

const char ascii_pieces[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                               'p', 'n', 'b', 'r', 'q', 'k'};

void Position::reset() {
  st = &setupState;
  setupState = StateInfo();

  std::memset(bitboards, 0, sizeof(bitboards));
  std::memset(occupancies, 0, sizeof(occupancies));
}

void Position::update_occupancies() {
  std::memset(occupancies, 0, sizeof(occupancies));

  for (int piece = P; piece <= K; piece++) {
    occupancies[WHITE] |= bitboards[piece];
  }

  for (int piece = p; piece <= k; piece++) {
    occupancies[BLACK] |= bitboards[piece];
  }

  occupancies[BOTH] |= occupancies[WHITE];
  occupancies[BOTH] |= occupancies[BLACK];
}

void Position::set_pos(const std::string_view fen) {
  reset();
  std::istringstream ss(fen.data());

  size_t index = 0;
  int rank = 0; // FEN starts from rank 8.
  int file = 0;

  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {
      // Getting current character from FEN
      if (index >= fen.length())
        break;
      char token = fen[index];

      int square = rank * 8 + file;

      if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) {
        int piece = -1;
        // Map FEN character to piece index
        switch (token) {
        case 'P':
          piece = P;
          break;
        case 'N':
          piece = N;
          break;
        case 'B':
          piece = B;
          break;
        case 'R':
          piece = R;
          break;
        case 'Q':
          piece = Q;
          break;
        case 'K':
          piece = K;
          break;
        case 'p':
          piece = p;
          break;
        case 'n':
          piece = n;
          break;
        case 'b':
          piece = b;
          break;
        case 'r':
          piece = r;
          break;
        case 'q':
          piece = q;
          break;
        case 'k':
          piece = k;
          break;
        }
        if (piece != -1)
          set_bit(bitboards[piece], square);
        index++;
      } else if (token >= '1' && token <= '8') {
        int empty_squares = token - '0';
        file += (empty_squares - 1);
        index++;
      } else if (token == '/') {
        file = -1; // Reset file for new rank
        index++;
      } else {
        index++;
      }
    }
  }

  // Jump spaces
  while (index < fen.length() && fen[index] == ' ')
    index++;

  // Parse sideToMove to move
  if (index < fen.length()) {
    sideToMove = (fen[index] == 'w') ? WHITE : BLACK;
    index += 2;
  }

  // Parse castling rights
  while (index < fen.length() && fen[index] != ' ') {
    switch (fen[index]) {
    case 'K':
      st->castle_rights =
          static_cast<CastlingRights>(st->castle_rights | WHITE_OO);
      break;
    case 'Q':
      st->castle_rights =
          static_cast<CastlingRights>(st->castle_rights | WHITE_OOO);
      break;
    case 'k':
      st->castle_rights =
          static_cast<CastlingRights>(st->castle_rights | BLACK_OO);
      break;
    case 'q':
      st->castle_rights =
          static_cast<CastlingRights>(st->castle_rights | BLACK_OOO);
      break;
    case '-':
      break;
    }
    index++;
  }
  index++;

  // Parse en passant square
  if (index < fen.length() && fen[index] != '-') {
    int file_idx = fen[index] - 'a';
    int rank_idx = fen[index + 1] - '1';
    int sq_idx = rank_idx * 8 + file_idx;
    enpassant = static_cast<Square>(sq_idx);
    index += 2;
  } else {
    enpassant = no_sq;
    index++;
  }

  update_occupancies();
}

std::ostream &operator<<(std::ostream &os, const Position &pos) {
  os << "\n";
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      int square = (7 - rank) * 8 + file;
      if (!file)
        os << "  " << 8 - rank << "  ";

      int piece = -1;
      for (int bb_piece = P; bb_piece <= k; bb_piece++) {
        if (get_bit(pos.bitboards[bb_piece], square)) {
          piece = bb_piece;
          break;
        }
      }
      os << (piece != -1 ? ascii_pieces[piece] : '.') << " ";
    }
    os << "\n";
  }
  os << "     a b c d e f g h\n\n";

  os << "     sideToMove: " << (pos.sideToMove == WHITE ? "white" : "black")
     << "\n";
  os << "     Enpassant: "
     << (pos.enpassant != no_sq ? square_to_coordinates[pos.enpassant] : "no")
     << "\n";

  os << "     Castling: " << ((pos.castle_rights() & WHITE_OO) ? 'K' : '-');
  os << ((pos.castle_rights() & WHITE_OOO) ? 'Q' : '-')
     << ((pos.castle_rights() & BLACK_OO) ? 'k' : '-')
     << ((pos.castle_rights() & BLACK_OOO) ? 'q' : '-') << "\n\n";

  return os;
}
