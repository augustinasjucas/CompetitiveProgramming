#include <bits/stdc++.h>
using namespace std;
const int dydis = 3e5 + 10;
int n;
int b[dydis];
int a[dydis];
long long dp[dydis];
vector<int> gr[dydis];

multiset<pair<long long, long long> > vec[51];
void del(multiset<pair<long long, long long> > &setas, pair<long long, long long> a){
    auto kur = setas.find(a);
    if(kur != setas.end()) setas.erase(kur);
}
void putIn(long long k, long long b){
    vec[k].insert({k, b});
}
void takeOut(long long k, long long b){
    del(vec[k], {k, b});
}
long long findMin(long long x){
    long long ret = 1e18;
    for(int i = 0; i < 51; i++){
        for(auto a : vec[i]){
            ret = min(ret, a.first * x + a.second);
            break;
        }
    }
    return ret;
}
void dfs(int v, int came, int h){
    if(v == 0){
        dp[v] = a[v];
    }else{
        dp[v] = findMin(h) + a[v];
    }
    
    putIn(b[v], dp[v] - 1ll * b[v] * h);

    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, h + 1);
    }
    takeOut(b[v], dp[v] - 1ll * b[v] * h);

}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 1; i < n; i++){
        int a; cin >> a;
        gr[i].push_back(a);
        gr[a].push_back(i);
    }
    dfs(0, -1, 0);
    for(int i = 0; i < n; i++){
        cout << dp[i] << " ";
    }
    return 0;
}
