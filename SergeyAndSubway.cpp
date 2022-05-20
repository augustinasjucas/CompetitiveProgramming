#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10; 
vector<int> gr[dydis];
long long sz[dydis][2] = {0};
long long dp[dydis][2] = {0};
int n;
long double ans = 0;
void dfs(int v, int came){
    sz[v][0] = 1;
    sz[v][1] = 0;
    dp[v][0] = dp[v][1] = 0; 

    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v);
        sz[v][0] += sz[x][1];
        sz[v][1] += sz[x][0];
        dp[v][0] += dp[v][1];
        dp[v][1] += dp[v][0];
    }
    cout << "esu " << v << ": \n";
    for(auto x : gr[v]){
        if(x == came) continue;
        cout << "saka " << x << endl;
        ans += (dp[x][1] + sz[x][1]) * (sz[v][0]-sz[x][1]-1)/2; // lyginis-lyginis
        cout << "L-L = " << (dp[x][1] + sz[x][1]) * (sz[v][0]-sz[x][1]-1)/2 << endl;
        ans += (dp[x][0]+1) * (sz[v][1]-sz[x][0]-1)/2; // nelyginis-nelyginis
        cout << "N-N = " <<  dp[x][0]+1 << " * " << (sz[v][1]-sz[x][0]-1) << "/ 2 = " << (dp[x][0]) * (sz[v][1]-sz[x][0]-1)/2 << endl;
        ans += (dp[x][0]+1) * (sz[v][0]-sz[x][0]-1)/2ll; // nelyg-lyg
        ans += (dp[x][1]) * (sz[v][1]-dp[x][1]-1); // lyg-nelyg
    }
    cout << endl;
    ans += dp[v][0]/2 + dp[v][1]/2 + sz[v][1];

}
int main(){
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    dfs(0, -1);
    cout << ans;
    return 0;

}
