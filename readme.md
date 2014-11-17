[![Build Status](https://secure.travis-ci.org/is-cpuex2014-5/fpu_in_c.png?branch=master)](https://travis-ci.org/is-cpuex2014-5/fpu_in_c)

fpuをCで実装したもの.

使い方
======
* topでmakeするとlibfpu.aが生成されます.
* fpu.hをincludeして,libfpu.aをリンクしてください.

仕様
====
* フォーマットはieee754の32bit floating pointを採用している.
* denormalized numberは採用していない.(0になる)
* roundingはround evenを採用している.

h_floorの仕様
=============

* floatを32bitで渡すと32bit符号付き整数を返す
* 丸め方向は0向き
* 大きすぎる数を与えると0を返す
* 中途半端に大きい数を与えると正負が逆転したりする
    * 後ろ２つはサポートしない (というか本来例外投げるべきだと思う)

Sample
------
* h_floor 1 -> 1
* h_floor 1.3 -> 1
* h_floor -1.3 -> -1
* h_floor -1 -> -1
* h_floor 20000000000 -> 0
* h_floor 1000000000 -> 1000000000
* h_floor -3000040000 -> 1294927360

feqの仕様
=========
* 等しかったらtrueを返す
* feq Nan Nan := false
* feq -0 0 := true

fltの仕様
=========
* flt A B := A < B
