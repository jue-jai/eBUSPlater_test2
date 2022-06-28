#include <gtest/gtest.h>

#include <map>
#include <string>




// テストフィクスチャとTEST_Fマクロを使う場合

class PixelTypeTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};


TEST_F(PixelTypeTest, Mono8) {
    EXPECT_EQ(2, 1+1);
    //EXPECT_EQ(PvPixelMono8, pixel_type.ToPvPixelType());
}

TEST_F(PixelTypeTest, Mono1) {
    EXPECT_EQ(1, 1 + 1);
    // EXPECT_EQ(PvPixelMono8, pixel_type.ToPvPixelType());
}
        