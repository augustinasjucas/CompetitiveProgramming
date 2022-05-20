#include <bits/stdc++.h>
using namespace std;
const int dydis = 1001;
vector<pair<pair<int, int>, pair<int, int> > > vec;
vector<vector<int> > skc;
int mas[dydis][dydis];
vector<int> gr[dydis];
vector<long long> pref[2], suf[2];
bool vis[dydis] = {0};
vector<int> dst[2];
bool galima = 1;
int dist[dydis] = {0};
bool inter(pair<pair<int, int>, pair<int, int> > &a, pair<pair<int, int>, pair<int, int> > &b){
    if(a.first.first > b.second.first || a.second.first < b.first.first) return false;
    if(a.first.second > b.second.second || a.second.second < b.first.second) return false;
    return true;
}
long long dp[101][101] = {0};
long long mn[101][101] = {0};
bool lieciasi(int i1, int i2){
    auto vn = vec[i1];
    auto kt = vec[i2];
    vn.first.first--;
    vn.first.second--;
    vn.second.second++;
    vn.second.first++;
    return inter(vn, kt);
}
void f(int ind){
//    cout << "f(" << ind << "): ";
    for(int i = vec[ind].first.first; i <= vec[ind].second.first; i++){
        for(int j = vec[ind].first.second; j <= vec[ind].second.second; j++){
//            cout << i << ";" << j << "  ";
            skc[ind].push_back(mas[i][j]);
        }
    }
//    cout << endl;
//    cout << "skc [" << ind << "] = ["; for(auto x : skc[ind]) cout << x << " "; cout << "]\n";
}
void dfs(int v, int d){
    if(!galima) return;
    if(vis[v]){
        if(d % 2 != dist[v] % 2){
            galima = 0; 
        }
        return;
    }
    for(auto x : skc[v]) dst[d].push_back(x);
    vis[v] = 1;
    dist[v] = d;
    for(auto x : gr[v]){
        dfs(x, !d);
    }
}
void precalc(int ind){
    int m = dst[ind].size();
    pref[ind].resize(m);
    suf[ind].resize(m);
    for(int i = 0; i < m; i++){
        pref[ind][i] = (i == 0 ? 0ll : pref[ind][i-1]) + dst[ind][i];
    }
    for(int j = m-1; j > -1; j--){
        suf[ind][j] = (j == m-1 ? 0ll : suf[ind][j+1]) + dst[ind][j];
    }
}
long long getVal(int ind, int kur){
    int vt = lower_bound(dst[ind].begin(), dst[ind].end(), kur) - dst[ind].begin();
    long long ret = 0;
    int m = dst[ind].size();
    if(vt != m) ret += suf[ind][vt] - (m - vt) * kur;
    if(vt != 0) ret += 1ll * (vt) * kur - pref[ind][vt-1];
    return ret;
}
void bandyk(int prm, int ant){
    long long vn = getVal(0, prm);
    long long an = getVal(1, ant);
    mn[prm][ant] = min(mn[prm][ant], vn + an);
    mn[ant][prm] = min(mn[ant][prm], vn + an);

    //if(prm == 1 && ant == 2) cout << "dp[" << prm << "][" << ant << "] += " << vn << " + " << an << endl; 
}

int main(){
    int n, m, k; cin >> n >> m >> k;
    vec.resize(k);
    skc.resize(k);
    for(auto &x : vec) {
        cin >> x.first.first >> x.first.second >> x.second.first >> x.second.second;
        x.first.first--;
        x.first.second--;
        x.second.first--;
        x.second.second--;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> mas[i][j];
        }
    }
    for(int i = 0; i < k; i++){
        f(i);
    }
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(i == j) continue;
            if(lieciasi(i, j)){
                gr[i].push_back(j);
  //              cout << i << " - " << j << "\n";
            }
        }
    }
    for(int i = 0; i < k; i++){
        if(vis[i]) continue;
        dst[0].clear();
        dst[1].clear();
        dfs(i, 0);
        if(!galima) break;
        for(int j = 0; j < 101; j++) for(int h = 0; h < 101; h++) mn[j][h] = 1e9;
/*        cout << "esu " << i << ", mas = [\n";
        for(auto x : dst[0]) cout << x << " "; cout << endl;
        for(auto x : dst[1]) cout <<  x<< " "; cout << endl;
        cout << endl;*/
        
        sort(dst[0].begin(), dst[0].end());
        sort(dst[1].begin(), dst[1].end());
        precalc(0);
        precalc(1);
        for(int j = 1; j <= 100; j++){
            for(int h = 1; h <= 100; h++){
                if(j == h) continue;
                bandyk(j, h);
            }
        }
        for(int j = 0; j < 101; j++) for(int h = 0; h < 101; h++) dp[j][h] += mn[j][h];

        
    }
    if(!galima){
        cout << "-1";
        return 0;
    }
    long long ans = 1e18;
    for(int i = 1; i <= 100; i++){
        for(int j = 1; j <= 100; j++){
            if(i == j) continue;
    //        if(i <= 10 && j <= 10)cout << i << "; " << j << "  ->  " << dp[i][j] << endl;
            ans = min(ans, dp[i][j]);
        }
    }
    cout << ans;
    return 0;
}
