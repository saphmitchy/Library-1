
// 形式的冪級数
// 計算量 加算・減算・微分・積分：O(n)、積・除算・inv・log・exp・pow・sqrt・Taylor Shift：O(n log(n))

// 定義
// df/dx := Σ[k=0,1,...]k([x^k]f(x))x^(k-1)
// ∫f(x)dx := Σ[k=0,1,...]([x^k]f(x))x^(k+1)/(k+1) 
// 1/f(x) := f(x)g(x) = 1 となるような g(x) ([x^0]f(x) = 0)
// log(1+f(x)) := Σ[k=0,1,...](-1)^(k+1)f(x)^k/k ([x^0]f(x) = 0)
// exp(f(x)) := Σ[k=0,1,...]f(x)^k/k! ([x^0]f(x) = 0)
// √f(x) := g(x)^2 = f(x) を満たす g(x)

// 概要
// 積：NTT
// inv・exp・sqrt：ニュートン法を用いた漸化式を立てて計算する。
// 除算：inv を用いて計算する。
// log：inv を用いて計算する。
// pow：log と exp を用いて計算する。
// Taylor Shift：係数を分解して畳み込みに持ち込む。

// verified with
// https://judge.yosupo.jp/problem/inv_of_formal_power_series
// https://judge.yosupo.jp/problem/log_of_formal_power_series
// https://judge.yosupo.jp/problem/exp_of_formal_power_series
// https://judge.yosupo.jp/problem/pow_of_formal_power_series
// https://judge.yosupo.jp/problem/division_of_polynomials
// https://judge.yosupo.jp/problem/polynomial_taylor_shift

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

template <typename T>
struct Formal_Power_Series : vector<T> {
    using NTT_ = Number_Theoretic_Transform<T>;
    using vector<T>::vector;

    Formal_Power_Series(const vector<T> &f) : vector<T>(f) {}

    // f(x) mod x^n
    Formal_Power_Series pre(int n) const {
        Formal_Power_Series ret(begin(*this), begin(*this) + min((int)this->size(), n));
        ret.resize(n, 0);
        return ret;
    }

    // f(1/x)x^{n-1}
    Formal_Power_Series rev(int n = -1) const {
        Formal_Power_Series ret = *this;
        if (n != -1) ret.resize(n, 0);
        reverse(begin(ret), end(ret));
        return ret;
    }

    void normalize() {
        while (!this->empty() && this->back() == 0) this->pop_back();
    }

    Formal_Power_Series operator-() const {
        Formal_Power_Series ret = *this;
        for (int i = 0; i < (int)ret.size(); i++) ret[i] = -ret[i];
        return ret;
    }

    Formal_Power_Series &operator+=(const T &t) {
        if (this->empty()) this->resize(1, 0);
        (*this)[0] += t;
        return *this;
    }

    Formal_Power_Series &operator+=(const Formal_Power_Series &g) {
        if (g.size() > this->size()) this->resize(g.size());
        for (int i = 0; i < (int)g.size(); i++) (*this)[i] += g[i];
        this->normalize();
        return *this;
    }

    Formal_Power_Series &operator-=(const T &t) {
        if (this->empty()) this->resize(1, 0);
        *this[0] -= t;
        return *this;
    }

    Formal_Power_Series &operator-=(const Formal_Power_Series &g) {
        if (g.size() > this->size()) this->resize(g.size());
        for (int i = 0; i < (int)g.size(); i++) (*this)[i] -= g[i];
        this->normalize();
        return *this;
    }

    Formal_Power_Series &operator*=(const T &t) {
        for (int i = 0; i < (int)this->size(); i++) (*this)[i] *= t;
        return *this;
    }

    Formal_Power_Series &operator*=(const Formal_Power_Series &g) {
        if (empty(*this) || empty(g)) {
            this->clear();
            return *this;
        }
        return *this = NTT_::convolve(*this, g);
    }

    Formal_Power_Series &operator/=(const T &t) {
        assert(t != 0);
        T inv = t.inverse();
        return *this *= inv;
    }

    // f(x) を g(x) で割った商
    Formal_Power_Series &operator/=(const Formal_Power_Series &g) {
        if (g.size() > this->size()) {
            this->clear();
            return *this;
        }
        int n = this->size(), m = g.size();
        return *this = (rev() * g.rev().inv(n - m + 1)).pre(n - m + 1).rev();
    }

    // f(x) を g(x) で割った余り
    Formal_Power_Series &operator%=(const Formal_Power_Series &g) { return *this -= (*this / g) * g; }

    // f(x)/x^k
    Formal_Power_Series &operator<<=(int k) {
        Formal_Power_Series ret(k, 0);
        ret.insert(end(ret), begin(*this), end(*this));
        return *this = ret;
    }

