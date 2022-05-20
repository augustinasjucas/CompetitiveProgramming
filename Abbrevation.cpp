#include <bits/stdc++.h>
using namespace std;
const long long dydis = 301;
const long long mod = 1e9 + 7;
int n;
vector<pair<int, int> > mas;
map<string, int> mapas;
long long pref[dydis];
long long pw[dydis];
int dbInd = 0;
int prefs[dydis];
int getInd(string a){
    if(mapas.count(a)) return mapas[a];
    return mapas[a] = dbInd++;
}
void calc(){
    for(int i = 0; i < n; i++){
        pref[i] = ((i == 0 ? 0ll : pref[i-1]) * dydis % mod + mas[i].first) % mod;
    }
}
long long getHsh(int l, int r){
    long long L = (l == 0 ? 0ll : pref[l-1]);
    long long R = pref[r];

    long long ret = (R - L * pw[r-l+1] % mod + mod) % mod;
    return ret;
}
int getSm(int l, int r){
    return prefs[r] - (l == 0 ? 0 : prefs[l-1]);
}
int f(int l, int r) {
    int sz = r - l + 1;
    int kek = 0;
    long long hsh = getHsh(l, r);
    for(int i = 0; i+sz-1 < n; i++){
        if(getHsh(i, i + sz - 1) != hsh) continue;
        kek++;
        i = i + sz - 1;
    }
    if(kek == 1) return 0;
    return kek * getSm(l, r) - kek * sz + (sz-1)*kek ;
}
int main(){
    int sm = 0;
    pw[0] = 1;
    for(int i = 1; i < dydis; i++){
        pw[i] = pw[i-1] * dydis % mod;
    }
    cin >> n;

    for(int i = 0; i < n; i++){
        string a; cin >> a;
        int ind = getInd(a);
        mas.push_back({ind, (int)a.size()});
        sm += a.size();
        prefs[i] = (i == 0 ? 0 : prefs[i-1]) + a.size();
    }
    sm += n-1;
    calc();
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            ans = max(ans, f(i, j));
        }
    }
    cout << sm - ans;
    return 0;
}
