#include <gtest/gtest.h>

#include <map>
#include <string>

#include "compressed_bitstream.hpp"

using namespace jaids::lossless;

// テストフィクスチャとTEST_Fマクロを使う場合

class CompressedBitStreamTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST(CompressedBitStreamTest, TestBit2) {
    uint8_t bindata[] = {0b10001110,0b01011010};
    CompressedBitStream cbit(bindata);

    EXPECT_EQ(-2, cbit.ToIntValue(0, 2));
    EXPECT_EQ(-1, cbit.ToIntValue(2, 2));
    EXPECT_EQ(0, cbit.ToIntValue(4, 2));
    EXPECT_EQ(1, cbit.ToIntValue(14, 2));
}

TEST(CompressedBitStreamTest, TestBit3) {
    uint8_t bindata[] = { 0b10001110, 0b01011010 };
    CompressedBitStream cbit(bindata);

    EXPECT_EQ(-4, cbit.ToIntValue(5, 3));
    EXPECT_EQ(-3, cbit.ToIntValue(7, 3));
    EXPECT_EQ(-2, cbit.ToIntValue(0, 3));
    EXPECT_EQ(-1, cbit.ToIntValue(1, 3));
    EXPECT_EQ(0, cbit.ToIntValue(4, 3));
    EXPECT_EQ(1, cbit.ToIntValue(3, 3));
    EXPECT_EQ(2, cbit.ToIntValue(8, 3));
    EXPECT_EQ(3, cbit.ToIntValue(11, 3));
}

TEST(CompressedBitStreamTest, TestBit4) {
    uint8_t bindata[] = { 0b10001110, 0b01011010, 0b11001001,0b10000011,0b00000000 };
    CompressedBitStream cbit(bindata);

    EXPECT_EQ(-8, cbit.ToIntValue(4, 4));
    EXPECT_EQ(-7, cbit.ToIntValue(16, 4));
    EXPECT_EQ(-6, cbit.ToIntValue(8, 4));
    EXPECT_EQ(-5, cbit.ToIntValue(11, 4));
    EXPECT_EQ(-4, cbit.ToIntValue(20, 4));
    EXPECT_EQ(-3, cbit.ToIntValue(9, 4));
    EXPECT_EQ(-2, cbit.ToIntValue(0, 4));
    EXPECT_EQ(-1, cbit.ToIntValue(22, 4));
    EXPECT_EQ(0, cbit.ToIntValue(26, 4));
    EXPECT_EQ(1, cbit.ToIntValue(3, 4));
    EXPECT_EQ(2, cbit.ToIntValue(30, 4));
    EXPECT_EQ(3, cbit.ToIntValue(24, 4));
    EXPECT_EQ(4, cbit.ToIntValue(5, 4));
    EXPECT_EQ(5, cbit.ToIntValue(12, 4));
    EXPECT_EQ(6, cbit.ToIntValue(10, 4));
    EXPECT_EQ(7, cbit.ToIntValue(1, 4));
}

TEST(CompressedBitStreamTest, TestBit5) {
    uint8_t bindata[] = { 0b10001110, 0b01011010, 0b11001001, 0b10000011, 0b00000000 };
    CompressedBitStream cbit(bindata);

    EXPECT_EQ(-16, cbit.ToIntValue(27, 5));
    EXPECT_EQ(-15, cbit.ToIntValue(3, 5));
    EXPECT_EQ(-14, cbit.ToIntValue(18, 5));
}

TEST(CompressedBitStreamTest, TestBit6) {
    uint8_t bindata[] = { 0b10001110, 0b01000100 };
    CompressedBitStream cbit(bindata);

    EXPECT_EQ(-28, cbit.ToIntValue(5, 6));
    EXPECT_EQ(17, cbit.ToIntValue(10, 6));
}

TEST(CompressedBitStreamTest, TestBit7) {
    uint8_t bindata[] = { 0b10001110, 0b01000100 };
    CompressedBitStream cbit(bindata);

    EXPECT_EQ(-57, cbit.ToIntValue(1, 7));
    EXPECT_EQ(34, cbit.ToIntValue(9, 7));
}