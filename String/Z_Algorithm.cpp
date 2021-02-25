
//z-alogorithm(文字列SとSのi文字目(0-indexed)以降の最長共通接頭辞の長さを記録した配列を求める)
//計算量 O(|S|)

//verified with
//https://atcoder.jp/contests/jag2013summer-day3/tasks/icpc2013summer_day3_h
//https://judge.yosupo.jp/problem/zalgorithm

#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<int> z_algorithm(const T &s){
    int n = s.size();
    vector<int> ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while(i < n){
        while(i+j < n && s[j] == s[i+j]) j++;
        ret[i] = j;
        if(j == 0) {i++; continue;}
        int k = 1;
        while(i+k < n && k+ret[k] < j) ret[i+k] = ret[k], k++;
        i += k, j -= k;
    }
    return ret;
}

int main(){
    string S; cin >> S;

    for(auto &e: z_algorithm(S)) cout << e << ' ';
    cout << '\n';
}