#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
struct seg_tree{
    vector<int> l, r, val, lazy;

    int n;
    int dbInd = 0;
    void build(int v){
        if(v >= n){
            l[v] = r[v] = dbInd++;
        }else{
            build(v * 2);
            build(v * 2 + 1);
            l[v] = l[v * 2];
            r[v] = r[v * 2 + 1];
        }
        val[v] = 0;
        lazy[v] = -inf;
    }
    seg_tree(int d){
        n = d;
        l.resize(n * 2 + 1);
        r.resize(n * 2 + 1);
        val.resize(n * 2 + 1);
        build(1);
    }
    void apply(int v){
        if(lazy[v] == -inf) return;
        val[v] = (r - l + 1) * lazy[v];
        if(v < n){
            lazy[v * 2] = lazy[v];
            lazy[v * 2 + 1] = lazy[v];
        }
        lazy[v] = -inf;
    }
    void change(int v, int L, int R, int x){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            lazy[v] = x;
            apply(v);
        }else if(R < l[v] || r[v] < L){
            return;
        }else{
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = val[v*2] + val[v*2+1];
        }
    }
    int get(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            return val[v];
        }else if(R < l[v] || r[v] < L){
            return 0;
        }else{
            return get(v*2, L, R) + get(v*2+1, L, R);
        }
    }
    int getNth(int v, int kel){
        if(l[v] == r[v]) return l[v];
        apply(v);
        if(l[v] >= kel){
            return getNth(v*2, kel);
        }else{
            apply(v * 2);
            return getNth(v*2+1, kel - val[v*2]);
        }
    }
}
const int dydis = 3e5 + 10;
int n;
vector<pair<int, int> > gr1[dydis], gr2[dydis];
int sz[dydis];
vector<int> trav;
int l[dydis];
int enter[dydis];
int leave[dydis];
int tevas[dydis];
void dfs1(int v, int came){ 
    sz[v] = 1;
    for(auto &x : gr2[v]){
        if(x == came) {
            x.first = -1;
            continue;
        }
        dfs1(x.second, v);
        sz[v] += sz[x];
        x.first = sz[x];
    }
    sort(gr2.begin(), gr2.end());
    reverse(gr2.begin(), gr2.end());
}
void dfs2(int v, int came, int eil){
    tevas[v] = came;
    enter[v] =trav.size();
    trav.push_back(v);
    dfs2(gr2[v][0].second, v, l[v]);
    l[v] = eil;
    for(int i = 1; i < gr[v].size(); i++){
        int x = gr[v][i].second;
        if(x == came) continue;
        dfs2(x, v, trav.size());
    }
    leave[v] = trav.size() - 1;
}
seg_tree marked(dydis), deleted(dydis);
int deletedInstead[dydis];
int didPutIn[dydis];
void takeOut(int v){
    marked.change(1, v, v, 0);
    deleted.change(1, enter[v], leave[v], 0);
}
void putIn(int v){
    marked.change(1, v, v, 1);
    deleted.change(1, enter[v], leave[v], 1);
}
void add(int v){
    if(deleted.get(1, v, v) == 0){
        putIn(v);
        didPutIn = 0;
    }else{
        
    }
}
void rem(int v){
    
}
void dfs3(int v, int came){
    add(v);
    for(auto x : gr1[v]){
        if(x == came) continue;
        dfs3(x, v);
    }
    rem(v);
}
int main(){
    int t; cin >> t; 
    while(t--){
        cin >> n;
        for(int i = 0; i < n; i++){
            deletedInstead[i] = -1;
            didPutIn[i] = 0;
        }
        for(int i = 0; i < n-1; i++){
            int a; cin >> a;
            gr1[i].push_back({1, a});
            gr1[a].push_back({1, i})
        }
        for(int i = 0; i < n-1; i++){
            int a; cin >> a;
            gr2[i].push_back({1, a});
            gr2[a].push_back({1, i});
        }
        for(int i = 0; i < n; i++) {
            gr1[i].clear();
            gr2[i].clear();
        }
        dfs2(0, -1, 0);
        dfs3(0, -1);
    }
    return 0;
}
