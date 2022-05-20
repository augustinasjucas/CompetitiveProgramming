#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 41;
int n, m;
vector<int> gr[dydis];
set<int> yra[dydis];
map<string, int> mapas;
int dbInd = 0;
int hsh(string a){
    if(mapas.count(a)) return mapas[a];
    return mapas[a] = dbInd++;
}
bool vis[100010] = {0};
int state[dydis] = {0};
int kur[dydis] = {0};
vector<int> sitas;
void dfs(int v){ // esu v
    if(vis[v]) return;
    vis[v] = 1;
    sitas.push_back(v);
    for(auto x : gr[v]){
        dfs(x);
    }
}
int ps = 0;
int db = 0;
void darom(int ind){
    if(sitas.size()-ind + db < ps) return;
    ps = max(ps, db);
    if(ind == sitas.size()) return;
    int v = sitas[ind];
    if(state[v] < 0) {
        darom(ind+1);
        return;
    }
    // state[ind] = 1
    darom(ind+1);
    for(auto x : gr[v]){
        state[x]--;
    }
    db++;
    darom(ind+1);
    db--;
    for(auto x : gr[v]){
        state[x]++;
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
/*    cout << "117 40\n";
    for(int i = 1; i <= 39; i++){
        cout << "1\n2 " << i << "\n2 " << i+1 << "\n";
    }*/
    for(auto &x : state) x = 0;
    cin >> n >> m;
    vector<pair<int, string > > mas;
    vector<set<string> > naujas;
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        if(t == 1){
            naujas.push_back({});
        }else{
            string a; cin >> a;
            naujas[naujas.size()-1].insert(a);
        }
    }
    for(auto x : naujas){
        for(auto y : x){
            hsh(y);
            for(auto z : x){
                if(y == z) continue;
                if(!yra[hsh(y)].count(hsh(z))){
                    gr[hsh(y)].push_back(hsh(z));
                    yra[hsh(y)].insert(hsh(z));
                }
//                cout << hsh(y) << " - " << hsh(z) << endl;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < dbInd; i++){
        if(vis[i]) continue;
        ps = 0;
        db = 0;
        sitas.clear();
        dfs(i);
        for(int i = 0; i < sitas.size(); i++){
            kur[sitas[i]] = i;
        }
        for(auto v : sitas){
            vector<int> naujas;
            for(auto x : gr[v]){
                if(kur[x] > kur[v]) naujas.push_back(x);
            }
            gr[v] = naujas;
        }
//        cout << "sitas = ["; for(auto x : sitas) cout << x << " "; cout << endl;
        darom(0);
        ans += ps;
    }
    cout << ans;
    return 0;
}
