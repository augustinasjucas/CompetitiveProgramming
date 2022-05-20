#include <bits/stdc++.h>
using namespace std;
string a, b;
const int dydis = 101;
int n;
int dp[dydis][dydis];
int lcs(int i1, int i2){
    if(i1 == -1 || i2 == -1) return 0;
    if(dp[i1][i2] != -1) return dp[i1][i2];
    if(a[i1] == b[i2]) return dp[i1][i2] = 1 + lcs(i1-1, i2-1);
    return dp[i1][i2] = max(lcs(i1-1, i2), lcs(i1, i2-1));
}
int main(){
    int t; cin >> t;
    while(t--){
        for(int i = 0; i < dydis; i++){
            for(int j = 0; j < dydis; j++){
                dp[i][j] = -1;
            }
        }
        multiset<char> prm, ant;
        cin >> n >> a >> b;
        for(auto x : a) prm.insert(x);
        for(auto x : b) ant.insert(x);
        if(prm != ant){
            cout << "-1\n";
            continue;
        }
        int answ = 1e9;
        int ind = 0;
        int prf = 0;
        for(int j = 0; j < n; j++){
            int ans = 0;
            ind = 0;
            for(int i = j; i < b.size(); i++){
                while(ind != n && a[ind] != b[i]){
                    ind++;
                }
                if(ind == n) break;
                ans++;
                ind++;
            }
//            cout << "j = " << j << ", pos = " << j << " + " << n << " - " << ans << endl;
//            cout << "j = " << j << "ans = " << ans << endl;
            answ = min(answ, n-ans);
        }
        cout << answ << "\n";
    }
    return 0;
}
/*
    aba
    baa
*/
