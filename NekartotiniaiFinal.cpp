#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<long long> primes;
void genPrimes() {
    vector<long long> primesx;
    const long long up = 5680;
    const int bbbup = up + 1;
    const long long up2 = up * up;
    bool ret[bbbup + 1] = {};
    for (long long i = 2; i <= up; ++i) {
        if (!ret[i]) {
            primesx.push_back(i);
            for (long long j = 2 * i; j <= up; j += i) {
                ret[j] = true;
            }
        }
    }
    for (long long i = 1, j = up; i <= up2; i += up, j += up) {
        if (j > up2) {
            j = up2;
        }
        memset(ret, 0, up + 1);
        for (long long p : primesx) {
            if (p * p <= j)
                for (long long l = max(2ll, (i + p - 1) / p) * p; l <= j; l += p) {
                    ret[l - i] = true;
                }
        }
        for (int l = max(2ll, i); l <= j; ++l) {
            if (!ret[l - i]) {
                primes.push_back(l);
            }
        }
    }

}
long long dbd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return dbd(b, a % b);
}
vector<long long> factorize(long long a) { // iskaido i x1^y1 * x2y2 * ...
    vector<long long> ret;
    for (auto x : primes) {
        if (a % x != 0) continue;
        long long kek = 0;
        while (a % x == 0) a /= x, kek++;
//        for(int i = 0; i < kek; i++) 
            ret.push_back(x);
    }
    if (a != 1) ret.push_back(a);
    return ret;
}

long long kk(long long r, long long a) { // kiek intervale [1; r] daliu is a
    return r / a;
}
long long l, r, n, k;

long long kek(vector<long long> &a) { // kiek intervale[1; r] daliu is bent vieno a elemento
    long long ret = 0;
    for(int i = 1; i < (1 << a.size()); i++){
        int kek = 0;
        long long sk = 1;
        for(int j = 0; j < a.size(); j++){
            if(!((1 << j) & i)) continue;
            kek++;
            sk *= a[j];
        }
        if(kek & 1){ // pliusas
            ret += kk(r, sk) - kk(l-1, sk);
        }else{ // minusas
            ret -= (kk(r, sk) - kk(l-1, sk));
        }
    }
    return ret;
}

long long coprime(){
    long long ret = 0;
    for(int i = l; i <= r; i++) {
        if(dbd(i, n) == i) ret++;
    }
    return ret;
}
int main() {
    genPrimes();
    cin >> l >> r >> n >> k;
    auto fc = factorize(n);
    vector<long long> rest;
    for(auto x : fc) if(x <= k) rest.push_back(x);  
    long long sk = kek(rest);
    cout << sk + coprime();
    return 0;
}

/*

1 1000000000000000
866421317361600 5000000
 
 */
