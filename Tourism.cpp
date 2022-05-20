#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, m;
vector<long long> w;
int medTevas[dydis] = {0};
bool vis[dydis] = {0};
set<pair<int, int> > bridges;
vector<int> gr[dydis];
int pl[dydis] = {0}; // kiek backedgu pasibaigia ties manimi
int he[dydis] = {0};
int tevas[dydis] = {0};
set<int> kaim[dydis];
bool vs[dydis] = {0};
long long sm[dydis] = {0};
long long dst[dydis] = {0};
int sz[dydis] = {0};
int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    cout << "connectinu " << a+1 << " su " << b+1 << endl;

    a = fP(a);
    b = fP(b);
    if(a == b) return;
    if(kaim[a].size() > kaim[b].size()) swap(a, b);
    tevas[a] = b;
    sm[b] += sm[a];
    sz[b] += sz[a];
//    cout << "sm[" << b+1 << "] = " << sm[b] << endl;
    for(auto x : kaim[a]) kaim[b].insert(fP(x));
}
void dfs(int v){
    vis[v] = 1;
    for(auto x : gr[v]){
        if(vis[x]) continue;
//        cout << "tree pridedu " << v+1 << " -> " << x+1 << endl;
        medTevas[x] = v;
        he[x] = he[v] + 1;
        dfs(x);
    }
}
int dfs1(int v){ // grazina, kiek backedgu eina virs manes
    int sm = 0;
//    cout << 1+v << ":\n";
    for(auto x : gr[v]){
        if(medTevas[x] != v && he[x] >= he[v]) continue; // jei briaunos zemyn.
        if(medTevas[x] == v){ // zemyn
            sm += dfs1(x);
        }else{ // aukstyn
            if(x == medTevas[v]) continue;
//            cout << "pridedu " << x+1 << "\n";
            pl[x] += 1;
            sm++;
        }
    }
    sm -= pl[v];
//    cout << "sm (" << v+1 << ") = " << sm << endl;
    if(sm == 0 && v != 0){
        bridges.insert({min(v, medTevas[v]), max(v, medTevas[v])});
        cout << "bridgas " << v+1 << "-" << medTevas[v] +1<< endl;
    }
    return sm;
}
void dfs2(int v){
    if(vs[v]) return;
    vs[v] = 1;
//    cout << "esu " << v << endl;
    for(auto x : gr[v]){
        if(bridges.count(make_pair(x, v)) || bridges.count(make_pair(v, x))) continue;
//        cout << "turiu " << x << ""
        conn(x, v);
        dfs2(x);
    }
}
void dfs3(int v, int came){
    cout << "esu " << 1+v << ", came = " << came << endl;
    for(auto x : kaim[v]){
        if(x != fP(x)) continue;
        if(x == came) continue;
        if(x == v) continue;
        dst[x] = dst[v] + sm[x];
        dfs3(x, v);
    }
}
void dfs4(int v, int came){
    
}
int main(){
    for(int i = 0; i < dydis; i++) {
        tevas[i] = i;
        sz[i] = 1;
    }
    cin >> n >> m;
    w.resize(n);
    for(auto &x : w) {
        cin >> x;
    }
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
        kaim[a].insert(b);
        kaim[b].insert(a);
    }
    for(int i = 0; i < n; i++){
        sm[i] = w[i];
    }
    he[0] = 0;
    dfs(0);
    dfs1(0);
    for(int i = 0; i < n; i++) dfs2(i);
    int prd = 0; cin >> prd; prd--;
    prd = fP(prd);
    dst[prd] = sm[prd];
     
    for(int i = 0; i < n; i++){
        if(fP(i) != i) continue;
        vector<int> ins;
        for(auto &x : kaim[i]) ins.push_back(fP(x));
        for(auto x : ins) kaim[i].insert(x);
        cout <<sm[i] << ", " <<  i +1<< " priklauso " << fP(i)+1 << " komp, jungiasi su "; for(auto x : kaim[i])  if(x != i && fP(x) == x) cout << x +1<< " ";
        cout << endl;
    }
    int dd = -1;
    for(int i = 0; i < n; i++){
        if(fP(i) != i) continue;
        if(sz[i] <= 2) continue;
        dd = i;
    }
    dfs4(i, -1);
     
    for(int i = 0; i < n; i++){
        if(fP(i) != i) continue;
        vector<int> ins;
        for(auto &x : kaim[i]) ins.push_back(fP(x));
        for(auto x : ins) kaim[i].insert(x);
        cout <<sm[i] << ", " <<  i +1<< " priklauso " << fP(i)+1 << " komp, jungiasi su "; for(auto x : kaim[i])  if(x != i && fP(x) == x) cout << x +1<< " ";
        cout << endl;
    }
    dfs3(prd, -1);
    long long ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, dst[i]);
        cout << "dst[" << i+1 << "] = " << dst[i] << endl;
    }
    cout << ans;
    return 0;
}
