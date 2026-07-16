#include "notation.h"

std::string move_to_algebraic(const Move &m, const Position &pos) {

  // Asumimos que Board tiene una forma de saber qué pieza está en una casilla
  // Por ejemplo: Board::get_piece_at(Square sq) -> Piece
  Piece piece = pos.get_piece_at(m.from_sq());
  char piece_char = pos.get_ascii_char(piece); // Q, R, N, etc.
  std::string notation = "";

  // 1. Manejar Enroques (Caso especial que no usa notación pieza-casilla)
  if (m.type_of() == CASTLING) {
    Square to = m.to_sq();
    if (to == g1 || to == g8)
      return "O-O";
    if (to == c1 || to == c8)
      return "O-O-O";
  }

  // 2. Añadir la Pieza (Excepto Peones, 'P' no se pone)
  if (piece != P && piece != p) {
    notation += piece_char;
  }

  // 3. Manejar Capturas
  // Necesitas una función para ver si 'to' tiene una pieza enemiga
  // bool is_capture = b.is_capture(m);
  if (is_capture) {
    // En peones, si capturan, se pone la columna de origen (ej: exd5)
    if (piece == P || piece == p) {
      notation += ('a' + (m.from_sq() & 7)); // Añade la columna de origen
    }
    notation += 'x';
  }

  // 4. Añadir la Casilla de Destino
  char f_dst = 'a' + (m.to_sq() & 7);
  char r_dst = '1' + (m.to_sq() >> 3);
  notation += f_dst;
  notation += r_dst;

  // 5. Manejar Promociones
  if (m.type_of() >= PROMO_N) { // Usando tus enums
    notation += '=';
    // Aquí necesitas mapear el flag de promoción a su carácter (Q, R, B, N)
    // Por ejemplo: notation += b.get_promo_char(m.type_of());
  }

  // 6. Ambiguiedad, Jaque/Mate (Lógica avanzada, se omite por ahora)

  return notation;
}
