#include <bits/stdc++.h>
using namespace std;
vector<pair<long long, long long> > mas;
int n;
long long s;
bool f(long long a){
    vector<long long> lik;
    int mz = 0, dg = 0;
    long long S = 0;
    for(auto x : mas){
        if(x.second < a){
            mz++;
            S += x.first;
        }
        else if(x.first > a){
            dg++;
            S += x.first;
        }
        else{
            lik.push_back(x.first);
        }
    }
    sort(lik.begin(), lik.end());
    if(mz > n/2 || dg > n/2 ) return false;
    for(int i = 0; i < n/2-mz; i++){ // $$..#.%%%
        S += lik[i];
    }
    for(int i = 0; i < n/2-dg; i++){
        S += a;
    }
    S += a;
    if(S > s) return false;

    return true;

}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n >> s;
        mas.resize(n);
        for(auto &x : mas) cin >> x.first >> x.second;
        sort(mas.begin(), mas.end());
        long long l = mas[n/2].first, r = s, mid;
        long long ans = l;
        while(l <= r){
            mid = (l+r)/2;
            if(f(mid)){
                ans = max(ans, mid);
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
