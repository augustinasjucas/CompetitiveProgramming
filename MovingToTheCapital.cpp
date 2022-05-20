#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int dydis = 2e5;
int n, m;
int dist[dydis] = {0};
int ans[dydis];
vector<int> gr[dydis];
int dp[dydis] = {0};
void bfs(int v){
    dist[v] = 0;
    queue<int> q; q.push(v);
    while(!q.empty()){
        v = q.front(); q.pop();
        for(auto x : gr[v]){
            if(dist[x] <= dist[v]+1) continue;
            dist[x] = dist[v]+1;
            q.push(x);
        }
    }
}
void dfs(int v){
    if(dp[v] != -1) return;
    int posAns = dist[v];
    for(auto x : gr[v]){
        if(dist[x] > dist[v]){
            dfs(x);
            posAns = min(posAns, dp[x]);
        }else{
            posAns = min(posAns, dist[x]);
        }
    }
    dp[v] = posAns;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n >> m;    
        for(int i = 0; i < n; i++){
            gr[i].clear();
            dist[i] = inf;
            dp[i] = -1;
            ans[i] = -1;
        }
        for(int i = 0; i < m; i++){
            int a, b; cin >> a >> b; a--; b--;
            gr[a].push_back(b);
        }
        bfs(0);
        dfs(0);
        for(int i = 0; i < n; i++){
            cout << dp[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
