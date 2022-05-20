#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
long long dbd(long long a, long long b) {
    if (b == 0) {
        return a;
    }

    return dbd(b, a % b);
}
const long long dydis = 32000000 + 10;
bool is[dydis] = {0};
vector<long long> primes;
vector<long long> factorize(long long a) {
    vector<long long> ret;

    for (auto x : primes) {
        if (a % x != 0) {
            continue;
        }

        ret.push_back(x);

        while (a % x == 0) {
            a /= x;
        }
    }

    if (a != 1) {
        ret.push_back(a);
    }

    return ret;
}
vector<pair<long long, long long> > primatize(long long a) { // iskaido i x1^y1 * x2y2 * ...
    vector<pair<long long, long long> > ret;

    for (auto x : primes) {
        if (a % x != 0) {
            continue;
        }

        long long kek = 0;

        while (a % x == 0) {
            a /= x, kek++;
        }

        ret.push_back({x, kek});
    }

    if (a != 1) ret.push_back({a, 1});
    return ret;
}
long long kk(long long r, long long a) { // kiek intervale [1; r] daliu is a
    return r / a;
}
vector<long long> prm, rest;
long long l, r, n, k;
long long getAns(int i1, long long sk, vector<long long> &a, long long kek) {
    if (i1 == a.size()) {
        if (kek == 0) {
            return 0;
        }

        return (kk(r, sk) - kk(l, sk)) * (kek % 2 == 1 ? 1 : -1);
    }

    long long ret = 0;
    ret += getAns(i1 + 1, sk, a, kek);
    __int128_t bus = sk;
    bus = bus * ((__int128_t)a[i1]) / ((__int128_t)dbd(bus, a[i1]));

    if (bus <= r) {
        ret += getAns(i1 + 1, bus, a, kek + 1);
    }

    return ret;
}
vector<long long> change(vector<long long> &a) {
    vector<bool> del(a.size(), 0);
    int sq = sqrt(a.size());

    for (int i = 0; i < sq; i++) {
        if (del[i]) {
            continue;
        }

        for (int j = i + 1; j < a.size(); j++) if (a[j] % a[i] == 0) {
                del[j] = 1;
            }
    }

    vector<long long> ret;

    for (int i = 0; i < a.size(); i++) if (!del[i]) {
            ret.push_back(a[i]);
        }

//    cout << "is ["; for(auto x : a) cout << x << " "; cout << "] i ["; for(auto x : ret) cout << x << " "; cout << "]\n";
    return ret;
}
long long kek(long long r, vector<long long> &a) { // kiek intervale[1; r] daliu is bent vieno a elemento
    if (r == 0) {
        return 0;
    }
    a = change(a);
    long long ret = getAns(0, 1, a, 0);
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
void genPrimes() {
    vector<long long> primesx;
    const long long up = 3170;
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
int main() {
    genPrimes();
    cin >> l >> r >> n >> k;
    auto fc = dals(n);

    for (auto x : fc) if (x <= k) {
            prm.push_back(x);
        }
        else {
            rest.push_back(x);
        }

//    cout << "tinkami dalikliai: "; for(auto x : rest) cout << x << " "; cout << endl;
    long long kD = kek(r, rest);
    cout << r - l + 1 - (kD);
    return 0;
}
