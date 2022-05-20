#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct node{
    long long val, l, r, plus;
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
    void add(int v, int l, int r, long long x){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].plus += x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
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
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
const int dydis = 3e5 + 10;
int n;
vector<int> gr[dydis];
int he[dydis] = {0};
long long pl[dydis] = {0};
long long ans[dydis] = {0};
vector<pair<int, int> > vec[dydis];
void dfs(int v, int came, int h){
    he[v] = h;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, h+1);
    }
}
seg_tree medis(dydis);

void dfs1(int v, int came){
    for(auto x : vec[v]){
        medis.add(1, he[v], min(n, he[v] + x.first), x.second);
    }
    ans[v] = medis.find(1, he[v], he[v]);
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs1(x, v);
    }
    for(auto x : vec[v]){
        medis.add(1, he[v], min(n, he[v] + x.first), -x.second);
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    int q; cin >> q;
    while(q--){
        int v, d, x; cin >> v >> d >> x; v--;
        vec[v].push_back({d, x});
    }
    dfs(0, -1, 0);
    dfs1(0, -1);
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    return 0;
}
