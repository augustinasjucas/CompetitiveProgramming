#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-lopps")
#pragma GCC target("avx2")
using namespace std;
int n, m, l, s, t;
const int dydis = 1e3 + 10;
const long long inf = 1e14;
long long d1[dydis] = {}, d2[dydis] = {};
vector<pair<long long, pair<int, int>  > > brn;
vector<int> un;
vector<pair<int, int> > gr[dydis];
void dij(int v, long long dist[]){
    for(int i = 0; i < n; i++){
        dist[i] = inf;
    }
    int prm = v;
    priority_queue<long long> q;
    dist[v] = 0;
    q.push(-v);
    long long dst;
    long long w;
    while(q.size()){
        v = -q.top() % 1000;
        dst = -q.top() / 1000ll;
        q.pop();
        if(dst != dist[v]) continue;
        if(prm == t && v == s) break;
        if(prm == s && v == t) break;
        for(auto x : gr[v]){
            w = brn[x.second].first;
            if(dist[x.first] > dist[v] + w){
                dist[x.first] = dist[v] + w;
                q.push(-(1000ll * dist[x.first] + x.first));
            }
        }
    }
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> l >> s >> t; 
    for(int i = 0; i < m; i++){
        long long w;
        int a, b; cin >> a >> b >> w; 
        if(w == 0) {
            w = inf;
            un.push_back(i);
        }
        brn.push_back({w, {a, b}});
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
    }
    dij(s, d1);
    if(d1[t] < l){
        cout << "NO";
        return 0;
    }
    for(int i = 0; i < m; i++){
        if(brn[i].first == inf) brn[i].first = 1;
    }
    dij(s, d1);
    if(d1[t] > l){
        cout << "NO";
        return 0;
    }
    int a, b;
    while(true){
        dij(s, d1);
        dij(t, d2);
        long long turi = d1[t];
        if(turi == l) break;
        for(auto x : un) {
            a = brn[x].second.first;
            b = brn[x].second.second;
            long long &w = brn[x].first;
            if(d1[a] + d2[b] + w == turi){
                w +=  l - turi;
                break;
            }else if(d1[b] + d2[a] + w == turi){    
                w += l - turi;
                break;
            }
        }
    }
    cout << "YES\n";
    for(auto x : brn){
        cout << x.second.first << " " << x.second.second << " " << x.first << "\n";
    }
    return 0;
}
