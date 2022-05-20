#include <bits/stdc++.h>
using namespace std;
int n;
const int dydis = 3e5 + 19;
vector<int> gr[dydis];
int dist[dydis];
const int inf = 1e9;
void nul(){
    for(int i = 0; i < n; i++) dist[i] = inf;
}
void dfs(int v, int came){
    for(auto x :  gr[v]){
        if(x == came) continue;
        dist[x] = dist[v] + gr[x].size()-1;
        dfs(x, v);
    }
}
int ans(){
    int ret = 0;
    int lap = 0;
    for(int i = 0; i < n; i++) if(gr[i].size() == 1) lap = i;
    nul(); dist[lap] = 1;
//    cout << "lap = " << lap+1 << endl;
    dfs(lap, -1);
    pair<int, int> mx = {-1, -1};
    for(int i = 0; i < n; i++) if(gr[i].size() == 1) mx = max(mx, make_pair(dist[i], i));
//    cout << "randu " << mx.first << " atstuma iki " << mx.second+1 << endl;
//    cout << "atstumai: "; for(int i = 0; i < n; i++) cout << i + 1 << ": " << dist[i] << "   "; cout << endl;
    nul();
    dist[mx.second] = 1;
    dfs(mx.second, -1);
    for(int i = 0; i < n; i++) if(gr[i].size() == 1) mx = max(mx, make_pair(dist[i], i));
    return mx.first+1;
}

int main(){
    int t; cin >> t;
    while(t--){
        cin >> n;
        if(n == 1){
            cout << "1\n";
            continue;
        }
        for(int i = 0; i < n-1; i++){
            int a, b; cin >> a >> b; a--; b--;
            gr[a].push_back(b);
            gr[b].push_back(a);
        }

        cout << ans() << "\n";
        for(int i = 0; i < n; i++) gr[i].clear();
    }

    return 0;
}
