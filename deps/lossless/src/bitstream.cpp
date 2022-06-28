#include "bitstream.hpp"

#include <cassert>
#include <stdexcept>

using namespace std;
namespace jaids::lossless {
    BitStream::BitStream(uint8_t* bindata) : pBinData_(bindata) {}
    uint8_t BitStream::GetStreamValue(const uint32_t start_bit, const uint8_t bit_width) {
        assert(bit_width <= 8);

        // bit_width=0はデータがない、意味的には0に相当する
        if (bit_width == 0) return 0;

        const uint8_t masks[] = { 0, 0b1, 0b11, 0b111, 0b1111, 0b11111, 0b111111, 0b1111111, 0b11111111 };

        // uint16_t bitstream_value = 0;
        //指定bitが1Byteに収まるか判定
        auto data_idx_s = start_bit >> 3;  // start_bit / 8;
        auto data_idx_e = (start_bit + bit_width - 1) >> 3;
        auto data_offset_s = start_bit & 0b111;

        auto d = &pBinData_[data_idx_s];
        if (data_idx_s == data_idx_e) {
            return (*d >> data_offset_s) & masks[bit_width];
        }
        else {
            auto v1 = *d >> data_offset_s;
            auto u = 8 - data_offset_s;
            auto v2 = *(d + 1) & masks[bit_width - u];
            v2 <<= u;
            return v1 + v2;
        }
    }
}  // namespace jaids::lossless
