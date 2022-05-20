#include <bits/stdc++.h>
using namespace std;
const int dydis = 51;
const long long inf = 1e18;
long long mas[dydis][dydis];
long long pref[dydis][dydis];
long long dp[dydis][dydis][dydis][dydis];
int n, m;
long long getAns(int e1, int s1, int e2, int s2){
    long long da = pref[e2][s2];
    long long ka = 0, kv = 0, dv = 0;
    if(s1 != 0) ka = pref[e2][s1-1];
    if(e1 != 0 && s1 != 0) kv = pref[e1-1][s1-1];
    if(e1 != 0) dv = pref[e1-1][s2];
    return da - ka - dv + kv;
}
long long f(int e1, int s1, int e2, int s2) {
    if(e1 == e2 && s1 == s2) return 0;
    if(dp[e1][s1][e2][s2] != -1) return dp[e1][s1][e2][s2];
    long long ret = inf;
    for(int i = e1; i < e2; i++){
        ret = min(ret, f(e1, s1, i, s2) + f(i+1, s1, e2, s2));
    }
    for(int i = s1; i < s2; i++){
        ret = min(ret, f(e1, s1, e2, i) + f(e1, i+1, e2, s2));
    }
    return dp[e1][s1][e2][s2] = ret + getAns(e1, s1, e2, s2);
}
void calc(){
    for(int i = 0; i < n; i++){
        long long sm = 0;
        for(int j = 0; j < m; j++){
            sm += mas[i][j];
            pref[i][j] = (i == 0 ? 0 : pref[i-1][j]) + sm;
        }
    }   
}
int main(){
    for(int i = 0; i < dydis; i++) for(int j = 0; j < dydis; j++) for(int h = 0; h < dydis; h++) for(int l = 0; l < dydis; l++) dp[i][j][h][l] = -1;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> mas[i][j];
        }
    }
    calc();
    cout << f(0, 0, n-1, m-1);
    return 0;
}
