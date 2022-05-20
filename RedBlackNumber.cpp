#include <bits/stdc++.h>
using namespace std;
bool dp[41][41][41][41] = {};
pair<pair<int, int>, pair<int, int> > came[41][41][41][41];
bool pirm[41][41][41][41] = {};
int main(){
    int t; cin >> t;
    while(t--){
        int n, a, b; cin >> n >> a >> b;
        vector<int> mas;
        for(int i =0; i < n; i++){
            char a; cin >> a;
            mas.push_back(a - '0');
        }
        for(int i = 0; i < n; i++){
            for(int l = 0; l <= n; l++){
                for(int j = 0; j < a; j++){
                    for(int k = 0; k < b; k++){
                        dp[i][l][j][k] = 0;
                        pirm[i][l][j][k] = 0;
                    }
                }
            }
        }
        dp[0][1][mas[0] % a][0] = 1; pirm[0][1][mas[0] % a][0] = 1; came[0][1][mas[0] % a][0] = {{-1, -1}, {-1, -1}};
        dp[0][0][0][mas[0] % b] = 1; pirm[0][0][0][mas[0] % b] = 0; came[0][0][0][mas[0] % b] = {{-1, -1}, {-1, -1}};
        int ans = 41;
        int I, L, J, H;
        for(int i = 0; i < n-1; i++){
            for(int l = 0; l < n; l++){
                for(int j = 0; j < a; j++){
                    for(int h = 0; h < b; h++){
                        if(!dp[i][l][j][h]) continue;
                        dp[i+1][l+1][(j * 10 + mas[i+1]) % a][h] = 1; 
                        came[i+1][l+1][(j * 10 + mas[i+1]) % a][h] = {{i, l}, {j, h}}; 
                        pirm[i+1][l+1][(j * 10 + mas[i+1]) % a][h] = 1;

                        
                        dp[i+1][l][j][(h * 10 + mas[i+1]) % b] = 1;
                        came[i+1][l][j][(h * 10 + mas[i+1]) % b] = {{i, l}, {j, h}};
                        pirm[i+1][l][j][(h * 10 + mas[i+1]) % b] = 0;
                    }
                }
            }
        }
        for(int l = 1; l < n; l++){
            if(dp[n-1][l][0][0]){
                if(ans > abs(l - (n-l))){
                    ans = abs(l - (n-l));
                    I = n-1, J = 0, H = 0, L = l;
                }
            }
        }

        if(ans == 41){
            cout << "-1\n";
        }else{
            string ANS = "";
            int ii, jj, ll, hh;
            while(true){
                ANS.push_back(pirm[I][L][J][H] ? 'R' : 'B');
                ii = came[I][L][J][H].first.first;
                ll = came[I][L][J][H].first.second;
                jj = came[I][L][J][H].second.first;
                hh = came[I][L][J][H].second.second;
                I = ii, L = ll, J = jj, H = hh;
                if(I == -1) break; 
            }
            reverse (ANS.begin(), ANS.end());
            cout << ANS << "\n";
        }
    }
    return 0;
}
