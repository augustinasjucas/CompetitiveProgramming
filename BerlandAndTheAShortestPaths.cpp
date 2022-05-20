#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
const int inf = 1e9;
int n, m, k;
int dist[dydis] = {0};
vector<int> srt;
vector<string> opts;
vector<pair<int, int> > gr[dydis];
string curTaken;
void bfs(){
    for(auto &x : dist) x = inf;
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(auto x : gr[v]){
            if(dist[x.first] > dist[v] + 1){
                dist[x.first] = dist[v] + 1;
                q.push(x.first);
            }
        }
    }
    vector<pair<int, int> > vec;
    for(int i = 1; i < n; i++){
        vec.push_back({dist[i], i});
    }
    sort(vec.begin(), vec.end());
    for(auto x : vec) srt.push_back(x.second);
}
void dar(int ind){
    if(ind == n-1){

        opts.push_back(curTaken);
        return;
    }
    int v = srt[ind];
    for(auto x : gr[v]){
        if(dist[x.first] != dist[v] - 1) continue;
        if(opts.size() >= k) break;
        curTaken[x.second] = '1';
        dar(ind+1);
        curTaken[x.second] = '0';
    }
}
int main(){
    cin >> n >> m >> k;
    for(int i = 0; i < m; i++) curTaken.push_back('0');
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
    }
    bfs();
    dar(0);
    cout << opts.size() << "\n";
    for(auto x : opts){
        cout << x << "\n";
    }
    return 0;
}
