#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<string> mas;
int n; 
const int dydis = 1e6 + 10;
pair<int, int> dp[dydis][2];
pair<int, int> f(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < 2; j++){
            dp[i][j] = {-1, -1};
        }
    }
    for(int ind = n-1; ind > -1; ind--){
        for(int changed = 0; changed < 2; changed++){
            if(ind ==0 && changed) continue;
            if(ind == n-1){
                char pries = (changed ? mas[ind-1][1] : mas[ind][0]);
                if(pries == mas[ind][1]) dp[ind][changed] = {1, 0};
                else dp[ind][changed] = {0, 0};
                continue;
            }
            auto vn = dp[ind+1][0];
            auto kt = dp[ind+1][1]; // jei swap
            kt.second--;
            char pries;
            if(changed) pries = mas[ind-1][1];
            else pries = mas[ind][0];
            if(mas[ind][1] == pries) vn.first++;
            if(mas[ind+1][0] == pries) kt.first++;
            dp[ind][changed] = max(kt, vn);           
        }
    }
    return dp[0][0];
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++){
        string a; cin >> a;
        mas.push_back(a);
    }
    pair<int, int> ans = {0, 0};
    
    ans = max(ans, f());

    swap(mas[0][0], mas[n-1][1]);
    auto kt = f(); kt.second--; // nes minusas
    ans = max(ans, kt);
    
    cout << ans.first << " " << -ans.second;
    
    return 0;
}
