#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
const int dydis = 2e5 + 19;
int n, d;
vector<int> gr[dydis];
int tevas[dydis];
vector<int> trav;
int enter[dydis], leave[dydis];
int lft[dydis][30];
int he[dydis] = {0};
int dbInd = 0;
int dist[dydis];
void dfs(int v, int came, int auk){
    trav.push_back(v);
    enter[v] = dbInd++;
    tevas[v] = came;
    he[v] = auk;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, auk+1);
    }
    leave[v] = dbInd;
}
void prep(){
    for(int i = 0; i < n; i++){
        lft[i][0] = tevas[i];
    }
    for(int j = 1; j < 30; j++){
        for(int i = 0; i < n; i++){
            lft[i][j] = lft[lft[i][j-1]][j-1];
        }
    }
}
int kilk(int v, int kek){
    for(int i = 29; i > -1; i--){
        if((1 << i) > kek) continue;
        kek -= (1 << i);
        v = lft[v][i];
    }
    return v;
}
int dp[dydis] = {0};
int root(int v){
    trav.clear();
    dbInd = 0;
    dfs(v, -1, 0);
    tevas[v] = v;
    prep();
    int ret = 1;
    reverse(trav.begin(), trav.end());
    cout << "v = " << v << endl;
    cout << "trav = "; for(auto x : trav) cout << x << " ";
    cout << endl;
    for(auto x : trav){
        ret = max(ret, dp[x]);
        cout << "esu " << x << ", dp[x] = " << dp[x] << endl;
        if(v == x) break;
        dp[tevas[x]] = max(dp[x], dp[tevas[x]]);
        dp[x] = max(dp[x], 1);
        if(he[x] < d) continue;
        int u = kilk(x, d);
        dp[u] = max(dp[x] + 1, dp[u]);
    }
    return ret;
}
bool don[dydis] = {0};
void dfs1(int v, int came, int dst){
    dist[v] = dst;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs1(x, v, dst+1);
    }
}
set<pair<int, int> > setas;
int tol(){
    return setas.rbegin()->second;
    for(int i = 0; i < n; i++) dist[i] = -1;
    /**/
}
int toll(){
    dfs1(0, -1, 0);

    pair<int, int> mx = {-1, -1};
    for(int i = 0; i < n; i++) if(!don[i]) mx = max(mx, make_pair(dist[i], i));
    return mx.second;
}
int ans = 0;
void spalvok(int v, int liko, int came){
    if(liko == 0){
        ans++;
        liko = d;
    }
    for(auto x : gr[v]){
        if(x == came) continue;
        spalvok(x, liko-1, v);
    }
}
void pasal(int v, int came, int dd){
    if(dd == 0) return;
    if(!don[v]){
        don[v] = 1;
        setas.erase({dist[v], v});
        return ;
    }
//    cout << "panaikinu " << v << endl;
    for(auto x : gr[v]){
        if(x == came) continue;
        pasal(x, v, dd-1);
    }
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> d;
    for(int i = 1; i < n; i++){
        int a; cin >> a;
        gr[a].push_back(i);
        gr[i].push_back(a);
    }
    int ans = 0;
    int rot = toll();
//    cout << "toll = " << rot << endl;
    for(int i = 0; i < n; i++){
        setas.insert({dist[i], i});
    }
    while(true){
        if(setas.size() == 0) break;
        pasal(tol(), -1, d);
        ans++;
    }
    cout << ans;
    return 0;
}
