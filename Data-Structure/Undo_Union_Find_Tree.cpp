
//Undo可能Union-Find木
//計算量 構築:O(N)、併合・結合判定・サイズ:O(log(N))、undo:O(1)
//空間計算量 O(N)

//verified with
//https://codeforces.com/contest/1445/problem/E

#include <bits/stdc++.h>
using namespace std;

struct Undo_Union_Find_Tree{
    vector<int> data;
    stack<pair<int, int>> history; //data配列の変更を記録
    const int n;
    
    Undo_Union_Find_Tree(int n) : data(n, -1), n(n) {}
    
    int root(int x) const{
        if(data[x] < 0) return x;
        return root(data[x]);
    }

    int operator [] (int i) const {return root(i);}
    
    bool unite(int x, int y){
        x = root(x), y = root(y);
        history.emplace(x, data[x]), history.emplace(y, data[y]);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y], data[y] = x;
        return true;
    }
    
    int size(int x) const {return -data[root(x)];}
    
    bool same(int x, int y) const {return root(x) == root(y);}

    void undo(int k){ //直前k回分のUnion操作をなかったことにする
        k <<= 1;
        while(k--){
            data[history.top().first] = history.top().second;
            history.pop();
        }
    }
    
    void clear() {while(!history.empty()) undo(1);}
};

int main(){
    int N, Q; cin >> N >> Q;

    Undo_Union_Find_Tree uf(N);
    
    while(Q--){
        int q, x, y; cin >> q >> x >> y;
        if(q == 0) uf.unite(x, y);
        else if(q == 1) cout << uf.same(x, y) << '\n';
        else uf.undo(1);
    }
}
