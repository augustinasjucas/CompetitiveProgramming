#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
const long long mod = 1e9 + 7;
int sm[61] = {0};
int n;
long long orW(long long a){
    long long db = 1;
    long long ret = 0;
    for(int i = 0; i < 61; i++){
        if(a & db){
            ret += (n) * (db%mod) % mod;
            ret %= mod;
        }else{
            ret += sm[i] * (db%mod) % mod;
            ret %= mod;
        }
        db = db << 1;
    }
    return ret;
}
long long andW(long long a){
    long long db = 1;
    long long ret = 0;
    for(int i = 0; i < 61; i++){
        if(a & db){
            ret += sm[i] * (db%mod) % mod;
            ret %= mod;
        }else{
            ret += 0 ;
        }
        db = db << 1;
    }
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        for(auto &x : sm) x= 0;
        cin >> n;
        vector<long long> mas; mas.resize(n);
        for(auto &x : mas){
            cin >> x;
            long long cp = x;
            for(int i = 0; i < 61; i++){
                sm[i] += (cp&1);
                cp = cp >> 1;
            }
        }
        long long s2 = 0;
        for(int j = 0; j < n; j++){
            long long orai = orW(mas[j]);
            long long andai = andW(mas[j]);
            s2 += andai*orai % mod;
            s2 %= mod;
        }
        cout << s2 <<  "\n";
        
    }
    return 0;
}
