#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
const long long inf = 1e18;
int n, m, A, B;
vector<pair<int, int> > gr1[dydis], gr2[dydis];
long long d1[dydis];
long long d2[dydis];
vector<pair<int, int> > g1[dydis];
int out[dydis] = {}, inc[dydis] = {};
void dij(int a, long long dist[], vector<pair<int, int> > gr[]){
    for(int i = 0; i < n; i++){
        dist[i] = inf;
    }
    priority_queue<pair<long long, int> > q;
    dist[a] = 0;
    q.push({0, a});
    int v; long long dst;
    while(q.size()){
        dst = -q.top().first;
        v = q.top().second;
        q.pop();
        if(dst != dist[v]) continue;
        for(auto x : gr[v]){
            if(dist[x.first] > dist[v] + x.second){
                dist[x.first] = dist[v] + x.second;
                q.push({-dist[x.first], x.first});
            }
        }
    }
}
set<int> brdg;

void darom(){
    set<pair<int, int> > setas;
    setas.insert({0, A});
    while(setas.size()){
        int v = setas.begin() -> second;
        setas.erase(*setas.begin());
        if(setas.size() == 0) {
            if(g1[v].size() == 1){
                brdg.insert(g1[v][0].second);
            }
        }
        for(auto x : g1[v]){
            setas.erase({inc[x.first], x.first});
            inc[x.first]--;
            setas.insert({inc[x.first], x.first});
        }
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    vector<pair<pair<int, int>, int> > brn;
    cin >> n >> m >> A >> B; A--; B--;    
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w; a--; b--;
        gr1[a].push_back({b, w});
        gr2[b].push_back({a, w});
        brn.push_back({{a, b}, w});
    }
    dij(A, d1, gr1);
    dij(B, d2, gr2);
    long long turi = d1[B];
    for(int i = 0; i < m; i++){
        auto &x = brn[i];
        int a = x.first.first;
        int b = x.first.second;
        long long w = x.second;
        if(d1[a] + d2[b] + w == turi){
            g1[a].push_back({b, i});
            out[a]++;
            inc[b]++;
        }   
    }
    darom();
    long long iki, nuo, turiBut;
    for(int i = 0; i < m; i++){
        iki = d1[brn[i].first.first];
        nuo = d2[brn[i].first.second];
        turiBut = (turi - 1) - iki - nuo;
        if(brdg.count(i)){
            cout << "YES\n";
        }else if(turiBut <= 0ll){
            cout << "NO\n";
        }else{
            cout << "CAN " << brn[i].second-turiBut << "\n";
        }
    } 
    return 0;
}
