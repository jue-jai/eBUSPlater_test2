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

#include "compressed_bitstream.hpp"

namespace jaids {
    namespace lossless {
        class CompressedLineBpp8 {
        public:
            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="">圧縮データバッファアドレス</param>
            CompressedLineBpp8(uint8_t*, const uint16_t width);
            virtual ~CompressedLineBpp8();
            CompressedLineBpp8(const CompressedLineBpp8& rhs);
            CompressedLineBpp8& operator=(const CompressedLineBpp8& rhs);
            CompressedLineBpp8(CompressedLineBpp8&& rhs);
            CompressedLineBpp8& operator=(CompressedLineBpp8&& rhs) noexcept;

            /// <summary>
            /// 伸長処理実行
            /// データによっては伸長対象データが非圧縮の場合もある。この場合dest_buffにコピーするがサイズを指定する必要がある。
            /// 伸長後のサイズはwidthとpixelformatによって決定可能
            /// </summary>
            /// <param name="dest_buff">伸長データ保存アドレス</param>
            /// <param name="decompressed_size">伸長後Lineデータサイズ</param>
            virtual void DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size);

            /// <summary>
            /// line headerを含め圧縮データLineサイズ
            /// </summary>
            /// <returns></returns>
            virtual uint32_t GetCompressedLineSize();
            /// <summary>
            /// lineheaderを解析しid_,version_,type_,blocksize_,blocknum_にセットする
            /// </summary>
            virtual void ParseLineHeader();

        protected:
            enum class BlockType : uint8_t {
                MonoColor = 0,
                TwoColor = 1,
            };
            uint16_t header_size_ = 8;
            uint16_t id_ = 0;
            uint16_t version_ = 0;
            BlockType type_;
            uint16_t block_size_ = 0;
            /// <summary>
            /// lineHeaderから取得した1blockのピクセル数
            /// </summary>
            uint16_t blocknum_ = 0;
            enum class PixelSize : uint8_t { Bit8 = 0, Bit10 = 1, Bit12 = 2, Undef = 0xff };
            PixelSize pixel_size_ = PixelSize::Undef;
            uint16_t line_size_ = 0;
            uint8_t* src_buffer_;
            uint16_t width_;
            CompressedBitStream cbit_stream_;
            virtual void ParseLineHeaderVer1();
            virtual void LogInvalidVersion(const uint16_t) {}
            virtual void LogParseLineHeaderVer1(const uint8_t*) {}
            virtual void LogParseLineHeaderVer1InvalidLineSize(const uint16_t line_size) {}
            virtual void LogParseLineHeaderVer1InvalidVersion(const uint16_t version) {}
        };
    }  // namespace lossless
}  // namespace jaids
