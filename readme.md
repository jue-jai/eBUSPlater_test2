# eBUS Player with lossless

lossless対応したeBUS Playerのリポジトリです  
eBUS SDKのSampleソース(eBUSPlayerSample)を元に修正

カメラから受信した圧縮画像の伸長は[lossless_compression](https://github.com/jai-rd/lossless_compression)を利用する。
本アプリは上記lossless_compressionライブラリをstaticリンクしておりeBUS Playerが動作する環境であればアプリ単体で動作可能である。

## eBUS Playerのビルド
lossless伸長に対応したeBUS Playerはlossless_compressionライブラリをビルドした後、eBUS Playerのビルドを実行する必要がある。
[ビルド手順の詳細](docs/build.md)

## eBUS Player with losslessの設計状況
2022/06/06時点ではMonoカメラのみカメラと接続した状態で動作が可能である。
ただし、下記リンク記載のカメラ側の不具合があり、lossless出力にあたっていくつか制約がある。特に"カメラ起動後にlosslessストリームが出力されない"のようなworkaroundな対応が必要な不具合も残っている。
https://teams.microsoft.com/l/message/19:ffd9f77cfab44731907ed03e578c2c39@thread.skype/1654232764552?tenantId=5faec0ed-5436-423f-aff6-da7f7b4452b8&groupId=ab2f3f69-0076-470c-8f73-80a04f0ebdba&parentMessageId=1654232764552&teamName=R%26D%202Group&channelName=%E3%82%AB%E3%83%A1%E3%83%A9%E7%94%BB%E5%83%8F%E3%81%AE%E5%9C%A7%E7%B8%AE%E4%BC%B8%E9%95%B7&createdTime=1654232764552

PlayerのDebugおよび動作確認には、まずはTestPatternを有効にした状態で行う事を推奨する。TestPatternを使う事で圧縮Off状態でのカメラ出力と、圧縮有効状態でlossless libraryで伸長した値とが正しいかの確認が行える。またカメラ側のDebug状況で改善されていくはずだが、2022/06/06時点ではTestPatternを無効にした状態ではカメラ/Player間での画像出力が数フレームで停止ししてしまうという現象も頻発し、以後カメラを再起動するまでは接続出来ないという状況が発生するが、TestPatternを有効にしwidth=320, height=240位にした場合は出力が止まるような現象は確認できない。

## eBUS Player with losslessの設計ポイント
基本的には`DisplayThread::OnBufferDisplay()`で受信時に圧縮モードが有効の場合、伸長用のBufferを新たに生成し、そのBufferをDisplay関数にセットしているだけであるが、以下が主な変更ポイントである。

### 圧縮データ伸長処理
eBUS PlayerのDisplayThread::OnBufferDisplay()処理内でデータ伸長を行う  
DisplayThreadにはOnBufferRetrieved()も存在するが名前の通りOnBufferDisplay()は画像表示時にコールバックされる。
画像表示する分だけ伸長できれば良いのでOnBufferDisplay()で処理を行う。

#### 圧縮モード設定取得
カメラから受信した画像が圧縮有効なのかはPlayerのDisplayThreadの情報だけでは分からない。したがってDisplayThread生成時にPvGenParameterArrayをセットしてカメラFeatureを参照し、圧縮が有効なのかを判定する。
https://github.com/jai-rd/eBUSPlayerLossless/blob/14d3416b71377512cd3aec489fe7d1feb85364b0/src/DisplayThread.cpp#L97-L106

#### 圧縮前のHeight取得
伸長データ確報バッファ作成のためHeightが必要である。圧縮有効な場合PvImageから取得できるHeightは圧縮後のHeightであり、伸長データ格納バッファ用途としては利用できない。
したがって現状は以下のようにFeatureを参照している。
https://github.com/jai-rd/eBUSPlayerLossless/blob/14d3416b71377512cd3aec489fe7d1feb85364b0/src/DisplayThread.cpp#L114-L120

顧客側で伸長libraryを使って処理処理を行う場合は、何らかの方法で圧縮前Heightを管理する必要がある。

### Camera Debug用のアプリ
https://github.com/jai-rd/eBUSPlayerLossless/blob/14d3416b71377512cd3aec489fe7d1feb85364b0/src/DisplayThread.cpp#L134
のようにCompressedBufferBpp8dを利用した場合Debugモードでアプリが生成される。
[Debugモードについて](https://github.com/jai-rd/lossless_compression/blob/develop/docs/design_debug.md)

2022/06/06時点ではまだカメラのDebugを行っている状況でありツールとしてリリースバージョンでの動作確認までは進んでいない。

Debugモードは`7-camera-debug用` branchをbuildした場合に利用可能である。DebugモードではeBUS Playerと同じフォルダにlossless.confファイルが存在する場合`AppData/Local/JAI`以下にlog.filenameでlog出力を行う事に加え、伸長エラー時は受信画像をファイル出力を行う。

ただしDebugモードは上記のようにlog出力、画像のファイル保存が行われるため、カメラのフレームレートが高いとエラーとなってしまう。

```
log.level = "info"
log.filename = "lossless.log"
```
ログの見方などは[Debugモードについて](https://github.com/jai-rd/lossless_compression/blob/develop/docs/design_debug.md)に記載

[Camera Debug用のアプリマニュアル](https://jaionline-my.sharepoint.com/:p:/g/personal/nma_jai_com/EdoY_iIC9kVHsnrOtI_AkN8BKN5jgoxANEevs6DLsdadBA)


### 伸長処理自体のDebug
[伸長library](https://github.com/jai-rd/lossless_compression) 自体のDebugが必要になった場合だが、Playerの状態でカメラから画像取得しながらDebugするとタイムアウトなど発生するため、伸長library単体でのDebugをお勧めする。Camera Debug用のアプリは伸長エラーを検出すると受信Dataをファイル出力する機能がある。そのファイルを[test_app](https://github.com/jai-rd/lossless_compression/blob/cace56b7f4bca3034284fa7e1d07bbf199bd9618/test_app/test_app.cpp#L19)でReadする事でカメラと接続なしでDebug可能である。ただし画像サイズは手作業で設定が必要である。
https://github.com/jai-rd/lossless_compression/blob/cace56b7f4bca3034284fa7e1d07bbf199bd9618/test_app/test_app.cpp#L33-L34



### Colorカメラ対応
2022/06/06時点ではColorカメラのDebugは未着手である。MonoもColorも圧縮/伸長処理自体は基本的には同じである。大きな違いとしては伸長後の画像の並べ替えが必要である。
https://github.com/jai-rd/lossless_compression/blob/develop/docs/design.md#compressedlinebpp8
上記リンクの`CompressedBlockBayerBpp8`がBayer用の並べ替えに対応したクラスであるが、本クラスの動作確認、Debugが必要となる。


## eBUS Playerのリリース
生成したPlayerはeBUS SDKがインストールされたPCの任意の場所に保存してダブルクリックする事で実行可能である。
リリースするファイルはexeファイル1つであり、インストーラ形式でのリリースは行わない。

### Release build
繰り返しになるが2022/06/06時点ではDebugモードを使ったカメラDebugを行っている状況であり、実際にeBUS PlayerをリリースするためにはReleaseビルドした生成物で動作確認が必要となる。`7-camera-debug用` branchをDebugビルドした物はDebug用の仕込みが入っている事に加え、伸長処理をシングルスレッドで行っている。Release時は`develop`branchを使う事でマルチスレッドで伸長処理を行うといった対応は済だが、伸長スレッド数のチューニングは必要となる可能性がある。

#### 伸長スレッド数のチューニング
現実装ではPC側のCPUが有するコア数だけスレッドを生成している。

具体的には
https://github.com/jai-rd/eBUSPlayerLossless/blob/3bd9e6d251ebe412b2587ea8110e28d3aa592c2f/src/DisplayThread.cpp#L136
の引数 thread_numをデフォルトのまま実行した場合は伸長処理用のスレッドを`std::thread::hardware_concurrency()`生成する。
したがってチューニングを行う場合は、この値を変更する必要がある。少し古い測定ではあるが、スレッド数と伸長時間の変化はhttps://github.com/jai-rd/lossless_compression/blob/cace56b7f4bca3034284fa7e1d07bbf199bd9618/docs/performance_decompress.md
のデータが参考として利用できる。

#### リリース時の確認ポイント
特に1stリリース時は、メモリリーク等発生していない事の確認が必要となる。

