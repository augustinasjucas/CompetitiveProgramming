#include <bits/stdc++.h>
using namespace std;
int n, t;
int sz = 9;
int cnt = 0;
int kiekZero(int l, int r){
    cout << "? " << l+1 << " " << r+1 << endl;
    int ret; cin >> ret;
    return r - l + 1 - ret;
}
int getFirstK(int l, int r, int k, int kk){
    int mid;
    int ret = r;
    r--;
    l += kk-1;
    while(l <= r){
        mid = (l + r) / 2;
        if(kiekZero(0, mid) >= k) ret = min(ret, mid), r = mid-1;
        else l = mid+1;
    }
    return ret;
}
int main(){
    cin >> n >> t;
    vector<int> sums;
    vector<pair<int, int> > intervs;
    intervs.push_back({0, min(n-1, sz-1)});
    sums.push_back(kiekZero(0, intervs.back().second));
    while(true){
        int l = intervs.back().second + 1;
        int r = min(n-1, l + sz-1);
        if(l >= n) break;
        intervs.push_back({l, r});
        sums.push_back(kiekZero(l, r));
    }
    for(int j = 0; j < t; j++){
        int kk = k;
        for(int i = 0; i < sums.size(); i++){
            if(k - sums[i] <= 0){
                int cc = getFirstK(intervs[i].first, intervs[i].second, kk, k);
                cout << "! " << cc+1 << endl;
                sums[i]--;
                break;
            }else{
                k -= sums[i];
            }
        }
        if(j != t-1) cin >> k;
    }
    return 0;
}
