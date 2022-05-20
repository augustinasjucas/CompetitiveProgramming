#include <bits/stdc++.h>
using namespace std;
const int dydis = 11;
const int inf = 1e9;
int n;
pair<int, int> kur[dydis * dydis];
pair<int, int> dist[dydis][dydis][3];
pair<int, int> dp[dydis][dydis][3] = {};
void nul(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < dydis; j++){
            for(int h = 0; h < 3; h++){
                dist[i][j][h] = {inf, inf};
            }
        }
    }
}
vector<pair<int, int> > zirgas = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, 1}, {-2, -1}, {2, -1}, {2, 1}};
void bfs(int e, int s){
    priority_queue<pair<pair<pair<int,int>, int>, pair<int, int> > > q;
    for(int i = 0; i < 3; i++) q.push({{{-dist[e][s][i].first, -dist[e][s][i].second}, e}, {s, i}});
    while(q.size()){
        auto dst = q.top().first.first; dst.first *= -1; dst.second *= -1;
        int e = q.top().first.second;
        int s = q.top().second.first;
        int fig = q.top().second.second;
        q.pop();
        if(dst != dist[e][s][fig]) continue;
        for(int i = 0; i < 3; i++){
            auto pos = make_pair(dist[e][s][fig].first + 1, dist[e][s][fig].second + 1);
            if(dist[e][s][i] > pos){
                dist[e][s][i] = pos;
                q.push({{{-dist[e][s][i].first, -dist[e][s][i].second}, e}, {s, i}});
            }
        }
        if(fig == 0){ // rikis
            for(int h = -n; h <= n; h++){   
                int pe = e + h;
                int ps = s + h;
                if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
                auto pos = make_pair(dist[e][s][fig].first + 1, dist[e][s][fig].second);
                if(pos < dist[pe][ps][fig]){
                    dist[pe][ps][fig] = pos;
                    q.push({{{-dist[pe][ps][fig].first, -dist[pe][ps][fig].second}, pe}, {ps, fig}});
                }
            }
            for(int h = -n; h <= n; h++){   
                int pe = e + h;
                int ps = s - h;
                if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
                auto pos = make_pair(dist[e][s][fig].first + 1, dist[e][s][fig].second);
                if(pos < dist[pe][ps][fig]){
                    dist[pe][ps][fig] = pos;
                    q.push({{{-dist[pe][ps][fig].first, -dist[pe][ps][fig].second}, pe}, {ps, fig}});
                }
            }

        }else if(fig == 1){ // zirgas
            for(auto x : zirgas){
                int pe = x.first + e;
                int ps = x.second + s;
                if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
                auto pos = make_pair(dist[e][s][fig].first + 1, dist[e][s][fig].second);
                if(pos < dist[pe][ps][fig]){
                    dist[pe][ps][fig] = pos;
                    q.push({{{-dist[pe][ps][fig].first, -dist[pe][ps][fig].second}, pe}, {ps, fig}});
                }
            }
        }else{ // bokstas
            for(int h = -n; h <= n; h++){   
                int pe = e + h;
                int ps = s;
                if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
                auto pos = make_pair(dist[e][s][fig].first + 1, dist[e][s][fig].second);
                if(pos < dist[pe][ps][fig]){
                    dist[pe][ps][fig] = pos;
                    q.push({{{-dist[pe][ps][fig].first, -dist[pe][ps][fig].second}, pe}, {ps, fig}});
                }
            }
            for(int h = -n; h <= n; h++){   
                int pe = e;
                int ps = s + h;
                if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
                auto pos = make_pair(dist[e][s][fig].first + 1, dist[e][s][fig].second);
                if(pos < dist[pe][ps][fig]){
                    dist[pe][ps][fig] = pos;
                    q.push({{{-dist[pe][ps][fig].first, -dist[pe][ps][fig].second}, pe}, {ps, fig}});
                }
            }            
        }
    }
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int a; cin >> a; a--;
            kur[a] = {i, j};
        }
    }
    for(int i = 1; i < n*n; i++){
        int e1 = kur[i-1].first;
        int s1 = kur[i-1].second;
        int e2 = kur[i].first;
        int s2 = kur[i].second;
        nul();
        for(int j = 0; j < 3; j++) dist[e1][s1][j] = dp[e1][s1][j];
        bfs(e1, s1);
        for(int j = 0; j < 3; j++) dp[e2][s2][j] = dist[e2][s2][j];
    }
    pair<int, int> mn = {inf, inf};
    for(int i = 0; i < 3; i++){
        mn = min(mn, dp[kur[n*n-1].first][kur[n*n-1].second][i]);
    }
    cout << mn.first << " " << mn.second;
    return 0;
}
