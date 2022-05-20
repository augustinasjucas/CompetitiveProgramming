#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct seg_tree {
    vector<int> l, r, val;
    int n;
    int dbInd = 0;
    void build (int v = 1){
        if(v >= n){
            l[v] = r[v] = dbInd++;
        }else {
            build(v*2);
            build(v*2+1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
    }
    seg_tree(int dd){
        n = dd;
        l.resize(dd * 2 + 1);
        r.resize(dd * 2 + 1);
        val.resize(dd * 2 + 1);
        build();
    }
    void change(int v, int L, int R, int x){
        if(L <= l[v] && r[v] <= R){
            val[v] += x;
        }else if(R < l[v] || r[v] < L){
            return ;
        }else{
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = val[v*2] + val[v*2+1];
        }
    }
    void keisk(int v, int L, int R, int x){
        if(L <= l[v] && r[v] <= R){
            val[v] = x;
        }else if(R < l[v] || r[v] < L){
            return ;
        }else{
            keisk(v*2, L, R, x);
            keisk(v*2+1, L, R, x);
            val[v] = val[v*2] + val[v*2+1];
        }
    }
    int getSum(int v, int L, int R){
        if(L <= l[v] && r[v] <= R){
            return val[v];
        }else if(R < l[v] || r[v] < L){
            return 0;
        }else{
            return getSum(v*2, L, R) + getSum(v*2+1, L, R);
        }
    }
    int fnd(int v, int x){
        if(l[v] == r[v]) return l[v];
        if(val[v*2] >= x) return fnd(v*2, x);
        return fnd(v*2+1, x - val[v*2]);
    }
};
const int dydis = 1e6 + 10;
seg_tree medis(dydis);
vector<int> gr[dydis];
int ans[dydis];
int tevas[dydis];
int num[dydis];
vector<pair<int, pair<int, int> > > quer[dydis];
unordered_set<int> setas[dydis];
int kur[dydis] = {};
void add(int x){
    medis.change(1, kur[x], kur[x], -1);
    setas[kur[x]].erase(x);
    kur[x]++;
    setas[kur[x]].insert(x);
    medis.change(1, kur[x], kur[x], +1);

}
void rem(int x){
    medis.change(1, kur[x], kur[x], -1);
    setas[kur[x]].erase(x);
    kur[x]--;
    setas[kur[x]].insert(x);
    medis.change(1, kur[x], kur[x], +1);
}
int n;
void dfs(int v){
    add(num[v]);
    for(auto x : quer[v]){
        int i = x.first;
        int l = x.second.first;
        int k = x.second.second;
        int y = medis.getSum(1, 0, l-1);
        int ind = k + y;
        if(ind >= n+1) {
            ans[i] = -1;
            continue;
        }
        int kr = medis.fnd(1, ind);
        
        ans[i] = *setas[kr].begin();
        
    }
    for(auto x : gr[v]){
        dfs(x);
    }
    rem(num[v]);
    
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        int q;
        cin >> n >> q;
        medis.keisk(1, 0, 0, n);
        for(int i = 0; i < n; i++) setas[0].insert(i);
        for(int i = 0; i < n; i++) cin >> num[i];
        for(int i = 1; i < n; i++) {
            int a; cin >> a; a--;
            tevas[i] = a;
            gr[a].push_back(i);
        }
        for(int i = 0; i < q; i++){
            int v, l, k;
            cin >> v >> l >> k; v--;
            quer[v].push_back({i, {l, k}});
        }
        dfs(0);
        for(int i = 0; i <= n; i++){
            gr[i].clear();
            setas[i].clear();
            kur[i] = 0;
            quer[i].clear();
        }
        for(int i = 0; i < q; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
