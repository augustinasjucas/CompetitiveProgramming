#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    
    vector<pair<long long, long long> > mas(n);
    for(auto &x : mas) cin >> x.first >> x.second;
    for(auto &x : mas) x.first += 1000001, x.second += 1000001;
    int it = 0;
    while(true){
        vector<int> ans;
        for(int i = 1; i <= n; i++) {
            long long a = mas[i-1].first;
            long long b = mas[i-1].second;
            if((a * a + b * b) % 2 == 0){
                ans.push_back(i);
            }
        }
        if(ans.size() == 0 || ans.size() == n){
            ans.clear();
            if((mas[0].first + mas[0].second)%2 == 1){
                for(auto &x : mas){
                    x.first++;
                }
            }
            for(int i = 0; i < n; i++){
                if(mas[i].first % 2 == 1){
                    ans.push_back(i+1);
                }
            }
            /*cout << "mas = [";
            for(auto x : mas) cout << "(" << x.first << ", " << x.second << "), ";
            cout << "]\n";*/
            if(ans.size() == 0 || ans.size() == n){
                for(auto &x : mas) x.first /= 2, x.second /= 2;
                continue;
            }
        }
        cout << ans.size() << "\n";
        for(auto x : ans) cout << x << " ";
        break;
    }
    return 0;
}
