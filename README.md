# rook
自作の言語処理系の開発リポジトリです。リポジトリ名は愛犬の名前から取りました。  
完全な趣味の作成物なので、マイペースにコツコツと作っていこうと思います。

開発の記録はブログにも残していくつもりなので、誰かの何かのお役に立てば嬉しいです。

## ビルド＆実行方法
### ビルド
```
$ git clone https://github.com/corgi0901/rook.git
$ cd rook
$ make
```
### 実行
```
$ ./rook <ソースファイル>
```

## サンプルコード
```
# sample.rk - Sample code for rook

# Calcurate Fibonacci number
func fib(n)
{
	if(n <= 2){
		return 1
	} else {
		return fib(n-1) + fib(n-2)
	}
}

# main function
func main()
{
	ret = fib(10)	# Calcurate
	put(ret)		# Print result
}
```

## 開発記録（ブログ）
第0回：[イントロ編](https://corgi-lab.com/self-made/lang-processor-0/)

第1回：[数値を読み込む](https://corgi-lab.com/self-made/lang-processor-1/)

第2回：[加減算を実装する](https://corgi-lab.com/self-made/lang-processor-2/)

第3回：[乗除算を実装する](https://corgi-lab.com/self-made/lang-processor-3/)

第4回：[括弧付き計算と単項演算子](https://corgi-lab.com/self-made/lang-processor-4/)

第5回：[連続した式の実行](https://corgi-lab.com/self-made/lang-processor-5/)

第6回：[変数を実装する](https://corgi-lab.com/self-made/lang-processor-6/)

第7回：[比較演算子を実装する](https://corgi-lab.com/self-made/lang-processor-7/)