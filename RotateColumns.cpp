#include <bits/stdc++.h>
using namespace std;

int f(vector<int> &sh, vector<pair<int, vector<int> > > &mas){
    int k = sh.size();
    int n = mas[0].second.size();
    int mx[n];
    for(int i = 0; i < n; i++) mx[i] = 0;
    for(int i = 0; i < k; i++){
        int shft = sh[i];
        for(int j = 0; j < n; j++){
            mx[(j+shft)%n] = max(mx[(j+shft)%n], mas[i].second[j]);
        }
    }
    int s = 0;
    for(int i = 0; i < n; i++) s += mx[i];
    return s;
}
int main(){
    int t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        vector<pair<int, vector<int> > > mas(m, {0, {}});
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int a; cin >> a;
                mas[j].second.push_back(a);
                mas[j].first = max(mas[j].first, a);
            }
        }
        sort(mas.begin(), mas.end()); reverse(mas.begin(), mas.end());
        vector<int> shifts(m);
        int kek = min(n, m);
        int mx = pow(n, kek);
        int ans = 0;
        for(int i = 0; i < mx; i++){
            vector<int> shifts;
            int cp =i;
            for(int j = 0; j < kek; j++){
                shifts.push_back(cp%n);
                cp /= n;
            }
            ans = max(ans, f(shifts, mas));
        }
        cout << ans << "\n";

    }
    return 0;
}
