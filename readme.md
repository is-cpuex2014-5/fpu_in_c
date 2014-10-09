fpuをCで実装したもの.

仕様
====

* フォーマットはieee754の32bit floating pointを採用している.
* denormalized numberは採用していない.(0になる)
* roundingはround evenを採用している.
