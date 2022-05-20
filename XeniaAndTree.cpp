#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
struct seg_tree{
    const int inf = 1e9 + 10;
    int n;
    vector<int> l, r;
    vector<int> min1, min2, max1, lazy, max2;
    int dbInd = 0;
    void build (int v = 1){
        if(v >= n){
            l[v] = r[v] = dbInd++;
        }else{
            build(v * 2);
            build(v * 2 + 1);
            l[v] = l[v * 2];
            r[v] = r[v * 2 + 1];
        }
    }
    seg_tree(int dd){
        n = dd;
        l.resize(n * 2 + 1);
        r.resize(n * 2 + 1);
        min1.resize(n * 2 + 1);
        min2.resize(n * 2 + 1);
        max1.resize(n * 2 + 1);
        max2.resize(n * 2 + 1);
        lazy.resize(n * 2 + 1);
        build();
    }

    void apply(int v){
        if(lazy[v] == inf){
            return ;
        }
        min1[v] = lazy[v];
        min2[v] = min1[v] - 2 * max2[v];
        max1[v] = lazy[v];

        if(v < n){
            lazy[v*2] = lazy[v];
            lazy[v*2+1] = lazy[v];
        }
        lazy[v] = inf;
    }
    void change(int v, int L, int R, int x){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            lazy[v] = x;
            apply(v);
        }else if(R < l[v] || r[v] < L){
            return ;
        }else{
            change(v * 2, L, R, x);
            change(v * 2 + 1, L, R, x);
            min1[v] = min(min1[v*2], min1[v*2+1]);
            min2[v] = min(min2[v*2], min2[v*2+1]);
            max1[v] = max(max1[v*2], max1[v*2+1]);
        }
    }
    void change2(int v, int L, int R, int x){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            max2[v] = x;
        }else if(R < l[v] || r[v] < L){
            return ;
        }else{
            change2(v * 2, L, R, x);
            change2(v * 2 + 1, L, R, x);
            max2[v] = max(max2[v*2], max2[v*2+1]);
        }   
    }
    int getVal1(int v, int L, int R){
         apply(v);
        if(L <= l[v] && r[v] <= R){
            return min1[v];
        }else if(R < l[v] || r[v] < L){
            return inf;
        }else{
            return min(getVal1(v*2, L, R), getVal1(v*2+1, L, R));
        }   
    }
    int getVal2(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            return min2[v];
        }else if(R < l[v] || r[v] < L){
            return inf;
        }else{
            return min(getVal2(v*2, L, R), getVal2(v*2+1, L, R));
        }   
    }
    int getInd(int v, int L, int R, int x){     
        apply(v);
        if(L <= l[v] && r[v] <= R){
            if(max1[v] < x) return inf;
            if(l[v] == r[v]) return l[v];
            int prm = getInd(v*2, L, R, x);
            if(prm != inf) return prm;
            return getInd(v*2+1, L, R, x);
        }else if(R < l[v] || r[v] < L){
            return inf;
        }else{
            int prm = getInd(v*2, L, R, x);
            if(prm != inf) return prm;
            return getInd(v*2+1, L, R, x);
        }
    
    }

};
const int dydis = 1e6 + 10;
int n, m;
seg_tree virsus(dydis), raudoni(dydis);
vector<pair<int, int> > gr[dydis];
int sz[dydis];
int dbInd = 0;
vector<int> trav;
int leftmost[dydis];
int h[dydis];
int kur[dydis];
int tevas[dydis];
int LEFT[dydis];
int RIGHT[dydis];
void dfs1(int v, int came, int he = 0){
    sz[v] = 1;
    h[v] = he;
    tevas[v] = came;
    for(auto &x : gr[v]){
        if(x.second == came) continue;
        dfs1(x.second, v, he + 1);
        sz[v] += sz[x.second];
        x.first = sz[x.second];
    }
    sort(gr[v].begin(), gr[v].end());
    reverse(gr[v].begin(), gr[v].end());
}

void dfs2(int v, int came, int frst){
    trav.push_back(v);
    kur[v] = trav.size()-1;
    leftmost[v] = frst;
    LEFT[v] = trav.size()-1;
    for(int i = 0; i < gr[v].size(); i++){
        int x = gr[v][i].second;
        if(x == came) continue;
        if(i == 0){
            dfs2(x, v, frst);    
        }else{
            dfs2(x, v, trav.size());
        }
    }
    RIGHT[v] = trav.size()-1;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n -1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({0, b});
        gr[b].push_back({0, a});
    }
    dfs1(0, -1);
    dfs2(0, -1, 0);
    for(int i = 0; i < n; i++){
        virsus.change2(1, kur[i], kur[i], h[i]);
    }
    for(int i = 0; i < n; i++){
        virsus.change(1, kur[i], kur[i], h[i] * 2);
    }
    for(int i = 0; i < n; i++) raudoni.change(1, i, i, inf);
    raudoni.change(1,kur[0], kur[0], 0);
    while(m--){
        int t;
        cin >> t;
        int v; cin >> v; v--;
        if(t == 1){         
            raudoni.change(1, kur[v], kur[v], h[v]);
            int H = h[v];
            while(v != -1){
                int R = kur[v];
                int L = leftmost[v];
                int kr = virsus.getInd(1, L, R, H);
                virsus.change(1, kr, R, H);
                v = tevas[trav[leftmost[v]]];
                if(kr != L && kr != R) break;
            }
        }else{              
            int ans = inf;
            ans = min(ans, raudoni.getVal1(1, LEFT[v], RIGHT[v]) - h[v]);
            int V = v;
            while(v != -1){
                int R = kur[v];
                int L = leftmost[v];
                ans = min(ans, virsus.getVal2(1, L, R) + h[V]);
                v = tevas[trav[leftmost[v]]];
            }
            cout << ans << endl;
        }
    }
    return 0;
}   
