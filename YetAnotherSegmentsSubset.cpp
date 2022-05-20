#include <bits/stdc++.h>
using namespace std;
struct tree{
    vector<int> l, r;
    vector<int> mx;
    int n;
    int dbInd = 0;
    void build(int v = 1) {
        if(v >= n) {
            l[v] = r[v] = dbInd++;
        }else {
            build(v*2);
            build(v*2+1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
    }
    tree(int dd) {
        l.resize(dd*2+1);
        r.resize(dd*2+1);
        mx.resize(dd*2+1);
        n = dd;
        build(1);
    }
    void change(int v, int L, int R, int x) {
        if(L <= l[v] && r[v] <= R) {
            mx[v] = max(mx[v], x);
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else {
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            mx[v] = max(mx[v*2], mx[v*2+1]);
        }
    }
    void changee(int v, int L, int R, int x) {
        if(L <= l[v] && r[v] <= R) {
            mx[v] = x;
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else {
            changee(v*2, L, R, x);
            changee(v*2+1, L, R, x);
            mx[v] = max(mx[v*2], mx[v*2+1]);
        }
    }
    long long getMax(int v, int L, int R){
        if(L <= l[v] && r[v] <= R) {
            return mx[v];
        }else if(R < l[v] || r[v] < L) {
            return 0;
        }else {
            return max(getMax(v*2, L, R), getMax(v*2+1, L, R));
        }
    }

};
const int dydis = 3e3 + 10;
tree medis(2e5 + 10);
vector<pair<int, int> > mas;
int n;
int dp[dydis];
int val(int ind) {
    if(dp[ind] != -1) return dp[ind];
    vector<int> sitie;
    for(int i = 0; i <= n; i++) {
        if(mas[ind].first <= mas[i].first && mas[i].second <= mas[ind].second && i != ind) {
            sitie.push_back(i);
        }
    }
    int ret = 0;
    for(auto x : sitie) {
        int vl = val(x);
        int mx = medis.getMax(1, 0, mas[x].first-1);
        mx += vl;
        medis.change(1, mas[x].second, mas[x].second, mx);
        ret = max(ret, mx);
    }
    for(auto x : sitie) {
        medis.changee(1, mas[x].second, mas[x].second, 0);
    }
    return dp[ind] = ret + 1;

}
int main () {
    int t; cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i <= n; i++) dp[i] = -1;
        mas.clear();
        for(int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            mas.push_back({a, b});
        }
        mas.push_back({0, 200001});
        sort(mas.begin(), mas.end());
        vector<pair<int, int> > vec;
        for(int i = 0; i <= n; i++) {
            vec.push_back({mas[i].second-mas[i].first, i});
        }
        sort(vec.begin(), vec.end());
        int ans = 0;
        for(auto x : vec){
            auto sitas = val(x.second);
            ans = max(ans, sitas);
        } 
        cout << ans-1 << "\n";
    }
    return 0;
}
