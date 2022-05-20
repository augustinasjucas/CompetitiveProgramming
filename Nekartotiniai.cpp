#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
long long dbd(long long a, long long b){
    if(b == 0) return a;
    return dbd(b, a%b);
}
const int dydis = 3e7 + 10;
bool is[dydis] = {0};
vector<int> primes;
vector<long long> factorize(long long a){
    vector<long long> ret;
    for(auto x : primes){
        if(a % x != 0) continue;
        ret.push_back(x);
        while(a % x == 0) a /= x;
    }
    if(a != 1) ret.push_back(a);
    return ret;
}
long long kk(long long r, long long a){ // kiek intervale [1; r] daliu is a
    return r / a;
}
vector<long long> prm, rest;
long long kek(long long r, vector<long long> &a, long long dg, long long pl){ // kiek intervale[1; r] daliu is bent vieno a elemento
    if(r == 0) return 0;
    long long mx = (1 << a.size());
    long long ret = 0;
    for(int i = 1; i < mx; i++){
        long long sk = 1; int kek = 0;
        for(int j = 0; j < a.size(); j++){
            if(!(i & (1 << j))) continue;
            sk *= a[j]; kek++;
        }
        ret += kk(r, sk * dg) * ((pl+kek) % 2 == 1 ? 1 : -1);
        cout << "try " << sk << ", " << kk(r, sk) << endl;
    }
    cout << "intervale [1; " << r << "], yra " << ret << " skaiciu daliu is bent vieno is ["; for(auto x : a) cout << x << " "; cout << "]\n" ;
    return ret;
}
long long kekk(long long r, vector<long long> &a){
    if(r == 0) return 0;
    long long mx = (1 << a.size());
    long long ret = 0;
    for(int i = 1; i < mx; i++){
        long long sk = 1; int keek = 0;
        for(int j = 0; j < a.size(); j++){
            if(!(i & (1 << j))) continue;
            sk *= a[j]; keek++;
        }
        ret += kek(r, prm, sk, keek);
    }
//    cout << "intervale [1; " << r << "], yra " << ret << " skaiciu daliu is bent vieno is ["; for(auto x : a) cout << x << " "; cout << "]\n" ;
    return ret;
}

long long tarpP(long long r, long long a){ // intervale [1; r], kiek tarp. pirminiu su a
    long long ans = 0;
    for(int i = 1; i <= r; i++) if(dbd(a, i) == 1) {
        ans++;
//        cout << i << ", ";
    }
    return ans;
}
long long l, r, n, k;
long long maz(long long a){
    long long sq = sqrt(a);
    vector<long long> dal;
    for(int i = 1; i <= sq; i++){
        if(a % i != 0)  continue;
        if(i > k) dal.push_back(i);
        if(i * i != a && a/i > k) dal.push_back(a/i);
    }
    cout << "dal = [" ; for(auto x : dal) cout << x << " "; cout << "]\n";
    long long desn  = kek(r, dal, 1, 0);
    long long kair = kek(l-1, dal, 1, 0);
    return desn-kair;
}
int main(){
    for(auto &x : is) x = 1;
    for(int i = 2; i < dydis; i++){
        if(!is[i]) continue;
        primes.push_back(i);
        for(int j = 2*i; j < dydis; j += i) is[j] = 0;
    }
    cin >> l >> r >> n >> k;
    cout << r-l + 1- maz(n);
    return 0;
    auto fc = factorize(n);
    for(auto x : fc) if(x <= k) prm.push_back(x); else rest.push_back(x);
    prm.push_back(1);
    long long kD = kekk(r, rest);
    long long kK = kekk(l-1, rest);

    cout << r-l+1 + kD - kK ;
    return 0;
}
