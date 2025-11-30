#include "attacks.h"
#include <gtest/gtest.h>

class BishopAttackTest : public ::testing::Test {
protected:
  static void SetUpTestSuite() { Attacks::init(); }
};

TEST_F(BishopAttackTest, EmptyBoard_Corner_a1) {
  Square sq = a1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b2);
  set_bit(expected, c3);
  set_bit(expected, d4);
  set_bit(expected, e5);
  set_bit(expected, f6);
  set_bit(expected, g7);
  set_bit(expected, h8);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a1 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_Corner_h1) {
  Square sq = h1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, g2);
  set_bit(expected, f3);
  set_bit(expected, e4);
  set_bit(expected, d5);
  set_bit(expected, c6);
  set_bit(expected, b7);
  set_bit(expected, a8);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on h1 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_Corner_a8) {
  Square sq = a8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b7);
  set_bit(expected, c6);
  set_bit(expected, d5);
  set_bit(expected, e4);
  set_bit(expected, f3);
  set_bit(expected, g2);
  set_bit(expected, h1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a8 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_Corner_h8) {
  Square sq = h8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, g7);
  set_bit(expected, f6);
  set_bit(expected, e5);
  set_bit(expected, d4);
  set_bit(expected, c3);
  set_bit(expected, b2);
  set_bit(expected, a1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on h8 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_Center_d4) {
  Square sq = d4;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, e5);
  set_bit(expected, f6);
  set_bit(expected, g7);
  set_bit(expected, h8);
  set_bit(expected, c5);
  set_bit(expected, b6);
  set_bit(expected, a7);
  set_bit(expected, e3);
  set_bit(expected, f2);
  set_bit(expected, g1);
  set_bit(expected, c3);
  set_bit(expected, b2);
  set_bit(expected, a1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on d4 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_Center_e5) {
  Square sq = e5;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, f6);
  set_bit(expected, g7);
  set_bit(expected, h8);
  set_bit(expected, d6);
  set_bit(expected, c7);
  set_bit(expected, b8);
  set_bit(expected, f4);
  set_bit(expected, g3);
  set_bit(expected, h2);
  set_bit(expected, d4);
  set_bit(expected, c3);
  set_bit(expected, b2);
  set_bit(expected, a1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on e5 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_b2) {
  Square sq = b2;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, c3);
  set_bit(expected, d4);
  set_bit(expected, e5);
  set_bit(expected, f6);
  set_bit(expected, g7);
  set_bit(expected, h8);
  set_bit(expected, a3);
  set_bit(expected, c1);
  set_bit(expected, a1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on b2 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_g2) {
  Square sq = g2;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, f3);
  set_bit(expected, e4);
  set_bit(expected, d5);
  set_bit(expected, c6);
  set_bit(expected, b7);
  set_bit(expected, a8);
  set_bit(expected, h3);
  set_bit(expected, f1);
  set_bit(expected, h1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on g2 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_b7) {
  Square sq = b7;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, a8);
  set_bit(expected, c8);
  set_bit(expected, c6);
  set_bit(expected, d5);
  set_bit(expected, e4);
  set_bit(expected, f3);
  set_bit(expected, g2);
  set_bit(expected, h1);
  set_bit(expected, a6);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on b7 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_g7) {
  Square sq = g7;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, h8);
  set_bit(expected, f8);
  set_bit(expected, h6);
  set_bit(expected, f6);
  set_bit(expected, e5);
  set_bit(expected, d4);
  set_bit(expected, c3);
  set_bit(expected, b2);
  set_bit(expected, a1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on g7 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_a4) {
  Square sq = a4;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b5);
  set_bit(expected, c6);
  set_bit(expected, d7);
  set_bit(expected, e8);
  set_bit(expected, b3);
  set_bit(expected, c2);
  set_bit(expected, d1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a4 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_h4) {
  Square sq = h4;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, g5);
  set_bit(expected, f6);
  set_bit(expected, e7);
  set_bit(expected, d8);
  set_bit(expected, g3);
  set_bit(expected, f2);
  set_bit(expected, e1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on h4 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_d1) {
  Square sq = d1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, e2);
  set_bit(expected, f3);
  set_bit(expected, g4);
  set_bit(expected, h5);
  set_bit(expected, c2);
  set_bit(expected, b3);
  set_bit(expected, a4);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on d1 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, EmptyBoard_e8) {
  Square sq = e8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, f7);
  set_bit(expected, g6);
  set_bit(expected, h5);
  set_bit(expected, d7);
  set_bit(expected, c6);
  set_bit(expected, b5);
  set_bit(expected, a4);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on e8 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Blocked_Surrounded_d4) {
  Square sq = d4;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, e5);
  set_bit(occupancy, c5);
  set_bit(occupancy, e3);
  set_bit(occupancy, c3);
  Bitboard expected = 0ULL;
  set_bit(expected, e5);
  set_bit(expected, c5);
  set_bit(expected, e3);
  set_bit(expected, c3);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on d4 surrounded failed:\n"
                              << Visual(result);
}

