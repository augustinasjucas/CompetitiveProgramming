#include <bits/stdc++.h>
using namespace std;

const int dydis = 1e6;
bool isPrime[1000010]  = {0};
int  main(){
    for(int i = 2; i < dydis; i++){
        isPrime[i] = 1;
    }
    for(int j = 2; j < dydis; j++){
        if(!isPrime[j]) continue;
        for(int i = 2*j; i < dydis; i+=j){
            isPrime[i] = 0;
        }
    }
    pair<int, int> ans = {0, 0};
    for(int i = 0; i < dydis; i++){
        int sq = sqrt(i);
        vector<int> fac;
        set<int> don;
        vector<int> dal;
        for(int j = 1; j <= sq; j++){
            if(i % j != 0) continue;
            if(isPrime[j] && don.count(j) == 0){
                don.insert(j);
                int cp = i;
                while(cp % j == 0) {
                    cp /= j;
                    dal.push_back(j);
                }
            }
            if(isPrime[i/j] && don.count(i/j) == 0){
                don.insert(i/j);
                int cp = i;
                while(cp % (i/j) == 0) {
                    cp /= (i/j);
                    dal.push_back(j);
                }
            }
        }
        int st = 0;
        for(auto x : dal){
            int kek =0;
            while(x != 0){
                kek++; x/= 10;
            }
            st += kek;
        }
        ans = max(ans , make_pair(st, i));
    }
    cout << ans.first << " " << ans.second;
    int b = ans.second;
}
