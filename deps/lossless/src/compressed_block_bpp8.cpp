#include "compressed_block_bpp8.hpp"

#include <cassert>
#include <cstdio>
#include <utility>

#include "compressed_bitstream.hpp"
#include "logger.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedBlockBpp8::CompressedBlockBpp8(CompressedBitStream& cbit_stream, uint8_t* dest_buffer,
                                             const uint32_t block_start_bits, const uint32_t pixelnum_in_block)
        : cbit_stream_(cbit_stream),
          block_start_bits_(block_start_bits),
          pixelnum_in_block_(pixelnum_in_block),
          dest_buffer_(dest_buffer) {}

    CompressedBlockBpp8::~CompressedBlockBpp8() {}

    void CompressedBlockBpp8::Decompress() {
        ParseBlockHeader();

        // Blockの先頭は圧縮されていないオリジナルデータなのでそのまま使用
        auto v1 = cbit_stream_.GetStreamValue(block_start_bits_, 8);
        *dest_buffer_++ = v1;
        block_start_bits_ += 8;

        //ひとつ前のPixelとの差分が2の補数で入っている
        auto prevpixel_value = v1;
        int16_t v2;
        for (uint32_t pixel_idx = 1; pixel_idx < pixelnum_in_block_; ++pixel_idx) {
            v2 = cbit_stream_.ToIntValue(block_start_bits_, quantized_bitwidth_);
            *dest_buffer_ = prevpixel_value + v2;
            block_start_bits_ += quantized_bitwidth_;
            prevpixel_value = *dest_buffer_++;
        }
    }

    void CompressedBlockBpp8::ParseBlockHeader() {
        // V1 block header sizze
        constexpr uint8_t block_header_size_bit = 8;
        constexpr auto quantized_bit_width_startbit = 3;
        constexpr auto quantized_bit_width_lengthbit = 4;
        // 3bit-6bitがquantized_bitwidth　std::pairにはstart bit, sizeをセット
        constexpr std::pair<uint8_t, uint8_t> quantized_bitwidth_bit = { quantized_bit_width_startbit,
                                                                         quantized_bit_width_lengthbit };
        auto v = cbit_stream_.GetStreamValue(block_start_bits_ + quantized_bitwidth_bit.first, quantized_bitwidth_bit.second);
        quantized_bitwidth_ = v;
        LogParseBlockHeader(block_start_bits_, quantized_bitwidth_);
        block_start_bits_ += block_header_size_bit;
    }


}  // namespace jaids::lossless