#include "twos_complement_bitwidth5.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth5::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 5));
        return value_from_bitstreams[bitstream_value];
    }
}  // namespace jaids::lossless
