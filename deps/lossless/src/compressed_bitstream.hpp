#pragma once

#include "bitstream.hpp"

#include <cstdint>
#include <unordered_map>
#include <array>
#include "itwos_complement_bitwidth.hpp"

namespace jaids {
    namespace lossless {
        /// <summary>
        /// 2の補数表現されたbitstream処理
        /// </summary>
        class CompressedBitStream : public BitStream {
        public:
            CompressedBitStream() = default;
            CompressedBitStream(uint8_t*);
            int16_t ToIntValue(const uint32_t start_bit, const uint8_t bit_width);

        private:
            static std::array<ITwosComplementBitWidth*, 9> two_complement_value;
        };
    }  // namespace lossless
}  // namespace jaids
