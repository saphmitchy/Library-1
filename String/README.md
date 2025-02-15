# 文字列

## Z algorithm

文字列の各接尾辞が、元の文字列と何文字の接頭辞を共通に持っているかを求めるアルゴリズム。

- [Z algorithm](Z_Algorithm.hpp)

## Manachar

文字列の各文字を中心とした最長回分の半径を求めるアルゴリズム。

- [Manachar](Manachar.hpp)

## MP 法・KMP 法

文字列のすべての接頭辞について、その共通する最長の接頭辞・接尾辞を求めるアルゴリズム。

- [MP 法・KMP 法](KMP.hpp)

## トライ木

文字列集合に対してトライ木（各頂点は 1 文字を表していて、根から 1 文字ずつたどることで文字列が表現される木）を構築する。

- [トライ木](Trie.hpp)

- [Aho-Corasick法](Aho_Corasick.hpp)（トライ木に、パターンが存在しない場合の後退辺を新たに付け加えたもの）

## ローリングハッシュ

文字列や配列をハッシュ値に置き換えるアルゴリズム。

- [ローリングハッシュ](Rolling_Hash.hpp)

## 接尾辞配列

文字列の全ての接尾辞を辞書順にソートしたものを記録するアルゴリズム。

- [接尾辞配列・高さ配列](Suffix_Array.hpp)

- [最長共通（連続）部分文字列](Longest_Common_Substring.hpp)（2 つの文字列の最長共通部分文字列を求める）

## run 列挙

文字列の run を全て列挙するアルゴリズム。

- [run 列挙](Run_Enumerate.hpp)
