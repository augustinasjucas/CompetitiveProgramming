#include <bits/stdc++.h>
using namespace std;
const int dydis = 401;
const int inf = 1e9;
int dp[dydis][dydis] = {0};
bool tinka(string visas, string a, string b){
    for(int i = 0; i <= visas.size(); i++){
        for(int j = 0; j <= a.size(); j++){
            dp[i][j] = -inf;
        }
    }
    dp[0][0] = 0;
//    cout << "visas = " << visas << ", a = [" << a << "], b = " << b << "]\n";
    for(int i = 0; i < visas.size(); i++){
        for(int j = 0; j <= a.size(); j++){
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);

            if(dp[i][j] < b.size() && visas[i] == b[dp[i][j]]){
                dp[i+1][j] = max(dp[i+1][j], dp[i][j] + 1);
            }
            if(j != a.size() && a[j] == visas[i]){
                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
            }
        }
//        cout << "DP[" << i << "]: "; for(int j = 0; j <= a.size(); j++) cout <<j <<", "<< dp[i][j] << ";  ";cout << endl;
    }
//    cout << endl << endl;
    return dp[visas.size()][a.size()] == b.size();
}
int main(){ 
    int t; cin >> t;
    while(t--){
        string a, b; cin >> a >> b;
        string ans = "NO";
        for(int i = 0; i < b.size(); i++){
            string kair = "", desn = "";
            if(i != 0) kair = b.substr(0, i);
            desn = b.substr(i, b.size()-i);
            if(tinka(a, kair, desn)) ans = "YES";
        }
        cout << ans << "\n";
    }
    return 0;
}
