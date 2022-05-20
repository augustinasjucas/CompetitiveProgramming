#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
struct tree {
    int n;
    vector<int> l, r, val;
    int dbInd = 0;
    void build(int v = 1) {
        if(v >= n) {
            val[v] = 0;
            l[v] = r[v] = dbInd++;
        }else {
            build(v * 2);
            build(v * 2 + 1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
    }
    tree (int dd){
        n = dd;
        l.resize(dd * 2 + 1);
        r.resize(dd * 2 + 1);
        val.resize(dd*2+1);
        build(1);
    }
    void change(int v, int L, int R, int x) {
        if(L <= l[v] && r[v] <= R) {
            val[v] = x;
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else {
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            val[v] = max(val[v*2], val[v*2+1]);
        }
    }
    int getMin(int v, int L, int R){
         if(L <= l[v] && r[v] <= R) {
            return val[v];
         }else if(R < l[v] || r[v] < L) {
            return 0;
        }else {
            return max(getMin(v*2, L, R), getMin(v*2+1, L, R));
        }   
    }
};
const int dydis = 2e5 + 10;
int n, d;
vector<int> mas;
unordered_map<int, int> pressed;
vector<int> tikras;
void prep(vector<int> &mas){
    set<int> vec;
    for(auto x : mas) {
        vec.insert(x);
        vec.insert(x+d);
    }
    int ind = 0;
    for(auto x : vec) {
        tikras.push_back(x);
        pressed[x] = ind++;
    }
}
void compress(vector<int> &vec){
    for(auto &x : mas) {
        x = pressed[x];
    }
}

int dp1[dydis]; // dp1[i] - koks ilgiausias didejantis posekis, kuris baigiasi ties i-uoju skaiciumi?
int dp2[dydis]; // dp2[i] - koks ilgiausias mazejantis posekis nuo galo gali baigtis ties i-uoju skaiciumi,
                // jei visi tame posekyje esantys skaiciai didesni uz A[i-1]
void getDp1(){
    vector<int> dp(dydis, inf);
    int i = 0;
    for(auto x : mas) {
        auto kur = lower_bound(dp.begin(), dp.end(), x);
        *kur = x;
        dp1[i++] = kur - dp.begin() + 1;
    }
}
void getDp2(){
    tree medis(2*n+1);
    for(int i = n-1; i > -1; i--) {
        int x = pressed[tikras[mas[i]] + d];
        int vl = medis.getMin(1, x+1, inf) + 1;
        medis.change(1, x, x, vl);
        int pries = (i == 0 ? -1 : mas[i-1]);
        dp2[i] = medis.getMin(1, pries + 1, inf);
    }
}
int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> d;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    prep(mas);
    compress(mas);
    getDp1();
    getDp2();
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int st = dp1[i];
        int kt;
        if(i == n-1) kt = 0;
        else kt = dp2[i+1];
        ans = max(ans, st + kt);
    }
    cout << ans ;
    return 0;
}
