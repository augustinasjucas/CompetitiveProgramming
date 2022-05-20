#include <bits/stdc++.h>
using namespace std;
bool comp(pair<int, int> &a, pair<int, int> &b){
    if(a.second == b.second) return a.first < b.first;
    return a.second < b.second;

}
int main(){
    int t; cin >> t;
    while(t--){
        int n, m; cin >> m >> n;
        vector<pair<int, int> > mas;
        for(int i = 0; i < n; i++){
            int a, b; cin >> a >> b;
            mas.push_back({a, b});
        }
        sort(mas.begin(), mas.end(), comp);
        int laste = -1, lasts = -1;
        string ans = "YES";
        for(int i = 0; i < n; i++){
            if (i != n-1 && mas[i].second == mas[i+1].second){
                if(laste != -1) {
                    ans = "NO";
                    break;
                }
                i++;
                continue;
            }
            if(laste != -1){
                int keis = mas[i].second-lasts;
                if(keis % 2 == 1) {
                    if(laste == 1) laste = 2;
                    else laste = 1;
                }
                if(laste == mas[i].first){
                    ans = "NO";
                    break;
                }
                laste = -1; lasts = -1;
            }else{
                laste = mas[i].first;
                lasts = mas[i].second;
            }
        }
        if(laste != -1) ans = "NO";
        cout << ans << "\n";
    }
    return 0;
}
