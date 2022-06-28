#include "compressed_block_bayerbpp8.hpp"

#include <utility>

#include "compressed_bitstream.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedBlockBayerBpp8::CompressedBlockBayerBpp8(CompressedBitStream& cbit_stream, uint8_t* dest_buffer,
                                                         const uint32_t process_start_bits,
                                     const uint32_t pixelnum_in_block)
        : CompressedBlockBpp8(cbit_stream, dest_buffer,process_start_bits, pixelnum_in_block) {}

    void CompressedBlockBayerBpp8::Decompress() {

        ParseBlockHeader();

        // block先頭は8bit
        auto v1 = cbit_stream_.GetStreamValue(block_start_bits_, 8);
        *dest_buffer_ = v1;
        // bayerは1バイト飛ばし
        dest_buffer_ += 2;
        block_start_bits_ += 8;

        //ひとつ前のPixelとの差分が2の補数で入っている
        auto prevpixel_value = v1;
        int16_t v2;
        for (uint32_t pixel_idx = 1; pixel_idx < pixelnum_in_block_; ++pixel_idx) {
            v2 = cbit_stream_.ToIntValue(block_start_bits_, quantized_bitwidth_);
            *dest_buffer_ = prevpixel_value + v2;
            block_start_bits_ += quantized_bitwidth_;
            prevpixel_value = *dest_buffer_;
            // bayerは1バイト飛ばし
            dest_buffer_ += 2;
        }
    }
}  // namespace jaids::lossless