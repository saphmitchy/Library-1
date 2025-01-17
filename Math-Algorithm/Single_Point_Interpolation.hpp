
// ラグランジュ補間（1 点）
// 計算量 O(n)

// 概要
// n-1 次以下の多項式 f(x) について f(0),f(1),...,f(n-1) の値が与えられたときに、与えられた 1 点 c について f(c) を求める。
// ラグランジュ補間をすると、
// f(c) = Σ[0<=i<n] f(i)Π[j!=i](c-j)/(i-j)
// であるから、階乗の逆数と x-i の累積積を左右から求めることで高速化する。

// verified with
// https://atcoder.jp/contests/arc033/tasks/arc033_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T single_point_interpolation(const vector<T> &ys, T c) {
    int n = ys.size();
    vector<T> ifac(n);
    ifac[n - 1] = 1;
    for (int i = 1; i < n; i++) ifac[n - 1] *= i;
    ifac[n - 1] = T(1) / ifac[n - 1];
    for (int i = n - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i;
    vector<T> L(n + 1, 1), R(n + 1, 1);
    for (int i = 0; i < n; i++) L[i + 1] = L[i] * (c - i);
    for (int i = n - 1; i >= 0; i--) R[i] = R[i + 1] * (c - i);
    T ret = 0;
    for (int i = 0; i < n; i++) {
        T tmp = ys[i] * L[i] * R[i + 1] * ifac[i] * ifac[n - 1 - i];
        ret += ((n - 1 - i) & 1 ? -tmp : tmp);
    }
    return ret;
}
