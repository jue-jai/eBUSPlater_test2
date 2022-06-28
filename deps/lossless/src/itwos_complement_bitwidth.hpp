#pragma once

#include <cstdint>

namespace jaids {
    namespace lossless {
        /// <summary>
        /// 2の補数表現bitstreamをint16に変換
        /// </summary>
        class ITwosComplementBitWidth {
        public:
            virtual int ToIntValue(const unsigned int bitstream_value) = 0;
        };
    }  // namespace lossless
}  // namespace jaids
