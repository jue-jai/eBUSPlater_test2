#include "twos_complement_bitwidth1.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth1::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 1));
        // 2の補数変換
        // 2bit 2の補数表現では
        // 00->0, 01->1, 10->-2, 11->-1となるので以下配列で変換する。他のBitも同じ
        return value_from_bitstreams[bitstream_value];
    }
}  // namespace jaids::lossless
