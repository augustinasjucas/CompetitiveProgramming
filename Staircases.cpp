#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 10;
long long dp[dydis][dydis][2] = {};
bool taken[dydis][dydis] = {};
int n, m;
int like = 0;
int calcKek(int e, int s, int dir){
    int ret = 0;
    while(true){
        if(e >= n || s >= m || taken[e][s]) break;
        ret++;
        if(dir){
            e++;
        }else{
            s++;
        }
        dir = !dir;
    }
    return ret;
}
long long ans = 0;
void prd(int e, int s, int dir, int pl){
    while(true){
        if(e == -1 || s == -1 || taken[e][s]) break;
        dp[e][s][dir] += pl;
        ans += pl;
        if(dir){
            s--;
        }else{
            e--;
        }
        dir = !dir;
    }
}
void change(int e, int s){
    // [0], jei po to i desine
    // [1], jei po to zemyn
    int kek = 0;
    bool bus = !taken[e][s];
    taken[e][s] = 0;
    int k0 = calcKek(e, s, 0) * (bus ? -1 : 1);
    int k1 = calcKek(e, s, 1) * (bus ? -1 : 1);
    prd(e, s, 0, k0);
    prd(e, s, 1, k1);
    taken[e][s] = bus;
    if(bus) like--;
    else like++;
}
void prec(){
    for(int i = n-1; i > -1; i--){
        for(int j = m-1; j > -1; j--){
            dp[i][j][0] = (j == m-1 ? 0 : dp[i][j+1][1])+1;
            dp[i][j][1] = (i == n-1 ? 0 : dp[i+1][j][0])+1;
            ans += dp[i][j][0] + dp[i][j][1];
        }
    }
}
int main(){
    cin >> n >> m;
    prec();
    like = n * m;
    int q; cin >> q;
    while(q--){
        int a, b; cin >> a >> b; a--; b--;
        change(a, b); 
        cout << ans - like << "\n";
    }
    return 0;
}
/*
 
AAAAAA
AAAAAA
AAAAAA
AAAAAA
AAA3AA
 */
