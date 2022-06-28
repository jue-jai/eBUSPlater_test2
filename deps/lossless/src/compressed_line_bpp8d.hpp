/*********************************************************************
 * @file   compressed_line_bpp8.hpp
 * @brief
 *
 * @author nma
 * @date   May 2022 Header Version1対応
 * @copyright Copyright (c)JAI Corporation 2022
 *********************************************************************/
#pragma once

#include <cstdint>

#include "compressed_line_bpp8.hpp"
#include "compressed_bitstream.hpp"

namespace jaids {
    namespace lossless {
        class CompressedLineBpp8d : public CompressedLineBpp8 {
        public:
            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="">圧縮データバッファアドレス</param>
            CompressedLineBpp8d(uint8_t*, const uint16_t width, const uint16_t line, const uint32_t offset);
            ~CompressedLineBpp8d();

            /// <summary>
            /// 伸長処理実行
            /// データによっては伸長対象データが非圧縮の場合もある。この場合dest_buffにコピーするがサイズを指定する必要がある。
            /// 伸長後のサイズはwidthとpixelformatによって決定可能
            /// </summary>
            /// <param name="dest_buff">伸長データ保存アドレス</param>
            /// <param name="decompressed_size">伸長後Lineデータサイズ</param>
            void DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size) override;

        private:
            void LogInvalidVersion(const uint16_t) override;
            void LogParseLineHeaderVer1(const uint8_t*) override;
            void LogParseLineHeaderVer1InvalidLineSize(const uint16_t line_size) override;
            void LogParseLineHeaderVer1InvalidVersion(const uint16_t version) override;
            const uint16_t line_;
            const uint32_t offset_;
        };
    }  // namespace lossless
}  // namespace jaids
