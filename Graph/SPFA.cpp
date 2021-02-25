
//Shortest-Path-Fast-Algorithm(負辺があっても動作する単一始点最短路)
//計算量 O(E*V)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Weighted_Graph{
    struct edge{
        int to; T cost; int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<T> d;
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), d(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T shortest_path_faster_algorithm(int s, int t = 0){
        fill(begin(d), end(d), INF_T);
        queue<int> que;
        vector<bool> inque(n, false);
        vector<int> cnt(n, 0);
        que.emplace(s), inque[s] = true, ++cnt[s], d[s] = 0;
        while(!que.empty()){
            int i = que.front(); que.pop();
            inque[i] = false;
            for(auto &e: es[i]){
                if(d[i]+e.cost < d[e.to]){
                    d[e.to] = d[i]+e.cost;
                    if(!inque[e.to]){
                        if(++cnt[e.to] >= n) return -INF_T; //sから到達できる負閉路あり
                        que.emplace(e.to), inque[e.to] = true;
                    }
                }
            }
        }
        return d[t];
    }
};

int main(){
    int V, E, s; cin >> V >> E >> s;

    Weighted_Graph<int, true> G(V);

    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    if(G.shortest_path_faster_algorithm(s) == -(INT_MAX/2)) cout << "NEGATIVE CYCLE\n";
    else{
        for(auto &e: G.d){
            if(e == (INT_MAX)/2) cout << "INF\n";
            else cout << e << '\n';
        }
    } 
}