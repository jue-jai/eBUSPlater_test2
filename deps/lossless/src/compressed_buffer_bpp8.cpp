
#include "compressed_buffer_bpp8.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>
#include <future>
#include <iostream>

#include "compressed_line_bpp8.hpp"
#include "ThreadPool.h"

using namespace std;
namespace jaids::lossless {
    CompressedBufferBpp8::CompressedBufferBpp8(const uint8_t* src_buffer, const uint16_t width,
                                               const uint16_t before_compressed_height, const uint16_t thread_num)
        : src_buffer_(src_buffer),
          threadpool_(jaids::lossless::ThreadPoolMgr::GetInstance(thread_num).GetPool()),
          width_(width),
          before_compressed_height_(before_compressed_height) {
    }

    void CompressedBufferBpp8::DoDecompress(uint8_t* dest_buffer) {
        auto out_buffer = dest_buffer;
        auto in_buffer = src_buffer_;
        vector<future<void>> results;

        for (uint32_t h = 0; h < before_compressed_height_; ++h) {
            auto compressed_line = make_shared<CompressedLineBpp8>((uint8_t*)in_buffer, width_);
            auto result = threadpool_.enqueue(
                [compressed_line](uint8_t* dest, const uint16_t width) {
                    // 8bitなので伸長後のLineデータサイズはwidthと等しい
                    compressed_line->DoDecompress(dest, width);
                },
                out_buffer, width_);
            //圧縮データについては1LineのデータサイズはHeaderを解析必要
            auto linesize = compressed_line->GetCompressedLineSize();
            in_buffer += (linesize /*+ v1_headersize*/);
            out_buffer += width_;
            results.push_back(move(result));
        }

        for (auto& r : results) {
            r.get();
        }
    }
}  // namespace jaids::lossless
