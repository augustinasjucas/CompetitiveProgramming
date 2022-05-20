#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 1;
long double dp[2][dydis] = {};
int main(){
    // dp[i] -- kiek vidutiniskai zmoniu tures i tasku?
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= m; i++) {
        dp[0][i] = 1;
    } 
    vector<int> mas(n);
    for(auto &x : mas) cin >> x;
    dp[0][mas[0]] = 0;
    int sm = 0;
    for(int i = 0; i < n; i++) sm += mas[i];
    long double isKiek = m-1.0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j <= n*m; j++) dp[(i+1)&1][j] = 0;
        int a = mas[i];
        
        for(int j = 1; j <= n*m; j++){
            // vidutiniskai dp[j] zmoniu tures j tasku
            for(int h = 1; h <= m; h++) {
                if(h == mas[i]) continue;
                dp[(i+1)&1][j+h] += (dp[i&1][j] / isKiek);
            }
        }
        long double suma = 0;
        for(int j = 1; j <= n*m; j++) {
            cout << "vidutiniskai " << dp[i&1][j] << " zmoniu tures " << j << " tasku" << endl;
            suma += dp[i&1][j];
        }
        cout << "suma = " << suma << endl;
        cout << endl;
    }
    for(int j = 1; j <= n*m; j++) {
        cout << "vidutiniskai " << dp[(n-1)&1][j] << " zmoniu tures " << j << " tasku" << endl;
    }
    cout << endl;
    cout << "sm = " << sm << endl;
    long double ans = 0;
    for(int i = 0; i <= n*m; i++) {
        if(i < sm) {
            ans += dp[(n-1)&1][i];
        }
    }

    cout << ans + 1;
    return 0;
}
