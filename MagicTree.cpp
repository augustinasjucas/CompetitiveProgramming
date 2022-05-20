#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int dydis = 1e5 + 10;
struct seg_tree {
    int n;
    vector<int> l, r;
    vector<long long> val;
    int dbInd = 0;
    void build (int v = 1) {
        if(v >= n) {
            l[v] = r[v] = dbInd++;
        }else {
            build(v*2);
            build(v*2+1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
        val[v] = 0;
    }
    seg_tree (int dd){
        val.resize(dd*2 + 1);
        l.resize(dd*2 + 1);
        r.resize(dd*2 + 1);
        n = dd;
        build();
    }
    void change(int v, int L, int R, long long x) {
        if(L <= l[v] && r[v] <= R) {
            val[v] = x;
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else{
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = val[v*2] + val[v*2+1];
        }
    }
    long long getSum(int v, int L, int R){
        if(L <= l[v] && r[v] <= R) {
            return val[v];
        }else if(R < l[v] || r[v] < L) {
            return 0;
        }else{
            return getSum(v*2, L, R) + getSum(v*2+1, L, R);
        }
    }
};
int n, m, k;
vector<int> gr[dydis];
int tevas[dydis];
int enter[dydis];
int leave[dydis];
int dbInd = 0;
long long vl[dydis] = {};
vector<pair<int, int> > vec[dydis];
int he[dydis] = {};
seg_tree medis(dydis * 2 + 10);
void dfs(int v, int cm) {
    enter[v] = dbInd++;
    for(auto &x : gr[v]) {
        if(x == cm) continue;
        he[x] = he[v] + 1;
        dfs(x, v);
    }
    leave[v] = dbInd++;
}
long long dfs2(int v, int came) {
    long long ret = 0;
    for(auto &x : gr[v]) {
        if(x == came) continue;
        ret += dfs2(x, v);
    }
    ret = max(ret, vl[v]);
    return ret;
}
int main () {
    cin >> n >> m >> k;
    for(int i = 1; i < n; i++) {
        int a; cin >> a; a--;
        tevas[a] = i;
        gr[a].push_back(i);
        gr[i].push_back(a);
    }
    dfs(0, 0);
    for(int i = 0; i < m; i++) {
        int v, t, c; cin >> v >> t >> c; v--;
        vec[t].push_back({v, c});
    }
    for(int i = 0; i <= k; i++) {
        for(auto &x : vec[i]) {
            int v = x.first;
            int c = x.second;
            medis.change(1, enter[v], enter[v], c);
        }
        for(auto &x : vec[i]) {
            int v = x.first;
            long long sm = 0;
            sm = medis.getSum(1, enter[v], leave[v]) ;
            vl[v] = sm;
            cout << "vl[" << v+1 << "] = " << vl[v] << endl;
        }
    }
    long long ans = dfs2(0, 0);
    cout << ans;
    return 0;
}
