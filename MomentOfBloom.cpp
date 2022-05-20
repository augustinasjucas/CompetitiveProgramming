#include <bits/stdc++.h>
using namespace std;
const int dydis = 3e5 + 10;
int n, m;
int tevas[dydis];
int cnt[dydis] = {};
vector<int> gr[dydis];
int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    tevas[a] = b;
}
vector<int> vec;
bool dfs(int v, int came, int a){
    bool as = (v == a);
    for(auto x : gr[v]){
        if(x == came) continue;
        as = as | dfs(x, v, a);
    }
    if(as) vec.push_back(v);
    return as;
}
vector<int> getPath(int a, int b){
    vec.clear();
    dfs(a, a, b);
    return vec;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dydis; i++) tevas[i] = i;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        if(fP(a) != fP(b)){
            conn(a, b);
            gr[a].push_back(b);
            gr[b].push_back(a);
        }
    }
    vector<pair<int, int> > vec;
    int q; cin >> q;
    while(q--){
        int a, b; cin >> a >> b; a--; b--;
        vec.push_back({a, b});
        cnt[a]++;
        cnt[b]++;
    }
    int nelyg = 0;
    for(int i = 0; i < n; i++){
        nelyg += cnt[i] % 2;
    }
    if(nelyg != 0){
        cout << "NO\n" << nelyg / 2;
        return 0;
    }
    cout << "YES\n";
    for(auto x : vec){
        int a = x.first;
        int b = x.second;
        auto c = getPath(b, a);
        cout << c.size() << "\n";
        for(auto x : c) cout << x+1 << " ";
        cout << "\n";

    }
    return 0;
}
