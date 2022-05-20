#include <bits/stdc++.h>
using namespace std;
string a, b, c; 
const int dydis = 1e3 + 10;
int dp[dydis][52][52];
int pll[2] = {0};

int calc(string a){
    int ret= 0;
    for(int i = 0; i < a.size()-1; i++){
        auto sub1 = a.substr(0, i+1);
        auto sub2 = a.substr(a.size()-i-1, i+1); // n = 5. 01234
//        cout << sub1 << "-" << sub2 << endl;
        if(sub1 == sub2){
            ret = i+1;
        }
    }
    return ret;
}


int f(int ind, int sz1, int sz2){
    int pind = ind, ps1=sz1, ps2=sz2;
    int pl = 0;
    if(sz1 == b.size()){
        pl++;
        sz1 = pll[0];
    }
    if(sz2 == c.size()){
        pl--;
        sz2 = pll[1];
    }
    if(ind == a.size()) return pl;
    if(dp[pind][ps1][ps2] != -1000000000) {
        return dp[pind][ps1][ps2];
    }

    if(a[ind] != '*'){
        int p1 = sz1, p2 = sz2;
        if(a[ind] == b[sz1]) p1++;
        else p1 = 0;

        if(a[ind] == c[sz2]) p2++;
        else p2 = 0;

        int ret = dp[pind][ps1][ps2] = pl  + f(ind+1, p1, p2);
        return ret;
            
    }else{
        int ret = -1e9;
        for(int i = 0; i <= 25; i++){
            int p1 = sz1;
            int p2 = sz2;
        
            if((i+'a') == b[p1]) p1++;
            else p1 = 0;

            if((i+'a') == c[p2]) p2++;
            else p2 = 0;
            ret = max(ret, pl  + f(ind+1, p1, p2));
        }
        return dp[pind][ps1][ps2] = ret;
    }
}
int main(){
    for(auto &x : dp) for(auto &y : x) for(auto &z : y) z = -1000000000;
    cin >> a >> b >> c;
    pll[0] = calc(b);
    pll[1] = calc(c);
    cout << f(0, 0, 0);

    return 0;
}
