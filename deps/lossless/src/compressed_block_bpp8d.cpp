#include "compressed_block_bpp8d.hpp"

#include <stdexcept>
#include <utility>

#include "compressed_bitstream.hpp"
#include "logger.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedBlockBpp8d::CompressedBlockBpp8d(CompressedBitStream& cbit_stream, uint8_t* dest_buffer,
                                               const uint32_t block_start_bits, const uint32_t pixelnum_in_block)
        : CompressedBlockBpp8(cbit_stream, dest_buffer, block_start_bits, pixelnum_in_block) {}

    CompressedBlockBpp8d::~CompressedBlockBpp8d() {}


    void CompressedBlockBpp8d::LogParseBlockHeader(const uint32_t block_start_bits, const uint8_t quantized_bitwidth) {
        logger::GetInstance().Debug("[blockheader] block_start_bits:{}, Byte: {:#02x}, Offset Bit: {} quantized_bitwidth:{}", block_start_bits,
                                   block_start_bits / 8, block_start_bits % 8, quantized_bitwidth);
        if (quantized_bitwidth > 8) {
            auto msg = fmt::format("Invalid quantized_bitwidth: {}", quantized_bitwidth);
            logger::GetInstance().Info("block_start_bits:{}, Byte: {:#02x}, Offset Bit: {} quantized_bitwidth:{}",
                                       block_start_bits, block_start_bits / 8, block_start_bits % 8, quantized_bitwidth);
            logger::GetInstance().Error(msg);
            throw runtime_error(msg);
        }
    }
}  // namespace jaids::lossless