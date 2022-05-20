#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
long long dbd(long long a, long long b) {
    if (b == 0) return a;
    return dbd(b, a % b);
}
const int dydis = 32000000 + 10;
bool is[dydis] = {0};
vector<int> primes;
vector<long long> factorize(long long a) {
    vector<long long> ret;
    for(auto x : primes) {
        if(a % x != 0) continue;
        ret.push_back(x);
        while(a % x == 0) {
            a /= x;
        }
        if(a == 1) break;
    }
    if(a != 1) ret.push_back(a);
    return ret;
}
vector<pair<long long, int> > primatize(long long a) { // iskaido i x1^y1 * x2y2 * ...
    vector<pair<long long, int> > ret;
    for(auto x : primes) {
        if(a % x != 0) continue;
        int kek = 0;
        while(a % x == 0) a /= x, kek++;
        ret.push_back({x, kek});
    }
    if(a != 1) ret.push_back({a, 1});
    return ret;
}
long long kk(long long r, long long a) { // kiek intervale [1; r] daliu is a
    return r / a;
}
vector<long long> prm, rest;
long long brute(long long r, vector<long long> &a) {
    long long ans = 0;
    for(long long i = 1; i <= r; i++) {
        bool st = 0;
        for(auto x : a) if(i % x == 0) {st = 1; break;}
        ans += st;
    }

    return ans;
}
__int128_t getAns(int i1, long long sk, vector<long long> &a, int kek, long long r) {
    if(i1 == a.size()) {
        if(kek == 0) return 0;
        return kk(r, sk) * (kek % 2 == 1 ? 1ll : -1ll);
    }
    __int128_t ret = 0;
    ret += getAns(i1 + 1, sk, a, kek, r);
    __int128_t bus = sk;
    bus = bus * ((__int128_t)a[i1]) / ((__int128_t)dbd(bus, a[i1]));
    if (bus <= r) {
        ret += getAns(i1 + 1, bus, a, kek + 1, r);
    }
    return ret;
}
long long n, l, r, k;
long long kek(long long l, long long r, vector<long long> &a) { // kiek intervale[1; r] daliu is bent vieno a elemento
    if (r == 0) {
        return 0;
    }

    long long mx = (1 << a.size());
    long long ret = 0;
    for(int i = 1; i < mx; i++){
        long long sk = 1; int kek = 0;
        for(int j = 0; j < a.size(); j++){
            if(!(i & (1 << j))) continue;
            sk = sk * a[j]; kek++;
        }
        if(sk > k){
//            cout << "pridedu kk(" << sk <<  ") * " << (kek % 2 == 1 ? 1 : -1) << endl;
            ret += (kk(r, (long long)sk)-kk(l-1, sk)) * (kek % 2 == 1 ? 1 : -1);
        }

    }
//    cout << "intervale [" << l << "; " << r << "], yra " << ret << " skaiciu daliu is bent vieno is ["; for(auto x : a) cout << x << " "; cout << "],  " ;
//    cout << "vs " << brute(r, a) << endl;
    return ret;
}



vector<long long> ret;
void darom(int i1, long long san, vector<pair<long long, int> > &vec) {
    if (vec.size() == i1) {
        ret.push_back(san);
        return ;
    }

    for (int i = 0; i <= vec[i1].second; i++) {
        darom(i1 + 1, san, vec);
        san *= vec[i1].first;
    }
}
vector<long long> dals(int a) {
    auto prims = primatize(a);
    ret.clear();
    darom(0, 1, prims);
    sort(ret.begin(), ret.end());
    return ret;
}
int main() {
    for (auto &x : is) {
        x = 1;
    }
    for (int i = 2; i < dydis; i++) {
        if (!is[i]) {
            continue;
        }
        primes.push_back(i);
        for (int j = 2 * i; j < dydis; j += i) {
            is[j] = 0;
        }
    }

    cin >> l >> r >> n >> k;
    auto fc = factorize(n);

    for (auto x : fc){ 
        if (x <= k) {
            rest.push_back(x);
        }
        else {
            rest.push_back(x);
        }
    }

//    cout << "tinkami dalikliai: "; for(auto x : rest) cout << x << " "; cout << endl;
    long long kD = kek(l, r, rest);
    cout << r - l + 1 - (kD);
    return 0;
}
