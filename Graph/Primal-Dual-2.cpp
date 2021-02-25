
//sからtへの流量fのフローの最小費用流を求める(最初のグラフに負の閉路が存在しない場合)
//計算量 O(E*V+F*E*log(V))、初期状態でコストが負の辺が存在しない場合:O(F*E*log(V))

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
    vector<T> d, h;
    vector<int> pre_v, pre_e;
    const T INF_T;
    const int n;

    Min_Cost_Flow(int n) : es(n), d(n), h(n), pre_v(n), pre_e(n), INF_T(numeric_limits<T>::max()), n(n) {}

    void add_edge(int from, int to, T cap, T cost){
        es[from].emplace_back(to, cap, cost, (int)es[to].size());
        es[to].emplace_back(from, 0, -cost, (int)es[from].size()-1);
    }

    void bellman_ford(int s){
        fill(begin(h), end(h), INF_T);
        h[s] = 0;
        while(true){
            bool update = false;
            for(int i = 0; i < n; i++){
                if(h[i] == INF_T) continue;
                for(auto &e: es[i]){
                    if(e.cap > 0 && h[i]+e.cost < h[e.to]){
                        h[e.to] = h[i]+e.cost;
                        update = true;
                    }
                }
            }
            if(!update) break;
        }
    }

    void dijkstra(int s){
        fill(begin(d), end(d), INF_T);
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P> > que;
        que.emplace(d[s] = 0, s);
        while(!que.empty()){
            auto [p, i] = que.top(); que.pop();
            if(p > d[i]) continue;
            for(int j = 0; j < es[i].size(); j++){
                edge &e = es[i][j];
                if(e.cap > 0 && d[i]+e.cost+h[i]-h[e.to] < d[e.to]){
                    d[e.to] = d[i]+e.cost+h[i]-h[e.to];
                    pre_v[e.to] = i, pre_e[e.to] = j;
                    que.emplace(d[e.to], e.to);
                }
            }
        }
    }

    T min_cost_flow(int s, int t, T flow){
        T ret = 0;
        bellman_ford(s); //初期状態でコストが負の辺が存在しない場合は行わなくて良い
        while(flow > 0){
            dijkstra(s);
            if(d[t] == INF_T) return -1;
            for(int i = 0; i < n; i++){
                if(h[i] == INF_T || d[i] == INF_T) h[i] = INF_T;
                else h[i] += d[i];
            }
            T f = flow;
            for(int now = t; now != s; now = pre_v[now]){
                f = min(f, es[pre_v[now]][pre_e[now]].cap);
            }
            ret += f*h[t], flow -= f;
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