#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e3 + 10;
long long n, k;
vector<int> mas;
long long ans[dydis][dydis * 2 + 10] = {0};
long long mod = 998244353;
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        mas.push_back(a);
    }
    ans[0][dydis] = 1;
    for(int i = 0; i < n; i++){ 
        long long nul = 0;
        long long plv = 0;
        long long mnv = 0;
        if(mas[i] == mas[(i+1)%n]){
            mnv = 0;
            nul = k;
            plv = 0;
        }else{
            plv = 1;
            mnv = 1;
            nul = k-2;
        }
//        cout << "i = " << i << ", nul = " << nul << ", pliusV = " << plv << ", minusV = " << mnv << endl;
        for(int j = -n; j <= n; j++){
            ans[i+1][j+dydis] = (ans[i+1][j+dydis] + (ans[i][j+dydis] * nul % mod))%mod;
            ans[i+1][j-1 + dydis] = (ans[i+1][j-1+dydis] + (ans[i][j+dydis] * mnv % mod))%mod;
            ans[i+1][j+1 + dydis] = (ans[i+1][j+1+dydis] + (ans[i][j+dydis] * plv % mod))%mod;
//            cout << "dabar ans[" << i+1 <<  "][" << j-1+dydis << "] = " << ans[i+1][j-1 + dydis] << endl;
        }
    }
    long long answ = 0;
    for(int i = dydis-4; i < dydis+5; i++){
//        cout << i-dydis << ": " << ans[n][i] << endl;
    }
    for(int i = dydis+1; i < dydis*2 + 1; i++){
        answ  = (answ + ans[n][i]) % mod;
    }
    cout << answ;
    return 0;
}
