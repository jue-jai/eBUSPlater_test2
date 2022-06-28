#pragma once

#include <cstdint>
#include <utility>

namespace jaids {
    namespace lossless {
        class BitStream {
        public:
            BitStream() = default;
            BitStream(uint8_t*);
            uint8_t GetStreamValue(const uint32_t start_bit, const uint8_t bit_width);

        protected:
            uint8_t* pBinData_ = nullptr;
        };
    }  // namespace lossless
}  // namespace jaids
