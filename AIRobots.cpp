
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int n, k;
vector<pair<int, pair<int, int> > > mas;
long long ans = 0 ;
const int base = 2;
const int kek = log(10000000000) / log(base) + 2 ;
const int dydis = kek * 10000 + 10;
//const int dydis = 100000;
struct tre{
    int nxt[dydis][base];
    int val[dydis] = {0};
    int dbInd = 1;
    vector<int> getSkait(int a){
        vector<int> ret;
        for(int i = 0; i < kek; i++){
            ret.push_back(a % base);
            a = a / base;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
    int newN(){
        return dbInd++;
    }
    void prd(vector<int> &vec, int v, int ind, int kek){
//        cout << "v = " << v << endl;
        val[v] += kek;
        if(ind == vec.size()) return;
        if(nxt[v][vec[ind]] == -1) nxt[v][vec[ind]] = newN();
        prd(vec, nxt[v][vec[ind]], ind+1, kek);
    }
    void add(int a){
        vector<int> skait = getSkait(a);
//        cout << "pridedu!" << ", skait = " ; 
//        for(auto x : skait) cout << x << " " ;
//        cout << endl;
        prd(skait, 0, 0, 1);
//        cout << "baigiau!" << endl;
    }
    void err(int a){
        vector<int> skait = getSkait(a);
        prd(skait, 0, 0, -1);
    }
    int fd(vector<int> &vec, int v, int ind){
        if(ind == vec.size()) return val[v];
        int ret = 0;
        for(int i = 0; i < vec[ind]; i++){
            if(nxt[v][i] == -1) continue;
            ret += val[nxt[v][i]];
        }
        int kt = 0;
        if(nxt[v][vec[ind]] != -1) kt = fd(vec, nxt[v][vec[ind]], ind+1);
        return ret + kt;
    }
    int find(int r){ // kiek <= r?
        vector<int> skait = getSkait(r);
        return fd(skait, 0, 0);
    }
    int find(int l, int r){ // kiek intervale [l; r] skaiciu?
        r = min(r, 1000000000);
        int vn = 0, an = 0;
        if(l >= 1){
            vn = find(l-1);
        }
        an = find(r);
        return an-vn;
    }
    tre(){
        for(auto &x : nxt) for(auto &y : x) y = -1;
    }
};
tre medis[21];
long long f(){
    vector<pair<int, pair<int, pair<int, int> > > > inte;
    for(int i = 0; i < n; i++){
        auto &x = mas[i];
//        if(x.first > sk + k) break;
    //    if(sk - k <= x.first && x.first <= sk + k){
        int pos = x.second.first;
        int r = x.second.second;
        inte.push_back({pos-r, {1, {pos, x.first}}});
        inte.push_back({pos, {2, {r, x.first}}});
        inte.push_back({pos+r+1, {0, {pos, x.first}}});
  //      }
    }
/*      cout << "aplink " << sk << "yra: \n";
    for(auto x : vec){
        cout << "[" << x.first << "-[" << x.second.first << ", " << x.second.second << "]]  ";
    }
    cout << endl;*/
    sort(inte.begin(), inte.end());
    long long ret = 0;
    for(auto x : inte){
        if(x.second.first == 0){
//            cout << "isimu " << x.second.second << "\n";
            medis[x.second.second.second].err(x.second.second.first);
        }else if(x.second.first == 1){
//            cout << "idedu " << x.second.second << "\n";
            medis[x.second.second.second].add(x.second.second.first);
        }else{
//            cout << "priskaiciuoju nuo " << x.first << "\n";
            int lvl = x.second.second.second;
            for(int i = max(lvl-k, 0); i <= min(lvl+k, 20); i++){
                ret += medis[i].find(x.first-x.second.second.first, x.first + x.second.second.first);
            }
            ret--;
        }
    }
//    cout <<sk << " returnina " << ret << "\n";
    return ret;
}
set<int> iqs;
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int x, r, q; cin >> x >> r >> q;
        mas.push_back({q, {x, r}});
        iqs.insert(q);
    }
    sort(mas.begin(), mas.end());
    ans += f();
    cout << ans/2;
    return 0;
}


