#include <gtest/gtest.h>

#include <map>
#include <string>


#include "JaidsConfig.h"


// テストフィクスチャとTEST_Fマクロを使う場合

class CoreVersionImplTest : public ::testing::Test {
protected:
    //std::unique_ptr<jaids::core::base::pv::CoreVersionImpl> corecersion;
    // データメンバーの初期化
    virtual void SetUp() { data1_ = 2.0; }
    // データメンバー
    double data1_;

    //CoreVersionImplTest() { corecersion = std::make_unique<jaids::core::base::pv::CoreVersionImpl>(); }
};

TEST_F(CoreVersionImplTest, CoreVersionTest) {

}
