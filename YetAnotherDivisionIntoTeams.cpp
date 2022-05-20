#include <bits/stdc++.h>
using namespace std;
const long long inf = 1000000000000000000;
const long long dydis = 2e5 + 10;
long long dp[dydis][7] = {0};
pair<int, int> came[dydis][7];
int color[dydis] = {0};
vector<pair<long long, int> > mas;
int n;
long long f(int ind, int last){
    if(last >= 6) return inf;
    if(ind == n){
        if(last <= 2) return inf;
        
        return mas[ind-1].first - mas[ind-last].first;
    }
    if(dp[ind][last] != -1) return dp[ind][last];
    long long p1 = inf, p2 = inf;
    if(last >= 3){
        p1 = mas[ind-1].first - mas[ind-last].first + f(ind+1, 1);
    }
    p2 = f(ind+1, last+1);
    if(p1 < p2){
        came[ind][last] = {ind+1, 1};
    }else{
        came[ind][last] = {ind+1, last+1};
    }
    return dp[ind][last] = min(p1, p2);
}
int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < 7; j++){
            dp[i][j] = -1;
        }
    }
    cin >> n; mas.resize(n);
    for(auto &x : mas) cin >> x.first;
    for(int i = 0; i < mas.size(); i++){
        mas[i].second = i;
    }
    sort(mas.begin(), mas.end());
    long long ans = f(0, 0);
    int dbI = 0, dbL = 0, col = 0;
    for(int i = 0; i < n; i++){
        auto kk = came[dbI][dbL];
        if(kk.second == 1) col++;
        color[mas[i].second] = col;
        dbI = kk.first;
        dbL = kk.second;
    }
    cout << ans << " " << col << "\n";
    for(int i = 0; i < n; i++){
        cout << color[i] << " ";
    }
    return 0;
}
