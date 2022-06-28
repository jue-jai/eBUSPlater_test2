#include "twos_complement_bitwidth7.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth7::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 7));
        return value_from_bitstreams[bitstream_value];
    }
}  // namespace jaids::lossless