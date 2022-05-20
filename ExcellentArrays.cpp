#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
const long long mod = 1e9 + 7;
long long fact[dydis];

long long pw(int x, int y){ // x ^ y
    if(y == 0) return 1;
    auto sq = pw(x, y / 2);
    sq = sq * sq % mod;
    if(y & 1) sq = sq * x % mod;
    return sq;
}
long long inv(long long a){
    return pw(a, mod-2);
}
long long C(long long x, long long y){ // C{x, y} -> kiek budu isrinkti x dalyku, kai turiu ju y
   // cout << "C(" << x << ", " << y << ")";
    if(x > y) return 0;
    return fact[y] * inv(fact[x]) % mod * inv(fact[y - x]) % mod;
}
bool isL[dydis] = {}, isR[dydis] = {};
vector<int> uniq (vector<int> a){
    sort(a.begin(), a.end());
    vector<int> ret ={a[0]};
    for(auto x : a){
        if(x != ret.back()) ret.push_back(x);
    }
    reverse(ret.begin(), ret.end());
    return ret;

}
int main(){
    fact[0] = 1;
    for(int i = 1; i < dydis; i++) fact[i] = 1ll * fact[i-1] * i % mod;

    int t; cin >> t;
    while(t--){
        int n, l, r; cin >> n >> l >> r;
        for(int i = 0; i <= n; i++) isL[i] = isR[i] = 0;
        vector<pair<int, int> > kaire, desine;
        vector<int> pts;
        for(int i = 1; i <= n; i++){
            if(i - r < 0){
                kaire.push_back({i - r, i});
            }else if(i - r > 0){
                desine.push_back({i - r - 1, i});   
            }
            if(i - l < 0){
                kaire.push_back({i - l + 1, i});
            }else if(i - l > 0){
                desine.push_back({i - l, i});
            }
            pts.push_back(abs(i-l));
            pts.push_back(abs(i-r));
            pts.push_back(abs(i-r-1));
            pts.push_back(abs(i-l+1));
        }
        pts = uniq(pts); 
        sort(kaire.begin(), kaire.end());
        sort(desine.begin(), desine.end()); reverse(desine.begin(), desine.end());
        int ind = 0;
        long long ans = 0;
        int totalL = 0;
        int totalR = 0;
        int common = 0;
        int ind1 = 0;
        pts.push_back(0);
        for(int i = 0; i < pts.size()-1; i++){
            int p = pts[i];
            if(p == 0) continue;
            while(ind1 < kaire.size()){
                auto &x = kaire[ind1];
                if(p > abs(x.first)) break;
                if(isL[x.second]){
                    totalL--;
                    if(isR[x.second]){
                        common--;
                    }
                    isL[x.second] = 0;
                }else{
                    totalL++;
                    if(isR[x.second]){
                        common++;
                    }
                    isL[x.second] = 1;
                }
                ind1++;
            }
            while(ind < desine.size()){
                auto &y = desine[ind];
                if(abs(p) > abs(y.first)) break;
                if(isR[y.second]){
                    totalR--;
                    if(isL[y.second]){
                        common--;
                    }
                    isR[y.second] = 0;
                }else{
                    totalR++;
                    if(isL[y.second]){
                        common++;
                    }
                    isR[y.second] = 1;
                }
                ind++;
            }
            if(totalL + totalR - common != n) continue;
            long long pl = 0;
            int dw = n / 2;
            int up = n / 2 + (n & 1);
            if(totalR - common <= up && dw - (totalL - common) >= 0){
                pl += C(dw - (totalL - common), common); // jei prie kairiojo pridesiu kiek jam truksta iki n / 2
                pl %= mod;
            }
            if(totalR - common <= dw && (n & 1) && up - (totalL - common) >= 0) {
                pl += C(up - (totalL - common), common);
                pl %= mod;
            }
            
            long long k = 0;
            if(i == 0) continue; 
            k = abs(pts[i] - pts[i+1]);
            ans = (ans + k * pl % mod) % mod;
        }
        cout << ans << "\n";
    }
    return 0;
}
