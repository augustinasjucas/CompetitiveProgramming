#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 2e3 + 10;
long long mod1 = 1000000007;

long long mod2 = 100000000000009;
vector<int> gr[dydis];
int inc[dydis] = {0};
vector<string> mas;
vector<long long> be1[dydis];
long long hsh[dydis];
int n;
int dist[dydis] = {0};
bool isBr(int i, int j){
    if(mas[i].size() != mas[j].size() + 1) return false;
    auto kur = lower_bound(be1[i].begin(), be1[i].end(), hsh[j]);
    if(kur == be1[i].end() || *kur != hsh[j]) return false;
    return true;
}
long long pref[dydis], suf[dydis];
void process(int ind){
    int m = mas[ind].size() ;
    pref[0] = mas[ind][0]-'A';
    suf[m-1] = mas[ind][m-1]-'A';
    for(int i = 1; i < m; i++){
        pref[i] = (pref[i-1] * 26ll % mod1 + (mas[ind][i]-'A')) % mod1;
    }
    long long dg1 = 1, dg2 = 1;
    for(int i = m-2; i > -1; i--){
        dg1 = dg1 * 26ll % mod1;
        suf[i] = (suf[i+1] + dg1 * (mas[ind][i]-'A') % mod1) % mod1;
    }
    dg1 = 1, dg2 = 1;
    for(int i = m-1; i > -1; i--){
        long long sitas;
        sitas = ((i == 0 ? 0ll : pref[i-1]) * dg1 % mod1 + (i == m-1 ? 0ll : suf[i+1])%mod1)%mod1;
        dg1 = dg1 * 26ll % mod1;
        be1[ind].push_back(sitas);
    }
    hsh[ind] = pref[m-1];
}
int dfs(int v){
    queue<int> q;
    q.push(v);
    int ret = 0;
    while(!q.empty()){
        v = q.front(); q.pop();
        ret = max(ret, dist[v]);
        for(auto x : gr[v]){
            if(dist[x] < dist[v] + 1){
                dist[x] = dist[v] + 1;
                q.push(x);
            }
        }
    }
    return ret;
}
int f(int ind){
    return dfs(ind);
}
int main(){
    for(int i = 0; i < dydis; i++) dist[i] = 0;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n; mas.resize(n);
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        cin >> mas[i];
        process(i);
    }
    for(auto &x : be1){
        if(x.size() <= 1) continue;
        sort(x.begin(), x.end());
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(isBr(i, j)){
//                cout << mas[i] << " -> "  << mas[j] << endl;
                gr[i].push_back(j);
                inc[j]++;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(inc[i] != 0) continue;
        ans = max(ans, f(i));
    }
    cout << ans;
    return 0;
}
