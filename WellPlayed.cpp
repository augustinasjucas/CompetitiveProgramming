#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 19;
int n, a, b;
vector<pair<int, int> > pr;
vector<pair<int, int> > skr;
int kur[dydis] = {0};
long long pref[dydis] = {0};
vector<pair<int, int> > mas;
int main(){
    cin >> n >> a >> b;
    long long sm = 0;
    long long delta = 0;
    for(int i = 0; i < n; i++){
        long long c, d; cin >> c >> d;
        sm += d;
        mas.push_back({c, d});
        skr.push_back({c-d, i});
    }
    if(b == 0){
        cout << sm;
        return 0;
    }
    sort(skr.begin(), skr.end()); reverse(skr.begin(), skr.end());
//    cout << "pref = [";
    for(int i = 0; i < n; i++){
        kur[skr[i].second] = i;
        pref[i] = (i == 0 ? 0ll : pref[i-1]) + max(skr[i].first, 0);
//        cout << pref[i] << " ";
    }
//    cout << "]\n";
    pref[n] = pref[n-1];
    b = min(b, n);
    long long ans = 0;
    for(int i = 0; i < n; i++){ 
        long long st = sm;
        long long dg = (1ll << a) * mas[i].first;
        long long dlt = max(0ll, dg-mas[i].second);
        st += dlt; 
//        cout << "st = " << dlt << " + " << sm << endl;
        if(kur[i] < b){
            st += pref[b-1] - max(skr[kur[i]].first, 0);
//            cout << "pridedu " << pref[b] << " - "<< skr[kur[i]].first << endl;
        }else{
            st += (b == 1 ? 0ll : pref[b-2]);
//            cout << "pridedu " << pref[b-1] << endl;
        }
//        cout << "jei i = " << i << ", st = " << st << ", o dlt = " << dlt << endl << endl;
        ans = max(ans, st);
    }
    cout << ans;
    return 0;
}
