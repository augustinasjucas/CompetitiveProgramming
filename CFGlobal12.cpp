#include <bits/stdc++.h>
using namespace std;
const int dydis = 101;
vector<int> gr[dydis];
int dist[dydis];
int n, k;
void bfs(int v){
    queue<int> q;
    for(int i = 0; i < n; i++) dist[i] = 1e9;
    q.push(v);
    dist[v] = 0;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(auto x : gr[v]){
            if(dist[x] > dist[v] + 1){
                dist[x] = dist[v] + 1;
                q.push(x);
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--){
        cin >> n >> k;
        vector<pair<int, int> > mas;
        for(int i = 0; i < n; i++) gr[i].clear();
        for(int i = 0; i < n; i++){
            int a,b; cin >> a>> b;
            mas.push_back({a, b});
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                if(abs(mas[i].first - mas[j].first) + abs(mas[i].second - mas[j].second) <= k){
                    gr[i].push_back(j);
                }
            }
        }
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            bfs(i);
            int mx = 0;
            for(int j = 0; j < n; j++){
                mx = max(mx, dist[j]);
            }
            ans = min(ans, mx);
        }
        if(ans == ((int)(1e9)) || ans > 1){
            cout << "-1\n";
        }else cout << ans  << "\n"; 
        
    }
    return 0;
}