TEST_F(BishopAttackTest, Blocked_Far_d4) {
  Square sq = d4;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, h8);
  set_bit(occupancy, a7);
  set_bit(occupancy, g1);
  set_bit(occupancy, a1);
  Bitboard expected = 0ULL;
  set_bit(expected, e5);
  set_bit(expected, f6);
  set_bit(expected, g7);
  set_bit(expected, h8);
  set_bit(expected, c5);
  set_bit(expected, b6);
  set_bit(expected, a7);
  set_bit(expected, e3);
  set_bit(expected, f2);
  set_bit(expected, g1);
  set_bit(expected, c3);
  set_bit(expected, b2);
  set_bit(expected, a1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on d4 far blocked failed:\n"
                              << Visual(result);
}

TEST_F(BishopAttackTest, Blocked_Shadow_g2) {
  Square sq = g2;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, e4);
  set_bit(occupancy, c6);
  Bitboard expected = 0ULL;
  set_bit(expected, f3);
  set_bit(expected, e4);
  set_bit(expected, h3);
  set_bit(expected, h1);
  set_bit(expected, f1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on g2 shadow failed:\n"
                              << Visual(result);
}

TEST_F(BishopAttackTest, Blocked_Corner_a1) {
  Square sq = a1;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, b2);
  Bitboard expected = 0ULL;
  set_bit(expected, b2);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a1 blocked failed:\n"
                              << Visual(result);
}

TEST_F(BishopAttackTest, Empty_c1) {
  Square sq = c1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b2);
  set_bit(expected, a3);
  set_bit(expected, d2);
  set_bit(expected, e3);
  set_bit(expected, f4);
  set_bit(expected, g5);
  set_bit(expected, h6);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on c1 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_f1) {
  Square sq = f1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, e2);
  set_bit(expected, d3);
  set_bit(expected, c4);
  set_bit(expected, b5);
  set_bit(expected, a6);
  set_bit(expected, g2);
  set_bit(expected, h3);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on f1 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_c8) {
  Square sq = c8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b7);
  set_bit(expected, a6);
  set_bit(expected, d7);
  set_bit(expected, e6);
  set_bit(expected, f5);
  set_bit(expected, g4);
  set_bit(expected, h3);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on c8 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_f8) {
  Square sq = f8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, e7);
  set_bit(expected, d6);
  set_bit(expected, c5);
  set_bit(expected, b4);
  set_bit(expected, a3);
  set_bit(expected, g7);
  set_bit(expected, h6);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on f8 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_a3) {
  Square sq = a3;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b2);
  set_bit(expected, c1);
  set_bit(expected, b4);
  set_bit(expected, c5);
  set_bit(expected, d6);
  set_bit(expected, e7);
  set_bit(expected, f8);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a3 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_h3) {
  Square sq = h3;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, g2);
  set_bit(expected, f1);
  set_bit(expected, g4);
  set_bit(expected, f5);
  set_bit(expected, e6);
  set_bit(expected, d7);
  set_bit(expected, c8);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on h3 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_a6) {
  Square sq = a6;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, b7);
  set_bit(expected, c8);
  set_bit(expected, b5);
  set_bit(expected, c4);
  set_bit(expected, d3);
  set_bit(expected, e2);
  set_bit(expected, f1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a6 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_h6) {
  Square sq = h6;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, g7);
  set_bit(expected, f8);
  set_bit(expected, g5);
  set_bit(expected, f4);
  set_bit(expected, e3);
  set_bit(expected, d2);
  set_bit(expected, c1);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on h6 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_b1) {
  Square sq = b1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, a2);
  set_bit(expected, c2);
  set_bit(expected, d3);
  set_bit(expected, e4);
  set_bit(expected, f5);
  set_bit(expected, g6);
  set_bit(expected, h7);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on b1 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Empty_g8) {
  Square sq = g8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;
  set_bit(expected, h7);
  set_bit(expected, f7);
  set_bit(expected, e6);
  set_bit(expected, d5);
  set_bit(expected, c4);
  set_bit(expected, b3);
  set_bit(expected, a2);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on g8 failed:\n" << Visual(result);
}

TEST_F(BishopAttackTest, Blocked_Edge_a4) {
  Square sq = a4;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, b5);
  set_bit(occupancy, b3);
  Bitboard expected = 0ULL;
  set_bit(expected, b5);
  set_bit(expected, b3);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on a4 blocked failed:\n"
                              << Visual(result);
}

TEST_F(BishopAttackTest, Blocked_Edge_h5) {
  Square sq = h5;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, g6);
  set_bit(occupancy, g4);
  Bitboard expected = 0ULL;
  set_bit(expected, g6);
  set_bit(expected, g4);
  Bitboard result = Attacks::get_bishop_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Bishop on h5 blocked failed:\n"
                              << Visual(result);
}
