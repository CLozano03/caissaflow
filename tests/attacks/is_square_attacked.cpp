#include "attacks.h"
#include <gtest/gtest.h>

struct AttackParam {
  std::string fen;
  Square sq;
  Color side;
  bool expected;
};

class ParamAttackTest : public ::testing::TestWithParam<AttackParam> {};

TEST_P(ParamAttackTest, CheckAllAttacks) {
  auto param = GetParam();
  Position pos;
  pos.set_pos(param.fen);

  EXPECT_EQ(Attacks::is_square_attacked(param.sq, param.side, pos),
            param.expected)
      << "Failed attack test for square " << param.sq << " in position "
      << param.fen;
}

INSTANTIATE_TEST_SUITE_P(
    ChessTests, ParamAttackTest,
    ::testing::Values(
        AttackParam{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                    e3, WHITE, true},
        AttackParam{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                    e6, WHITE, false},
        AttackParam{"4k3/8/8/8/8/8/4P3/4K3 w - - 0 1", d3, WHITE, true}));
