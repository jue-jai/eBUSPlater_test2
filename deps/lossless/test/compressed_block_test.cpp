#include <gtest/gtest.h>

#include <map>
#include <string>

#include "compressed_block.hpp"
#include "compressed_bitstream.hpp"

using namespace jaids::lossless;


// テストフィクスチャとTEST_Fマクロを使う場合

class CompressedBlockTest : public ::testing::Test {
protected:
    // std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    // CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST(CompressedBlockTest, TestQuantizedBitW2Offset0) {
    uint8_t bindata[] = { 0b00000000, 0b01011010 };
    CompressedBitStream cbit(bindata);

    //CompressedBlock cblock(cbit, 0, 4);
    //cblock.ParseHeader();
    //int16_t value = 0;
    //int16_t expected[] = { -2, -4, -3, -2 };
    //uint16_t idx = 0;
    //while (cblock.GetValue(value)) {
    //    EXPECT_EQ(expected[idx++], value);
    //}
    //EXPECT_EQ(16, cblock.GetProcessedBits());
}
