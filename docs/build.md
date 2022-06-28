# Build eBUS Player

lossless 伸長libraryはgit submoduleとしてdeps/losslessに配置してある。PlayerをBuildするにはlossless library, Playerの順にbuildが必要となる。

通常リリース時は`develop`branchを利用する事、カメラDebug用のPlayerをbuildするときは`7-camera-debug用` branchを利用する事。



1. lossless library

   基本は[こちらの手順](https://github.com/jai-rd/lossless_compression/tree/develop/docs#how-to-build)のとおりbuildを行えばよい。

   ```
   $cd lossless
   $lossless>mkdir build
   $lossless>cd build
   $build>cmake ..
   $build>cmake --build . --config Release
   ```

   上記手順でBuild行った場合`lossless\build\src\Release`配下に`liblossless.lib`が生成される。Debug buildを行う場合は以下実行すると`lossless\build\src\Debug`配下に生成される。

   ```
   $build>cmake --build . --config Debug
   ```

2. Version更新

   リリース時はAbout Dialogで表示されるVersionを更新する

   https://github.com/jai-rd/eBUSPlayerLossless/blob/5a730b38dc809cb6d745012a5b17e1175defc686/src/eBUSPlayerDlg.h#L44

3. eBUS Player

   `eBUSPlayerSample.vcxproj`をVisual Studioで開き、通常のProject同様buildを行う。リリース時は必ず`develop`branch でビルドを行う必要がある。