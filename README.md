guess4r (仮）
=============

guess4r は、libguess を Ruby から扱うことを目的にしたライブラリ（になる予定）です。
まだ開発中です。

ビルド・インストール
--------------------
ruby >= 1.9.X と libguess が必要です。

    $ ruby extconf.rb
    $ make
    $ sudo make install

基本手順はこうなります。各自の環境にあわせて変更してください。

使い方
------

    confused_string.encoding       # => #<Encoding:ASCII-8BIT>
    confused_string.guess_encoding # => #<Encoding:Windows-31J>
    confused_string.guess.encoding # => #<Encoding:Windows-31J>
    confused_string.guess!         # => "\x{8356}\x{8374}\x{8367}JIS\x{95B6}\x{8E9A}\x{97F1}"
    confused_string.encoding       # => #<Encoding:Windows-31J>

ライセンス
----------

COPYING, COPYING.ja, BSDL, BSDL.ja, ZLIBL, ZLIBL.ja のいずれかのファイルに従ってください。
前半の 3 ファイルは ruby のものをそのまま拝借しただけです。
要約すると、2-clause BSD ライセンスか zlib/libpng ライセンスか Ruby の独自ライセンス部分
またはそれぞれの和訳、のいずれかお好きなものをお選びください、ということです。
なお和訳については、
[OSI承認オープンソースライセンス 日本語参考訳](http://sourceforge.jp/projects/opensource/wiki/licenses)
を参考にさせていただきました。

その他
======

## 開発動機

libguess の ruby バインディングとしては
[libguess-ruby](http://raa.ruby-lang.org/project/libguess-ruby/)
がすでにありますが、

*   ライセンスに "Ruby's" とあり、最終更新日の 2007-04-19 時点のものか最新のものでもよいのかわからない。
    最終更新日時点と解釈すると、BSDL ではなく GPL と Ruby の独自条項のデュアルライセンスとなり、個人的にちょっと嫌。
*   Ruby 1.9 以降は M17N が入ったのだから、せっかくならそれを使いたい。

という私のわがままにより、guess4r をでっち上げることにしました。
