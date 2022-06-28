#pragma once

#include "itwos_complement_bitwidth.hpp"

#include <cstdint>

namespace jaids {
    namespace lossless {
        /// <summary>
        /// 2の補数表現されたbitstream処理
        /// </summary>
        class TwosComplementBitWidth2 : public ITwosComplementBitWidth {
        public:
            TwosComplementBitWidth2() = default;
            int ToIntValue(const unsigned int bitstream_value) override;

        private:
            const int value_from_bitstreams[4] = { 0, 1, -2, -1 };
        };
    }  // namespace lossless
}  // namespace jaids
