#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    long long pw[10];
    pw[9] = 1;
    for(int i = 8; i > -1; i--){
        pw[i] = pw[i+1] * 10ll;
    }

    while(t--){
        long long s, n; cin >> s >> n;
        vector<int> dig;
        int sm = 0;
        int S = s;
        for(int i = 0; i < 10; i++){
            dig.push_back(s % 10);
            sm += s % 10;
            s /= 10;
        }
        s = S;
        reverse(dig.begin(), dig.end());
        while(sm < n){
//            cout << "darau!" << endl;
            for(int i = 8; i > -1; i--){
                if(dig[i] > 0){
                    dig[i+1] += 10;
                    dig[i]--;
                    sm += 9;
                    break;
                }
            }
        }
  /*      cout << "dig: ";
        for(auto x : dig) cout << x << " ";
        cout << endl;*/
        vector<long long> ret(n, 0);
        int ind = 0;
        for(int i = 0; i < 10; i++){
            while(dig[i] > 0){
                dig[i]--;
                ret[ind++] += pw[i];
                if(ind == n) break;
            }
            if(ind == n) break;
        }
        for(int i = 0; i < 10; i++){
            while(dig[i] > 0){
                dig[i]--;
                ret[0] += pw[i];
            }
        }
        for(auto x : ret){
            cout << x << " ";
        }
        cout <<"\n";
//        cout << endl;    

    }
    return 0;
}
