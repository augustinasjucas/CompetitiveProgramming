#include <bits/stdc++.h>
#pragma GCC optimize("O2")
#pragma GCC target("avx2")
using namespace std;
const int dydis = 3e5 + 1;
long long fen1[dydis] = {};
void upd1(int p, int x) {
    for (int i = p; i < dydis; i += i&(-i))
        fen1[i] += x;
}
long long sum1 (int p) {
    long long ret = 0;
    for (int i = p; i > 0; i -= i&(-i))
        ret += fen1[i];
    return ret;
}
long long q1(int l, int r){
    return sum1(r) - (l == 0 ? 0ll : sum1(l-1));
}

long long fen2[dydis] = {};
void upd2(int p, int x) {
    for (int i = p; i < dydis; i += i&(-i))
        fen2[i] += x;
}
long long sum2 (int p) {
    long long ret = 0;
    for (int i = p; i > 0; i -= i&(-i))
        ret += fen2[i];
    return ret;
}
long long q2(int l, int r){
    return sum2(r) - (l == 0 ? 0ll : sum2(l-1));
}
struct seg_tree {
    int l[dydis * 2], r[dydis * 2];
    long long val[dydis * 2], lazy[dydis * 2];
    int n = dydis;
    int dbInd = 0;
    void build(int v = 1){
        if(v == 1){
            dbInd = 0;
        }
        if(v >= n){
            l[v] = r[v] = dbInd++;
        }else{
            build(v * 2);
            build(v * 2 + 1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
        val[v] = lazy[v] = 0;
    }
    void apply(int v){
        val[v] += 1ll * (r[v] - l[v] + 1) * lazy[v];
        if(v < n){
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v]; 
        }
        lazy[v] = 0; 
    }
    long long fSum(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            return val[v];
        }else if(R < l[v] || r[v] < L){
            return 0;
        }else{
            return fSum(v*2, L, R) + fSum(v*2+1, L, R);
        }
    }
    void change(int v, int L, int R, int x){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            lazy[v] += x;
            apply(v);
        }else if(R < l[v] || r[v] < L){
            return ;
        }else{
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = val[v*2] + val[v*2+1];
        }
    }
    seg_tree(){
        build();
    }
};
vector<int> mas;
seg_tree sum;
long long l, r;
vector<long long> calc(vector<int> a){
    vector<long long> ret;
    for(int i = 0; i < (int) a.size(); i++){
        long long pl = 0;
        for(int j = 0; j < dydis; j++){
            if(1ll * j * a[i] > dydis) break;
            l = j * a[i];
            r = (j + 1) * a[i] - 1;
            r = min(r, 1ll * dydis-1);
            pl += q1(l, r) - (l * q2(l, r));
        }
        upd1(a[i], a[i]);
        upd2(a[i], 1);
        ret.push_back((ret.size() ? ret.back() : 0) + pl);
    }
    return ret;
}
vector<long long> calc2(vector<int> a){

    vector<long long> ret;
    for(int i = 0; i < (int) a.size(); i++){
        ret.push_back(sum.fSum(1, 0, a[i]) + (ret.size() ? ret.back() : 0ll));
        if(i == a.size()-1) break;
        sum.change(1, 1, dydis-1, 1);
        for(int j = 0; j < dydis; j++){
            if(1ll * j * a[i] >= dydis) break;
            l = j * a[i];
            r = (j + 1) * a[i] - 1;
            if(j != 0) {
                sum.change(1, l, l, -a[i]);
            }
        }
    }
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    
    auto prm = calc(mas); 
    auto ant = calc2(mas);
    
    for(int i = 0; i < n; i++){
        cout << prm[i] + ant[i] << " ";
    }
    return 0;
}
