#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<bool> toB(int a){
    vector<bool> ret;
    for(int i = 0; i < n; i++){
        ret.push_back(a & 1);
        a = a >> 1;
    }
//    cout << "ret = ["; for(auto x : ret) cout << x<< " "; cout << endl;
    return ret;
}
int cnt(vector<bool> &vec){
    int ret = 0;
    for(auto x : vec) ret += x;
    return ret;
}
int daryk(vector<bool> &m1, vector<bool> &m2, int kair, int desn){
    vector<int> cur;
    for(auto x : m1) cur.push_back(x);
    int ret = 0;
    if(kair > 0){
        cur[0] += kair;
        ret += kair;
        kair = 0;
    }
    if(desn > 0){
        ret += desn;
        cur[n-1] += desn;
        desn = 0;
    }
//    cout << "db ret = " << ret << endl;
    if(kair < 0){
        kair = -kair;
        for(int i = 0; i < n; i++){
            if(cur[i] == 0) continue;
            int kek = min(kair, cur[i]);
            cur[i] -= kek;
            ret += kek * (i+1);
            kair -= kek;
        }
    }
    if(desn < 0){
        desn = -desn;
        for(int i = n-1; i > -1; i--){
            if(cur[i] == 0) continue;
            int kek = min(desn, cur[i]);
            cur[i] -= kek;
            ret += kek * (n-i);
            desn -= kek;
        }
    }
//    cout << "dabar ret = " << ret << endl;
    vector<int> mn, tv;
    for(int i = 0; i < n; i++){
        while(cur[i]){
            mn.push_back(i);
            cur[i]--;
        }
    }
    for(int i = 0; i < n; i++){
        if(m2[i]){
            tv.push_back(i);
        }
    }
//    cout << "mn = ["; for(auto x : mn) cout << x << " "; cout << endl;
//    cout << "tv = ["; for(auto x : tv) cout << x << " ";
    for(int i = 0; i < mn.size(); i++){
        ret += abs(mn[i]-tv[i]);
    }
//    cout << "return " << ret << endl;
    return ret;
}
int dist(int a, int b){
    auto m1 = toB(a);
    auto m2 = toB(b);
    int vnt[2] = {cnt(m1), cnt(m2)};
    int ret = n*n*n;
    for(int i = -n; i <= n; i++){ // kaireje ieis i vyruku
        int reiks = vnt[1]-vnt[0]-i; // desineje ieis reiks.  reiks + i + vnt[0] = vnt[1]
//        cout << "kaireje ieis " << i << ", desineje ieis " << reiks << endl;
        ret = min(ret, daryk(m1, m2, i, reiks));
    }
    return ret;
}
int main(){
    cin >> n >> m;
    int last =0;
    int ans = 0;
    for(int i =0 ; i < m; i++){
        int a; cin >> a;
//        cout << dist(last, a) << "\n";
        ans += dist(last, a);
        last = a;
    }
    cout << ans;
    return 0;
}
