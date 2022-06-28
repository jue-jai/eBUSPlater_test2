#pragma once

#include "compressed_buffer_bpp8.hpp"

namespace jaids {
    namespace lossless {
        class CompressedLineBpp8;
        class CompressedBufferBpp8d : public CompressedBufferBpp8 {
        public:
            /// <summary>
            /// 8bit圧縮画像を伸長するクラス
            /// </summary>
            /// <param name="src_buffer">圧縮画像データ</param>
            /// <param name="width"></param>
            /// <param name="before_compressed_height"></param>
            CompressedBufferBpp8d(const uint8_t* src_buffer, const uint16_t width, const uint16_t before_compressed_height, uint64_t block_id);
            ~CompressedBufferBpp8d() = default;
            /// <summary>
            /// 伸長を実行する
            /// </summary>
            /// <param name="dest_buffer">伸長先アドレス</param>
            void DoDecompress(uint8_t* dest_buffer) override;

        private:
            uint64_t block_id_ = 0;
        };
    }  // namespace lossless
}  // namespace jaids
