#pragma once

#include <cstdint>
#include <utility>

#include "compressed_block_bpp8.hpp"

namespace jaids {
    namespace lossless {
        class CompressedBitStream;
        class CompressedBlockBayerBpp8 : public CompressedBlockBpp8 {
        public:
            CompressedBlockBayerBpp8(CompressedBitStream&, uint8_t* dest_buffer, const uint32_t process_start_bits,
                                      const uint32_t pixelnum_in_block);
            void Decompress() override;

        private:
            //uint8_t* dest_buffer_ = nullptr;
        };
    }  // namespace lossless
}  // namespace jaids
