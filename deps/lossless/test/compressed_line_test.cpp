#include <gtest/gtest.h>

#include <map>
#include <string>

#include "compressed_line_bpp8.hpp"

using namespace jaids::lossless;


// テストフィクスチャとTEST_Fマクロを使う場合

class CompressedLine8Test : public ::testing::Test {
protected:
    // データメンバーの初期化
    virtual void SetUp() {}
    // データメンバー

};


TEST(CompressedLine8Test, TestQuantizedBitW2Offset0) {
    uint8_t header[] = { 0x00, 0x00, 0x01, 0x02 };  // Mono, blocknum=2
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
