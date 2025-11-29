/*
 * This program generates magic numbers for bishop and rook move generation
 * using bitboards in chess programming. It uses brute-force search to find
 * suitable magic numbers that map occupancy bitboards to attack bitboards
 * without collisions.
 * It outputs the generated magic numbers in a C++ header format.
 */
#include <cstdint>
#include <iostream>

typedef uint64_t Bitboard;

Bitboard get_bit(Bitboard bitboard, int square) {
  return (bitboard & (1ULL << square));
}
void set_bit(Bitboard &bitboard, int square) { bitboard |= (1ULL << square); }
void pop_bit(Bitboard &bitboard, int square) {
  if (get_bit(bitboard, square))
    bitboard ^= (1ULL << square);
}

// Generador de números aleatorios (XORShift)
unsigned int state = 1804289383;
unsigned int get_random_U32_number() {
  unsigned int number = state;
  number ^= number << 13;
  number ^= number >> 17;
  number ^= number << 5;
  state = number;
  return number;
}
uint64_t get_random_U64_number() {
  uint64_t n1 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
  uint64_t n2 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
  uint64_t n3 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
  uint64_t n4 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
  return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}
uint64_t generate_magic_candidate() {
  return get_random_U64_number() & get_random_U64_number() &
         get_random_U64_number();
}

int bishop_relevant_bits[64] = {6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5,
                                5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5,
                                5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5,
                                5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

Bitboard mask_bishop_attacks(int square) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;
  for (r = tr + 1, f = tf + 1; r < 7 && f < 7; r++, f++)
    set_bit(attacks, r * 8 + f);
  for (r = tr - 1, f = tf + 1; r > 0 && f < 7; r--, f++)
    set_bit(attacks, r * 8 + f);
  for (r = tr + 1, f = tf - 1; r < 7 && f > 0; r++, f--)
    set_bit(attacks, r * 8 + f);
  for (r = tr - 1, f = tf - 1; r > 0 && f > 0; r--, f--)
    set_bit(attacks, r * 8 + f);
  return attacks;
}

Bitboard mask_rook_attacks(int square) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;
  for (r = tr + 1; r < 7; r++)
    set_bit(attacks, r * 8 + tf);
  for (r = tr - 1; r > 0; r--)
    set_bit(attacks, r * 8 + tf);
  for (f = tf + 1; f < 7; f++)
    set_bit(attacks, tr * 8 + f);
  for (f = tf - 1; f > 0; f--)
    set_bit(attacks, tr * 8 + f);
  return attacks;
}

Bitboard bishop_attacks_on_the_fly(int square, Bitboard block) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;
  for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
    set_bit(attacks, r * 8 + f);
    if (get_bit(block, r * 8 + f))
      break;
  }
  return attacks;
}

Bitboard rook_attacks_on_the_fly(int square, Bitboard block) {
  Bitboard attacks = 0ULL;
  int r, f;
  int tr = square / 8;
  int tf = square % 8;
  for (r = tr + 1; r <= 7; r++) {
    set_bit(attacks, r * 8 + tf);
    if (get_bit(block, r * 8 + tf))
      break;
  }
  for (r = tr - 1; r >= 0; r--) {
    set_bit(attacks, r * 8 + tf);
    if (get_bit(block, r * 8 + tf))
      break;
  }
  for (f = tf + 1; f <= 7; f++) {
    set_bit(attacks, tr * 8 + f);
    if (get_bit(block, tr * 8 + f))
      break;
  }
  for (f = tf - 1; f >= 0; f--) {
    set_bit(attacks, tr * 8 + f);
    if (get_bit(block, tr * 8 + f))
      break;
  }
  return attacks;
}

Bitboard set_occupancy(int index, int bits_in_mask, Bitboard attack_mask) {
  Bitboard occupancy = 0ULL;
  for (int count = 0; count < bits_in_mask; count++) {
    int square = __builtin_ctzll(attack_mask);
    pop_bit(attack_mask, square);
    if (index & (1 << count))
      set_bit(occupancy, square);
  }
  return occupancy;
}

uint64_t find_magic_number(int square, int relevant_bits, int is_bishop) {
  Bitboard occupancies[4096];
  Bitboard attacks[4096];
  Bitboard used_attacks[4096];

  Bitboard attack_mask =
      is_bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);
  int occupancy_indices = 1 << relevant_bits;

  for (int index = 0; index < occupancy_indices; index++) {
    occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);
    if (is_bishop)
      attacks[index] = bishop_attacks_on_the_fly(square, occupancies[index]);
    else
      attacks[index] = rook_attacks_on_the_fly(square, occupancies[index]);
  }

  for (int k = 0; k < 100000000; k++) {
    uint64_t magic_candidate = generate_magic_candidate();
    if (__builtin_popcountll((attack_mask * magic_candidate) &
                             0xFF00000000000000ULL) < 6)
      continue;

    for (int i = 0; i < 4096; i++)
      used_attacks[i] = 0ULL;

    bool fail = false;
    for (int index = 0; index < occupancy_indices && !fail; index++) {
      int magic_index =
          (int)((occupancies[index] * magic_candidate) >> (64 - relevant_bits));
      if (used_attacks[magic_index] == 0ULL)
        used_attacks[magic_index] = attacks[index];
      else if (used_attacks[magic_index] != attacks[index])
        fail = true;
    }
    if (!fail)
      return magic_candidate;
  }
  std::cerr << "Magic failed for square " << square << "\n";
  return 0ULL;
}

void print_array(const std::string &name, const uint64_t *data, int size) {
  std::cout << "const uint64_t " << name << "[" << std::dec << size
            << "] = {\n";
  for (int i = 0; i < size; i++) {
    std::cout << "  0x" << std::hex << std::uppercase << data[i] << "ULL";
    if (i < size - 1)
      std::cout << ",";
    if ((i + 1) % 4 == 0)
      std::cout << "\n";
  }
  std::cout << "};\n\n";
}

int main() {
  uint64_t calculated_bishop_magics[64];
  uint64_t calculated_rook_magics[64];

  std::cerr << "--- Generating magic numbers... --\n";

  for (int sq = 0; sq < 64; sq++) {
    calculated_bishop_magics[sq] =
        find_magic_number(sq, bishop_relevant_bits[sq], 1);
    calculated_rook_magics[sq] =
        find_magic_number(sq, rook_relevant_bits[sq], 0);
    if (sq % 8 == 0)
      std::cerr << ".";
  }

  // Imprimir el header completo
  std::cout << "// File generated by magic_generator.cpp\n";
  std::cout << "// Do not edit manually!\n\n";
  std::cout << "#ifndef MAGICS_GENERATED_H\n";
  std::cout << "#define MAGICS_GENERATED_H\n\n";
  std::cout << "#include <cstdint>\n\n";
  std::cout << "namespace Attacks {\n\n";

  print_array("bishop_magics", calculated_bishop_magics, 64);
  print_array("rook_magics", calculated_rook_magics, 64);

  std::cout << "} // namespace Attacks \n";
  std::cout << "#endif\n";

  return 0;
}
