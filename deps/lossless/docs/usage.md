# how to use lossless library

## 伸長処理
### CompressedBufferBpp8
フレーム単位で伸長を行うクラスである  
本クラスは8bit画像の伸長が可能、10bit,12bit画像に対応したクラスは未実装

#### インスタンス生成
```
            /// <summary>
            /// 8bit圧縮画像を伸長するクラス
            /// </summary>
            /// <param name="src_buffer">圧縮画像データ</param>
            /// <param name="width"></param>
            /// <param name="height"></param>
            CompressedBufferBpp8(const uint8_t* src_buffer, uint16_t width,
                                 const uint16_t height);
```

`src_buffer`にカメラから取得したRAW画像のポインターをセットする。仮に非圧縮画像が指定された場合でも機能的には問題ないがデータコピーが発生する。

#### 伸長処理

```
            /// <summary>
            /// 伸長を実行する
            /// </summary>
            /// <param name="dest_buffer">伸長先アドレス</param>
            void DoDecompress(uint8_t* dest_buffer);
```
予め確保した伸長画像を展開するバッファー指定しDoDecompressを実行する事で伸長処理を行う。伸長処理はLine毎に個別スレッドで処理を行う。


### PvBufferに伸長する例
伸長先のPvBufferを生成しメモリをAllocした上で
https://github.com/jai-rd/lossless_compression/blob/9ffd616e1959bc22fc461ccc431d3db2e5ed3f7f/test_app/test_app.cpp#L37-L39

image->GetDataPointer()に伸長する
https://github.com/jai-rd/lossless_compression/blob/9ffd616e1959bc22fc461ccc431d3db2e5ed3f7f/test_app/test_app.cpp#L44-L46

