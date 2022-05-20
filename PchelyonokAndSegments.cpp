#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 1;
long long inf = 1e18;
const int dd = 449;
bool dp[dydis][dd];
long long a[dydis][dd];
int n;
vector<int> mas;
long long pref[dydis];
long long q(int l, int r){
    return pref[r] - (l == 0 ? 0ll : pref[l-1]);
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n;
        mas.resize(n);
        for(auto &x : mas) cin >> x;
        pref[0] = mas[0];
        for(int i = 1; i < n; i++){
            pref[i] = pref[i-1] + mas[i];
        }

        int sq = sqrt(n);
        for(long long i = 0; i <= n; i++){
            if(i * (i+1) / 2ll <= 1ll*n) sq = i;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= sq; j++){
                a[i][j] = -inf;
            }
        }
        for(int i = n-1; i > -1; i--){
            dp[i][1] = 1;
            a[i][1] = max(1ll * mas[i], (i == n-1 ? -inf : a[i+1][1]));
        }
        int ans = 1;

        for(int j = 2; j <= sq; j++){
            for(int i = n-j-1; i >= 0; i--){
                dp[i][j] = (a[i+j][j-1] > q(i, i+j-1));
                a[i][j] = a[i+1][j];
                if(dp[i][j]) a[i][j] = max(a[i+1][j], q(i, i+j-1));
                if(dp[i][j]) ans = max(ans, j);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}

