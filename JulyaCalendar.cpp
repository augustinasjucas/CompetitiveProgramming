#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e6;
long long memDistTo0[dydis + 10];
pair<int,long long> memDistToMinus[dydis+10][10];

int maxDig(long long a){
    long long ret = 0;
    while(a != 0) {ret = max(ret, a % 10); a /= 10;};
    return ret;
}
long long brute(long long a){
    long long ans = 0;
    while(true){
        if(a == 0) break;
        a = a - maxDig(a);
        ans++;
    }
    return ans;
}
long long distTo0(int start){ // start yra [1; 1e6]
    if(memDistTo0[start] != -1)  return memDistTo0[start];
    if(start == 0) return 0;
    return memDistTo0[start] = distTo0(start - maxDig(start)) + 1;
}
pair<int, long long> distToMinus(int start, int mn){
    if(start == 0){
        if(mn == 0) return {0, 0};
        return {-mn, 1};
    }
    if(start <= 9){
        return {min(0, start-mn), 1};
    }
    if(memDistToMinus[start][mn] != make_pair(-1, -1ll)) return memDistToMinus[start][mn];
    auto ret = distToMinus(start-max(maxDig(start), mn), mn) ;
    ret.second++;
    return memDistToMinus[start][mn] = ret;
}
long long distTo0InSecond(long long left, long long right){
    long long ans = 0;
    
    if(left == 0){
        return distTo0(right);
    }
    auto nu = distToMinus(right, maxDig(left));
    ans += nu.second;
    if(nu.first == 0) {
        ans++;
        nu.first = -maxDig(left);
    }
    right = dydis+nu.first;
    left--;
    return distTo0InSecond(left, right) + ans;
}
//map<pair<long long, long long>, pair<long long, long long> > memDistToMinusInSecond;
pair<long long, long long> distToMinusInSecond(long long left, long long right, int mn){
//    if(memDistToMinusInSecond.count({left, right})) return memDistToMinusInSecond[{left, right}];
    long long ans = 0;
    
    if(left == 0){
        return distToMinus(right, mn);
    }
    auto nu = distToMinus(right, maxDig(left));
    ans += nu.second;
    if(nu.first == 0) {
        ans++;
        nu.first = -maxDig(left);
    }
    right = dydis+nu.first;
    left--;
    return distTo0InSecond(left, right) + ans; 
}
int main(){
    for(auto &x : memDistTo0) x = -1;
    for(auto &x : memDistToMinus) for(auto &y : x) y = {-1, -1};
    long long a;
    cin >> a;

    long long left, right, mid;
    
    right = a % dydis;
    mid = a / dydis % dydis;
    left = a / dydis / dydis;
    long long ans = 0;
    while(left != 0 || mid != 0 || right != 0){
        if(left == 0){
            ans += distTo0InSecond(mid, right);
            break;
        }

        


    }
    cout << ans;
    
    
    //        << " vs " << brute(a) ;
    return 0;
}
