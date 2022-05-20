#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, m;
vector<int> gr[dydis];
int da, db, ina, inb;
int dist[dydis];
void dfs(int v, int came, int dst){
    dist[v] = dst;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, dst+1);
    }
}
int diam(){
    dfs(0, -1, 0);
    pair<int, int> mx = {-1, -1};
    for(int i = 0; i < n; i++) mx = max(mx, make_pair(dist[i], i));
    dfs(mx.second, -1, 0);
    for(int i = 0; i < n; i++) mx = max(mx, make_pair(dist[i], i));
    return mx.first;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n >> ina >> inb >> da >> db;
        for(int i = 0; i < n; i++) gr[i].clear();
        ina--; inb--;
        for(int i = 0; i < n-1; i++){
            int a, b; cin >> a >> b; a--; b--;
            gr[a].push_back(b);
            gr[b].push_back(a);
        }       
        int dm = diam();
        if(dm / 2 + (dm & 1) <= da){
//            cout << "dm" << endl;
            cout << "Alice\n";
            continue;
        }
        dfs(ina, -1, 0);
        if(dist[inb] <= da){
            cout << "Alice\n";
            continue;
        }
        if(db >= da*2 + 1){
            cout << "Bob\n";
        }else{
            cout << "Alice\n";
        }
    }
    return 0;
}
