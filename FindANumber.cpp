#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 5001;
const int dd = 501;
int dp[dydis][dd] = {0};
vector<int> kur[dd];
pair<int, int> came[dydis][dd];
int mod, goal;
const int inf = 1e9;
int iv = 0;
int main(){
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < dd; j++){
            dp[i][j] = inf;
        }
    }
    cin >> mod >> goal;

    dp[goal][0] = 1;
    came[goal][0] = {goal, 0};
    for(int i = 0; i < mod; i++) kur[i*10%mod].push_back(i); // is i, dauginant is 10 pateksiu i [i*10%mod]
    //    cout << "iv = " << iv << endl;
    for(int i = goal; i > 0; i--){
//        for(int l = 0; l < 50; l++)
        for(int j = mod-1; j > -1; j--){
            pair<int, int> mz = {inf, inf};
//            cout << "darau sm = "<< i << ", md = " << j << endl;
            for(int h = 0; h < 10; h++){
                if(i+h > goal) continue;
                mz = min(mz, {dp[i+h][(j*10+h)%mod], h});
            }
            if(mz.first == inf){
                continue;
            }
  //          cout << "galiu sm = " << i << ", md = " << j << endl;
            if(dp[i][j] > mz.first + 1 || (dp[i][j] == mz.first + 1 && mz.second < came[i][j].second)) came[i][j] = {mz.second + i, (j * 10 +mz.second)%mod};
            dp[i][j] = min(mz.first + 1, dp[i][j]);
        }
//        cout << "i = " << i << ", dabar dp:\n";
//        for(int j = 0; j < mod; j++) cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << "\n";
//        cout << endl;
//        for()
        queue<int> q;
        for(int j = mod-1; j > -1; j--){
            q.push(j);
        }
        while(!q.empty()){
            int v = q.front(); q.pop();
            for(auto x : kur[v]){
                if(dp[i][x] >= dp[i][v] + 1){
                    dp[i][x] = dp[i][v] + 1;
                    came[i][x] = {i, v};
                    q.push(x);
                }
            }
        }
    }

    pair<int, int> rz = {inf, inf};
    for(int i = 1; i < 10; i++){
        rz = min(rz, make_pair(dp[i][i%mod], i));
    }
  //  cout << "rz = {" << rz.first << "; " << rz.second <<"}" <<  endl;
    if(rz.first == inf){
        cout << -1;
        return 0;
    }
//    cout << rz.second << " ir " << rz.first << endl;
    int sm = rz.second; int md = rz.second % mod;
    cout << rz.second;

    while(true){
        if(came[sm][md] == make_pair(sm, md)) break;
        cout << came[sm][md].first - sm;
        int smm = came[sm][md].first;
        int mdd = came[sm][md].second;
//        cout << "\ncame " << sm << "; " << md << " = {" << smm << ", " << mdd << "}\n";
        sm = smm;
        md = mdd;
//        cout << sm << "; " << md << endl;
        if(sm == goal && md == 0) break;
    }
    return 0;
}
