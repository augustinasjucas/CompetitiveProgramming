#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
const int dd = 51;
const int inf = 1e9;
int n, m;
vector<pair<int, int> > gr[dydis];
int ans[dydis];
int dist[dydis][dd][3];
void dij(){
    priority_queue<pair<pair<int, int>, pair<int, int> > > q;
    q.push({{0, 0}, {0, 0}});
    dist[0][0][0] = 0;
    while(!q.empty()){
        int dst = -q.top().first.first;
        int v = q.top().first.second;
        int cameVal = q.top().second.first;
        int esuKelintas = q.top().second.second;
        q.pop();
//        cout << "esu v=" << v << "; came=" << cameVal << ", kelyje esu " << esuKelintas << ", dst = " << dst << endl;
        if(esuKelintas == 2 || esuKelintas == 0){
            ans[v] = min(dst, ans[v]);
        }
        for(auto x : gr[v]){
            if(esuKelintas == 0){
                if(dist[x.first][x.second][1] > dist[v][cameVal][esuKelintas]){
                    dist[x.first][x.second][1] = dist[v][cameVal][esuKelintas];
                    q.push({{-dist[x.first][x.second][1], x.first}, {x.second, 1}});
                }
            }else if(esuKelintas == 1){
                 if(dist[x.first][x.second][2] > dist[v][cameVal][esuKelintas] + (cameVal+x.second) * (cameVal+x.second)){
                    dist[x.first][x.second][2] = dist[v][cameVal][esuKelintas] + (cameVal+x.second) * (cameVal+x.second);
                    q.push({{-dist[x.first][x.second][2], x.first}, {x.second, 2}});
                }               
            }else if(esuKelintas == 2){
                  if(dist[x.first][x.second][1] > dist[v][cameVal][esuKelintas]){
                    dist[x.first][x.second][1] = dist[v][cameVal][esuKelintas] ;
                    q.push({{-dist[x.first][x.second][1], x.first}, {x.second, 1}});
                }                              
            }
        }
    }
}
int main(){
    for(int i = 0; i < dydis; i++){
        ans[i] = inf;
        for(int j = 0; j < dd; j++){
            for(int h = 0; h < 3; h++){
                dist[i][j][h] = inf;
            }
        }
    }
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c});
    }
    dij();
    for(int i = 0; i < n; i++){
        cout << (ans[i] == inf ? -1 : ans[i]) << " ";
    }
    return 0;
}
