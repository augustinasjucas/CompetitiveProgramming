#include <bits/stdc++.h>
using namespace std;
const int dydis = 501;
int n, m;
bool vis[dydis] = {0};
vector<int> gr[dydis];
vector<int> cyc;
vector<int> stekas;
pair<int, int> ignor = {-1, -1};
bool onS[dydis] = {0};
void dfs(int v){
    if(cyc.size() != 0) return;
//    cout << "esu " << v << endl;
    if(vis[v]){
        int u;
        if(!onS[v]) return ;
        while(true){
            u = stekas.back();
            cyc.push_back(u);
            stekas.pop_back();
            if(u == v) break;
        }
        return;
    }
    vis[v] = 1;
    onS[v] = 1;
    stekas.push_back(v);
    for(auto x : gr[v]){
        if(v == ignor.first && x == ignor.second) continue;
        dfs(x);
    }
    if(stekas.size())stekas.pop_back();
    onS[v] = 0;
}
bool veikia(int a, int b){
    for(int i = 0; i < n; i++) vis[i] = 0;
    ignor = {b, a};
    stekas.clear();
    cyc.clear();
    for(int i = 0; i < n; i++){
        if(cyc.size() != 0) break;
        if(vis[i]) continue;
        dfs(i);
    }
    return cyc.size() == 0;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
    }
    for(int i = 0; i < n; i++){
        if(cyc.size() != 0) break;
        if(vis[i]) continue;
        dfs(i);
    }
//    cout << "cyc = ["; for(auto x : cyc) cout << x << " "; cout << "]\n";
    if(cyc.size() == 0){
        cout << "YES";
        return 0;
    }
    auto cc = cyc;
    for(int i = 0; i < cc.size(); i++){
        if(veikia(cc[i], cc[(i+1)%cc.size()])){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
