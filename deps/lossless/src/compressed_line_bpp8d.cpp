#include "compressed_line_bpp8d.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdio>

#include "compressed_bitstream.hpp"
#include "compressed_block_bpp8d.hpp"
#include "compressed_block_bayerbpp8.hpp"
#include "logger.hpp"

using namespace std;
namespace jaids::lossless {
    CompressedLineBpp8d::CompressedLineBpp8d(uint8_t* linebuf, uint16_t width, const uint16_t line, const uint32_t offset)
        : CompressedLineBpp8(linebuf, width), line_(line), offset_(offset) {}

    CompressedLineBpp8d::~CompressedLineBpp8d() {}

    void CompressedLineBpp8d::DoDecompress(uint8_t* dest_buff, uint16_t decompressed_size) {
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
            CompressedBlockBpp8d cblock(cbit_stream_, dest_buff, block_offset, block_size_);
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

    void CompressedLineBpp8d::LogInvalidVersion(const uint16_t version) {
        auto msg = fmt::format("Invalid version of line header: {:x}", version);
        logger::GetInstance().Error(msg);
        throw runtime_error(msg);
    }
    void CompressedLineBpp8d::LogParseLineHeaderVer1(const uint8_t* p) {
        logger::GetInstance().Error(
            "line[{}], header: {:#02x} {:#02x} {:#02x} {:#02x} {:#02x} {:#02x} {:#02x} {:#02x}, file offset: {:#02x}", line_, p[0], p[1],
            p[2], p[3], p[4], p[5], p[6], p[7], offset_);
    }
    void CompressedLineBpp8d::LogParseLineHeaderVer1InvalidLineSize(const uint16_t line_size) {
        auto msg = fmt::format("Invalid linesize of line header: {}", line_size);
        logger::GetInstance().Error(msg);
        throw runtime_error(msg);
    }
    void CompressedLineBpp8d::LogParseLineHeaderVer1InvalidVersion(const uint16_t pixelsize) {
        auto msg = fmt::format("Invalid pixel size of line header: {}", pixelsize);
        logger::GetInstance().Error(msg);
        throw runtime_error(msg);
    }
}  // namespace jaids::lossless