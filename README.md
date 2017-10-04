SATライブラリ
====
人工衛星の軌道計算をするうえで必要となるルーチンを集めたライブラリ。<br>

概要
----
人工衛星の軌道計算をするうえで必要となるルーチンを集めたライブラリである。<br>
衛星の軌道計算に必要となる座標変換などの機能も詰め込んだ。

リファレンス
----
データや関数の使い方は[REFERENCE.md](REFERENCE.md)を参照すること。

利用できる環境
----
cl (Windows 7) Version 19.11.25507.1 for x86とgcc (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609でビルドを確認した。

要求
----
以下の環境のインストールが必要である。

 * [tle v2.1.0](https://github.com/mkaminaga/tle)

Windowsで使用する場合には、上記に加え以下の環境が必要

 * [Microsoft Visual Studio Community 2017](https://www.microsoft.com/ja-jp/dev/products/community.aspx)
 * [Windows SDK 8.1](https://developer.microsoft.com/ja-jp/windows/downloads/windows-8-1-sdk)

注意
----
Windowsの場合には、開発者コマンドプロンプトや[Cygwin](https://www.cygwin.com/)、[MSYS2](http://www.msys2.org/)等のターミナルを用いてビルドする方法を説明する。<br>

インストール
----

方法1: ダウンロード
------
[releaseページ](https://github.com/mkaminaga/sat/releases)からzipファイルをダウンロードし、適当なディレクトリに展開する。<br>

方法2: クローン & ビルド -> スタティックリンクライブラリの作成
----

clの場合
```
$ git clone https://github.com/mkaminaga/sat
$ cd sat
$ vim sat_windows.mk
$ nmake /f sat_windows.mk | iconv -f cp932 -t utf-8
```

gccの場合
```
$ git clone https://github.com/mkaminaga/sat
$ cd sat
$ make -f sat.mk
```

注意点は、ビルドを実行する前にメイクファイルを編集することである。

使用方法
----
clの場合、リンク時に`sat.lib`を指定すること。<br>
gccの場合、リンク時に`libsat.a`を指定すること。<br>
makefileは必要に応じて書き換えること。<br>

サンプルのビルド
----

clの場合
```
$ cd sat
$ nmake /f makefile_windows.mk | iconv -f cp932 -t utf-8
$ ./test.exe
```

gccの場合
```
$ cd sat
$ make
$ ./test.exe
```

注意点は、makeを実行する前にmakefileを環境に合わせて書き換えることである。

検証
----
計算の精度については[TEST.md](TEST.md)を参照すること。<br>

参考
----
このライブラリを作成するに当たり以下の資料を参考にした。

 * [CALSAT32のからくり](http://jr1huo.my.coocan.jp/jr1huo_calsat32/Calsat32Karakuri.htm)
 * [宇宙関連講義資料](http://lss.mes.titech.ac.jp/~matunaga/)
 * [Revisiting Spacetrack Report #3 AIAA 2006-6753](http://www.celestrak.com/publications/AIAA/2006-6753/)
 * [人工衛星位置推算の実際（最終版）](http://www.infra.kochi-tech.ac.jp/takagi/Geomatics/5Estimation2.pdf)
 * [Revisiting Spacetrack Report #3 AIAA 2006-6753](http://www.celestrak.com/publications/AIAA/2006-6753/)

ライセンス
----
MITライセンスで公開する。<br>
詳しくは[LICENSE.md](LICENSE.md)を参照すること。
