
//プリム法(最小全域木)
//計算量 O(E*log(V))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Weighted_Graph{
    struct edge{
        int to; T cost; int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T prim(){
        vector<T> mincost(n, INF_T);
        vector<bool> used(n, false);
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(mincost[0] = 0, 0);
        T ret = 0;
        while(!que.empty()){
            auto [p, i] = que.top(); que.pop();
            if(used[i]) continue;
            used[i] = true, ret += p;
            for(auto &e: es[i]){
                if(!used[e.to] && e.cost < mincost[e.to]){
                    que.emplace(mincost[e.to] = e.cost, e.to);
                }
            }
        }
        for(int i = 0; i < n; i++) if(!used[i]) return INF_T;
        return ret;
    }
};

int main(){
    int V, E; cin >> V >> E;

    Weighted_Graph<int> G(V);

    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    cout << G.prim() << '\n';
}
