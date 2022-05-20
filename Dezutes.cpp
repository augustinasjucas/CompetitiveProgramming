#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;
vector<int> primesx;
const long long up = 10000;
const long long up2 = up * up;
const long long bbbup = 1e4  + 2;
bool ret[bbbup + 1] = {};
const int dd = 1e8 + 1;
int answe[dd];
const int ddd = 5761455+1;
int primes[ddd];
int curInd = 0;
int kekDal(int a){
    int sq = sqrt(a);
    int ret = 1;
    for(auto x : primes){
        if(a == 1) break;
        if(x > sq){
            break;
        }
        int kek = 0;
        while(a % x == 0) {kek++; a /= x;}
        ret *= kek+1;
    }
    if(a != 1){
        ret *= 2;
    }
    return ret;

}
int L, R, kek;
int ans = 0;
void gen(int ind, long long sk, int dals){
    if(kek % dals != 0) return;
    if(sk > R || dals > kek) return;
    if(dals != kek && dals * 2 > kek) return;
    if(dals != kek && sk * primes[ind] > R) return;
    if(ind > 800){
        if(dals * 4 < kek) return;
    }
    if(ind > 1000) {
        if(dals * 3 < kek) return;
    }
    if(ind > 2500) if(dals * 2 < kek) return ;
    if(ind == curInd || sk * primes[ind] > R) {


        if(L <= sk && sk <= R && dals == kek){
            ans += (L <= sk && sk <= R);
        }
        return;
    }
    for(int i = 0; i <= 27; i++){
        gen(ind+1, sk, dals * (i+1));
        sk *= primes[ind];
        if(sk > R)  break;
    }
}
int main() {
    for (int i = 2; i <= up; ++i) {
        if (!ret[i]) {
            primesx.push_back(i);

            for(int j = 2 * i; j <= up; j += i) {
                ret[j] = true;
            }
        }
    }

    for (int i = 1, j = up; i <= up2; i += up, j += up) {
        if (j > up2) {
            j = up2;
        }

        memset(ret, 0, up + 1);

        for (int &p : primesx) {
            if (p * p <= j)
                for (int l = max(2, (i + p - 1) / p) * p; l <= j; l += p) {
                    ret[l - i] = true;
                }
        }

        for (int l = max(2, i); l <= j; ++l) {
            if (!ret[l - i]) {
                primes[curInd++] = l;
            }
        }
    }
//    cout << primes[2500] << endl;
    cin >> L >> R >> kek;

    if(kek == 1){
        cout << 0;
        return 0;
    }
    if(kek & 1){
        int ret = 0;
        for(int i = 1; i <= 1e4; i++){
            int sk = i * i;
            int kiek = kekDal(sk);
            if(L <= sk && sk <= R && kek == kiek) ret++;
        }
        cout << ret;
        return 0;
    }
    //    cout << "primes: "; for(auto x : primes) cout << x << " ";
    gen(0, 1, 1);
    cout << ans;
}
