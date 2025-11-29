#include "attacks.h"
#include <gtest/gtest.h>

class PawnAttackTest : public ::testing::Test {
protected:
};

TEST_F(PawnAttackTest, White_Corner_a2) {
  Bitboard expected = 0ULL;
  set_bit(expected, b3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, a2);
  EXPECT_EQ(result, expected) << "White Pawn on a2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Corner_h2) {
  Bitboard expected = 0ULL;
  set_bit(expected, g3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, h2);
  EXPECT_EQ(result, expected) << "White Pawn on h2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Center_d2) {
  Bitboard expected = 0ULL;
  set_bit(expected, c3);
  set_bit(expected, e3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, d2);
  EXPECT_EQ(result, expected) << "White Pawn on d2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Center_e2) {
  Bitboard expected = 0ULL;
  set_bit(expected, d3);
  set_bit(expected, f3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, e2);
  EXPECT_EQ(result, expected) << "White Pawn on e2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_InnerEdge_b2) {
  Bitboard expected = 0ULL;
  set_bit(expected, a3);
  set_bit(expected, c3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, b2);
  EXPECT_EQ(result, expected) << "White Pawn on b2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_InnerEdge_g2) {
  Bitboard expected = 0ULL;
  set_bit(expected, f3);
  set_bit(expected, h3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, g2);
  EXPECT_EQ(result, expected) << "White Pawn on g2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Edge_a3) {
  Bitboard expected = 0ULL;
  set_bit(expected, b4);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, a3);
  EXPECT_EQ(result, expected) << "White Pawn on a3 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Edge_h3) {
  Bitboard expected = 0ULL;
  set_bit(expected, g4);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, h3);
  EXPECT_EQ(result, expected) << "White Pawn on h3 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Mid_d4) {
  Bitboard expected = 0ULL;
  set_bit(expected, c5);
  set_bit(expected, e5);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, d4);
  EXPECT_EQ(result, expected) << "White Pawn on d4 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Mid_e5) {
  Bitboard expected = 0ULL;
  set_bit(expected, d6);
  set_bit(expected, f6);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, e5);
  EXPECT_EQ(result, expected) << "White Pawn on e5 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Edge_a6) {
  Bitboard expected = 0ULL;
  set_bit(expected, b7);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, a6);
  EXPECT_EQ(result, expected) << "White Pawn on a6 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Edge_h6) {
  Bitboard expected = 0ULL;
  set_bit(expected, g7);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, h6);
  EXPECT_EQ(result, expected) << "White Pawn on h6 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_InnerEdge_b6) {
  Bitboard expected = 0ULL;
  set_bit(expected, a7);
  set_bit(expected, c7);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, b6);
  EXPECT_EQ(result, expected) << "White Pawn on b6 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_InnerEdge_g6) {
  Bitboard expected = 0ULL;
  set_bit(expected, f7);
  set_bit(expected, h7);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, g6);
  EXPECT_EQ(result, expected) << "White Pawn on g6 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Start_c2) {
  Bitboard expected = 0ULL;
  set_bit(expected, b3);
  set_bit(expected, d3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, c2);
  EXPECT_EQ(result, expected) << "White Pawn on c2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Start_f2) {
  Bitboard expected = 0ULL;
  set_bit(expected, e3);
  set_bit(expected, g3);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, f2);
  EXPECT_EQ(result, expected) << "White Pawn on f2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Promoting_d7) {
  Bitboard expected = 0ULL;
  set_bit(expected, c8);
  set_bit(expected, e8);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, d7);
  EXPECT_EQ(result, expected) << "White Pawn on d7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Promoting_e7) {
  Bitboard expected = 0ULL;
  set_bit(expected, d8);
  set_bit(expected, f8);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, e7);
  EXPECT_EQ(result, expected) << "White Pawn on e7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Promoting_a7) {
  Bitboard expected = 0ULL;
  set_bit(expected, b8);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, a7);
  EXPECT_EQ(result, expected) << "White Pawn on a7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, White_Promoting_h7) {
  Bitboard expected = 0ULL;
  set_bit(expected, g8);
  Bitboard result = Attacks::mask_pawn_attacks(WHITE, h7);
  EXPECT_EQ(result, expected) << "White Pawn on h7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Corner_a7) {
  Bitboard expected = 0ULL;
  set_bit(expected, b6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, a7);
  EXPECT_EQ(result, expected) << "Black Pawn on a7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Corner_h7) {
  Bitboard expected = 0ULL;
  set_bit(expected, g6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, h7);
  EXPECT_EQ(result, expected) << "Black Pawn on h7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Center_d7) {
  Bitboard expected = 0ULL;
  set_bit(expected, c6);
  set_bit(expected, e6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, d7);
  EXPECT_EQ(result, expected) << "Black Pawn on d7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Center_e7) {
  Bitboard expected = 0ULL;
  set_bit(expected, d6);
  set_bit(expected, f6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, e7);
  EXPECT_EQ(result, expected) << "Black Pawn on e7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_InnerEdge_b7) {
  Bitboard expected = 0ULL;
  set_bit(expected, a6);
  set_bit(expected, c6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, b7);
  EXPECT_EQ(result, expected) << "Black Pawn on b7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_InnerEdge_g7) {
  Bitboard expected = 0ULL;
  set_bit(expected, f6);
  set_bit(expected, h6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, g7);
  EXPECT_EQ(result, expected) << "Black Pawn on g7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Edge_a6) {
  Bitboard expected = 0ULL;
  set_bit(expected, b5);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, a6);
  EXPECT_EQ(result, expected) << "Black Pawn on a6 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Edge_h6) {
  Bitboard expected = 0ULL;
  set_bit(expected, g5);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, h6);
  EXPECT_EQ(result, expected) << "Black Pawn on h6 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Mid_d5) {
  Bitboard expected = 0ULL;
  set_bit(expected, c4);
  set_bit(expected, e4);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, d5);
  EXPECT_EQ(result, expected) << "Black Pawn on d5 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Mid_e4) {
  Bitboard expected = 0ULL;
  set_bit(expected, d3);
  set_bit(expected, f3);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, e4);
  EXPECT_EQ(result, expected) << "Black Pawn on e4 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Edge_a3) {
  Bitboard expected = 0ULL;
  set_bit(expected, b2);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, a3);
  EXPECT_EQ(result, expected) << "Black Pawn on a3 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Edge_h3) {
  Bitboard expected = 0ULL;
  set_bit(expected, g2);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, h3);
  EXPECT_EQ(result, expected) << "Black Pawn on h3 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_InnerEdge_b3) {
  Bitboard expected = 0ULL;
  set_bit(expected, a2);
  set_bit(expected, c2);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, b3);
  EXPECT_EQ(result, expected) << "Black Pawn on b3 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_InnerEdge_g3) {
  Bitboard expected = 0ULL;
  set_bit(expected, f2);
  set_bit(expected, h2);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, g3);
  EXPECT_EQ(result, expected) << "Black Pawn on g3 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Start_c7) {
  Bitboard expected = 0ULL;
  set_bit(expected, b6);
  set_bit(expected, d6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, c7);
  EXPECT_EQ(result, expected) << "Black Pawn on c7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Start_f7) {
  Bitboard expected = 0ULL;
  set_bit(expected, e6);
  set_bit(expected, g6);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, f7);
  EXPECT_EQ(result, expected) << "Black Pawn on f7 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Promoting_d2) {
  Bitboard expected = 0ULL;
  set_bit(expected, c1);
  set_bit(expected, e1);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, d2);
  EXPECT_EQ(result, expected) << "Black Pawn on d2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Promoting_e2) {
  Bitboard expected = 0ULL;
  set_bit(expected, d1);
  set_bit(expected, f1);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, e2);
  EXPECT_EQ(result, expected) << "Black Pawn on e2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Promoting_a2) {
  Bitboard expected = 0ULL;
  set_bit(expected, b1);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, a2);
  EXPECT_EQ(result, expected) << "Black Pawn on a2 error:\n" << Visual(result);
}

TEST_F(PawnAttackTest, Black_Promoting_h2) {
  Bitboard expected = 0ULL;
  set_bit(expected, g1);
  Bitboard result = Attacks::mask_pawn_attacks(BLACK, h2);
  EXPECT_EQ(result, expected) << "Black Pawn on h2 error:\n" << Visual(result);
}
