#include "twos_complement_bitwidth3.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth3::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 3));
        return value_from_bitstreams[bitstream_value];
    }
}  // namespace jaids::lossless