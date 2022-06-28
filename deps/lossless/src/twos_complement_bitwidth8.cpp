#include "twos_complement_bitwidth8.hpp"

#include <cassert>
#include <cmath>

using namespace std;
namespace jaids::lossless {
    int TwosComplementBitWidth8::ToIntValue(const unsigned int bitstream_value) {
        assert(bitstream_value < pow(2, 8));
        return (int)bitstream_value;
    }
}  // namespace jaids::lossless