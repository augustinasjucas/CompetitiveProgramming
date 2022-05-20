#include <bits/stdc++.h>
using namespace std;
long long X, Y, n; 
const long long inf = 1000000000000000000;
string A;
pair<long long, long long> pilnas = {0ll, 0ll};
pair<long long, long long> daryk(long long kek){
    long long kekP = kek/n;
    long long liks = kek - kekP*n;
    pair<long long, long long> ret = {0ll, 0ll};
    for(int i = 0; i < liks; i++){
        char x = A[i];
        if(x == 'U') ret.second++;
        if(x == 'D') ret.second--;
        if(x == 'L') ret.first--;
        if(x == 'R') ret.first++;
    }
    ret.first += pilnas.first*kekP;
    ret.second += pilnas.second*kekP;
    return ret;
}
bool f(long long x){
    pair<long long, long long> kur = daryk(x);
    if(abs(kur.first-X) + abs(kur.second-Y) <= x) return true;
    return false;
}
int main(){
    int a, b; cin >> a >> b >> X >> Y >> n >> A;
    for(auto x : A){
        if(x == 'U') pilnas.second++;
        if(x == 'D') pilnas.second--;
        if(x == 'L') pilnas.first--;
        if(x == 'R') pilnas.first++;
    }
    X -= a; Y -= b;
    long long l = 0, r = inf;
    long long ans = inf;
    while(l <= r){
        long long mid = (l+r)/2;
        if(f(mid)){
            ans = min(ans, mid);
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    cout << (ans == inf ? -1 : ans);
    return 0;
}
