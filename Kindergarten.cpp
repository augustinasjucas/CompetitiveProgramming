#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int dydis = 1e6 + 10;
vector<long long> mas;
long long dp[dydis][7];
int n;
long long f(int i, int dd){
    long long mn = inf;
    long long mx = -inf;
    for(int j = i-dd; j <= i; j++){
        mn = min(mn, mas[j]);
        mx = max(mx, mas[j]);
    }
    return mx - mn;
}
vector<long long> f(vector<long long> mas){
    vector<long long> ret;
    if(mas.size() >= 1) ret.push_back(mas[0]);
    if(mas.size() >= 2) ret.push_back(mas[1]);
    for(int i = 2; i < mas.size(); i++){
        if(ret[ret.size()-1] == ret[ret.size()-2] && ret.back() == mas[i]) continue;
        ret.push_back(mas[i]);
    }
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    long long ans = 0;
    int l = 0;
    mas = f(mas);
    n = mas.size();
    vector<int> vec1;
    set<int> vec2;
    
    for(int i = 0; i < n; i++){
        if(i == 0 || i == n-1){
            vec1.push_back(i);
        }else{
            if(mas[i] == mas[i-1]){
                if(i == 1){
                    vec1.push_back(i);
                }else if(mas[i-2] <= mas[i-1] && mas[i] <= mas[i+1]){
                    continue;
                }else if(mas[i-2] >= mas[i-1] && mas[i] >= mas[i+1]){
                    continue;
                }else{
                    vec1.push_back(i-1);
                    vec1.push_back(i);
                }
                continue;
            }
            if(mas[i-1] <= mas[i] && mas[i] <= mas[i+1]) continue;
            if(mas[i-1] >= mas[i] && mas[i] >= mas[i+1]) continue;
            vec1.push_back(i);
        }
    }
    for(auto x : vec1){
        if(x - 1 >= 0) vec2.insert(x-1);
        vec2.insert(x);
        if(x + 1 < n) vec2.insert(x+1);
    }
    vector<long long> vec;
    for(auto x : vec2) vec.push_back(mas[x]);
//    cout << "vec: "; for(auto x : vec) cout << x << " ";
    

    mas = vec;
    n = mas.size();

    for(auto &x : dp) for(auto &y : x) y = -inf;
    dp[0][0] = 0; 
    for(int i = 1; i < n; i++){
        for(int j = 0; j < min(i, 5); j++){
            dp[i][j+1] = dp[i-1][j] - f(i-1, j) + f(i, j+1);
        }
        dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2], dp[i-1][3], dp[i-1][4]});
    }
    cout << max({dp[n-1][0], dp[n-1][1], dp[n-1][2], dp[n-1][3], dp[n-1][4]});


    return 0;
}
