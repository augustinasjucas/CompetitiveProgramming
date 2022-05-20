#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const long long inf = 1e9;
struct treeMin {
    vector<int> l, r;
    vector<int> lazy, mn;
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
    treeMin(int dd) {
        l.resize(dd*2+1);
        r.resize(dd*2+1);
        mn.resize(dd*2+1);
        lazy.resize(dd*2+1);
        n = dd;
        build(1);
    }
    void apply(int v) {
        mn[v] += lazy[v];
        if(v < n) {
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }
        lazy[v] = 0;
    }
    void add(int v, int L, int R, int x) {
        apply(v);
        if(L <= l[v] && r[v] <= R) {
            lazy[v] = x;
            apply(v);
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else {
            add(v*2, L, R, x);
            add(v*2+1, L, R, x);
            mn[v] = min(mn[v*2], mn[v*2+1]);
        }
    }
    int getMin(int v, int L, int R){
        apply(v);
        if(L <= l[v] && r[v] <= R) {
            return mn[v];
        }else if(R < l[v] || r[v] < L) {
            return inf;
        }else {
            return min(getMin(v*2, L, R), getMin(v*2+1, L, R));
        }
    }

};
struct treeSum{
    vector<int> l, r;
    vector<int> sm;
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
    treeSum(int dd) {
        l.resize(dd*2+1);
        r.resize(dd*2+1);
        sm.resize(dd*2+1);
        n = dd;
        build(1);
    }
    void add(int v, int L, int R, int x) {
        if(L <= l[v] && r[v] <= R) {
            sm[v] += x;
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else {
            add(v*2, L, R, x);
            add(v*2+1, L, R, x);
            sm[v] = sm[v*2] + sm[v*2+1];
        }
    }
    int getSum(int v, int L, int R){
        if(L <= l[v] && r[v] <= R) {
            return sm[v];
        }else if(R < l[v] || r[v] < L) {
            return 0;
        }else {
            return getSum(v*2, L, R) + getSum(v*2+1, L, R);
        }
    }
};
int n, m;
vector<int> a, b;
void compress(vector<int> &a, vector<int> &b) {
    vector<int> bendras = a;
    for(auto &x : b) bendras.push_back(x);
    sort(bendras.begin(), bendras.end());
    vector<int> ids = {bendras[0]};
    for(auto &x : bendras) {
        if(x != ids.back()) ids.push_back(x);
    }
    for(auto &x : a) {
        x = lower_bound(ids.begin(), ids.end(), x) - ids.begin();
    }
    for(auto &x : b) {
        x = lower_bound(ids.begin(), ids.end(), x) - ids.begin();
    }
}
int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        a.resize(n);
        b.resize(m);
        treeMin medis(n);
        treeSum kitas(n);
        vector<pair<int, int> > vec;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            vec.push_back({a[i], i});
        }
        for(int j = 0; j < m; j++) {
            cin >> b[j];
        }
        sort(b.begin(), b.end());
        sort(vec.begin(), vec.end());
        long long ans = 0;
        
        for(auto &x : vec) {
            ans += kitas.getSum(1, x.second, n-1);
            kitas.add(1, x.second, x.second, 1);
        }
        int mx = n + m;
        for(auto &x : vec) {
            int val = x.first;
            int ind = x.second;
            medis.add(1, ind+1, n-1, 1);
        }
        int i = 0;  // i zymi pirma ta, kuris gali atsirasti apacioje
        vector<pair<int, int> > did;
        for(int h = 0; h < b.size(); h++) {
            auto x = b[h];
            while(i != n && vec[i].first < x) {
                medis.add(1, vec[i].second+1, n-1, -1);
                medis.add(1, 0, vec[i].second-1, 1);
                i++;
            }

            while(i != n && vec[i].first == x) {
                medis.add(1, vec[i].second+1, n-1, -1);
                did.push_back(vec[i]);
                i++;
            }

            ans += medis.getMin(1, 0, n-1);
            if(h != m-1 && b[h+1] != b[h]){
                for(auto x : did) {
                    medis.add(1, 0, x.second-1, 1);
                }
                did.clear();
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
