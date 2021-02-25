
//Warshall_Floyed法(負辺があっても動作する全点対最短路)
//計算量 O(V^3)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Table{
    vector<vector<T>> es;
    const T INF_T;
    const int n;

    inline const vector<T> &operator [] (int k) const{
        return es[k];
    }

    inline vector<T> &operator [] (int k){
        return es[k];
    }

    Table(int n) : es(n), INF_T(numeric_limits<T>::max()/2), n(n){
        for(int i = 0; i < n; i++) es[i].assign(n, INF_T);
        for(int i = 0; i < n; i++) es[i][i] = 0;
    }

    void add_edge(int from, int to, T cost = 1){
        es[from][to] = min(es[from][to], cost);
        if(!directed) es[to][from] = min(es[to][from], cost);
    }

    void warshall_floyd(){
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(es[i][k] == INF_T || es[k][j] == INF_T) continue;
                    es[i][j] = min(es[i][j], es[i][k]+es[k][j]);
                }
            }
        }
    }
};

int main(){
    int V, E; cin >> V >> E;

    Table<long long, true> G(V);

    for(int i = 0; i < E; i++){
        int u, v; long long c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    G.warshall_floyd();

    for(int i = 0; i < V; i++){
        if(G[i][i] < 0){
            cout << "NEGATIVE CYCLE\n"; return 0;
        }
    }

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(G[i][j] == LLONG_MAX/2) cout << "INF";
            else cout << G[i][j];
            cout << (j == V-1? '\n' : ' ');
        }
    }
}