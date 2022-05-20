#include <bits/stdc++.h>
using namespace std;
int n, m;
int N, k;
const int dydis = 251;
int sm[dydis][dydis] = {};
int dp1[dydis][dydis] = {}, dp2[dydis][dydis] = {};
/*
 012345
0**C****
1A****B*
2*******
3*E***D*



*/
const int inf = 1e9;
void rotate(int mas[dydis][dydis], int n, int m){ 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m/2 + (m&1); j++){
            if((m & 1) && j == (m/2 + (m&1)-1) && i >= n/2) continue;
            swap(mas[i][j], mas[n-i-1][m-j-1]);
        }
    }
}
int get(int e1, int s1, int e2, int s2, int pref[dydis][dydis]){
    int kv = 0, ka = 0, dv = 0, da = 0;
    if(e1 != 0 && s1 != 0) kv = pref[e1-1][s1-1];
    if(e1 != 0) dv = pref[e1-1][s2];
    if(s1 != 0) ka = pref[e2][s1-1];
    da = pref[e2][s2];
    return da - dv - ka + kv;
}
void f(int sm[dydis][dydis], int pref[dydis][dydis], int n, int m){
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < m; j++){
            sum += sm[i][j];
            pref[i][j] = (i == 0 ? 0 : pref[i-1][j]) + sum;
        }
    }
}
int f(int e, int s, int sm[dydis][dydis], int pref[dydis][dydis]){
    int ret = inf;
    for(int i = 0; i <= e; i++){
        // bus eilutes [i; e], kiek daugiausiai galiu i kaire nueiti?
        if(get(i, 0, e, s, pref) < k) continue;
        if(get(i, s, e, s, pref) >= k){
            if(get(i, s, e, s, pref) == k) ret = min(ret, (e - i + 2) * 2);
            continue;
        }
        int l = 0; int r = s, mid;
        int fd = inf;
        while(l <= r){ // ieskau desiniausio, kad suma < k
//            cout << "darau!" << l << "; " << r << 
            mid = (l + r) / 2;
            if(get(i, mid, e, s, pref) < k){
                r = mid-1;
                fd = min(mid, fd);
            }else{
                l = mid+1;
            }
        }
        fd--;
        if(get(i, fd, e, s, pref) == k){
//            cout << "get(" << i << ", " << fd << ", " << e << ", " << s << ") = " << get(i, fd, e, s, pref) << endl;
            ret = min(ret, (e-i + s-fd + 2) * 2);
//            cout << "i = " << i << ", fd  = " << fd << endl;
        }
    }
//    cout << "f(" << e << ", " << s << ") = " << ret << endl;
    return ret;
}
void calc(int dp[dydis][dydis], int sm[dydis][dydis], int n, int m){
/*    cout << "sm: \n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << sm[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/
    int pref[dydis][dydis];
    f(sm, pref, n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // dp[i][j] = max(dp[i-1][j], dp[i][j-1], f(i, j));
            dp[i][j] = inf;
            if(i != 0) dp[i][j] = dp[i-1][j];
            if(j != 0) dp[i][j] = min(dp[i][j], dp[i][j-1]);
            dp[i][j] = min(dp[i][j], f(i, j, sm, pref));
        }
    }
}
int main(){
    for(int i = 0; i < dydis; i++) for(int j =0 ; j < dydis; j++) dp2[i][j] = inf;
    cin >> m >> n >> N >> k;

    for(int i = 0; i < N; i++){
        int a, b; cin >> a >> b; a--; b--; swap(a, b);
        a = n-a-1;
        sm[a][b]++;
    }
/*    cout << "sm:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << sm[i][j] << " ";
        }
        cout << endl;
    }
    rotate(sm, n, m);
    cout << "sm:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << sm[i][j] << " ";
        }
        cout << endl;
    }*/
//    cout << "ce" << endl;
    calc(dp1, sm, n, m);
    rotate(sm, n, m);
    calc(dp2, sm, n, m);
    rotate(dp2, n, m);
    int ret = inf;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int st = dp1[i][j];
//            cout << "dp2[" << i+1 << "][" << 0 << "] = " << dp2[i+1][j] << endl;
            int kt = min(dp2[i+1][0], dp2[0][j+1]);
            ret = min(ret, st + kt);
        }
    }
    if(ret >= inf) cout << "NO";
    else cout << ret;

    return 0;
}
