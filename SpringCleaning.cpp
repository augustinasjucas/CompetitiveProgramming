#include <bits/stdc++.h>
using namespace std;
struct seg {
    vector<int> l, r;
    vector<int> val, lazy;
    int n ;
    int dbInd = 0;
    void build(int v = 1){
        if(v >= n){
            l[v] = r[v] = dbInd++;
        }else{
            build(v * 2);
            build(v * 2 + 1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
    }
    seg(int dd){
        n = dd;
        val.resize(n * 2);
        l.resize(n * 2);
        r.resize(n * 2);
        lazy.resize(n * 2);
        build(1);
    }
    void apply(int v){
        if(!lazy[v]) return ;
        val[v] = r[v] - l[v] + 1 - val[v];
        if(l[v] != r[v]) {
            lazy[2*v] = !lazy[2*v];
            lazy[2*v+1] = !lazy[2*v+1];
        }
        lazy[v] = 0;
    }
    int getSum(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            return val[v];
        }else if(r[v] < L || R < l[v]){
            return 0;
        }else{
            return getSum(v*2, L, R) + getSum(v*2+1, L, R);
        }
    }
    void invert(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            lazy[v] = 1;
            apply(v);
        }else if(r[v] < L || R < l[v]){
            return ;
        }else{
            invert(v*2, L, R);
            invert(v*2+1, L, R);
            val[v] = val[v*2] + val[v*2+1];
        }
    }
    void change(int v, int L, int R, int x){
        apply(v);
        if(L <= l[v] && r[v] <= R){
            val[v] = x;
        }else if(r[v] < L || R < l[v]){
            return;
        }else{
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = val[v*2] + val[v*2+1];
        }       
    }
};
const int dydis = 1e5 + 10;
vector<pair<int, int> > gr[dydis];
int n, q;
int sz[dydis] = {};
int lp[dydis] = {};
int tevas[dydis];
void dfs(int v, int came) {
    sz[v] = 1;
    tevas[v] = came;
    lp[v] = gr[v].size() == 1;
    for(auto &x : gr[v]) {
        if(x.second == came) continue;
        dfs(x.second, v);
        x.first = sz[x.second];
        sz[v] += sz[x.second];
        lp[v] += lp[x.second];
    }
    sort(gr[v].begin(), gr[v].end());
    reverse(gr[v].begin(), gr[v].end());
}
int dbInd = 0;
int l[dydis];
int kas[dydis];
int ind[dydis];
seg medis(dydis);
vector<int> VEC;
void dfs1(int v, int came){
    kas[dbInd] = v;
    ind[v] = dbInd++;
    VEC.push_back(v);
    for(int i = 0; i < gr[v].size(); i++){
        auto x = gr[v][i];
        if(x.second == came) continue;
        if(i == 0){
            l[x.second] = l[v];
            dfs1(x.second, v);
        }else{
            l[x.second] = dbInd;
            dfs1(x.second, v);
        }
    }
}

void rev(int v){
//    cout << "aukstyn nuo " << v+1 << endl;
    while(v != -1){
//        cout << "invert (" << l[v] << "; " << ind[v] << ")\n";
        medis.invert(1, l[v], ind[v]);
        v = tevas[kas[l[v]]];
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 0; i  < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({0, b});
        gr[b].push_back({0, a});
    }
    dfs(0, -1);
    dfs1(0, -1);
/*    cout << "eile: ";
    for(auto x : VEC) cout << x+1 << " ";
    cout << endl;
    cout << "pries:\n";*/
    for(int i = 0; i < n; i++){
        medis.change(1, ind[i], ind[i], (lp[i]+1) % 2);
//        cout << "[" << i+1 << "] - " << medis.getSum(1, i, i) << endl;
    }
    int visoLapu = 0;
    for(int i = 0; i < n; i++) visoLapu += gr[i].size() == 1;
    for(int i = 0; i < q; i++){
        int m; cin >> m;
        vector<int> vec;
        set<int> takenOut;
        int pamazejo = 0;
        for(int i = 0; i < m; i++){
            int a; cin >> a; a--;

            if(gr[a].size() == 1 && takenOut.count(a) == 0){
                pamazejo++;
                takenOut.insert(a);
            }else{
                rev(a);
                vec.push_back(a);
            }
        }
/*        cout << "po: ";
        for(int i = 0; i < n; i++){
            cout << "[" << i+1 << "] - " << medis.getSum(1, i, i) << endl;
        }
        cout << endl;*/
        if((visoLapu - pamazejo + m) % 2 == 0){
            cout << medis.getSum(1, 0, n-1) + n + m-2 << "\n";
        }else{
            cout << "-1\n";
        }
        for(auto x : vec){
            rev(x);
        } 
    }

    return 0;
}
