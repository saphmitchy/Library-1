#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/FPS.hpp"

template<int mod, int primitive_root>
struct Kitamasa{
    using T = Mod_Int<mod>;
    using FPS = Formal_Power_Series<mod, primitive_root>;

    //d項間線形漸化式 a[n] = c[1]*a[n-1]+c[2]*a[n-2]+・・・+c[d]*a[n-d]
    const vector<T> a, c;
    const int d;
    //f(x) := x^d-c[1]*x^(d-1)-・・・-c[d-1]*x-c[d]
    vector<T> f;

    Kitamasa(const vector<T> &a, const vector<T> &c) : a(a), c(c), d(a.size()){
        f.resize(d+1);
        f[d] = 1;
        for(int i = 1; i <= d; i++) f[d-i] = -c[i];
    }

    vector<T> mul(const vector<T> &p, const vector<T> &q) const{ //p(x)*q(x)をf(x)で割った余り
        FPS ret = FPS(p)*FPS(q);
        ret %= FPS(f);
        return ret;
    }

    vector<T> pow(vector<T> p, long long n) const{ //p(x)^nをf(x)で割った余り
        vector<T> ret(d, 0);
        ret[0] = 1;
        while(n){
            if(n&1) ret = mul(ret, p);
            p = mul(p, p), n >>= 1;
        }
        return ret;
    }

    T operator [] (long long n) const{ //a[n](0-indexed)
        vector<T> x(d+1, 0);
        x[1] = 1, x = pow(x, n);
        x.resize(d);
        T ret = 0;
        for(int i = 0; i < d; i++) ret += x[i]*a[i];
        return ret;
    }
};
