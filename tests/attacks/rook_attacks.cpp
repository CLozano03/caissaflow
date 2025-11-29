#include "attacks.h"
#include <gtest/gtest.h>

class RookAttackTest : public ::testing::Test {
protected:
  static void SetUpTestSuite() { Attacks::init(); }
};

TEST_F(RookAttackTest, EmptyBoard_Corner_a1) {
  Square sq = a1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;

  // File A (North)
  set_bit(expected, a2);
  set_bit(expected, a3);
  set_bit(expected, a4);
  set_bit(expected, a5);
  set_bit(expected, a6);
  set_bit(expected, a7);
  set_bit(expected, a8);
  // Rank 1 (East)
  set_bit(expected, b1);
  set_bit(expected, c1);
  set_bit(expected, d1);
  set_bit(expected, e1);
  set_bit(expected, f1);
  set_bit(expected, g1);
  set_bit(expected, h1);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on a1 (Empty) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, EmptyBoard_Corner_h8) {
  Square sq = h8;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;

  // File H (South)
  set_bit(expected, h7);
  set_bit(expected, h6);
  set_bit(expected, h5);
  set_bit(expected, h4);
  set_bit(expected, h3);
  set_bit(expected, h2);
  set_bit(expected, h1);
  // Rank 8 (West)
  set_bit(expected, g8);
  set_bit(expected, f8);
  set_bit(expected, e8);
  set_bit(expected, d8);
  set_bit(expected, c8);
  set_bit(expected, b8);
  set_bit(expected, a8);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on h8 (Empty) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, EmptyBoard_Center_e4) {
  Square sq = e4;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;

  // North
  set_bit(expected, e5);
  set_bit(expected, e6);
  set_bit(expected, e7);
  set_bit(expected, e8);
  // South
  set_bit(expected, e3);
  set_bit(expected, e2);
  set_bit(expected, e1);
  // East
  set_bit(expected, f4);
  set_bit(expected, g4);
  set_bit(expected, h4);
  // West
  set_bit(expected, d4);
  set_bit(expected, c4);
  set_bit(expected, b4);
  set_bit(expected, a4);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on e4 (Empty) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, EmptyBoard_Edge_a5) {
  Square sq = a5;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;

  // North & South (Entire File A)
  set_bit(expected, a1);
  set_bit(expected, a2);
  set_bit(expected, a3);
  set_bit(expected, a4);
  set_bit(expected, a6);
  set_bit(expected, a7);
  set_bit(expected, a8);
  // East (Rank 5)
  set_bit(expected, b5);
  set_bit(expected, c5);
  set_bit(expected, d5);
  set_bit(expected, e5);
  set_bit(expected, f5);
  set_bit(expected, g5);
  set_bit(expected, h5);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on a5 (Empty) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, EmptyBoard_Edge_d1) {
  Square sq = d1;
  Bitboard occupancy = 0ULL;
  Bitboard expected = 0ULL;

  // North (File D)
  set_bit(expected, d2);
  set_bit(expected, d3);
  set_bit(expected, d4);
  set_bit(expected, d5);
  set_bit(expected, d6);
  set_bit(expected, d7);
  set_bit(expected, d8);
  // East/West (Rank 1)
  set_bit(expected, a1);
  set_bit(expected, b1);
  set_bit(expected, c1);
  set_bit(expected, e1);
  set_bit(expected, f1);
  set_bit(expected, g1);
  set_bit(expected, h1);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on d1 (Empty) failed:\n"
                              << Visual(result);
}
TEST_F(RookAttackTest, Blocked_Surrounded_d4) {
  Square sq = d4;
  Bitboard occupancy = 0ULL;

  // Set blockers on all 4 adjacent squares
  set_bit(occupancy, d5); // North
  set_bit(occupancy, d3); // South
  set_bit(occupancy, e4); // East
  set_bit(occupancy, c4); // West

  Bitboard expected = 0ULL;
  // Rook captures/hits the blocker, but goes no further
  set_bit(expected, d5);
  set_bit(expected, d3);
  set_bit(expected, e4);
  set_bit(expected, c4);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on d4 (Surrounded) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Blocked_Corner_a1_Immediate) {
  Square sq = a1;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, a2); // Block North
  set_bit(occupancy, b1); // Block East

  Bitboard expected = 0ULL;
  set_bit(expected, a2);
  set_bit(expected, b1);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on a1 (Trapped) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Blocked_FarEdges_e4) {
  Square sq = e4;
  Bitboard occupancy = 0ULL;

  // Blockers at the very edge of the board
  set_bit(occupancy, e8); // North Edge
  set_bit(occupancy, e1); // South Edge
  set_bit(occupancy, h4); // East Edge
  set_bit(occupancy, a4); // West Edge

  Bitboard expected = 0ULL;
  // Should attack everything up to AND INCLUDING the edge blockers
  // North
  set_bit(expected, e5);
  set_bit(expected, e6);
  set_bit(expected, e7);
  set_bit(expected, e8);
  // South
  set_bit(expected, e3);
  set_bit(expected, e2);
  set_bit(expected, e1);
  // East
  set_bit(expected, f4);
  set_bit(expected, g4);
  set_bit(expected, h4);
  // West
  set_bit(expected, d4);
  set_bit(expected, c4);
  set_bit(expected, b4);
  set_bit(expected, a4);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on e4 (Far Blockers) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Shadowing_File_g) {
  Square sq = g2;
  Bitboard occupancy = 0ULL;

  // Two blockers on the North ray
  set_bit(occupancy, g5); // First blocker
  set_bit(occupancy, g7); // Second blocker (hidden)

  Bitboard expected = 0ULL;
  // North: Stops at g5
  set_bit(expected, g3);
  set_bit(expected, g4);
  set_bit(expected, g5);
  // South: Free (g1)
  set_bit(expected, g1);
  // East: Free (h2)
  set_bit(expected, h2);
  // West: Free (a2-f2)
  set_bit(expected, f2);
  set_bit(expected, e2);
  set_bit(expected, d2);
  set_bit(expected, c2);
  set_bit(expected, b2);
  set_bit(expected, a2);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on g2 (Shadow Test) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Shadowing_Rank_5) {
  Square sq = h5;
  Bitboard occupancy = 0ULL;

  // Two blockers on the West ray
  set_bit(occupancy, f5); // First blocker
  set_bit(occupancy, c5); // Second blocker (hidden)

  Bitboard expected = 0ULL;
  // West: Stops at f5
  set_bit(expected, g5);
  set_bit(expected, f5);
  // North: Free
  set_bit(expected, h6);
  set_bit(expected, h7);
  set_bit(expected, h8);
  // South: Free
  set_bit(expected, h4);
  set_bit(expected, h3);
  set_bit(expected, h2);
  set_bit(expected, h1);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on h5 (Shadow Test) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Mixed_Scenario_c3) {
  Square sq = c3;
  Bitboard occupancy = 0ULL;

  set_bit(occupancy, c7); // North blocker
  set_bit(occupancy, g3); // East blocker
  // South and West are open

  Bitboard expected = 0ULL;
  // North -> Stops at c7
  set_bit(expected, c4);
  set_bit(expected, c5);
  set_bit(expected, c6);
  set_bit(expected, c7);
  // East -> Stops at g3
  set_bit(expected, d3);
  set_bit(expected, e3);
  set_bit(expected, f3);
  set_bit(expected, g3);
  // South -> Free to c1
  set_bit(expected, c2);
  set_bit(expected, c1);
  // West -> Free to a3
  set_bit(expected, b3);
  set_bit(expected, a3);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on c3 (Mixed) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Mixed_Scenario_b7) {
  Square sq = b7;
  Bitboard occupancy = 0ULL;

  set_bit(occupancy, b8); // Immediate North block
  set_bit(occupancy, b2); // Far South block
  set_bit(occupancy, f7); // Mid East block
  // West is free (only a7)

  Bitboard expected = 0ULL;
  set_bit(expected, b8); // North
  set_bit(expected, b6);
  set_bit(expected, b5);
  set_bit(expected, b4);
  set_bit(expected, b3);
  set_bit(expected, b2); // South
  set_bit(expected, c7);
  set_bit(expected, d7);
  set_bit(expected, e7);
  set_bit(expected, f7); // East
  set_bit(expected, a7); // West

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on b7 (Mixed) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Tunnel_Vertical_d2) {
  // Rook trapped in a vertical "tunnel"
  Square sq = d2;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, c2); // Block Left
  set_bit(occupancy, e2); // Block Right

  Bitboard expected = 0ULL;
  // Horizontal (Blocked immediately)
  set_bit(expected, c2);
  set_bit(expected, e2);
  // Vertical (Totally free)
  set_bit(expected, d1);
  set_bit(expected, d3);
  set_bit(expected, d4);
  set_bit(expected, d5);
  set_bit(expected, d6);
  set_bit(expected, d7);
  set_bit(expected, d8);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on d2 (Tunnel) failed:\n"
                              << Visual(result);
}

TEST_F(RookAttackTest, Tunnel_Horizontal_f7) {
  // Rook trapped in a horizontal "tunnel"
  Square sq = f7;
  Bitboard occupancy = 0ULL;
  set_bit(occupancy, f8); // Block Up
  set_bit(occupancy, f6); // Block Down

  Bitboard expected = 0ULL;
  // Vertical (Blocked immediately)
  set_bit(expected, f8);
  set_bit(expected, f6);
  // Horizontal (Totally free)
  set_bit(expected, a7);
  set_bit(expected, b7);
  set_bit(expected, c7);
  set_bit(expected, d7);
  set_bit(expected, e7);
  set_bit(expected, g7);
  set_bit(expected, h7);

  Bitboard result = Attacks::get_rook_attacks(sq, occupancy);
  EXPECT_EQ(result, expected) << "Rook on f7 (Tunnel) failed:\n"
                              << Visual(result);
}
