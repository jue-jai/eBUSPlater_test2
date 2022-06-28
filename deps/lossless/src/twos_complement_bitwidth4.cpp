#include "twos_complement_bitwidth4.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth4::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 4));
        return value_from_bitstreams[bitstream_value];
    }
}  // namespace jaids::lossless
