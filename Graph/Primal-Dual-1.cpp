
//Primal-Dual法(最小費用流)
//計算量 O(F*E*V)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Min_Cost_Flow{
    struct edge{
        int to; T cap, cost; int rev;
        edge(int to, T cap, T cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {} 
    };

    vector<vector<edge>> es;
    vector<T> d;
    vector<int> pre_v, pre_e;
    const T INF_T;
    const int n;

    Min_Cost_Flow(int n) : es(n), d(n), pre_v(n), pre_e(n), INF_T(numeric_limits<T>::max()), n(n) {}

    void add_edge(int from, int to, T cap, T cost){
        es[from].emplace_back(to, cap, cost, (int)es[to].size());
        es[to].emplace_back(from, 0, -cost, (int)es[from].size()-1);
    }

    void bellman_ford(int s){
        fill(begin(d), end(d), INF_T);
        d[s] = 0;
        while(true){
            bool update = false;
            for(int i = 0; i < n; i++){
                if(d[i] == INF_T) continue;
                for(int j = 0; j < (int)es[i].size(); j++){
                    edge &e = es[i][j];
                    if(e.cap > 0 && d[i]+e.cost < d[e.to]){
                        d[e.to] = d[i]+e.cost;
                        pre_v[e.to] = i, pre_e[e.to] = j;
                        update = true;
                    }
                }
            }
            if(!update) break;
        }
    }

    T min_cost_flow(int s, int t, T flow){
        T ret = 0;
        while(flow > 0){
            bellman_ford(s);
            if(d[t] == INF_T) return -1;
            T f = flow;
            for(int now = t; now != s; now = pre_v[now]){
                f = min(f, es[pre_v[now]][pre_e[now]].cap);
            }
            ret += f*d[t], flow -= f;
            for(int now = t; now != s; now = pre_v[now]){
                edge &e = es[pre_v[now]][pre_e[now]];
                e.cap -= f, es[now][e.rev].cap += f;
            }
        }
        return ret;
    }
};

int main(){
    int V, E, F; cin >> V >> E >> F;

    Min_Cost_Flow<int> G(V);
    for(int i = 0; i < E; i++){
        int u, v, c, d; cin >> u >> v >> c >> d;
        G.add_edge(u, v, c, d);
    }
    
    cout << G.min_cost_flow(0, V-1, F) << '\n';
}
