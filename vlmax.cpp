#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5  + 100;
vector<int> gr[dydis];
int sz[dydis];
int mxKaim[dydis];
int kas[dydis];
int n;
long long ans = 0;
void dfs(int v, int came){
    sz[v] = 1;
    int ss = 1;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v);
        sz[v] += sz[x];
        ss += sz[x];
        mxKaim[v] = max(mxKaim[v], sz[x]);
    }
    mxKaim[v] = max(mxKaim[v], n - ss);
    if(came != -1){
        ans += min(ss, n - ss) * 2;
    }
    return ;
}
vector<int> vec;
void dfs2(int v, int came){
    vec.push_back(v);
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs2(x, v);
    }
}
vector<int> vecs[dydis];
void merg(int a, int b){
//    cout << vecs[a].size() << " su " << vecs[b].size()  << endl;
    swap(kas[vecs[a].back()], kas[vecs[b].back()]);
    vecs[a].pop_back();
    vecs[b].pop_back();
}
int main(){
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    for(int i =0; i < n; i++) kas[i] = i;
    dfs(0, -1);
    int r = 0;
//    cout << "ran dfs, ans = " << ans << endl;
    for(int i = 0; i < n; i++){
        if(mxKaim[i] <= n / 2){
            r = i;
        }
    }
    vector<vector<int>> vc;
    vector<pair<int, int> > kaims;
    for(auto x : gr[r]){
        kaims.push_back({-sz[x], x});
    }
    
    sort(kaims.begin(), kaims.end());
    set<pair<int, int> > setas;
    int sm = 0;
    for(auto y : kaims){
        auto x = y.second;
//        cout << "turiu " << x << "; [";
        dfs2(x, r);
        vecs[x] = vec;
//        for(auto x : vec) cout << x << " "; cout << "]\n";
        vec.clear();
        setas.insert({vecs[x].size(), x});
        sm += vecs[x].size();
    }
    if(sm % 2 != 0){
        setas.insert({1, r});
        vecs[r] = {r};
        sm += 1;
    }
    while(sm != 0){
        int mz = setas.rbegin() -> second;
        setas.erase({vecs[mz].size(), mz});
        int dd = setas.rbegin() -> second;
        setas.erase({vecs[dd].size(), dd});
//        cout << "merge " << mz << " su " << dd << ": "; for(auto x : vecs[mz]) cout << x << " "; cout << ";   ";
//        for(auto x : vecs[dd]) cout << x << " "; cout << "\n";
        sm -= 2;
        merg(mz, dd);
        if(vecs[mz].size() != 0) setas.insert({vecs[mz].size(), mz});
        if(vecs[dd].size() != 0) setas.insert({vecs[dd].size(), dd});
    }
    
    if(n % 2 == 1){
        swap(kas[r], kas[(r+1) % n]);
    }
    cout << ans << endl;
    for(int i = 0; i  < n; i++){
        cout << kas[i] + 1 << " ";
    }
    
    return 0;
}
