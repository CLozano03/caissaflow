#include "attacks.h"
#include <gtest/gtest.h>

class KnightAttackTest : public ::testing::Test {
protected:
};

TEST_F(KnightAttackTest, CornerSquare_h1) {
  Bitboard expected = 0ULL;
  set_bit(expected, f2);
  set_bit(expected, g3);
  Bitboard result = Attacks::mask_knight_attacks(h1);
  EXPECT_EQ(result, expected) << "Knight on h1 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, CornerSquare_a8) {
  Bitboard expected = 0ULL;
  set_bit(expected, b6);
  set_bit(expected, c7);
  Bitboard result = Attacks::mask_knight_attacks(a8);
  EXPECT_EQ(result, expected) << "Knight on a8 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, CornerSquare_h8) {
  Bitboard expected = 0ULL;
  set_bit(expected, f7);
  set_bit(expected, g6);
  Bitboard result = Attacks::mask_knight_attacks(h8);
  EXPECT_EQ(result, expected) << "Knight on h8 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_b1) {
  Bitboard expected = 0ULL;
  set_bit(expected, a3);
  set_bit(expected, c3);
  set_bit(expected, d2);
  Bitboard result = Attacks::mask_knight_attacks(b1);
  EXPECT_EQ(result, expected) << "Knight on b1 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_g1) {
  Bitboard expected = 0ULL;
  set_bit(expected, e2);
  set_bit(expected, f3);
  set_bit(expected, h3);
  Bitboard result = Attacks::mask_knight_attacks(g1);
  EXPECT_EQ(result, expected) << "Knight on g1 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_b8) {
  Bitboard expected = 0ULL;
  set_bit(expected, a6);
  set_bit(expected, c6);
  set_bit(expected, d7);
  Bitboard result = Attacks::mask_knight_attacks(b8);
  EXPECT_EQ(result, expected) << "Knight on b8 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_g8) {
  Bitboard expected = 0ULL;
  set_bit(expected, e7);
  set_bit(expected, f6);
  set_bit(expected, h6);
  Bitboard result = Attacks::mask_knight_attacks(g8);
  EXPECT_EQ(result, expected) << "Knight on g8 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_a2) {
  Bitboard expected = 0ULL;
  set_bit(expected, b4);
  set_bit(expected, c3);
  set_bit(expected, c1);
  Bitboard result = Attacks::mask_knight_attacks(a2);
  EXPECT_EQ(result, expected) << "Knight on a2 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_h2) {
  Bitboard expected = 0ULL;
  set_bit(expected, f1);
  set_bit(expected, f3);
  set_bit(expected, g4);
  Bitboard result = Attacks::mask_knight_attacks(h2);
  EXPECT_EQ(result, expected) << "Knight on h2 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_a7) {
  Bitboard expected = 0ULL;
  set_bit(expected, b5);
  set_bit(expected, c6);
  set_bit(expected, c8);
  Bitboard result = Attacks::mask_knight_attacks(a7);
  EXPECT_EQ(result, expected) << "Knight on a7 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_h7) {
  Bitboard expected = 0ULL;
  set_bit(expected, f8);
  set_bit(expected, f6);
  set_bit(expected, g5);
  Bitboard result = Attacks::mask_knight_attacks(h7);
  EXPECT_EQ(result, expected) << "Knight on h7 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_c1) {
  Bitboard expected = 0ULL;
  set_bit(expected, a2);
  set_bit(expected, b3);
  set_bit(expected, d3);
  set_bit(expected, e2);
  Bitboard result = Attacks::mask_knight_attacks(c1);
  EXPECT_EQ(result, expected) << "Knight on c1 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_f1) {
  Bitboard expected = 0ULL;
  set_bit(expected, d2);
  set_bit(expected, e3);
  set_bit(expected, g3);
  set_bit(expected, h2);
  Bitboard result = Attacks::mask_knight_attacks(f1);
  EXPECT_EQ(result, expected) << "Knight on f1 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_c8) {
  Bitboard expected = 0ULL;
  set_bit(expected, a7);
  set_bit(expected, b6);
  set_bit(expected, d6);
  set_bit(expected, e7);
  Bitboard result = Attacks::mask_knight_attacks(c8);
  EXPECT_EQ(result, expected) << "Knight on c8 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_f8) {
  Bitboard expected = 0ULL;
  set_bit(expected, d7);
  set_bit(expected, e6);
  set_bit(expected, g6);
  set_bit(expected, h7);
  Bitboard result = Attacks::mask_knight_attacks(f8);
  EXPECT_EQ(result, expected) << "Knight on f8 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_a3) {
  Bitboard expected = 0ULL;
  set_bit(expected, b1);
  set_bit(expected, c2);
  set_bit(expected, c4);
  set_bit(expected, b5);
  Bitboard result = Attacks::mask_knight_attacks(a3);
  EXPECT_EQ(result, expected) << "Knight on a3 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_a6) {
  Bitboard expected = 0ULL;
  set_bit(expected, b4);
  set_bit(expected, c5);
  set_bit(expected, c7);
  set_bit(expected, b8);
  Bitboard result = Attacks::mask_knight_attacks(a6);
  EXPECT_EQ(result, expected) << "Knight on a6 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_h3) {
  Bitboard expected = 0ULL;
  set_bit(expected, f2);
  set_bit(expected, g1);
  set_bit(expected, g5);
  set_bit(expected, f4);
  Bitboard result = Attacks::mask_knight_attacks(h3);
  EXPECT_EQ(result, expected) << "Knight on h3 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, EdgeSquare_h6) {
  Bitboard expected = 0ULL;
  set_bit(expected, g4);
  set_bit(expected, f5);
  set_bit(expected, f7);
  set_bit(expected, g8);
  Bitboard result = Attacks::mask_knight_attacks(h6);
  EXPECT_EQ(result, expected) << "Knight on h6 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, InnerRing_b2) {
  Bitboard expected = 0ULL;
  set_bit(expected, d1);
  set_bit(expected, d3);
  set_bit(expected, c4);
  set_bit(expected, a4);
  Bitboard result = Attacks::mask_knight_attacks(b2);
  EXPECT_EQ(result, expected) << "Knight on b2 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, InnerRing_g2) {
  Bitboard expected = 0ULL;
  set_bit(expected, e1);
  set_bit(expected, e3);
  set_bit(expected, f4);
  set_bit(expected, h4);
  Bitboard result = Attacks::mask_knight_attacks(g2);
  EXPECT_EQ(result, expected) << "Knight on g2 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, InnerRing_b7) {
  Bitboard expected = 0ULL;
  set_bit(expected, a5);
  set_bit(expected, c5);
  set_bit(expected, d6);
  set_bit(expected, d8);
  Bitboard result = Attacks::mask_knight_attacks(b7);
  EXPECT_EQ(result, expected) << "Knight on b7 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, InnerRing_g7) {
  Bitboard expected = 0ULL;
  set_bit(expected, h5);
  set_bit(expected, f5);
  set_bit(expected, e6);
  set_bit(expected, e8);
  Bitboard result = Attacks::mask_knight_attacks(g7);
  EXPECT_EQ(result, expected) << "Knight on g7 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, CenterSquare_d4) {
  Bitboard expected = 0ULL;
  set_bit(expected, b3);
  set_bit(expected, b5);
  set_bit(expected, c2);
  set_bit(expected, c6);
  set_bit(expected, e2);
  set_bit(expected, e6);
  set_bit(expected, f3);
  set_bit(expected, f5);
  Bitboard result = Attacks::mask_knight_attacks(d4);
  EXPECT_EQ(result, expected) << "Knight on d4 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, CenterSquare_e5) {
  Bitboard expected = 0ULL;
  set_bit(expected, c4);
  set_bit(expected, c6);
  set_bit(expected, d3);
  set_bit(expected, d7);
  set_bit(expected, f3);
  set_bit(expected, f7);
  set_bit(expected, g4);
  set_bit(expected, g6);
  Bitboard result = Attacks::mask_knight_attacks(e5);
  EXPECT_EQ(result, expected) << "Knight on e5 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, MidSquare_c3) {
  Bitboard expected = 0ULL;
  set_bit(expected, b1);
  set_bit(expected, a2);
  set_bit(expected, a4);
  set_bit(expected, b5);
  set_bit(expected, d5);
  set_bit(expected, e4);
  set_bit(expected, e2);
  set_bit(expected, d1);
  Bitboard result = Attacks::mask_knight_attacks(c3);
  EXPECT_EQ(result, expected) << "Knight on c3 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, MidSquare_f3) {
  Bitboard expected = 0ULL;
  set_bit(expected, h4);
  set_bit(expected, g5);
  set_bit(expected, e5);
  set_bit(expected, d4);
  set_bit(expected, d2);
  set_bit(expected, e1);
  set_bit(expected, g1);
  set_bit(expected, h2);
  Bitboard result = Attacks::mask_knight_attacks(f3);
  EXPECT_EQ(result, expected) << "Knight on f3 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, MidSquare_c6) {
  Bitboard expected = 0ULL;
  set_bit(expected, a7);
  set_bit(expected, b8);
  set_bit(expected, d8);
  set_bit(expected, e7);
  set_bit(expected, e5);
  set_bit(expected, d4);
  set_bit(expected, b4);
  set_bit(expected, a5);
  Bitboard result = Attacks::mask_knight_attacks(c6);
  EXPECT_EQ(result, expected) << "Knight on c6 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, MidSquare_f6) {
  Bitboard expected = 0ULL;
  set_bit(expected, d7);
  set_bit(expected, e8);
  set_bit(expected, g8);
  set_bit(expected, h7);
  set_bit(expected, h5);
  set_bit(expected, g4);
  set_bit(expected, e4);
  set_bit(expected, d5);
  Bitboard result = Attacks::mask_knight_attacks(f6);
  EXPECT_EQ(result, expected) << "Knight on f6 error:\n" << Visual(result);
}

TEST_F(KnightAttackTest, CenterSquare_d5) {
  Bitboard expected = 0ULL;
  set_bit(expected, c7);
  set_bit(expected, e7);
  set_bit(expected, f6);
  set_bit(expected, f4);
  set_bit(expected, e3);
  set_bit(expected, c3);
  set_bit(expected, b4);
  set_bit(expected, b6);
  Bitboard result = Attacks::mask_knight_attacks(d5);
  EXPECT_EQ(result, expected) << "Knight on d5 error:\n" << Visual(result);
}
