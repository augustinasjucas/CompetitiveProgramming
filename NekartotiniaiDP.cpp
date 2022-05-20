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
vector<pair<long long, long long> > primatize(long long a) { // iskaido i x1^y1 * x2y2 * ...
    vector<pair<long long, long long> > ret;
    for (auto x : primes) {
        if (a % x != 0) continue;
        long long kek = 0;
        while (a % x == 0) a /= x, kek++;
        ret.push_back({x, kek});
    }
    if (a != 1) ret.push_back({a, 1});
    return ret;
}
vector<long long> change(vector<long long> &a) {
    vector<bool> del(a.size(), 0);
    int sq = a.size();
    for (int i = 0; i < sq; i++) {
        if (del[i]) continue;
        for (int j = i + 1; j < a.size(); j++) {
            if (a[j] % a[i] == 0) del[j] = 1;
        }
    }
    vector<long long> ret;
    for (int i = 0; i < a.size(); i++) 
        if (!del[i]) {
            ret.push_back(a[i]);
        }

    return ret;
}
long long kk(long long r, long long a) { // kiek intervale [1; r] daliu is a
    return r / a;
}
vector<long long> rest;
long long l, r, n, k;
int kur(vector<long long> &a, int pl, long long x){
    return lower_bound(a.begin() + pl, a.end(), x) - a.begin();
}
long long MBK(long long a, long long b){
    return (__int128_t) a * ((__int128_t)b) / ((__int128_t)dbd(a, b));
}
vector<long long> getMBKs(vector<long long> &a){
    vector<long long> ret;
    set<long long> setas;
    for(int i = 0; i < a.size(); i++){
        for(int j = i; j < a.size(); j++){
            setas.insert(MBK(a[i], a[j]));
        }
    }
    for(auto x : setas) ret.push_back(x);
    return ret;

}
long long kek(vector<long long> &a) { // kiek intervale[1; r] daliu is bent vieno a elemento
    if (r == 0) {
        return 0;
    }
    auto b = change(a);
    a = getMBKs(b);
    long long dp[2][a.size() + 1][2]; // kiek yra rinkiniu, kad ju mbk bus a[i], ju dydis mod2 yra j
    for (int l = 0; l < 2; l++) {
        for (int i = 0; i < a.size(); i++) {
            dp[l][i][0] = dp[l][i][1] = 0;
        }
    }

    long long mbk;
//    cout << "A sz = " << a.size() << ", B sz = " << b.size() << endl;
    
    for (int l = 0; l < b.size(); l++) {
        for (int i = 0; i < a.size(); i++) {
            dp[(l + 1) & 1][i][0] = dp[l & 1][i][0], dp[(l + 1) & 1][i][1] = dp[l & 1][i][1];
        }
        int ind;
        for (int i = a.size() - 1; i > -1; i--) {
            mbk = ((__int128_t) b[l] * (a[i])) / ((__int128_t)dbd(b[l], a[i]));
            ind = kur(a, i, mbk);
            for (int j = 0; j < 2; j++) {
                dp[(l + 1) & 1][ind][!j] += dp[l & 1][i][j];
            }
        }
        dp[(l + 1) & 1][kur(a, 0, b[l])][1]++;
    }
    __int128_t ret = 0;
    for (int i = 0; i < a.size(); i++) {
        ret += (dp[b.size() & 1][i][1] - dp[b.size() & 1][i][0]) * (kk(r, a[i]) - kk(l-1, a[i]));
    }
    return ret;
}

vector<long long> ret;
void darom(long long i1, long long san, vector<pair<long long, long long> > &vec) {
    if (vec.size() == i1) {
        ret.push_back(san);
        return ;
    }

    for (int i = 0; i <= vec[i1].second; i++) {
        darom(i1 + 1, san, vec);
        san *= vec[i1].first;
    }
}
vector<long long> dals(long long a) {
    auto prims = primatize(a);
    ret.clear();
    darom(0, 1, prims);
    sort(ret.begin(), ret.end());
    return ret;
}
int main() {
    genPrimes();
    cin >> l >> r >> n >> k;
    auto fc = dals(n);
    for (auto x : fc) if(x > k) rest.push_back(x);
    
    long long sk = kek(rest);
    cout << r - l + 1 - (sk);
    return 0;
}

/*

1 1000000000000000
866421317361600 5000000
 
 */
