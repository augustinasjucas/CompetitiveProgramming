#include <bits/stdc++.h>
using namespace std;
int n, m;
const long long mod = 998244353;
long long balt = 0;
const int dydis = 3e5 + 10;
long long pw[dydis] = {};
long long dp[dydis];
long long vl(long long l){
    if(l == 0) return 1;
    if(l == 1) return 2;
    if(dp[l] != -1) return dp[l];
    return dp[l] = (vl(l-2) + pw[l]) % mod;
    // skaiciuoja 2^(l) + 2 ^ (l-3) + 2^(l-5) + ... + 2^(0)

}
long long rest[dydis];
long long f(long long sz){
    // jei ruozas yra l, koks ats?
    if(sz == 2){
//        cout << "f(" << 2 << ") = " << 2ll * pw[balt-sz] << endl;
        return pw[balt-sz];
    }
    long long ret = pw[balt-sz] * (sz/2) % mod;
//    cout << "jei pilnas, tai bus " << ret << endl;
    for(int l = sz-1; l >= 2; l--){
        long long padeti = sz - l - 1;
        long long kt = 1;
        if(padeti != 0){
            kt = kt * pw[balt - l - 2] % mod;
            kt = kt * 1ll * (l /2) % mod;
        }
//        cout << "padedit = " << padeti << ", kt = " << kt <<" ";
        long long sitas = kt * padeti % mod;
        sitas = (sitas + ((pw[sz-l ] * pw[balt - sz]) % mod * ((l)/2)) % mod) % mod;
        // jei sitoje eileje dedu l dydzio bloka, tai kiek yra budu jam padeti?
        ret = (ret + sitas) % mod;
//        cout << "jei desiu " << l << " dydzio eile, tai bus " <<sitas << endl;
    }
//    cout << "f( " << sz << ") = " << ret << endl;
    return ret;
}
int main(){
    pw[0] = 1;
    for(int i = 1; i < dydis; i++) pw[i] = pw[i-1] * 2ll % mod;
    cin >> n >> m;
    vector<vector<bool> > mas;
    mas.resize(n + 2);
    for(auto &x : mas) x.resize(m + 2);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char a; cin >> a;
            mas[i][j] = a == 'o';
            balt += a == 'o';
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // kairysis langelis;
            if(!mas[i][j]) continue;
            if(!(j == 0 || !mas[i][j-1])) continue;
            if(!mas[i][j+1]) continue;
            int r = j;
            for(int h = j; h <= m; h++) {
                if(!mas[i][h]) {
                    r = h-1;
                    break;
                }
            }
            ans = (ans + f(r - j + 1)) % mod;
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            // kairysis langelis;
            if(!mas[j][i]) continue;
            if(!(j == 0 || !mas[j-1][i])) continue;
            if(!mas[j+1][i]) continue;
            int r = j;
            for(int h = j; h <= n; h++) {
                if(!mas[h][i]) {
                    r = h-1;
                    break;
                }
            }
            ans = (ans + f(r - j + 1)) % mod;
        }
    }
    cout << ans;
    return 0;
}
