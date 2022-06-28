# 設計資料
decompress libraryは他のjaidsライブラリへの依存はなく単独で動作する。Ver1.0.0時点ではstatic library版のみリリースしている。

## How to build

本ツールはCMakeを利用してbuildを行う。

```
$git clone https://github.com/jai-rd/lossless_compression
$cd lossless_compression
$lossless_compression>mkdir build
$lossless_compression>cd build
$build>cmake --build . --config Release
```

buildが完了すると`build/bin/Release`以下に`liblossless.lib`が生成される。  
上記手順でbuild可能であるが、[こちら](https://github.com/jai-rd/jaids-utils/blob/develop/docs/build.md#build手順)にCMakeを利用したbuild手順詳細を記載している。

## folder構成

```
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----        2022/04/01     11:38                .github
d-----        2022/04/27     17:13                docs
d-----        2022/04/05     19:29                include
d-----        2022/04/05     19:29                src
d-----        2022/04/01     11:38                test
d-----        2022/04/05     19:29                test_app
```

| folder   |                                |
| -------- | ------------------------------ |
| docs     | 設計ドキュメントを格納         |
| include  | 公開ヘッダファイル             |
| src      | src code                       |
| test     | google testを利用したtest code |
| test_app | 伸長画像をPvBufferへ展開する例 |

## 利用しているOSS

| OSS name   | Version | Url                                    |
| ---------- | ------- | -------------------------------------- |
| ThreadPool |         | https://github.com/progschj/ThreadPool |

* ThreadPoolはZlib Licenceであるため自由に使えアプリケーションへの表記も必須ではない

## モジュール設計

​	[モジュール設計](design.md)

