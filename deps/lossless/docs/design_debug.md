### CompressedBufferBpp8d, CompressedLineBpp8d,CompressedBlockBpp8d

上記クラスはカメラおよびPC側ライブラリのDebug用途に利用するクラスであり、クラス名にdが付与される。基本的な責務は夫々Baseとなるクラスと同じだがLogを出力する点が大きく異なる。

アプリ側で`CompressedBufferBpp8d`を生成した場合にDebug用途クラスである`CompressedLineBpp8d`,`CompressedBlockBpp8d`が利用される。これらのクラスを使った場合は、伸長処理はシングルスレッドで実行され、また実行経過をログ出力するため、伸長処理に時間がかかる。またログ出力にOSSを利用している関係で、ユーザへの公開は想定していない。

Debug版では`lossless.conf`設定に従い、処理経過をファイルとしてログ出力を行う。また圧縮データ異常を検出した場合、処理を停止させ`std::runtime_error`が発生する。したがってログファイルを見ることで、どのあたりのデータを異常と判断したか確認可能である。

以下は一例であるが、`h: 25, offset: 0x5830`の出力は25Line目、Dataオフセット 0x5830から伸長処理を行った場合に出力される。該当Lineにエラーを検出しなかった場合は`h: 26, offset: 0x5c30`のように次のLineが出力される。以下の場合26Line目の伸長においてLineHeader異常を検出したため、該当LineHeaderのデータを出力し処理を停止した結果である。

```
[20220531-134627.552778000][debug] h: 25, offset: 0x5830
[20220531-134627.552798300][debug] h: 26, offset: 0x5c30
[20220531-134633.743235400][debug] line header, src_buffer: 0x0 0x0 0x1 0xb0 0x38 0x8e 0xe3 0x38
[20220531-134633.743385000][debug] Invalid version of line header: 0
```



実際のデータ伸長処理までステップが進んだ場合はLine毎に以下のような各BlockのHeader情報を出力する

```
[20220601-165736.674895400][info] [DoDecompress] line: 823, offset from top: 0x21c18
[20220601-165736.674917200][debug] block_start_bits:64, Byte: 0x8, Offset Bit: 0 quantized_bitwidth:1
[20220601-165736.674942200][debug] block_start_bits:143, Byte: 0x11, Offset Bit: 7 quantized_bitwidth:1
[20220601-165736.674972400][debug] block_start_bits:222, Byte: 0x1b, Offset Bit: 6 quantized_bitwidth:1
[20220601-165736.674997900][debug] block_start_bits:301, Byte: 0x25, Offset Bit: 5 quantized_bitwidth:1
[20220601-165736.675021900][debug] block_start_bits:380, Byte: 0x2f, Offset Bit: 4 quantized_bitwidth:1
[20220601-165736.675045500][debug] block_start_bits:459, Byte: 0x39, Offset Bit: 3 quantized_bitwidth:1
[20220601-165736.675069000][debug] block_start_bits:538, Byte: 0x43, Offset Bit: 2 quantized_bitwidth:1
[20220601-165736.675092200][debug] block_start_bits:617, Byte: 0x4d, Offset Bit: 1 quantized_bitwidth:1
[20220601-165736.675116700][debug] block_start_bits:696, Byte: 0x57, Offset Bit: 0 quantized_bitwidth:1
[20220601-165736.675141100][debug] block_start_bits:775, Byte: 0x60, Offset Bit: 7 quantized_bitwidth:1
[20220601-165736.675164800][debug] block_start_bits:854, Byte: 0x6a, Offset Bit: 6 quantized_bitwidth:1
[20220601-165736.675188000][debug] block_start_bits:933, Byte: 0x74, Offset Bit: 5 quantized_bitwidth:1
[20220601-165736.675210600][debug] block_start_bits:1012, Byte: 0x7e, Offset Bit: 4 quantized_bitwidth:1
[20220601-165736.675235500][debug] block_start_bits:1091, Byte: 0x88, Offset Bit: 3 quantized_bitwidth:1
[20220601-165736.675261400][debug] block_start_bits:1170, Byte: 0x92, Offset Bit: 2 quantized_bitwidth:1
[20220601-165736.675285300][debug] block_start_bits:1249, Byte: 0x9c, Offset Bit: 1 quantized_bitwidth:1
```



`[info] [DoDecompress] line: 823, offset from top: 0x21c18`

これは823LineのDataを伸長している事を表す。また823LineのDataはBuffer先頭からオフセット0x21c18バイトから開始している事を意味する。

`[debug] block_start_bits:143, Byte: 0x11, Offset Bit: 7 quantized_bitwidth:1`

これはBlockHeaderを出力している。block_start_bits:143はLine先頭から143bitの場所から該当Blockが開始してる事を表す。Byte: 0x11, Offset Bit: 7は上記block_start_bitsがLine先頭から0X11バイトの7bitの場所から始まることを意味している。ただしこのByteはLine先頭からのオフセットでありバッファ先頭からのオフセットはoffset from topを加算する必要がある事は注意が必要。



