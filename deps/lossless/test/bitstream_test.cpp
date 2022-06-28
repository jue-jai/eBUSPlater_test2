#include <gtest/gtest.h>

#include <map>
#include <string>

#include "bitstream.hpp"

using namespace jaids::lossless;

// テストフィクスチャとTEST_Fマクロを使う場合

class BitStreamTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST(BitStreamTest, GetTest1) {
    uint8_t bindata[] = {0b10101010,0b01011010};
    BitStream cbit(bindata);

    auto x = cbit.GetStreamValue(0, 4);
    EXPECT_EQ(0b1010, cbit.GetStreamValue(0, 4));
    EXPECT_EQ(0b1010101, cbit.GetStreamValue(1, 7));
    EXPECT_EQ(0b010, cbit.GetStreamValue(8, 3));
    EXPECT_EQ(0b101, cbit.GetStreamValue(7, 3));
    EXPECT_EQ(0b101010, cbit.GetStreamValue(6, 6));
}

TEST(BitStreamTest, GetTest2) {
    uint8_t bindata[] = { 0, 0, 0b01001101, 0b0000001, 0b00000000, 0b00000000, 8, 0 };
    BitStream cbit(bindata);

    EXPECT_EQ(0b01, cbit.GetStreamValue(16, 2));
    EXPECT_EQ(0b1101, cbit.GetStreamValue(16, 4));
    EXPECT_EQ(0b11, cbit.GetStreamValue(18, 2));

}