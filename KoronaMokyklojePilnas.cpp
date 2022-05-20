#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct node{
    int l, r;
    long long mx = 0, val, plus = 0;
};
struct seg_tree{
    
    vector<node> tree;
    int currInd = 0;
    int n;
    
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = currInd++;
            tree[v].val = tree[v].plus = 0;
        }else{
            build(v*2);
            build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    void apply(int v){
        tree[v].val += tree[v].plus * (tree[v].r - tree[v].l + 1);
        tree[v].mx += tree[v].plus;
        if(v < n) tree[v*2].plus += tree[v].plus;
        if(v < n) tree[v*2+1].plus += tree[v].plus;
        tree[v].plus = 0;
    }
    void add(int v, int l, int r, int x){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].plus += x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
            tree[v].mx = max(tree[v*2].mx, tree[v*2+1].mx);
        }
        apply(v);
    }
    long long find(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
    long long findMx(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].mx;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return max(findMx(v*2, l, r), findMx(v*2+1, l, r));
        }
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
const int dydis = 1e5 + 19;
int n;
vector<int> gr[dydis];
int enter[dydis] = {0};
int leave[dydis] = {0};
int sz[dydis] = {0};
int dbInd = 0;
vector<int> trav;
int tevas[dydis];
int l[dydis];
int r[dydis];
int lift[dydis][30] = {0};
int parent[dydis] = {0};
seg_tree medis(dydis);
int fP(int a){
    if(tevas[a] == a) return a;
    return tevas[a] = fP(tevas[a]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    if(a == b) return;
    tevas[b] = a;
    l[a] = min(l[a], l[b]);
    r[a] = max(r[a], r[b]);
}
void dfs(int v, int came){
    parent[v] = came;
    sz[v] = 1;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v);
        sz[v] += sz[x];
    }
}
void dfs1(int v, int came){
    vector<pair<int, int> > vec;
    for(auto x : gr[v]){
        if(x == came) continue;
        vec.push_back({sz[x], x});
    }
    sort(vec.begin(), vec.end()); reverse(vec.begin(), vec.end());
    enter[v] = dbInd++;
    l[v] = trav.size();
    r[v] = trav.size();
    trav.push_back(v);
    for(auto x : vec){
        dfs1(x.second, v);
    }
    if(vec.size()) conn(v, vec[0].second);

    leave[v] = dbInd;
}

void calc(){
    parent[0] = 0;
    for(int i = 0; i < n; i++){
        lift[i][0] = parent[i];
    }
    for(int j = 1; j < 30; j++){
        for(int i = 0; i < n; i++){
            lift[i][j] = lift[lift[i][j-1]][j-1];
        }
    }
}
bool isPar(int a, int b){ // ar a yra b tevas;
    return enter[a] <= enter[b] && leave[b] <= leave[a];
}
int lca(int a, int b){
    if(isPar(a, b)) return a;
    if(isPar(b, a)) return b;
    for(int i = 29; i > -1; i--){
        if(!isPar(lift[b][i], a)){
            b = lift[b][i];
        }
    }
    return parent[b];
}
bool priklausoPomedziui(int v, int came, int kas){
    if(lca(v, came) == came){
        return lca(v, kas) == v; // jei pomedis pilnas, tai tsg lca
    }else{
        return lca(came, kas) != came; // tada pomedis kazkur i virsu, tereikia patikrinti ar nepriklauso zemesnianm
    }
}
long long pridekPomedi(int v, int came, int kaina){
    if(came == lca(v, came)){ // ateinu is virsaus
        int L = enter[v];
        int R = leave[v]-1;
        long long ret = medis.findMx(1, L, R);
        medis.add(1, L, R, kaina);
        return ret;
    }else{
        int L = enter[came];
        int R = leave[came]-1;
        long long ret = max(medis.findMx(1, 0, L-1), medis.findMx(1, R+1, n-1));
        medis.add(1, 0, L-1, kaina);
        medis.add(1, R+1, n-1, kaina);
        return ret;
    }
}
long long prd(int v, int tv, int kaina){
    long long ret = 0;
    while(fP(v) != fP(tv)){
        long long rez = medis.findMx(1, l[fP(v)], enter[v]);
        medis.add(1, l[fP(v)], enter[v], kaina);
        v = parent[trav[l[fP(v)]]];
        ret = max(ret, rez);
    }
    long long rez = medis.findMx(1, enter[tv], enter[v]);
    medis.add(1, enter[tv], enter[v], kaina);
    ret = max(ret, rez);
    return ret;
}
long long pridekKelia(int a, int b, int kaina){
    int tc = lca(a, b);
    long long vn = prd(a, tc, kaina);
    medis.add(1, enter[tc], enter[tc], -kaina);
    long long an = prd(b, tc, kaina);
    return max(an, vn);
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dydis; i++) {
        tevas[i] = i;
        l[i] = 1000000000;
        r[i] = -1;
    }

    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    dfs(0, -1);
    dfs1(0, -1);
    calc();    
    int q; cin >> q;
    while(q--){
        char g; cin >> g;
        if(g == 'K'){ // pomedis judes
            int a, x, b, v; cin >> a >> x >> b >> v;
            a--; x--; b--;
            long long ans = 0;
            ans = max(pridekPomedi(a, x, v), ans);
            if(!priklausoPomedziui(a, x, b)) {
                medis.add(1, enter[a], enter[a], -v);
                ans = max(pridekKelia(a, b, v), ans);
            }
            cout << ans << "\n";
        }else{
            int a, b, v; cin >> a >> b >> v;
            a--; b--;
            long long ans = pridekKelia(a, b, v);
            cout << ans << "\n";
        }
    }
    return 0;
}

