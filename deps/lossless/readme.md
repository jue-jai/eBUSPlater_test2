# lossless Decompress library

GOX-4th Genで対応予定のlossless compressionされた画像に対しDecompress処理を行うlibraryである。本library設計時点ではlossless画像をどのようにアプリ側でみせるか決まっていない。またDecompress処理をlibraryとして提供するのかも決まっていない。したがって、eBUS Playerで伸長画像表示できる処理のみ実装する。

Ver1リリース時点では8bit画像のみ対応する。



## How to use library

[libray 使い方](./docs/usage.md)

## Performance

25MP圧縮画像を伸長する処理時間

[伸長処理測定](./docs/performance_decompress.md)  






