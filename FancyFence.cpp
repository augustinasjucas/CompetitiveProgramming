#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<long long, long long> > vec;
const long long mod = 1000000007 ;
long long sitame (long long w, long long h){
    return (((w*(w+1) / 2ll) % mod) * ((h * (h+1) / 2ll) % mod)) % mod;
}
int main() {
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i].first;
    }
    for(int i = 0; i < n; i++) {
        cin >> vec[i].second;
    }
    long long ans = 0;
    vector<pair<long long, long long> > ms;
    long long s = 0, b;
    for(int i = 0; i < n; i++) {
        ans = (ans + sitame(vec[i].first, vec[i].second)) % mod;
        long long kek = vec[i].second;
        for(int j = ms.size()-1; j > -1; j--){
            if(ms[j].first < vec[i].first) break;
            kek = (kek + ms[j].second) % mod;
            
            s = (s - ( ( (ms[j].first * (ms[j].first+1) / 2ll) % mod) % mod * ms[j].second ) % mod + mod) % mod;

            ms.pop_back();
        }
        ms.push_back({vec[i].first, kek});
        b = (s + (vec[i].first * (vec[i].first + 1) /2ll) % mod * ((kek-vec[i].second+mod)%mod) % mod) % mod;
        s = (s + (vec[i].first * (vec[i].first + 1) /2ll) % mod * kek % mod) % mod;
        long long sitoSnd = vec[i].second;
        ans = (ans + (b * sitoSnd) % mod) % mod; 
    }
    cout << ans;
    return 0;
}
