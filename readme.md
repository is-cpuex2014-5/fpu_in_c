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
