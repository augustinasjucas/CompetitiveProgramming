#include <bits/stdc++.h>
//#pragma GCC optimize("O3")
using namespace std;
vector<long long> primes;
long long ret = 1, kek = 0;
const long long sz = 2e7 + 1;
long long dp[sz] = {0};
long long kekDal(int b){ // kek dalikliu a * b
    return dp[b];
}
//const __int128_t inf = 100000000000000000;
int main(){
    for(auto &x : dp) x = 1;
    
    for(int i = 2; i <= sz-1; i++){
            if(dp[i] == 1){
                for(int j = i; j < sz; j+= i){
                dp[j] *= 2;
            }
        }
    }

//    cout << "sz = " << primes.size() << endl;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        long long c, d, x; cin >> c >> d >> x;
        long long sq = sqrt(x);
        vector<long long> dals;
        for(int i = 1; i <= sq; i++){
            if(x % i == 0){
                dals.push_back(i);
                if(x != i*i) dals.push_back(x/i);
            }
        }
        long long ans = 0;
 //       unordered_set<__int128_t> setas;
        for(auto dbd : dals){
            long long vard = x + d * dbd;
            if(vard % c != 0) {
                continue;
            }
            long long mbk = vard / c;
            if(mbk % dbd != 0) continue;
//            cout << "mbk gali byt " << mbk << ", dbd = " << dbd << endl;
//            cout << "tai pridedu " << kekDal(mbk/dbd) << endl;
   //         if(setas.count(mbk*inf+dbd)) continue;
     //       setas.insert(mbk*inf+ dbd);
            ans += kekDal(mbk/dbd);
        }
        cout << ans << "\n";
    }
    return 0;
}
