#pragma once

#include "itwos_complement_bitwidth.hpp"

#include <cstdint>

namespace jaids {
    namespace lossless {
        /// <summary>
        /// 2の補数表現されたbitstream処理
        /// </summary>
        class TwosComplementBitWidth5 : public ITwosComplementBitWidth {
        public:
            TwosComplementBitWidth5() = default;
            int ToIntValue(const unsigned int bitstream_value) override;

        private:
            const int value_from_bitstreams[32] = { 0,   1,   2,   3,   4,   5,   6,   7,  8,  9,  10, 11, 12, 13, 14, 15,
                                                  -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1 };
        };
    }  // namespace lossless
}  // namespace jaids

