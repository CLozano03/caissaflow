#include "types.h"
#include <gtest/gtest.h>

class MoveTest : public ::testing::Test {
protected:
  void verify(Move m, Square f, Square t, MoveType ty) {
    EXPECT_EQ(m.from_sq(), f);
    EXPECT_EQ(m.to_sq(), t);
    EXPECT_EQ(m.type_of(), ty);
  }
};

TEST_F(MoveTest, NormalMoves) {
  verify(Move(a1, a2), a1, a2, NORMAL);
  verify(Move(e2, e4), e2, e4, NORMAL);
  verify(Move(g1, f3), g1, f3, NORMAL);
  verify(Move(h7, h5), h7, h5, NORMAL);
  verify(Move(d8, d1), d8, d1, NORMAL);
  verify(Move(b2, c3), b2, c3, NORMAL);
  verify(Move(f7, f8), f7, f8, NORMAL);
  verify(Move(c4, d5), c4, d5, NORMAL);
  verify(Move(a8, h8), a8, h8, NORMAL);
  verify(Move(h1, a1), h1, a1, NORMAL);
}

TEST_F(MoveTest, CastlingMoves) {
  verify(Move::make<CASTLING>(e1, g1), e1, g1, CASTLING);
  verify(Move::make<CASTLING>(e1, c1), e1, c1, CASTLING);
  verify(Move::make<CASTLING>(e8, g8), e8, g8, CASTLING);
  verify(Move::make<CASTLING>(e8, c8), e8, c8, CASTLING);
}

TEST_F(MoveTest, EnPassantMoves) {
  verify(Move::make<EN_PASSANT>(e5, d6), e5, d6, EN_PASSANT);
  verify(Move::make<EN_PASSANT>(d5, e6), d5, e6, EN_PASSANT);
  verify(Move::make<EN_PASSANT>(c4, b3), c4, b3, EN_PASSANT);
  verify(Move::make<EN_PASSANT>(g4, h3), g4, h3, EN_PASSANT);
  verify(Move::make<EN_PASSANT>(a5, b6), a5, b6, EN_PASSANT);
  verify(Move::make<EN_PASSANT>(h4, g3), h4, g3, EN_PASSANT);
}

TEST_F(MoveTest, PromotionQueen) {
  Move m1 = Move::make<PROMOTION>(a7, a8, QUEEN);
  verify(m1, a7, a8, PROMOTION);
  EXPECT_EQ(m1.promo_piece(), QUEEN);

  Move m2 = Move::make<PROMOTION>(h2, h1, QUEEN);
  verify(m2, h2, h1, PROMOTION);
  EXPECT_EQ(m2.promo_piece(), QUEEN);
}

TEST_F(MoveTest, PromotionRook) {
  Move m1 = Move::make<PROMOTION>(b7, b8, ROOK);
  verify(m1, b7, b8, PROMOTION);
  EXPECT_EQ(m1.promo_piece(), ROOK);

  Move m2 = Move::make<PROMOTION>(g2, g1, ROOK);
  verify(m2, g2, g1, PROMOTION);
  EXPECT_EQ(m2.promo_piece(), ROOK);
}

TEST_F(MoveTest, PromotionBishop) {
  Move m1 = Move::make<PROMOTION>(c7, c8, BISHOP);
  verify(m1, c7, c8, PROMOTION);
  EXPECT_EQ(m1.promo_piece(), BISHOP);

  Move m2 = Move::make<PROMOTION>(f2, f1, BISHOP);
  verify(m2, f2, f1, PROMOTION);
  EXPECT_EQ(m2.promo_piece(), BISHOP);
}

TEST_F(MoveTest, PromotionKnight) {
  Move m1 = Move::make<PROMOTION>(d7, d8, KNIGHT);
  verify(m1, d7, d8, PROMOTION);
  EXPECT_EQ(m1.promo_piece(), KNIGHT);

  Move m2 = Move::make<PROMOTION>(e2, e1, KNIGHT);
  verify(m2, e2, e1, PROMOTION);
  EXPECT_EQ(m2.promo_piece(), KNIGHT);
}

TEST_F(MoveTest, ExtremeSquares) {
  verify(Move(a1, h8), a1, h8, NORMAL);
  verify(Move(h8, a1), h8, a1, NORMAL);
  verify(Move(a8, h1), a8, h1, NORMAL);
  verify(Move(h1, a8), h1, a8, NORMAL);
}

TEST_F(MoveTest, BitBoundaryCheck) {
  for (int f = 0; f < 64; ++f) {
    for (int t = 0; t < 64; ++t) {
      if (f == t)
        continue;
      Move m(static_cast<Square>(f), static_cast<Square>(t));
      EXPECT_EQ(m.from_sq(), f);
      EXPECT_EQ(m.to_sq(), t);
    }
  }
}

TEST_F(MoveTest, TypeIntegrity) {
  Square f = e2, t = e4;
  EXPECT_EQ(Move::make<NORMAL>(f, t).type_of(), NORMAL);
  EXPECT_EQ(Move::make<PROMOTION>(f, t, QUEEN).type_of(), PROMOTION);
  EXPECT_EQ(Move::make<EN_PASSANT>(f, t).type_of(), EN_PASSANT);
  EXPECT_EQ(Move::make<CASTLING>(f, t).type_of(), CASTLING);
}

TEST_F(MoveTest, NullMove) {
  Move m = Move::null();
  EXPECT_FALSE(m.is_ok());
}

TEST_F(MoveTest, PromotionValues) {
  Square f = a7, t = a8;
  EXPECT_EQ(Move::make<PROMOTION>(f, t, QUEEN).promo_piece(), QUEEN);
  EXPECT_EQ(Move::make<PROMOTION>(f, t, ROOK).promo_piece(), ROOK);
  EXPECT_EQ(Move::make<PROMOTION>(f, t, BISHOP).promo_piece(), BISHOP);
  EXPECT_EQ(Move::make<PROMOTION>(f, t, KNIGHT).promo_piece(), KNIGHT);
}

TEST_F(MoveTest, MoveEquality) {
  Move m1(e2, e4);
  Move m2(e2, e4);
  Move m3(e2, e3);
  EXPECT_EQ(m1, m2);
  EXPECT_NE(m1, m3);
}
