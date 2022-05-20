#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
const long long inf = 1e18;
const int dydis = 2e5 + 100;
struct seg_tree {
    vector<int> l, r;
    vector<long long> val, lazy;
    int n;
    int dbInd = 0;
    void build(int v = 1) {
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
    seg_tree (int dd = dydis) {
        n = dd;
        l.resize(n * 2 + 1);
        r.resize(n * 2 + 1);
        val.resize(n * 2 + 1);
        lazy.resize(n * 2 + 1);
        dbInd = 0;
        build();
    }
    void apply (int v) {
        val[v] += lazy[v];
        if(v < n) {
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }
        lazy[v] = 0;
    }
    long long getMax(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R) {
            return val[v];
        }else if (R < l[v] || r[v] < L){
            return -inf;
        }else {
            return max(getMax(v*2, L, R), getMax(v*2+1, L, R));
        }
    }
    void add(int v, int L, int R, long long x) {
        apply(v);
        if(L <= l[v] && r[v] <= R) {
            lazy[v] = x;
            apply(v);
        }else if (R < l[v] || r[v] < L){
            return ;
        }else {
            add(v*2, L, R, x);
            add(v*2+1, L, R, x);
            val[v] = max(val[v*2], val[v*2+1]);
        }
    }
};
struct seg_tree1 {
    vector<int> l, r;
    vector<long long> val;
    int n;
    int dbInd = 0;
    void build(int v = 1) {
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
    seg_tree1 (int dd = dydis) {
        n = dd;
        l.resize(n * 2 + 1);
        r.resize(n * 2 + 1);
        val.resize(n * 2 + 1);
        dbInd = 0;
        build();
    }
    long long getMax(int v, int L, int R){
        if(L <= l[v] && r[v] <= R) {
            return val[v];
        }else if (R < l[v] || r[v] < L){
            return -inf;
        }else {
            return max(getMax(v*2, L, R), getMax(v*2+1, L, R));
        }
    }
    int kurMax(int v){
        if(l[v] == r[v]) return l[v];
        if(val[v*2] > val[v*2+1]) return kurMax(v*2);
        return kurMax(v*2+1);
    }
    void change(int v, int L, int R, long long x) {
        if(L <= l[v] && r[v] <= R) {
            val[v] = x;
        }else if (R < l[v] || r[v] < L){
            return ;
        }else {
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = max(val[v*2], val[v*2+1]);
        }
    }
};
int subTreeInd = 0;
seg_tree1 subTreeVals(dydis); 
int n, q;
long long w;
vector<pair<int, long long> > gr[20][dydis];
vector<seg_tree1> nVals;
seg_tree dist[20];
int sz[20][dydis] = {};
bool removed[20][dydis] = {};
bool vis[dydis] = {};
int root[20][dydis];
int enter[20][dydis];
int leave[20][dydis];
int dbInd[20] = {};
int scnd[20][dydis] = {};
int totalLevels = 0;
int treeInd[20][dydis];
int kelintasN[20][dydis];
void er(multiset<long long> &a, long long x) {
    auto kur = a.find(x);
    if(kur != a.end()) a.erase(kur);
}
int dfs1(int l, int v, int cm, int n) {
    sz[l][v] = 1;
    int mx = 0;
    int ret = -1;
    for(auto x : gr[l][v]) {
        if(x.first == cm) continue;
        ret = max(ret, dfs1(l, x.first, v, n));
        sz[l][v] += sz[l][x.first];
        mx = max(mx, sz[l][x.first]);
    }
    mx = max(mx, n - sz[l][v]);
    if(mx <= n / 2) {
        return v;
    }
    return ret;
}
vector<int> nodes;
void dfs2(int l, int v) {
    vis[v] = 1;
    nodes.push_back(v);
    for(auto x : gr[l][v]) {
        if(vis[x.first]) continue;
        dfs2(l, x.first);
    }
}
 
void dfs3(int l, int v, int cm, long long dst) {
    enter[l][v] = dbInd[l]++;
    for(auto x : gr[l][v]) {
        if(x.first == cm) continue;
        dfs3(l, x.first, v, dst + x.second);
        dist[l].add(1, enter[l][x.first], leave[l][x.first], x.second);
    }
    leave[l][v] = dbInd[l]++;
}
void dfs4(int l, int v, int came, int sc) {
    scnd[l][v] = sc;
    for(auto x : gr[l][v]) {
        if(x.first == came) continue;
        dfs4(l, x.first, v, sc);
    }
}
int findCentroid(int l, vector<int> &nodes) {   
    int m = dfs1(l, nodes[0], -1, nodes.size());
    return m;
}
long long calcMaxOfSubtree(int l, int v) {
    int ind = treeInd[l][v];
    long long mx = nVals[ind].getMax(1, 0, 1e9);
    int kr = nVals[ind].kurMax(1);
    nVals[ind].change(1, kr, kr, -inf);
    long long kt = nVals[ind].getMax(1, 0, 1e9);
    nVals[ind].change(1, kr, kr, mx);
    return mx + kt;
}
void precalcVal(int l, int v, vector<int> &nodes){  
    dfs3(l, v, -1, 0);
    nVals.push_back(seg_tree1(gr[l][v].size()+2));
    for(int i = 0; i < gr[l][v].size(); i++){
        auto &x = gr[l][v][i];
        nVals[subTreeInd].change(1, i, i, dist[l].getMax(1, enter[l][x.first], leave[l][x.first]));
        kelintasN[l][x.first] = i;
    }
    treeInd[l][v] = subTreeInd;
    subTreeVals.change(1, subTreeInd, subTreeInd, calcMaxOfSubtree(l, v));
    subTreeInd++;
}
int separate(int l){   
    int ret = 0;
    for(int i = 0; i < n; i++) vis[i] = 0;
    for(int i = 0; i < n; i++) {
        removed[l+1][i] = (removed[l][i] | removed[l+1][i]);
        if(removed[l][i]) continue;
        if(vis[i]) continue;
        ret++;
        nodes.clear();
        dfs2(l, i);
        int cen = findCentroid(l, nodes);
        removed[l+1][cen] = 1;
        for(auto &x : nodes) root[l][x] = cen;
        for(auto &x : nodes) {
            for(auto &y : gr[l][x]) {
                if(y.first == cen) continue;
                gr[l+1][x].push_back(y);
            }
        }
        for(auto &x : gr[l][cen]) {
            dfs4(l, x.first, cen, x.first);
        }
        precalcVal(l, cen, nodes);
    }
    return ret;
}
 
vector<pair<pair<int, int>, long long> > brn;
void updateValues(int a, int b, long long delta) {
    int tevas = -1;
    int ka;
    for(int l = 0; l < totalLevels; l++) {
        if(removed[l][a] || removed[l][b]) break;
        if(enter[l][a] > enter[l][b]) swap(a, b);
        tevas = root[l][a];
        ka = scnd[l][b];
        dist[l].add(1, enter[l][b], leave[l][b], delta);
        nVals[treeInd[l][tevas]].change(1, kelintasN[l][ka], kelintasN[l][ka], dist[l].getMax(1, enter[l][ka], leave[l][ka]));
        subTreeVals.change(1, treeInd[l][tevas], treeInd[l][tevas], calcMaxOfSubtree(l, tevas));
    }
}
int main (){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q >> w;
    for(int i = 0; i < n-1; i++) {
        long long w;
        int a, b; cin >> a >> b >> w; a--; b--;
        gr[0][a].push_back({b, w});
        gr[0][b].push_back({a, w});
        brn.push_back({{a, b}, w});
    }
    for(int i = 0; i < 20; i++) {
        int sk = separate(i);
        if(sk == 0) {
            totalLevels = i;
            break;
        }
    }
    long long ind = 0, ind1;
    long long we = 0, we1;
    long long last = 0;
    while(q--) {
        cin >> ind1 >> we1;
        ind = (ind1 + last) % (n-1);
        we = (we1 + last) % w;
        int a = brn[ind].first.first;
        int b = brn[ind].first.second;
        long long deltaW = we - brn[ind].second;
        updateValues(a, b, deltaW);
        last = subTreeVals.getMax(1, 0, 1e9);
        brn[ind].second = we;
        cout << last << "\n";
     }
    return 0;
}

