
// モノイドの例

// 定義
// (M,*,e) がモノイドであるとは
// 任意の a,b,c ∈ M について a*(b*c) = (a*b)*c (結合律)
// 任意の a ∈ M について a*e = e*a = a
// を満たすことである。

#pragma once
#include <bits/stdc++.h>
using namespace std;

// sum
template <typename T>
struct Plus_Monoid {
    using V = T;
    static constexpr V merge(V l, V r) { return l + r; };
    static const V id;
};

template <typename T>
const T Plus_Monoid<T>::id = 0;

// min
template <typename T>
struct Min_Monoid {
    using V = T;
    static constexpr V merge(V l, V r) { return min(l, r); };
    static const V id;
};

template <typename T>
const T Min_Monoid<T>::id = numeric_limits<T>::max();

// max
template <typename T>
struct Max_Monoid {
    using V = T;
    static constexpr V merge(V l, V r) { return max(l, r); };
    static const V id;
};

template <typename T>
const T Max_Monoid<T>::id = numeric_limits<T>::min();

// 代入
template <typename T>
struct Update_Monoid {
    using V = T;
    static constexpr V merge(V l, V r) {
        if (l == id) return r;
        if (r == id) return l;
        return r;
    }
    static const V id;
};

template <typename T>
const T Update_Monoid<T>::id = numeric_limits<T>::max();

// min count (T：最大値の型、S：個数の型)
template <typename T, typename S>
struct Min_Count_Monoid {
    using V = pair<T, S>;
    static constexpr V merge(V l, V r) {
        if (l.first < r.first) return l;
        if (l.first > r.first) return r;
        return V(l.first, l.second + r.second);
    }
    static const V id;
};

template <typename T, typename S>
const pair<T, S> Min_Count_Monoid<T, S>::id = make_pair(numeric_limits<T>::max(), 0);

// max count (T：最大値の型、S：個数の型)
template <typename T, typename S>
struct Max_Count_Monoid {
    using V = pair<T, S>;
    static constexpr V merge(V l, V r) {
        if (l.first > r.first) return l;
        if (l.first < r.first) return r;
        return V(l.first, l.second + r.second);
    }
    static const V id;
};

template <typename T, typename S>
const pair<T, S> Max_Count_Monoid<T, S>::id = make_pair(numeric_limits<T>::min(), 0);

// 一次関数 ax+b の合成 (左から順に作用)
template <typename T>
struct Affine_Monoid {
    using V = pair<T, T>;
    static constexpr V merge(V l, V r) { return V(l.first * r.first, l.second * r.first + r.second); };
    static const V id;
};

template <typename T>
const pair<T, T> Affine_Monoid<T>::id = make_pair(1, 0);

// モノイドの直積
template <typename Monoid_1, typename Monoid_2>
struct Cartesian_Product_Monoid {
    using V1 = typename Monoid_1::V;
    using V2 = typename Monoid_2::V;
    using V = pair<V1, V2>;
    static constexpr V merge(V l, V r) { return V(Monoid_1::merge(l.first, r.first), Monoid_2::merge(l.second, r.second)); }
    static const V id;
};

template <typename Monoid_1, typename Monoid_2>
const pair<typename Monoid_1::V, typename Monoid_2::V> Cartesian_Product_Monoid<Monoid_1, Monoid_2>::id = make_pair(Monoid_1::id, Monoid_2::id);

// range add range min
template <typename T>
struct Min_Plus_Acted_Monoid {
    using Monoid = Min_Monoid<T>;
    using Operator = Plus_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(M l, O r) { return l + r; };
};

// range add range max
template <typename T>
struct Max_Plus_Acted_Monoid {
    using Monoid = Max_Monoid<T>;
    using Operator = Plus_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(M l, O r) { return l + r; };
};

// range add range min count (T：最小値の型、S：個数の型)
template <typename T, typename S>
struct Min_Count_Add_Acted_Monoid {
    using Monoid = Min_Count_Monoid<T, S>;
    using Operator = Plus_Monoid<T>;
    using M = pair<T, S>;
    using O = T;
    static constexpr M merge(M l, O r) { return make_pair(l.first + r, l.second); };
};

// range add range max count (T：最大値の型、S：個数の型)
template <typename T, typename S>
struct Max_Count_Add_Acted_Monoid {
    using Monoid = Max_Count_Monoid<T, S>;
    using Operator = Plus_Monoid<T>;
    using M = pair<T, S>;
    using O = T;
    static constexpr M merge(M l, O r) { return make_pair(l.first + r, l.second); };
};

// range add range sum
template <typename T>
struct Plus_Plus_Monoid {
    using Monoid = Cartesian_Product_Monoid<Plus_Monoid<T>, Plus_Monoid<int>>;
    using Operator = Plus_Monoid<T>;
    using M = pair<T, int>;
    using O = T;
    static constexpr M merge(M l, O r) { return M(l.first + r * l.second, l.second); }
};

// range update range sum
template <typename T>
struct Plus_Update_Monoid {
    using Monoid = Cartesian_Product_Monoid<Plus_Monoid<T>, Plus_Monoid<int>>;
    using Operator = Update_Monoid<T>;
    using M = pair<T, int>;
    using O = T;
    static constexpr M merge(M l, O r) { return M(r * l.second, l.second); }
};

// range update range min
template <typename T>
struct Min_Update_Monoid {
    using Monoid = Min_Monoid<T>;
    using Operator = Update_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(M l, M r) { return r == Operator::id ? l : r; }
};

// range update range max
template <typename T>
struct Max_Update_Monoid {
    using Monoid = Max_Monoid<T>;
    using Operator = Update_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(M l, M r) { return r == Operator::id ? l : r; }
};

// range affine range sum
template <typename T>
struct Plus_Affine_Acted_Monoid {
    using Monoid = Cartesian_Product_Monoid<Plus_Monoid<T>, Plus_Monoid<T>>;
    using Operator = Affine_Monoid<T>;
    using M = pair<T, T>;
    using O = pair<T, T>;
    static constexpr M merge(M l, O r) { return M(r.first * l.first + r.second * l.second, l.second); };
};
