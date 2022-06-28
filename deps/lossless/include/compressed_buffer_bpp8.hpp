#pragma once

#include <cstdint>

#include "threadpool_mgr.hpp"

namespace jaids {
    namespace lossless {
        class CompressedLineBpp8;
        class CompressedBufferBpp8 {
        public:
            /// <summary>
            /// 8bit圧縮画像を伸長するクラス
            /// 1line毎にthrea処理で伸長処理を行う
            /// ただしthreadはスレッドプールを利用する
            /// </summary>
            /// <param name="src_buffer">圧縮画像データ</param>
            /// <param name="width"></param>
            /// <param name="before_compressed_height">圧縮前のHeight</param>
            /// <param name="thread_num">伸長処理実行スレッド数</param>
            CompressedBufferBpp8(const uint8_t* src_buffer, const uint16_t width, const uint16_t before_compressed_height,
                                 const uint16_t thread_num = std::thread::hardware_concurrency());
            virtual ~CompressedBufferBpp8() = default;
            /// <summary>
            /// 伸長を実行する
            /// </summary>
            /// <param name="dest_buffer">伸長先アドレス</param>
            virtual void DoDecompress(uint8_t* dest_buffer);

        protected:
            const uint8_t* src_buffer_;
            ThreadPool& threadpool_;
            const uint16_t width_;
            const uint16_t before_compressed_height_;
        };
    }  // namespace lossless
}  // namespace jaids
