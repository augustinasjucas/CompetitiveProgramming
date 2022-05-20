#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int n, m;
vector<pair<int, int> > mas;
const int dydis = 81;
const int dd = 100010;
int dp[dydis][dd];
//pair<int, int> goTo[dydis][dd] = {};
int f(int ind, int r){ // esu ind'ajame, jo r yra r;
    int x = mas[ind].first;
    int tol = x + r;
    if(tol >= m) return 0;
    if(dp[ind][r] != -1) return dp[ind][r];
    int ret = inf;
    for(int j = ind + 1; j < n; j++){
//        if(ind == 0 && r== 42) cout << "j = " << j << endl;
        if(mas[j].first + mas[j].second <= tol) continue;
        int newR = max(0, mas[j].first-mas[j].second - (tol + 1));
        int rz = f(j, mas[j].second + newR) + newR;
        if(ret > rz){
            ret = rz;
//            goTo[ind][r] = {j, mas[j].second + newR};
//            if(ind == 0 && r == 42){
//                cout << "padaray " << j << "; " << mas[j].second + newR << endl;
//            }
        }
    }
    int ps = f(ind, r+1)+1;
    if(ps < ret){
        ret = ps;
//        goTo[ind][r] = {ind, r+1};
//        if(ind == 0 && r == 42)cout << "rt " << ind << "; " << r+1 << endl;
    }
//    cout << "f(" << ind << ", " << r<< ") = " << ret << "\n";
    return dp[ind][r] = ret;
}
/*void dar(int a, int b){
    while(true){
        if(a == -1) break;
        cout << a << "; " << b << "\n";
        int pa = a, pb = b;
        a = goTo[pa][pb].first, b = goTo[pa][pb].second;
    }
    cout << endl;
}*/
int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < dd; j++) {
            dp[i][j] = -1;
//            goTo[i][j] = {-1, -1};
        }
    }
    cin >> n >> m;
    mas.resize(n);
    for(auto &x : mas) cin >> x.first >> x.second;
    sort(mas.begin(), mas.end());
    int ans = 1e9;
//    cout << "mas = ["; for(auto x : mas) cout << "(" << x.first << "; " << x.second << "),  ";
//    cout << endl;
    for(int i = 0; i < mas.size(); i++){
//        cout << "jei imu (" << mas[i].first << ";" << mas[i].second << "), tai prie ats reiks pridet " << max(mas[i].first-1-mas[i].second, 0) << endl;
        ans = min(ans, f(i, max(mas[i].first-1, mas[i].second)) + max(max(mas[i].first-1, mas[i].second)-mas[i].second, 0));
//        cout << "tada atsakymas pasidaro " << ans << endl << endl;
    }
//    dar(0, 42);
//    cout << endl;
    cout << ans;
    return 0;
}
