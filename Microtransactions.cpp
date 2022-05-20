#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> > offers;
vector<long long> mas;
int n, m;
bool f(long long a){
    if(a >= 400000)  return true;
    int last[n];
    for(int i = 0; i < n; i++){
        last[i] = -1;
    }
    for(int i = 0; i < m; i++){
        if(offers[i].first > a) break;
        last[offers[i].second] = offers[i].first;
    }
    long long curMon = 0;
    long long lastday = 0;
    long long left = 0;
    bool don[n];
    for(int i = 0; i < n; i++) don[i] = 0;
    for(auto x : offers){
        if(x.first > a) break;
        if(last[x.second] != x.first) continue;
        if(don[x.second]) continue;
        don[x.second]= 1;
        curMon += x.first-lastday;
        lastday = x.first;
        long long kek = min(mas[x.second], curMon);
        curMon -= kek;
        left += mas[x.second]-kek;
    }
    for(int i = 0; i < n; i++){
        if(last[i] == -1) left += mas[i];
    }
    curMon += a-lastday;
    if(left*2 > curMon) return false;
    return true;
}
int main(){
    cin >> n >> m;
    mas.resize(n);
    for(int i = 0; i < n; i++){
        cin >> mas[i];
    }
    for(int i = 0; i < m; i++){
        int a, b; cin >> b >> a; a--;
        offers.push_back({b, a});
    }
    sort(offers.begin(), offers.end());
    int l = 1, r = 400000;
    int ans = 1000000000;
    while(l <= r){
        int mid = (l+r)/2;
        if(f(mid)){
            ans = min(ans, mid);
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    if(f(399999) == 1){
        ans = min(ans, 399999);
    }    
    cout << ans;
    return 0;
}
