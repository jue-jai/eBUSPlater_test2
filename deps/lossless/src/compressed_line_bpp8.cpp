#include "compressed_line_bpp8.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdio>

#include "compressed_bitstream.hpp"
#include "compressed_block_bpp8.hpp"
#include "compressed_block_bayerbpp8.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedLineBpp8::CompressedLineBpp8(uint8_t* linebuf, uint16_t width) : src_buffer_(linebuf), width_(width) {
        CompressedBitStream cbit_stream(src_buffer_);
        cbit_stream_ = cbit_stream;
    }

    CompressedLineBpp8::~CompressedLineBpp8() {}

    CompressedLineBpp8::CompressedLineBpp8(const CompressedLineBpp8& rhs) = default;

    CompressedLineBpp8& CompressedLineBpp8::operator=(const CompressedLineBpp8& rhs) = default;

    CompressedLineBpp8::CompressedLineBpp8(CompressedLineBpp8&& rhs) = default;

    CompressedLineBpp8& CompressedLineBpp8::operator=(CompressedLineBpp8&& rhs) noexcept = default;

    void CompressedLineBpp8::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size) {
        //非圧縮なのでそのままコピー
        if (id_ != 0) {
            memcpy(dest_buff, src_buffer_, decompressed_size);
            return;
        }

        // line先頭はLineHeader分だけSkipする
        auto block_offset = 64;  // Ver0のheader=4byteだが独自でlinesize=4byteを追加している
        if (type_ == BlockType::MonoColor) {
            // cbit_stream_ => line分のbitstream
            // block_offset => block毎のbitstream内のoffset => line header分skip
            // pixelnum_each_block_ => lineHeaderから取得した1blockのピクセル数
            CompressedBlockBpp8 cblock(cbit_stream_, dest_buff, block_offset, block_size_);
            for (auto idx = 0; idx < blocknum_; idx++) {
                cblock.Decompress();
            }
        }
        else {
            // Bayerは2コンポーネント単位で処理
            // ex BayerRG
            //圧縮データはRがpixelnum_each_block_が連続して入っているので先にRを処理
            CompressedBlockBayerBpp8 c1_block(cbit_stream_, dest_buff, block_offset, block_size_);
            for (auto idx = 0; idx < blocknum_ / 2; idx++) {
                c1_block.Decompress();
            }
            //続けてGがpixelnum_each_block_が連続して入っているのでGを処理
            CompressedBlockBayerBpp8 c2_block(cbit_stream_, dest_buff + 1, block_offset, block_size_);
            for (auto idx = 0; idx < blocknum_ / 2; idx++) {
                c2_block.Decompress();
            }
        }
    }

    uint32_t CompressedLineBpp8::GetCompressedLineSize() {
        ParseLineHeader();
        return line_size_;
    }

    void CompressedLineBpp8::ParseLineHeader() {
        memcpy(&id_, src_buffer_, 2);
        // id_==0以外は非圧縮
        if (id_ == 0) {
            // version
            version_ = cbit_stream_.GetStreamValue(22, 2);
            if (version_ == 1) {
                ParseLineHeaderVer1();
            }
            else {
                LogParseLineHeaderVer1(src_buffer_);
                LogInvalidVersion(version_);
            }
        }
        else {
            //非圧縮の場合はlinesize = widthになる。heightを計算するために必要
            line_size_ = width_;
        }
    }

    void CompressedLineBpp8::ParseLineHeaderVer1() {
        type_ = cbit_stream_.GetStreamValue(20, 2) == 0 ? BlockType::MonoColor : BlockType::TwoColor;
        if (cbit_stream_.GetStreamValue(16, 2) == 1) {
            block_size_ = 64;
        }
        assert(block_size_ != 0);
        blocknum_ = cbit_stream_.GetStreamValue(24, 8);
        auto pixel_size = cbit_stream_.GetStreamValue(36, 2);
        if (pixel_size == 0) {
            pixel_size_ = PixelSize::Bit8;
        }
        else if (pixel_size == 1) {
            pixel_size_ = PixelSize::Bit10;
        }
        else if (pixel_size == 2) {
            pixel_size_ = PixelSize::Bit12;
        }
        else {
            LogParseLineHeaderVer1(src_buffer_);
            LogParseLineHeaderVer1InvalidVersion(pixel_size);
        }
        //現状GetStreamValueのwidthは8bitまでしかサポートしていないのでGetStreamValueを使わない
        // LineSizeがbyte境界を跨ぐ仕様になった場合はGetStreamValue対応必要
        // BigEndianなのでEndian変換
        line_size_ = (*(uint16_t*)(src_buffer_ + 6) << 8) + *(uint8_t*)(src_buffer_ + 7);
        if (line_size_ == 0) {
            LogParseLineHeaderVer1InvalidLineSize(line_size_);
        }
        line_size_ += 8;
    }
}  // namespace jaids::lossless