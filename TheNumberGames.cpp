#include <bits/stdc++.h>
using namespace std;
struct node{
    int val, l, r, plus;
    int mx = 0;
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
        if(v < n) tree[v*2].plus += tree[v].plus;
        if(v < n) tree[v*2+1].plus += tree[v].plus;
        tree[v].plus = 0;
    }
    void add(int v, int l, int r, int x){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].plus += x;
            apply(v);
            tree[v].mx = tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
            tree[v].mx = max(tree[v*2].mx, tree[v*2+1].mx);
        }
        apply(v);
    }
    int find(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
    int fd(int v, int x){ // rasti pirma indeksa, kuris didesnis uz x
        if(v >= n) return tree[v].l;
        if(tree[v*2+1].mx > x) return fd(v*2+1, x);
        return fd(v*2, x);
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
const int dydis = 1e3 + 1;
vector<int> gr[dydis];
int n, k;
int R;
int tevas[dydis] = {0};
int sz[dydis] = {0};
seg_tree medis(dydis+ 1);
vector<pair<int, int> > gr2[dydis];
int l[dydis];
int r[dydis];
int place[dydis];
vector<int> trav;
void dfs(int v, int came){
    tevas[v] = came;
    sz[v] = 1;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v);
        sz[v] += sz[x];
        gr2[v].push_back({sz[x], x});
    }
    sort(gr2[v].begin(), gr2[v].end()); reverse(gr2[v].begin(), gr2[v].end());
}
void dfs1(int v, int came){
    trav.push_back(v);
    bool prm = 1;
    place[v] = trav.size()-1;
    r[v] = trav.size()-1;
    l[v] = min(l[v], (int)trav.size()-1);
    for(auto x : gr2[v]){
        if(x.second == came) continue;
        if(prm){
            l[x.second] = l[v];
        }
        dfs1(x.second, v);
        if(prm){
            l[x.second] = l[v];
            r[v] = r[x.second];
        }
        prm = 0;
    }
}

bool marked[dydis] = {0}; // jei marked, tai jos ismest negaliu!
bool can = 1;
int dist(int v){ // atstumas nuo sito iki artimiausio vieneto virsuj
    while(true) {
        int L = l[v];
        int R = r[v];
        if(medis.find(1, L, R) != 0) { // jei sitame intervale yra bent vienas 1
            
        }else{
            v = tevas[trav[l[v]]];
        }
    }
}
int main(){
    for(int i = 0; i < dydis; i++) l[i] = 1e9;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k; R = n - 1;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    dfs(R, -1);
    dfs1(R, -1);
/*    cout << "trav = ["; for(auto x : trav) cout << x+1 << " ";
    cout << "]\n, intervalai:\n";
    for(int i = 0; i < n; i++) {
        cout << i + 1 << ": [" << l[i]  + 1<< "; " << r[i] + 1 << "]\n";
    }*/
    int left = n-1;
    medis.add(1, 0, 0, 1);
    for(int i = n-2; i > -1; i--){
        int dstTo = dist(i);
    }
    return 0;
}