    // f(x)x^k
    Formal_Power_Series &operator>>=(int k) {
        Formal_Power_Series ret;
        ret.insert(end(ret), begin(*this) + k, end(*this));
        return *this = ret;
    }

    Formal_Power_Series operator+(const T &t) const { return Formal_Power_Series(*this) += t; }

    Formal_Power_Series operator+(const Formal_Power_Series &g) const { return Formal_Power_Series(*this) += g; }

    Formal_Power_Series operator-(const T &t) const { return Formal_Power_Series(*this) -= t; }

    Formal_Power_Series operator-(const Formal_Power_Series &g) const { return Formal_Power_Series(*this) -= g; }

    Formal_Power_Series operator*(const T &t) const { return Formal_Power_Series(*this) *= t; }

    Formal_Power_Series operator*(const Formal_Power_Series &g) const { return Formal_Power_Series(*this) *= g; }

    Formal_Power_Series operator/(const T &t) const { return Formal_Power_Series(*this) /= t; }

    Formal_Power_Series operator/(const Formal_Power_Series &g) const { return Formal_Power_Series(*this) /= g; }

    Formal_Power_Series operator%(const Formal_Power_Series &g) const { return Formal_Power_Series(*this) %= g; }

    Formal_Power_Series operator<<(int k) const { return Formal_Power_Series(*this) <<= k; }

    Formal_Power_Series operator>>(int k) const { return Formal_Power_Series(*this) >>= k; }

    // f(c)
    T val(const T &c) const {
        T ret = 0;
        for (int i = (int)this->size() - 1; i >= 0; i--) ret *= c, ret += (*this)[i];
        return ret;
    }

    // df/dx
    Formal_Power_Series derivative() const {
        if (empty(*this)) return *this;
        int n = this->size();
        Formal_Power_Series ret(n - 1);
        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * i;
        return ret;
    }

    // ∫f(x)dx
    Formal_Power_Series integral() const {
        if (empty(*this)) return *this;
        int n = this->size();
        vector<T> inv(n + 1, 0);
        inv[1] = 1;
        int mod = T::get_mod();
        for (int i = 2; i <= n; i++) inv[i] = -inv[mod % i] * T(mod / i);
        Formal_Power_Series ret(n + 1, 0);
        for (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] * inv[i + 1];
        return ret;
    }

    // 1/f(x) mod x^n (f[0] != 0)
    Formal_Power_Series inv(int n = -1) const {
        assert((*this)[0] != 0);
        if (n == -1) n = this->size();
        Formal_Power_Series ret(1, (*this)[0].inverse());
        for (int m = 1; m < n; m <<= 1) {
            Formal_Power_Series f = pre(2 * m), g = ret;
            f.resize(2 * m), g.resize(2 * m);
            NTT_::ntt(f), NTT_::ntt(g);
            Formal_Power_Series h(2 * m);
            for (int i = 0; i < 2 * m; i++) h[i] = f[i] * g[i];
            NTT_::intt(h);
            for (int i = 0; i < m; i++) h[i] = 0;
            NTT_::ntt(h);
            for (int i = 0; i < 2 * m; i++) h[i] *= g[i];
            NTT_::intt(h);
            for (int i = 0; i < m; i++) h[i] = 0;
            ret -= h;
        }
        ret.resize(n);
        return ret;
    }

    // log(f(x)) mod x^n (f[0] = 1)
    Formal_Power_Series log(int n = -1) const {
        assert((*this)[0] == 1);
        if (n == -1) n = this->size();
        Formal_Power_Series ret = (derivative() * inv(n)).pre(n - 1).integral();
        ret.resize(n);
        return ret;
    }

