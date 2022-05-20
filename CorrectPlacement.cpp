#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<pair<pair<int, int>, int> > mas;
        for(int i = 0; i < n; i++){
            int a, b; cin >> a >> b; if(b < a) swap(a, b);
            // a< b;
            mas.push_back({{-a, -b}, i});
        }
        sort(mas.begin(), mas.end());
        int nxt[n];
        nxt[n-1] = n;
        for(int i = n-2; i > -1; i--){
            if(mas[i].first.first == mas[i+1].first.first){
                nxt[i] = nxt[i+1];
            }else{
                nxt[i] = i+1;
            }
        }
        pair<int, int> suf[n];
        suf[n-1] = {mas[n-1].first.second, n-1};
        for(int i = n-2; i > -1; i--){
            suf[i] = max(suf[i+1], make_pair(mas[i].first.second, i));
        }
        int ans[n];
        for(int i = 0; i < n; i++){
            if(nxt[i] == n){
                ans[mas[i].second] = -2;
            }else{
                auto mx = suf[nxt[i]];
                if(mx.first > mas[i].first.second) ans[mas[i].second] = mas[mx.second].second;
                else ans[mas[i].second] = -2;
            }
        }
        for(int i = 0; i < n; i++){
            cout << ans[i]+1 << " ";
        }
        cout << "\n";
        
    }
    return 0;
}
