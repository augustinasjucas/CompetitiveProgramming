#include <bits/stdc++.h>
using namespace std;
int n;
const int dydis = 1e5 + 100;
vector<pair<int, int> > mas[dydis], gr[dydis];
bool vis[dydis] = {0};
int ans[dydis] = {0};
int neut[dydis] = {0};
void dfs(int v){
    vis[v] = 1;
    for(auto x : mas[v]){
        if(vis[x.first]) continue;
        gr[x.first].push_back({v, x.second});
        gr[v].push_back({x.first, x.second});
        dfs(x.first);
    }
}
void mkN(int v){
    vector<int> st;
    for(auto x : gr[v]){
        st.push_back(x.second);
    }
    sort(st.begin(), st.end());
    int db = 1;
    for(auto x : st){
        if(x > db){
            neut[v] = db;
            return;
        }
        if(x == db) db++;
    }
    neut[v] = db;
}
void fAns(int v, int came){
    if(v == 0){
        ans[v] = neut[v];
    }
    for(auto x : gr[v]){
        if(x.first == came) continue;
        if(ans[v] != x.second) ans[x.first] = x.second;
        else ans[x.first] = neut[x.first];
        fAns(x.first, v);
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        mas[a].push_back({b, c});
        mas[b].push_back({a, c});
    }
    dfs(0);
    for(int i = 0; i < n; i++) mkN(i);
    fAns(0, -1);
    for(int i = 0; i < n; i++){
        cout << ans[i] << "\n";
    }
    return 0;
}