    // exp(f(x)) mod x^n (f[0] = 0)
    Formal_Power_Series exp(int n = -1) const {
        assert((*this)[0] == 0);
        if (n == -1) n = this->size();
        vector<T> inv(2 * n + 1, 0);
        inv[1] = 1;
        int mod = T::get_mod();
        for (int i = 2; i <= 2 * n; i++) inv[i] = -inv[mod % i] * T(mod / i);

        auto inplace_integral = [inv](Formal_Power_Series &f) {
            if (empty(f)) return;
            int n = f.size();
            f.insert(begin(f), 0);
            for (int i = 1; i <= n; i++) f[i] *= inv[i];
        };

        auto inplace_derivative = [](Formal_Power_Series &f) {
            if (empty(f)) return;
            int n = f.size();
            f.erase(begin(f));
            for (int i = 0; i < n - 1; i++) f[i] *= T(i + 1);
        };

        Formal_Power_Series ret{1, this->size() > 1 ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
        for (int m = 2; m < n; m *= 2) {
            auto y = ret;
            y.resize(2 * m);
            NTT_::ntt(y);
            z1 = z2;
            Formal_Power_Series z(m);
            for (int i = 0; i < m; i++) z[i] = y[i] * z1[i];
            NTT_::intt(z);
            fill(begin(z), begin(z) + m / 2, 0);
            NTT_::ntt(z);
            for (int i = 0; i < m; i++) z[i] *= -z1[i];
            NTT_::intt(z);
            c.insert(end(c), begin(z) + m / 2, end(z));
            z2 = c, z2.resize(2 * m);
            NTT_::ntt(z2);
            Formal_Power_Series x(begin(*this), begin(*this) + min((int)this->size(), m));
            inplace_derivative(x);
            x.resize(m, 0);
            NTT_::ntt(x);
            for (int i = 0; i < m; i++) x[i] *= y[i];
            NTT_::intt(x);
            x -= ret.derivative(), x.resize(2 * m);
            for (int i = 0; i < m - 1; i++) x[m + i] = x[i], x[i] = 0;
            NTT_::ntt(x);
            for (int i = 0; i < 2 * m; i++) x[i] *= z2[i];
            NTT_::intt(x);
            x.pop_back();
            inplace_integral(x);
            for (int i = m; i < min((int)this->size(), 2 * m); i++) x[i] += (*this)[i];
            fill(begin(x), begin(x) + m, 0);
            NTT_::ntt(x);
            for (int i = 0; i < 2 * m; i++) x[i] *= y[i];
            NTT_::intt(x);
            ret.insert(end(ret), begin(x) + m, end(x));
        }
        ret.resize(n);
        return ret;
    }

    // f(x)^k mod x^n
    Formal_Power_Series pow(long long k, int n = -1) const {
        if (n == -1) n = this->size();
        int m = this->size();
        for (int i = 0; i < m; i++) {
            if ((*this)[i] == 0) continue;
            T inv = (*this)[i].inverse();
            Formal_Power_Series g(m - i, 0);
            for (int j = i; j < m; j++) g[j - i] = (*this)[j] * inv;
            g = (g.log(n) * k).exp(n) * ((*this)[i].pow(k));
            Formal_Power_Series ret(n, 0);
            if (i > 0 && k > n / i) return ret;
            long long d = i * k;
            for (int j = 0; j + d < n && j < g.size(); j++) ret[j + d] = g[j];
            return ret;
        }
        Formal_Power_Series ret(n, 0);
        if (k == 0) ret[0] = 1;
        return ret;
    }

    // √f(x) mod x^n (存在しなければ空)
    Formal_Power_Series sqrt(int n = -1) const {
        if (n == -1) n = this->size();
        int mod = T::get_mod();

        auto sqrt_mod = [mod](const T &a) {
            if (mod == 2) return a;
            int s = mod - 1, t = 0;
            while (s % 2 == 0) s /= 2, t++;
            T root = 2;
            while (root.pow((mod - 1) / 2) == 1) root++;
            T x = a.pow((s + 1) / 2);
            T u = root.pow(s);
            T y = x * x * a.inverse();
            while (y != 1) {
                int k = 0;
                T z = y;
                while (z != 1) k++, z *= z;
                for (int i = 0; i < t - k - 1; i++) u *= u;
                x *= u, u *= u, y *= u;
                t = k;
            }
            return x;
        };

        if ((*this)[0] == 0) {
            for (int i = 1; i < (int)this->size(); i++) {
                if ((*this)[i] != 0) {
                    if (i & 1) return {};
                    if ((*this)[i].pow((mod - 1) / 2) != 1) return {};
                    if (n <= i / 2) break;
                    return ((*this) >> i).sqrt(n - i / 2) << (i / 2);
                }
            }
            return Formal_Power_Series(n, 0);
        }
        if ((*this)[0].pow((mod - 1) / 2) != 1) return {};
        T tw = T(2).inverse();
        Formal_Power_Series ret{sqrt_mod((*this)[0])};
        for (int m = 1; m < n; m *= 2) {
            Formal_Power_Series g = (*this).pre(m * 2) * ret.inv(m * 2);
            g.resize(2 * m);
            ret = (ret + g) * tw;
        }
        ret.resize(n);
        return ret;
    }

    // f(x+c)
    Formal_Power_Series Taylor_shift(T c) const {
        int n = this->size();
        vector<T> ifac(n, 1);
        Formal_Power_Series f(n), g(n);
        for (int i = 0; i < n; i++) {
            f[n - 1 - i] = (*this)[i] * ifac[n - 1];
            if (i < n - 1) ifac[n - 1] *= i + 1;
        }
        ifac[n - 1] = ifac[n - 1].inverse();
        for (int i = n - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i;
        T pw = 1;
        for (int i = 0; i < n; i++) {
            g[i] = pw * ifac[i];
            pw *= c;
        }
        f *= g;
        Formal_Power_Series b(n);
        for (int i = 0; i < n; i++) b[i] = f[n - 1 - i] * ifac[i];
        return b;
    }
};
