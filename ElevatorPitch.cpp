#include <bits/stdc++.h>
using namespace std;
const int dydis = 501;
vector<pair<int, int> > pos = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int dist[dydis][dydis] = {0};
int mas[dydis][dydis];
int ans = 0;
int n, m, pe, ps;
void bfs(int e, int s){
    dist[e][s] = mas[e][s];
    queue<pair<int, int> > q;
    q.push({e, s});
    while(!q.empty()){
        e = q.front().first;
        s = q.front().second;
        q.pop();
        for(auto x : pos){
            pe = x.first+e, ps = x.second+s;
            if(pe < 0 || ps < 0 || pe >= n || ps >= m) continue;
            if(dist[pe][ps] < min(dist[e][s], mas[pe][ps])){
                dist[pe][ps] = min(dist[e][s], mas[pe][ps]);
                q.push({pe, ps});
            }
        }
    }
}
int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < dydis; j++){
            dist[i][j] = 1;
        }
    }
    cin >> n >> m;
    priority_queue<pair<int, pair<int, int> > > q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int a; cin >> a;
            mas[i][j] = a;
            q.push({a, {i, j}});
        }
    }
    while(!q.empty()){
        auto v = q.top(); q.pop();
        int e = v.second.first;
        int s = v.second.second;
        if(dist[e][s] >= mas[e][s]) continue;
        ans++;
        bfs(e, s);
    }
    cout << ans;
    return 0;
}
