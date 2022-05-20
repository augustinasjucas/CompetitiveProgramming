#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 10;
const int inf = 1e9;
int n, m, p;
vector<pair<int, int> > pos = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char mas[dydis][dydis];
pair<int, int> kur[10];
int ex[10];
int ans[10] = {0};
int owns[dydis][dydis];
int dist[dydis][dydis] = {0};
priority_queue<pair<int, pair<int, int> > > q[10];
int main(){
    for(int i = 0; i < dydis; i++) for(int j = 0; j < dydis; j++) owns[i][j] = -1, dist[i][j] = inf;
    cin >> n >> m >> p;
    for(int i = 0; i < p; i++) cin >> ex[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char a; cin >> a;
            if(a != '.' && a != '#'){
                kur[(a-'0'-1)] = {i, j};
                q[(a-'0'-1)].push(make_pair(0, make_pair(i, j)));
                dist[i][j] = 0;
            }
            mas[i][j] = a;
        }
    }
    int ind = 0;
    while(true){
        bool br = 1;
        for(auto x : q) if(!x.empty()) br = 0;
        if(br) break;
        vector<pair<int, int> > nauji;
        while(!q[ind].empty() && -q[ind].top().first <= ex[ind]){

            int dst = -q[ind].top().first;
            int e = q[ind].top().second.first;
            int s = q[ind].top().second.second;
            q[ind].pop();
            if(owns[e][s] != -1 && owns[e][s] != ind) continue;
            owns[e][s] = ind;
            for(auto x : pos){
                int pe = x.first+e;
                int ps = x.second+s;
                if(pe < 0 || ps < 0 || pe >= n || ps >= m || mas[pe][ps] == '#') continue;
                if(owns[pe][ps] != -1) continue;
                if(dist[pe][ps] > dist[e][s] + 1){
                    if(dist[e][s] + 1 > ex[ind]) continue;
                    dist[pe][ps] = dist[e][s] + 1;
                    q[ind].push({-dist[pe][ps], {pe, ps}});
                    if(dist[pe][ps] <= ex[ind]) nauji.push_back({pe, ps});
                }
            }
        }
        while(q[ind].size()) q[ind].pop();
        for(auto x : nauji){
            q[ind].push({0, x});
            dist[x.first][x.second] = 0;
        }
        ind = (ind+1)%p;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < m; j++){
            if(owns[i][j] == -1) continue;
            ans[owns[i][j]]++;
        }
    }
    for(int i = 0; i < p; i++) cout << ans[i] << " ";
    return 0;
}
