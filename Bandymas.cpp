#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
long long dbd(long long a, long long b){
    if(b == 0) return a;
    return dbd(b, a%b);
}
const int dydis = 3e7 + 10;
bool is[dydis] = {0};
vector<int> primes;
vector<long long> factorize(long long a){
    vector<long long> ret;
    for(auto x : primes){
        if(a % x != 0) continue;
        ret.push_back(x);
        while(a % x == 0) a /= x;
    }
    if(a != 1) ret.push_back(a);
    return ret;
}
vector<pair<long long, int> > primatize(long long a){ // iskaido i x1^y1 * x2y2 * ... 
    vector<pair<long long, int> > ret;
    for(auto x : primes){
        if(a % x != 0) continue;
        int kek = 0;
        while(a % x == 0) a /= x, kek++;
        ret.push_back({x, kek});
    }
    if(a != 1) ret.push_back({a, 1});
    return ret;
}
long long kk(long long r, long long a){ // kiek intervale [1; r] daliu is a
    return r / a;
}
vector<pair<long long, int> > prm, rest;
long long brute(long long r, vector<long long> &a){
    long long ans = 0;
    for(long long i = 1; i <= r; i++){
        bool st = 0;
        for(auto x : a) if(i % x == 0){ st = 1; break;}
        ans += st;
    }
    return ans;
}
long long getAns(int i1, long long sk, vector<pair<long long, int> > &a, int kek, long long r){
    if(i1 == a.size()) {
        if(kek == 0) return 0;
        return kk(r, sk) * (kek % 2 == 1 ? 1 : -1);
    }
    long long ret = 0;
    ret += getAns(i1+1, sk, a, kek, r);
    __int128_t bus = sk;
    bus = bus * ((__int128_t)a[i1].first) / ((__int128_t)dbd(bus, a[i1].first));
    if(bus > r) return 0;
    ret += getAns(i1+1, bus, a, kek+a[i1].second, r);
    return ret;
}
long long kek(long long r, vector<pair<long long, int> > &a){ // kiek intervale[1; r] daliu is bent vieno a elemento
    if(r == 0) return 0;
/*    long long mx = (1 << a.size());
    long long ret = 0;
    for(int i = 1; i < mx; i++){
        __int128_t sk = 1; int kek = 0;
        for(int j = 0; j < a.size(); j++){
            if(!(i & (1 << j))) continue;
            sk = sk * ((__int128_t)a[j]) / ((__int128_t)dbd(sk, a[j])); kek++;
            if(sk > r) {
                sk = r+1;
                break;
            }
        }
//        cout << "pridedu kk(" << sk << " / " << gc << ") * " << (kek % 2 == 1 ? 1 : -1) << endl;
        ret += kk(r, (long long)sk) * (kek % 2 == 1 ? 1 : -1);
    }
    */
    long long ret = getAns(0, 1, a, 0, r);
//    cout << "intervale [1; " << r << "], yra " << ret << " skaiciu daliu is bent vieno is ["; for(auto x : a) cout << x.first << " "; cout << "],  " ;
//    cout << "vs " << brute(r, a) << endl;
    return ret;
}


long long l, r, n, k;
vector<pair<long long, int> > ret;
void darom(int i1, long long san, vector<pair<long long, int> > &vec, int viso){
    if(vec.size() == i1){
        ret.push_back({san, viso});
        return ;
    }
    for(int i = 0; i <= vec[i1].second; i++){
        darom(i1+1, san, vec, viso + i);
        san *= vec[i1].first;
    }
}
vector<pair<long long, int> > dals(int a) {
    auto prims = primatize(a);
    ret.clear();
    darom(0, 1, prims, 0);
    sort(ret.begin(), ret.end());
    return ret;
}
int main(){
    for(auto &x : is) x = 1;
    for(int i = 2; i < dydis; i++){
        if(!is[i]) continue;
        primes.push_back(i);
        for(int j = 2*i; j < dydis; j += i) is[j] = 0;
    }
    cin >> l >> r >> n >> k;
    auto fc = dals(n);
    for(auto x : fc) if(x.first <= k) prm.push_back(x); else rest.push_back(x);
//    cout << "tinkami dalikliai: "; for(auto x : rest) cout << x << " "; cout << endl;
    long long kD = kek(r, rest);
    long long kK = kek(l-1, rest);

    cout << r-l+1 -(kD - kK);
    return 0;
}
