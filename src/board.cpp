#include "board.h"
#include <cstring>
#include <iostream>

const char *square_to_coordinates[] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "a2", "b2", "c2",
    "d2", "e2", "f2", "g2", "h2", "a3", "b3", "c3", "d3", "e3", "f3",
    "g3", "h3", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a5",
    "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a6", "b6", "c6", "d6",
    "e6", "f6", "g6", "h6", "a7", "b7", "c7", "d7", "e7", "f7", "g7",
    "h7", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"};

const char ascii_pieces[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                               'p', 'n', 'b', 'r', 'q', 'k'};

Board::Board() { reset(); }

void Board::reset() {
  std::memset(bitboards, 0, sizeof(bitboards));
  std::memset(occupancies, 0, sizeof(occupancies));
  side = WHITE;
  enpassant = no_sq;
  castle = 0;
}

void Board::update_occupancies() {
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

void Board::parse_fen(const std::string_view fen) {
  reset();

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

  // Parse side to move
  if (index < fen.length()) {
    side = (fen[index] == 'w') ? WHITE : BLACK;
    index += 2;
  }

  // Parse castling rights
  while (index < fen.length() && fen[index] != ' ') {
    switch (fen[index]) {
    case 'K':
      castle |= WHITE_OO;
      break;
    case 'Q':
      castle |= WHITE_OOO;
      break;
    case 'k':
      castle |= BLACK_OO;
      break;
    case 'q':
      castle |= BLACK_OOO;
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
    enpassant = rank_idx * 8 + file_idx;
    index += 2;
  } else {
    enpassant = no_sq;
    index++;
  }

  update_occupancies();
}

void Board::print() {
  std::cout << "\n";
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      int square = (7 - rank) * 8 + file;
      if (!file)
        std::cout << "  " << 8 - rank << "  ";

      int piece = -1;
      for (int bb_piece = P; bb_piece <= k; bb_piece++) {
        if (get_bit(bitboards[bb_piece], square)) {
          piece = bb_piece;
          break;
        }
      }
      std::cout << (piece != -1 ? ascii_pieces[piece] : '.') << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n     a b c d e f g h\n\n";

  std::cout << "     Side:      " << (side == WHITE ? "white" : "black")
            << "\n";
  std::cout << "     Enpassant: "
            << (enpassant != no_sq ? square_to_coordinates[enpassant] : "no")
            << "\n";
  std::cout << "     Castling:  " << ((castle & WHITE_OO) ? 'K' : '-')
            << ((castle & WHITE_OOO) ? 'Q' : '-')
            << ((castle & BLACK_OO) ? 'k' : '-')
            << ((castle & BLACK_OOO) ? 'q' : '-') << "\n\n";
}
