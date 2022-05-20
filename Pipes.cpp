#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 1e5 + 10;
const int inf = 1e9;
vector<pair<int, int> > gr[dydis];
int bal[dydis] = {0};
int ans[dydis] = {0};
int inc[dydis] = {0};
bool don[dydis] = {0};
bool vis[dydis] = {0};
map<pair<int, int>, int> mapas;
int n, m;
bool galima = 1;
int viso = 0;
pair<int, int> pan = {-1, -1};
void toposort(){
    viso = n;
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(don[i]) continue;
        if(inc[i] == 1){
            q.push(i);
        }
    }
    while(!q.empty()){
        int v = q.front(); q.pop();
        if(don[v]) continue;
        don[v] = 1;
        viso--;
        for(auto x : gr[v]){
            if(don[x.first]) continue;
            if(make_pair(v, x.first) == pan || make_pair(x.first, v) == pan) continue;
            inc[x.first]--;
            bal[x.first] -= bal[v];
            ans[x.second] = bal[v];
            if(inc[x.first] <= 1){
                q.push(x.first);
            }
        }
        bal[v] = 0;
    }
}
vector<int> ckl;
void dfs(int v){
    if(vis[v]) return;
    vis[v] = 1;
    for(auto x  : gr[v]){
        if(don[x.first]) continue;
        dfs(x.first);
    }
    ckl.push_back(v);
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dydis; i++){
        ans[i] = -inf;
        vis[i] = 0;
    }
    cin >> n >> m;
    if(n == 1){
        return 0;
    }
    for(int i = 0; i < n; i++){
        cin >> bal[i]; 
        bal[i] *= 2;
    }
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
        inc[a]++;
        inc[b]++;
//        mapas[{a, b}] = i;
//        mapas[{b, a}] = i;
    }
    if(m > n){
        cout << "0";
        return 0;
    }
    toposort();
    if(m == n && viso % 2 == 0){
        cout << "0";
        return 0;
    }
    if(m == n){
        int v = -1;
        for(int i = 0; i < n; i++) {
            if(!don[i]) v = i;
        }
        dfs(v);
        int i1;
        for(auto x : gr[ckl[0]]){
            if(x.first == ckl[1]){
                i1 = x.second;
            }
        }
        int s = bal[ckl[0]];
        for(int i = 1; i < ckl.size(); i++){
            s += ((i & 1) ?  -1 : 1) * -1 * bal[ckl[i]];
        }
        ans[i1] = s/2;
        bal[ckl[0]] -= s/2;
        bal[ckl[1]] -= s/2;
        pan = {ckl[0], ckl[1]};
        inc[ckl[0]]--;
        inc[ckl[1]]--;
        toposort();
    }
    for(int i = 0; i < m; i++)   {
        cout << ans[i] << "\n";
    }
    return 0;
}
