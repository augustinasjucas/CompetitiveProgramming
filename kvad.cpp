#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
using namespace std;
const int dydis = 701;
const __int128_t mod1 = 525823555650749267;
int n, m;
long long inv[dydis][dydis];

bool mas1[dydis][dydis];
long long hsh1[dydis][dydis];

bool mas2[dydis][dydis];
long long hsh2[dydis][dydis];

bool mas3[dydis][dydis];
long long hsh3[dydis][dydis];

bool mas4[dydis][dydis];
long long hsh4[dydis][dydis];

long long pw(long long a, long long x){ // a ^ x
    if(x == 0) return 1;
    __int128_t sk = pw(a, x / 2);
    sk = sk * sk % mod1;
    if(x & 1) sk = 1ll * sk * a % mod1;
    return sk;
}
long long getInd(int i, int j){
   return pw(dydis*dydis, (i * dydis + j));
}
long long getInv(__int128_t x, __int128_t md = mod1){
    return pw(x, md-2);
}
void precalc(bool mas[][dydis], long long hsh[][dydis], int n, int m){
    for(int i = 0; i < n; i++){
        __int128_t pref = 0;
        for(int j = 0; j < m; j++){
            pref = (pref + ((__int128_t)mas[i][j]) * getInd(i, j) % mod1) % mod1;
            hsh[i][j] = ((i == 0 ? 0ll : hsh[i-1][j]) + pref) % mod1;
//            cout << "hsh[" << i << "; " << j << "] = " << hsh[i][j] << endl;
        }
//        cout << endl;
    }
}
long long getVal(int e, int s, int sz, int n, int m, long long hsh[][dydis]){
    if(e + sz - 1 >= n || s + sz - 1 >= m) return -1;
    sz--;
    long long da = 0, ka = 0, dv = 0, kv = 0;
    da = hsh[e+sz][s+sz];
    if(s != 0) ka = hsh[e+sz][s-1];
    if(e != 0) dv = hsh[e-1][s+sz];
    if(e != 0 && s != 0) kv = hsh[e-1][s-1];
    __int128_t vl = ((da + kv) % mod1 - (ka + dv) % mod1 + mod1) % mod1;
    vl = vl * inv[e][s] % mod1;
    return vl;

}
bool hasEq(int sz){
    vector<long long> vec;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i + sz-1 < n && j + sz -1 < m){
                vec.push_back(getVal(i, j, sz, n, m, hsh1));
                vec.push_back(getVal(i, j, sz, n, m, hsh3));
            }
            if(i + sz - 1 < m && j + sz -1 < n){
                vec.push_back(getVal(i, j, sz, m, n, hsh2));
                vec.push_back(getVal(i, j, sz, m, n, hsh4));
            }
        }
    }
    sort(vec.begin(), vec.end());
    for(int i = 1; i < vec.size(); i++){
        if(vec[i] == vec[i-1]) return 1;
    }
    return 0;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for(int i = 0; i < max(n, m); i++){
        for(int j = 0; j < max(n, m); j++){
            inv[i][j] = getInv(getInd(i, j));
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char a; cin >> a ;
            mas1[i][j] = (a == '#');
            mas3[n-i][m-j] = (a == '#');

            mas2[j][n-i-1] = (a == '#');
            mas4[m-j-1][i] = (a == '#');
        }
    }
    precalc(mas1, hsh1, n, m);
    precalc(mas2, hsh2, m, n);
    precalc(mas3, hsh3, n, m);
    precalc(mas4, hsh4, m, n);

    int l = 1; int r = max(n, m), mid, ans = 1;
    while(l <= r){
        mid = (l + r ) /2;
        if(hasEq(mid)){
            ans = mid;
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
    cout << ans;
    return 0;
}
