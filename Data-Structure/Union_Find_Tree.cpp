
//重み付きUnion-Find-木(等式差分制約を扱える)
//計算量 構築:O(N)、併合・結合判定・サイズ・ポテンシャル取得:O(α(N))
//空間計算量 O(N)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=ja
//https://atcoder.jp/contests/atc001/tasks/unionfind_a
//https://judge.yosupo.jp/problem/unionfind

#include <bits/stdc++.h>
using namespace std;

struct Union_Find_Tree{
    vector<int> data;
    const int n;
    
    Union_Find_Tree(int n) : data(n, -1), n(n) {}
    
    int root(int x){ //xの根
        if(data[x] < 0) return x;
        return data[x] = root(data[x]);
    }

    int operator [] (int i) {return root(i);}
    
    bool unite(int x, int y){ //xの属する集合とyの属する集合を併合(返り値は併合が行われたかどうか)
        x = root(x), y = root(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y], data[y] = x;
        return true;
    }
    
    int size(int x) {return -data[root(x)];} //xの属する集合の要素数
    
    bool same(int x, int y) {return root(x) == root(y);} //xとyの属する集合が同じかどうか
    
    void clear() {fill(begin(data), end(data), -1);}
};

int main(){
    int N, Q; cin >> N >> Q;

    Union_Find_Tree uf(N);
    
    while(Q--){
        int q, x, y; cin >> q >> x >> y;
        if(q == 0) uf.unite(x, y);
        else cout << uf.same(x, y) << '\n';
    }
}
