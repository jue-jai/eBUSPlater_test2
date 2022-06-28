#pragma once

#include <cstdint>
#include <utility>

namespace jaids {
    namespace lossless {
        class CompressedBitStream;
        class CompressedBlockBpp8 {
        public:
            CompressedBlockBpp8(CompressedBitStream&, uint8_t* dest_buffer, const uint32_t process_start_bits,
                                 const uint32_t pixelnum_in_block);
            virtual ~CompressedBlockBpp8();
            virtual void Decompress();

        protected:
            void ParseBlockHeader();
            virtual void LogParseBlockHeader(const uint32_t block_start_bits, const uint8_t quantized_bitwidth) {}
            // get from lineheader
            uint8_t quantized_bitwidth_ = 0;

            CompressedBitStream& cbit_stream_;
            uint32_t block_start_bits_;
            uint32_t pixelnum_in_block_;
            uint8_t* dest_buffer_ = nullptr;
        };
    }  // namespace lossless
}  // namespace jaids
