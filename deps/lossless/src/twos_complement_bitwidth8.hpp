#pragma once

#include "itwos_complement_bitwidth.hpp"

#include <cstdint>

namespace jaids {
    namespace lossless {
        /// <summary>
        /// 2の補数表現されたbitstream処理
        /// </summary>
        class TwosComplementBitWidth8 : public ITwosComplementBitWidth {
        public:
            TwosComplementBitWidth8() = default;
            int ToIntValue(const unsigned int bitstream_value) override;

        private:
        };
    }  // namespace lossless
}  // namespace jaids

