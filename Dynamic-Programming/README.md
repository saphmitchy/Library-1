# 動的計画法(DP)

## 典型的なDP問題

- [各種ナップザック問題](https://github.com/tokusakurai/dynamic-programming/blob/main/Knapsack.cpp) (01ナップザック問題、個数制限なしナップザック問題、個数制限付きナップザック問題)

- [最長共通部分列](https://github.com/tokusakurai/dynamic-programming/blob/main/LCS.cpp)

- [編集距離](https://github.com/tokusakurai/dynamic-programming/blob/main/Edit_Distance.cpp)

- [最長増加部分列](https://github.com/tokusakurai/dynamic-programming/blob/main/LIS.cpp) (DP配列の再利用で計算量が落ちるインラインDP)

- [分割数テーブル](https://github.com/tokusakurai/dynamic-programming/blob/main/Partition_Number.cpp)

- [最大長方形](https://github.com/tokusakurai/dynamic-programming/blob/main/Largest_Rectangle.cpp)

- [スライド最小値](https://github.com/tokusakurai/dynamic-programming/blob/main/Slide_Min.cpp)

## 高速ゼータ・メビウス・アダマール変換
長さが2べきであるような配列に対する各種の変換。応用としてAND・OR・XOR畳み込みがある。

- [高速ゼータ・メビウス・アダマール変換](https://github.com/tokusakurai/dynamic-programming/blob/main/Zeta_Mobius_Hadamard.cpp)

## Convex-Hull-Trick
直線の追加クエリ(ただし、追加する直線の傾きは単調)と、追加された直線群におけるある点での値の最小値(または最大値)クエリを扱える。

- [Convex-Hull-Trick](https://github.com/tokusakurai/dynamic-programming/blob/main/Convex_Hull_Trick.cpp)

## Moのアルゴリズム
配列が静的であり、区間クエリの先読みが出来る場合、クエリを適切にソートすることで区間の伸縮によって高速にクエリを処理できる。

- [Moのアルゴリズム(雛形)](https://github.com/tokusakurai/Dynamic-Programming/blob/main/Mo_Template.cpp)

- [Moのアルゴリズム(例)](https://github.com/tokusakurai/Dynamic-Programming/blob/main/Mo_Example.cpp) (区間内の要素の種類数を扱える)