#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e3 + 10;
const long long mod = 1e9 + 7;
int n, a, b;
string mas;
short curInd[dydis][dydis];
long long pref[dydis];
long long invers[dydis];
long long pw(long long x, long long y){ // x^y
    if(y == 0) return 1;
    long long skn = pw(x, y/2);
    skn = skn * skn % mod;
    if(y & 1) skn = skn * x % mod;
    return skn;
}
long long getVal(int l, int r){
    __int128_t cur = pref[r];
    if(l != 0){
        cur = (mod + cur - (__int128_t)pref[l-1] * ((__int128_t) pw(26, r-l+1)) % mod)% mod;
    }
    __int128_t iv = 1;
    __int128_t ret = cur * iv;
    ret %= mod;
//    cout << "intervalo " << l << ";" << r << " hash = " << (long long) ret << ", cur = " << (long long) cur << endl;
    return (long long) ret;
}
int findNext(int kur, long long kas, int len){
    for(int i = max(kur, len-1); i <= n; i++){
        if(i == n || getVal(i-len+1, i) == kas) return i;
    }
    return n;
}

long long inv(long long a){
    return pw(a, mod-2);
}
long long inf = 1e9;

int dp[dydis][dydis];

long long f(int ind, int last){ // last - paskutinis indeksas, kuris priklauso dab grupei
    if(ind == n) {
        return 0;
    }
    if(dp[ind][last] != -1) return dp[ind][last];
    bool isSub = 0;
    long long pl = 0;
    if(ind == last){ 
        // ar yra subsequencas?

        int kr = findNext(0, getVal(last, ind), ind-last+1);
        if(kr >= ind){

        }else{
            isSub = 1;
            curInd[ind][last] = kr;
        }
        if(isSub){
            int prm = f(ind+1, ind+1) + min(a, b);
            int ant = f(ind+1, ind+1) + a;
            int tre = f(ind+1, ind);
            if(ind == n-1) tre = inf;
            return dp[ind][last] = min(prm, min(ant, tre) ) ;
        }else{
            return dp[ind][last] = f(ind+1, ind+1) + a;
        }
    }else{
        int kr = findNext(curInd[ind-1][last]+1, getVal(last, ind), ind-last+1);
//        cout << ind << "; " << last << "; " << isB << ", kr = " << kr << endl;
        if(kr >= last){
        }else{
            isSub = 1;
            curInd[ind][last] = kr;
        }
        if(isSub){
            int prm = f(ind+1, ind+1) + b;
            int ant = f(ind+1, last);
            if(ind == n-1) ant = inf;
            return dp[ind][last] = min(prm, ant);
        }else{
            return inf;
        }
    }

}
void precacl(){
    for(int i = 0; i < n; i++){
        pref[i] = ((i == 0 ? 0ll : pref[i-1]) * 26ll % mod + mas[i]-'a')%mod;
//        cout << "pref[" << i << "] = " << pref[i] << endl;
    }
    long long cur = 1;
    for(int i = 0; i <= n; i++){
        invers[i] = inv(cur); cur = cur * 26ll % mod;
    }
}
// 1236184
// 123
int main(){
    for(auto &x : dp) for(auto &y : x) y = -1;
    cin >> n >> a >> b;
    cin >> mas;
    precacl();
    cout << f(0, 0);


    return 0;
}
