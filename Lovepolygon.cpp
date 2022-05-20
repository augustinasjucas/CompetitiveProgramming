#include <bits/stdc++.h>
using namespace std;
const int dydis= 2e5 + 10;
int out[dydis];
bool vis[dydis] = {0}, vis1[dydis] = {0}, isIn[dydis] = {0};
int jeiImsiu[dydis], jeiNe[dydis];
vector<int> gr[dydis];
int n;
int dbInd = 0;
map<string, int> mapas;
int hsh(string a){
    if(mapas.count(a)) return mapas[a];
    return mapas[a] = dbInd++;
}
vector<int> cur;
vector<int> cyc;
void dfs(int v){
    if(cyc.size()) return;
    if(vis[v]){
        while(cur.back() != v){
            cyc.push_back(cur.back());
            cur.pop_back();
        }
        cyc.push_back(v);
//        cout << "["; for(auto x : cyc) cout << x<< " "; cout << "]\n";
        return;
    }
    vis[v] = 1;
    cur.push_back(v);
    dfs(out[v]);
    cur.pop_back();
}
void dfs1(int v){
    if(vis1[v]) return;
    vis1[v] = 1;
    for(auto x : gr[v]){
        dfs1(x);
    }
}
int dp[dydis][2][3];
pair<int, int> brn;
int ig1 = -1, ig2 = -1;
int f(int v, int came, bool can, int it){
//    cout << v << "; " << came << endl;
    if(dp[v][can][it] != -1) return dp[v][can][it];
    if(v == ig1 || v == ig2) can = 0;
    int ret = 0;
    int sm = 0;
    set<int> was;
    for(auto x : gr[v]){
        if(make_pair(x, v) == brn || make_pair(v, x) == brn) continue;
        if(x == v) continue;
        if(x == came) continue;
        if(was.count(x)) continue;
        was.insert(x);
        sm += f(x, v, 1, it);
    }
    for(auto x : gr[v]){
        if(make_pair(x, v) == brn || make_pair(v, x) == brn) continue;
        if(x == v) continue;
        if(x == came) continue;
        if(ig1 == x || ig2 == x) continue;
        ret = max(ret, sm - f(x, v, 1, it) + f(x, v, 0, it) + 1 + (out[x] == v && out[v] == x));
    }
    if(!can) return dp[v][can][it] = sm; 
    else return dp[v][can][it] = max(ret, sm);
    
}
    
 
int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < 2; j++){
            for(int h = 0; h < 3; h++){
                dp[i][j][h] = -1;
            }
        }
    }
 
    int n; cin >> n;
    if(n & 1){
        cout << "-1";
        return 0;
    }
    for(int i = 0; i < n; i++){
        string a, b; cin >> a >> b;
        int c = hsh(a);
        int d = hsh(b);
        out[c] = d;
        gr[c].push_back(d);
        gr[d].push_back(c);
//        cout << c << " -> " << d << endl;
    }
    int sm = 0;
    for(int i = 0; i < n; i++){
        if(vis[i]  ||  vis1[i]){
            continue;
        }
        cur.clear(); cyc.clear();
        dfs(i);
        dfs1(i);
        for(auto x : cyc) isIn[x] = 1;
        brn = {-1, -1};ig1 = ig2 = -1;
        if(cyc.size() == 1){
            sm += max(f(cyc[0], -1, 0,0), f(cyc[0], -1, 1, 0));
            continue;
        }    

        int sit = 0;
        if(cyc.size() != 2) brn = {cyc[0], cyc[1]};
        sit = max(sit, max(f(cyc[0], -1, 0, 0), f(cyc[0], -1, 1, 0)));
        ig1 = cyc[0];
        ig2 = cyc[1];
        sit = max(sit, max(f(cyc[0], -1, 0, 1), f(cyc[0], -1, 1, 1)) + 1 + (cyc.size() == 2)); // jei juos sujungiu 
        sm += sit;
    }
    cout << n-sm;
    return 0;
}
