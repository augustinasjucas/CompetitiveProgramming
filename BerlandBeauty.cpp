#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e3 + 10;
const int inf = 1e6;
vector<pair<int, int> > gr[dydis];
int val[dydis];
int n;
bool dfs(int v, int came, int gl, int vl){
    bool inP = 0;
    if(v == gl) return 1;
    for(auto x : gr[v]){
        if(x.first == came) continue;
        bool ip = dfs(x.first, v, gl, vl);
        if(ip) val[x.second] = vl;
        inP = inP | ip;
    }
    return inP;
}
int fd(int v, int came, int gl){
    if(v == gl) return inf;
    int isIn = 0;
    int ret = inf;
    for(auto x : gr[v]){
        if(x.first == came) continue;
        int sk = fd(x.first, v, gl);
        if(sk == -1) continue;
        isIn = 1;
        ret = min(ret, min(sk, val[x.second]));
    }
    if(!isIn) return -1;
    return ret;
}


int main(){
    for(int i = 0; i < dydis; i++) val[i] = inf;
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
    }
    vector<pair<int, pair<int, int> > >q;
    int m; cin >> m;
    bool galima = 1;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        q.push_back({c, {a, b}});
    }
    sort(q.begin(), q.end());
    for(auto x : q){
        dfs(x.second.first, -1, x.second.second, x.first);
    }
    for(auto x : q){
        int mn = fd(x.second.first, -1, x.second.second);
        if(mn != x.first) galima = 0;
    }
    if(!galima){
        cout << "-1";
        return 0;
    }
    for(int i = 0; i < n-1; i++){
        cout << val[i] << " ";
    }

    return 0;
}
