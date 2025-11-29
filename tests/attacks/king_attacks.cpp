#include "attacks.h"
#include <gtest/gtest.h>

class KingAttackTest : public ::testing::Test {
protected:
};

TEST_F(KingAttackTest, CornerSquare_a1) {
  Bitboard expected = 0ULL;
  set_bit(expected, b1);
  set_bit(expected, a2);
  set_bit(expected, b2);
  Bitboard result = Attacks::mask_king_attacks(a1);
  EXPECT_EQ(result, expected) << "King on a1 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CornerSquare_h1) {
  Bitboard expected = 0ULL;
  set_bit(expected, g1);
  set_bit(expected, g2);
  set_bit(expected, h2);
  Bitboard result = Attacks::mask_king_attacks(h1);
  EXPECT_EQ(result, expected) << "King on h1 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CornerSquare_a8) {
  Bitboard expected = 0ULL;
  set_bit(expected, a7);
  set_bit(expected, b7);
  set_bit(expected, b8);
  Bitboard result = Attacks::mask_king_attacks(a8);
  EXPECT_EQ(result, expected) << "King on a8 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CornerSquare_h8) {
  Bitboard expected = 0ULL;
  set_bit(expected, g7);
  set_bit(expected, h7);
  set_bit(expected, g8);
  Bitboard result = Attacks::mask_king_attacks(h8);
  EXPECT_EQ(result, expected) << "King on h8 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_d1) {
  Bitboard expected = 0ULL;
  set_bit(expected, c1);
  set_bit(expected, e1);
  set_bit(expected, c2);
  set_bit(expected, d2);
  set_bit(expected, e2);
  Bitboard result = Attacks::mask_king_attacks(d1);
  EXPECT_EQ(result, expected) << "King on d1 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_e1) {
  Bitboard expected = 0ULL;
  set_bit(expected, d1);
  set_bit(expected, f1);
  set_bit(expected, d2);
  set_bit(expected, e2);
  set_bit(expected, f2);
  Bitboard result = Attacks::mask_king_attacks(e1);
  EXPECT_EQ(result, expected) << "King on e1 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_b1) {
  Bitboard expected = 0ULL;
  set_bit(expected, a1);
  set_bit(expected, c1);
  set_bit(expected, a2);
  set_bit(expected, b2);
  set_bit(expected, c2);
  Bitboard result = Attacks::mask_king_attacks(b1);
  EXPECT_EQ(result, expected) << "King on b1 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_d8) {
  Bitboard expected = 0ULL;
  set_bit(expected, c7);
  set_bit(expected, d7);
  set_bit(expected, e7);
  set_bit(expected, c8);
  set_bit(expected, e8);
  Bitboard result = Attacks::mask_king_attacks(d8);
  EXPECT_EQ(result, expected) << "King on d8 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_g8) {
  Bitboard expected = 0ULL;
  set_bit(expected, f7);
  set_bit(expected, g7);
  set_bit(expected, h7);
  set_bit(expected, f8);
  set_bit(expected, h8);
  Bitboard result = Attacks::mask_king_attacks(g8);
  EXPECT_EQ(result, expected) << "King on g8 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_a4) {
  Bitboard expected = 0ULL;
  set_bit(expected, a3);
  set_bit(expected, b3);
  set_bit(expected, b4);
  set_bit(expected, a5);
  set_bit(expected, b5);
  Bitboard result = Attacks::mask_king_attacks(a4);
  EXPECT_EQ(result, expected) << "King on a4 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_a5) {
  Bitboard expected = 0ULL;
  set_bit(expected, a4);
  set_bit(expected, b4);
  set_bit(expected, b5);
  set_bit(expected, a6);
  set_bit(expected, b6);
  Bitboard result = Attacks::mask_king_attacks(a5);
  EXPECT_EQ(result, expected) << "King on a5 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_a2) {
  Bitboard expected = 0ULL;
  set_bit(expected, a1);
  set_bit(expected, b1);
  set_bit(expected, b2);
  set_bit(expected, a3);
  set_bit(expected, b3);
  Bitboard result = Attacks::mask_king_attacks(a2);
  EXPECT_EQ(result, expected) << "King on a2 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_h4) {
  Bitboard expected = 0ULL;
  set_bit(expected, g3);
  set_bit(expected, h3);
  set_bit(expected, g4);
  set_bit(expected, g5);
  set_bit(expected, h5);
  Bitboard result = Attacks::mask_king_attacks(h4);
  EXPECT_EQ(result, expected) << "King on h4 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_h5) {
  Bitboard expected = 0ULL;
  set_bit(expected, g4);
  set_bit(expected, h4);
  set_bit(expected, g5);
  set_bit(expected, g6);
  set_bit(expected, h6);
  Bitboard result = Attacks::mask_king_attacks(h5);
  EXPECT_EQ(result, expected) << "King on h5 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_h7) {
  Bitboard expected = 0ULL;
  set_bit(expected, g6);
  set_bit(expected, h6);
  set_bit(expected, g7);
  set_bit(expected, g8);
  set_bit(expected, h8);
  Bitboard result = Attacks::mask_king_attacks(h7);
  EXPECT_EQ(result, expected) << "King on h7 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, EdgeSquare_h2) {
  Bitboard expected = 0ULL;
  set_bit(expected, g1);
  set_bit(expected, h1);
  set_bit(expected, g2);
  set_bit(expected, g3);
  set_bit(expected, h3);
  Bitboard result = Attacks::mask_king_attacks(h2);
  EXPECT_EQ(result, expected) << "King on h2 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CenterSquare_d4) {
  Bitboard expected = 0ULL;
  set_bit(expected, c3);
  set_bit(expected, d3);
  set_bit(expected, e3);
  set_bit(expected, c4);
  set_bit(expected, e4);
  set_bit(expected, c5);
  set_bit(expected, d5);
  set_bit(expected, e5);
  Bitboard result = Attacks::mask_king_attacks(d4);
  EXPECT_EQ(result, expected) << "King on d4 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CenterSquare_e4) {
  Bitboard expected = 0ULL;
  set_bit(expected, d3);
  set_bit(expected, e3);
  set_bit(expected, f3);
  set_bit(expected, d4);
  set_bit(expected, f4);
  set_bit(expected, d5);
  set_bit(expected, e5);
  set_bit(expected, f5);
  Bitboard result = Attacks::mask_king_attacks(e4);
  EXPECT_EQ(result, expected) << "King on e4 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CenterSquare_d5) {
  Bitboard expected = 0ULL;
  set_bit(expected, c4);
  set_bit(expected, d4);
  set_bit(expected, e4);
  set_bit(expected, c5);
  set_bit(expected, e5);
  set_bit(expected, c6);
  set_bit(expected, d6);
  set_bit(expected, e6);
  Bitboard result = Attacks::mask_king_attacks(d5);
  EXPECT_EQ(result, expected) << "King on d5 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, CenterSquare_e5) {
  Bitboard expected = 0ULL;
  set_bit(expected, d4);
  set_bit(expected, e4);
  set_bit(expected, f4);
  set_bit(expected, d5);
  set_bit(expected, f5);
  set_bit(expected, d6);
  set_bit(expected, e6);
  set_bit(expected, f6);
  Bitboard result = Attacks::mask_king_attacks(e5);
  EXPECT_EQ(result, expected) << "King on e5 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, InnerRing_b2) {
  Bitboard expected = 0ULL;
  set_bit(expected, a1);
  set_bit(expected, b1);
  set_bit(expected, c1);
  set_bit(expected, a2);
  set_bit(expected, c2);
  set_bit(expected, a3);
  set_bit(expected, b3);
  set_bit(expected, c3);
  Bitboard result = Attacks::mask_king_attacks(b2);
  EXPECT_EQ(result, expected) << "King on b2 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, InnerRing_g2) {
  Bitboard expected = 0ULL;
  set_bit(expected, f1);
  set_bit(expected, g1);
  set_bit(expected, h1);
  set_bit(expected, f2);
  set_bit(expected, h2);
  set_bit(expected, f3);
  set_bit(expected, g3);
  set_bit(expected, h3);
  Bitboard result = Attacks::mask_king_attacks(g2);
  EXPECT_EQ(result, expected) << "King on g2 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, InnerRing_b7) {
  Bitboard expected = 0ULL;
  set_bit(expected, a6);
  set_bit(expected, b6);
  set_bit(expected, c6);
  set_bit(expected, a7);
  set_bit(expected, c7);
  set_bit(expected, a8);
  set_bit(expected, b8);
  set_bit(expected, c8);
  Bitboard result = Attacks::mask_king_attacks(b7);
  EXPECT_EQ(result, expected) << "King on b7 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, InnerRing_g7) {
  Bitboard expected = 0ULL;
  set_bit(expected, f6);
  set_bit(expected, g6);
  set_bit(expected, h6);
  set_bit(expected, f7);
  set_bit(expected, h7);
  set_bit(expected, f8);
  set_bit(expected, g8);
  set_bit(expected, h8);
  Bitboard result = Attacks::mask_king_attacks(g7);
  EXPECT_EQ(result, expected) << "King on g7 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, MidSquare_c3) {
  Bitboard expected = 0ULL;
  set_bit(expected, b2);
  set_bit(expected, c2);
  set_bit(expected, d2);
  set_bit(expected, b3);
  set_bit(expected, d3);
  set_bit(expected, b4);
  set_bit(expected, c4);
  set_bit(expected, d4);
  Bitboard result = Attacks::mask_king_attacks(c3);
  EXPECT_EQ(result, expected) << "King on c3 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, MidSquare_f3) {
  Bitboard expected = 0ULL;
  set_bit(expected, e2);
  set_bit(expected, f2);
  set_bit(expected, g2);
  set_bit(expected, e3);
  set_bit(expected, g3);
  set_bit(expected, e4);
  set_bit(expected, f4);
  set_bit(expected, g4);
  Bitboard result = Attacks::mask_king_attacks(f3);
  EXPECT_EQ(result, expected) << "King on f3 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, MidSquare_c6) {
  Bitboard expected = 0ULL;
  set_bit(expected, b5);
  set_bit(expected, c5);
  set_bit(expected, d5);
  set_bit(expected, b6);
  set_bit(expected, d6);
  set_bit(expected, b7);
  set_bit(expected, c7);
  set_bit(expected, d7);
  Bitboard result = Attacks::mask_king_attacks(c6);
  EXPECT_EQ(result, expected) << "King on c6 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, MidSquare_f6) {
  Bitboard expected = 0ULL;
  set_bit(expected, e5);
  set_bit(expected, f5);
  set_bit(expected, g5);
  set_bit(expected, e6);
  set_bit(expected, g6);
  set_bit(expected, e7);
  set_bit(expected, f7);
  set_bit(expected, g7);
  Bitboard result = Attacks::mask_king_attacks(f6);
  EXPECT_EQ(result, expected) << "King on f6 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, MidSquare_b4) {
  Bitboard expected = 0ULL;
  set_bit(expected, a3);
  set_bit(expected, b3);
  set_bit(expected, c3);
  set_bit(expected, a4);
  set_bit(expected, c4);
  set_bit(expected, a5);
  set_bit(expected, b5);
  set_bit(expected, c5);
  Bitboard result = Attacks::mask_king_attacks(b4);
  EXPECT_EQ(result, expected) << "King on b4 error:\n" << Visual(result);
}

TEST_F(KingAttackTest, MidSquare_g5) {
  Bitboard expected = 0ULL;
  set_bit(expected, f4);
  set_bit(expected, g4);
  set_bit(expected, h4);
  set_bit(expected, f5);
  set_bit(expected, h5);
  set_bit(expected, f6);
  set_bit(expected, g6);
  set_bit(expected, h6);
  Bitboard result = Attacks::mask_king_attacks(g5);
  EXPECT_EQ(result, expected) << "King on g5 error:\n" << Visual(result);
}
