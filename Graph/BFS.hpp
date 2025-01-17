
// BFS
// 計算量 O(n+m)

// 概要
// 始点から近い順に最短路を確定させる。
// queue を用いる。
// 辺のコストは全て 1 なので queue に入れるだけで始点から近い順が保たれる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct BFS {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> d;
    vector<int> pre_v, pre_e;
    const int INF_T = (1 << 30) - 1;
    const int n;
    int m;

    BFS(int n) : es(n), d(n), pre_v(n), pre_e(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int shortest_path(int s, int t = 0) {
        fill(begin(d), end(d), INF_T);
        queue<int> que;
        d[s] = 0;
        que.emplace(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                if (d[i] + 1 < d[e.to]) {
                    d[e.to] = d[i] + 1;
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    que.push(e.to);
                }
            }
        }
        return d[t];
    }

    vector<int> restore_path(int s, int t, bool use_id = false) {
        if (d[t] == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(use_id ? pre_e[now] : now);
        if (!use_id) ret.push_back(s);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
