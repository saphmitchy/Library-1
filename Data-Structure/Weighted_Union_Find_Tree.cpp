
//重み付きUnion-Find-木(等式差分制約を扱えるUnion-Find-木)
//計算量 構築:O(N)、併合:O(α(N))、結合判定:O(α(N))、サイズ:O(α(N))、ポテンシャル取得:O(α(N))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
//https://atcoder.jp/contests/arc090/tasks/arc090_b

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Weighted_Union_Find_Tree{
    vector<int> data;
    vector<T> ws;
    const int n;

    Weighted_Union_Find_Tree(int n) : data(n, -1), ws(n, 0), n(n) {}

    int root(int x){
        if(data[x] < 0) return x;
        int par = root(data[x]);
        ws[x] += ws[data[x]];
        return data[x] = par;
    }

    int operator [] (int i) {return root(i);}

    T weight(int x){
        root(x);
        return ws[x];
    }

    bool unite(int x, int y, T w){ //weight(y)-weight(x) = w
        w += weight(x), w -= weight(y);
        x = root(x), y = root(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y), w *= -1;
        data[x] += data[y], data[y] = x;
        ws[y] = w;
        return true;
    }

    T diff(int x, int y) {return weight(y)-weight(x);}

    int size(int x) {return -data[root(x)];}
    
    bool same(int x, int y) {return root(x) == root(y);}
    
    void clear(){
        fill(begin(data), end(data), -1), fill(begin(ws), end(ws), 0);
    }
};

int main(){
    int N, Q; cin >> N >> Q;

    Weighted_Union_Find_Tree<int> uf(N);
    
    while(Q--){
        int q, x, y; cin >> q >> x >> y;
        if(q == 0){
            int w; cin >> w;
            uf.unite(x, y, w);
        }
        else if(uf.same(x, y)) cout << uf.diff(x, y) << '\n';
        else cout << '?' << '\n';
    }
}
