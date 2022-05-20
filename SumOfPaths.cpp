#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9 + 7;
const int dydis = 5010;
int n, k, q;
long long dp[dydis][dydis] = {0};
long long kt[dydis][dydis] = {0};
long long sm[dydis] = {0};
int main(){
    cin >> n >> k >> q;

    /*
        dp[i][j] = kiek keliu, kuriu ilgis i ir pirmasis skaicius yra j?
    */

    for(int i = 0; i < n; i++){
        dp[1][i] = 1;
    }
    for(int i = 2; i <= k+1; i++){
        for(int j = 0; j < n; j++){
            long long kair = 0, des = 0;
            if(j != 0) kair = dp[i-1][j-1];
            if(j != n-1) des = dp[i-1][j+1];
            dp[i][j] = (kair+des)%mod;
//            cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
        }
    }
    for(int i = k+1; i >= 1; i--) {
        for(int j = 0; j < n; j++) {
            kt[i][j] = dp[i][j] * dp[k+1-i + 1][j] % mod;
            sm[j] = (sm[j]+kt[i][j])%mod;
        }
    }
    vector<int> mas(n);
    long long rez = 0;
    for(int i = 0; i < n; i++){
        cin >> mas[i];
        rez = (rez + 1ll * mas[i] * sm[i] % mod) % mod;
    }
//    cout << "pirmarez = " << rez << endl;
    while(q--){
        long long ind, x; 
        cin >> ind >> x; ind--;
        rez = (rez - 1ll * mas[ind] * sm[ind] % mod + mod) % mod;
        rez = (rez + 1ll * x * sm[ind] % mod + mod) % mod;
        mas[ind] = x;
        cout << rez << "\n";
    }

    return 0;

}
