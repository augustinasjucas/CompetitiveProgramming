#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
int n, p, k;
vector<int> mas;
const int dydis = 1e5 + 10;
int s[dydis][7];
long long dp[dydis][(1 << 7)] = {};
int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < (1 << 7); j++){
            dp[i][j] = -inf;
        }
    }
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> p >> k;
    mas.resize(n);
    for(int i = 0; i < n; i++) cin >> mas[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++) {
            cin >> s[i][j];
        }
    }
    vector<pair<int, int> > vec;
    for(int i = 0; i < n; i++) vec.push_back({mas[i], i});
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    dp[0][0] = vec[0].first;
    for(int i = 0; i < p; i++){
        dp[0][(1 << i)] = s[vec[0].second][i];
    }
    int kek = 0;
    long long ans = 0;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < (1 << p); j++){
            kek = (__builtin_popcount(j));
            if(kek > i+1) continue;
            dp[i][j] = dp[i-1][j];
            if(i - kek + 1 <= k) dp[i][j] = dp[i-1][j] + vec[i].first;
            for(int h = 0; h < p; h++){
                if(!(j & (1 << h))) continue;
                dp[i][j] = max(dp[i][j], dp[i-1][j ^ (1 << h)] + s[vec[i].second][h]);
            }
            if(j == (1 << p) - 1) ans = max(ans, dp[i][j]);
        }
    }
    cout << ans;
    return 0;
}
