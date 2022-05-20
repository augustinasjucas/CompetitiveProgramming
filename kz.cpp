#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
long long n, k;
vector<long long> mas;
const int dydis = 2e5 + 100;
long long dp[dydis] = {0};
int negaliButi[dydis] = {0};
int main() {
    cin >> n >> k;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    bool galima = 1;
    for(int i = 0; i+2 < n; i++){
        if(mas[i] != -1 && mas[i] == mas[i+2]) galima = 0;
    }
    if(!galima){
        cout << 0;
        return 0;
    }
    if(k == 2){
        int kas[2] = {-1, -1};
        for(int i = 0; i < n; i++){
            if(mas[i] == -1) continue;
            if(kas[i&1] == -1){
                kas[i & 1] = mas[i];
            }else{
                if(kas[i & 1] != mas[i]){
                    cout << "0";
                    return 0;
                }
            }
        }
        if(kas[0] == kas[1] && kas[0] == -1){
            cout << "2";
            return 0;
        }else{
            cout << "1";
            return 0;
        }
    }

    if(mas[n-1] == -1){
        dp[n-1] = k;
    }else{
        dp[n-1] = 1;
    }
    if(mas[n-2] == -1){
        dp[n-2] = dp[n-1] * k % mod;
    }else{
        dp[n-2] = dp[n-1];
    }

    for(int i = n-3; i > -1; i--){
        if(mas[i+2] != -1){ // jei ten yra skaicius
            negaliButi[i] = mas[i+2];
            dp[i] = dp[i+1] * (k-1) % mod;
        }else{
            if(negaliButi[i+2] == 0){ // anas gali buti bet kas
                dp[i] = dp[i+1] * (k-1) % mod;
            }else{ // anas gali buti bet kas isskyrus vienas
                dp[i] = dp[i+1]
            }
        }
    }
    
    
    return 0;
}
