#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 1;
vector<int> mas[dydis];
int sq;
bitset<dydis> is;
vector<pair<int, int> > ms[dydis];
int ind[dydis] = {};
void solve () {
    int n;
    cin >> n;
    vector<int> visi, un;
    int m = 0;
    for(int i = 0; i < n; i++) {
        int k, a; cin >> k;
        for(int j = 0; j < k; j++) {
            cin >> a;
            visi.push_back(a);
            mas[i].push_back(a);
        }
    }
    sort(visi.begin(), visi.end());
    un.push_back(visi[0]);
    for(auto &x : visi) {
        if(un.back() != x) un.push_back(x);
    }
    for(int i = 0; i < n; i++) {
        for(auto &x : mas[i]) {
            x = lower_bound(un.begin(), un.end(), x) - un.begin();
        }
        m += mas[i].size();
    }
    sq = sqrt(m);
    int i1 = -1, i2 = -1;
    for(int i = 0; i < n; i++) {
        if(mas[i].size() < sq) continue;
        for(int j = 0; j < m; j++) is[j] = 0;
        for(auto &x : mas[i]) {
            is[x] = 1;
        }
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            int cnt = 0;
            for(auto &x : mas[j]) {
                cnt += is[x];
            }
            if(cnt >= 2) {
                i1 = i;
                i2 = j;
                break;
            }
        }
        if(i1 != -1) break;
    }
    if(i1 != -1) {
        for(int i = 0; i < n; i++) {
            mas[i].clear();
        }
        if(i1 != -1){
            cout << i1 + 1 << " " << i2+1 << "\n";
        }else {
            cout << -1 << "\n";
        }
        return ;
    }
    for(int i = 0; i < n; i++) {
        if(mas[i].size() >= sq) continue;
        for(int j = 0; j < mas[i].size(); j++){
            auto &x = mas[i][j];
            for(int h = j+1; h < mas[i].size(); h++){
                auto &y = mas[i][h];
                ms[min(x, y)].push_back({max(x, y), i});
            }
        }
    }
    for(int x = 0; x < un.size(); x++) {
        for(auto &y : ms[x]) {
            if(ind[y.first] != -1) {
                i1 = y.second;
                i2 = ind[y.first];
            }
            ind[y.first] = y.second;
        }
        for(auto &y : ms[x]) {
            ind[y.first] = -1;
        }
        ms[x].clear();
    }
    for(int i = 0; i < n; i++) {
        mas[i].clear();
    }
    if(i1 != -1){
        cout << i1 + 1 << " " << i2+1 << "\n";
    }else {
        cout << -1 << "\n";
    }
}
int main () {
    for(int i = 0; i < dydis; i++) ind[i] = -1;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; 
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
