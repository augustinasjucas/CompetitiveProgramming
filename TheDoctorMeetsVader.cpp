#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 10;
int n, m;
vector<int> gr[dydis];
int dist[dydis][dydis] = {};
const int inf = 1e9;
int s, b, k, h;
vector<pair<int, pair<int, int> > > ships;
vector<pair<int, int> > bases;


vector<int> nGr[dydis + dydis + 100];
int dst[dydis + dydis + 100];
int pairL[dydis + dydis + dydis + 100], pairR[dydis + dydis + 100];
int nul = dydis*2-1;
bool dfs(int v){
    if(v == nul) return true;
    for(auto x : nGr[v]){
        if(dst[pairR[x]] == dst[v] + 1){
            if(dfs(pairR[x])){
                pairL[v] = x;
                pairR[x] = v;
                return true;
            }
        }
    }
    dst[v] = inf;
    return false;
}
bool bfs(vector<int> &kaire){
    queue<int> q;
    for(auto &x : kaire){
        if(pairL[x] == nul){
            dst[x]  = 0;
            q.push(x);
        }else{
            dst[x] = inf;
        }
    }
    dst[nul] = inf;
    while(!q.empty()){
        int v = q.front(); q.pop();
        if(dst[v] >= dst[nul]) continue;
        for(auto x : nGr[v]){
            if(dst[pairR[x]] == inf){
                dst[pairR[x]] = dst[v] + 1;
                q.push(pairR[x]);
            }
        }
    }
    return dst[nul] != inf;
}
int matchink(vector<int> &kaire, vector<int> &desine){
    int ret = 0;
    for(auto &x : kaire) pairL[x] = nul;
    for(auto &x : desine) pairR[x] = nul;
    while(bfs(kaire)){
        for(auto x : kaire){
            if(pairL[x] == nul) {
                if(dfs(x)){
                    ret++;
                }
            }
        }
    }
    return ret;
}

int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < dydis; j++){
            dist[i][j] = inf;
        }
    }
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
        dist[a][b] = dist[b][a] = 1;
    }
    for(int i = 0; i < n; i++) dist[i][i] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int h = 0; h < n; h++){
                dist[j][h] = min(dist[j][h], dist[j][i] + dist[i][h]);
            }
        }
    }
    
    cin >> s >> b >> k >> h;
    
    for(int i = 0; i < s; i++){
        int a, b, c; cin >> a >> b >> c; a--;
        ships.push_back({a, {b, c}});
    }
    for(int i = 0; i < b; i++){
        int a, b; cin >> a >> b; a--;
        bases.push_back({a, b});
    }
    for(int i = 0; i < s; i++){
        for(int j = 0; j < b; j++){
            if(dist[ships[i].first][bases[j].first] <= ships[i].second.second && ships[i].second.first >= bases[j].second){
                nGr[i].push_back(s+j);
                nGr[s+j].push_back(i);
    //            cout << i << " laivas su " << j << " baze!" << endl;
            }
        }
    }
    vector<int> kaire, desine;
    for(int i =0 ; i < s; i++) kaire.push_back(i);
    for(int i = s; i < s+b; i++) desine.push_back(i);
    long long mt = matchink(kaire, desine);
    long long ans = mt * k;
  //  cout << "mt = " << mt << endl;
    for(int i = 0; i <= s; i++){
        long long sitas = 0;
        if(i <= (s-mt)) sitas = 1ll * i * h + mt * k;
        else sitas = 1ll * (mt-(i-(s-mt))) * k + (1ll * i * h);
//        cout << "i = " << i << ", sitas = " << sitas << endl;
        ans = min(ans, sitas);
    }
    cout << ans;
    return 0;
}
