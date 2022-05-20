#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 2e5 + 10;
const long long inf = 1e18;
int n, m;
vector<pair<pair<int, int>, pair<int, int> > > vec;
long long dp[2][dydis];
int s = 0;
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int c, f, v;
        cin >> c >> f >> v;
        vec.push_back({{-f, 0}, {c, v}});
        s += c;
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        int c, f, v;
        cin >> c >> f >> v;
        vec.push_back({{-f, 1}, {c, v}});
    }
    sort(vec.begin(), vec.end());
    long long ans = 0;
    for(int j = 0; j <= s; j++) {
        dp[0][j] = dp[1][j] = -inf;
    }
    dp[1][0] = 0;
    for(int i = 0; i < n+m; i++) {
        for(int j = 0; j <= s; j++) {
            dp[i&1][j] = -inf;
        }
        int c, f, v;
        f = -vec[i].first.first;
        c = vec[i].second.first;
        v = vec[i].second.second;
        for(int j = 0; j <= s; j++) {
            dp[i&1][j] = max(dp[(i+1)&1][j], dp[i&1][j]);
            if(vec[i].first.second == 0) { // perku
                if(j-c >= 0){
                    dp[i&1][j] = max(dp[i&1][j], dp[(i+1)&1][j-c] - v);
                }

            }else{                      // parduodu
                if(j+c <= s){
                    dp[i&1][j] = max(dp[i&1][j], dp[(i+1)&1][j+c] + v);
                }
            }
            ans = max(ans, dp[i&1][j]);
        }
    }
    cout << ans;
    return 0;
}
