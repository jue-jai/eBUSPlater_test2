#pragma once

#include <cstdint>
#include <utility>

#include "compressed_block_bpp8.hpp"

namespace jaids {
    namespace lossless {
        class CompressedBitStream;
        class CompressedBlockBpp8d : public CompressedBlockBpp8 {
        public:
            CompressedBlockBpp8d(CompressedBitStream&, uint8_t* dest_buffer, const uint32_t process_start_bits,
                                 const uint32_t pixelnum_in_block);
            ~CompressedBlockBpp8d();
        protected:
            void LogParseBlockHeader(const uint32_t block_start_bits, const uint8_t quantized_bitwidth) override;
        };
    }  // namespace lossless
}  // namespace jaids
