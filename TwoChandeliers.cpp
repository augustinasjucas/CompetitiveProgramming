#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int n, m;
const int dydis = 5e5 + 19;
long long k = 0;
long long mbk = 0, dbd;
vector<int> mas[2];
long long visoNeat = 0;
vector<int> groups[2][dydis];
unordered_map<int, vector<int> > kur[2][dydis]; 
int kek[dydis * 2] = {0};
long long gcd(long long a, long long b){
    if(b == 0) return a;
    return gcd(a % b, b);
}
int perKiek = 0;
int cnt(vector<int> &vec, int l, int r){
    auto L = lower_bound(vec.begin(), vec.end(), l);
    auto R = upper_bound(vec.begin(), vec.end(), r);
    return R - L;
}
long long kiek(int ind, int k){
    int indInside = ind / dbd;
    long long skk = perKiek;

    skk *= indInside;
    skk %= (int)groups[1][ind%dbd].size();
    skk = (skk + (int)groups[1][ind%dbd].size()) % ((int)(groups[1][ind%dbd].size()));

    long long ret = 0;

    // kiek groups[1][ind%dbd] masyve, intervale [skk; (j + skk) % A.size()] yra mas[0][ind] nelygiu elementu?
    auto &A = groups[1][ind%dbd];
    vector<int> &vec = kur[1][ind%dbd][mas[0][ind]]; // cia gaunu kur yra visi mas[0][ind] atitikmenys
    int viso = k;
    int l = skk;
    int r = (skk + k - 1) % A.size();
    if(l <= r){
       viso -= cnt(vec, l, r); 
    }else{
        viso -= cnt(vec, r, n + m + 1) + cnt(vec, 0, l);
    }
//    for(int j = 0; j < k; j++){
//        ret += A[(j + skk) % ((int)A.size())] != mas[0][ind];
//    }
    return viso;
}
bool f(__int128_t t){
    __int128_t kek = 0; // kiek bus neatitikimu po t pasukimu?
    kek += (t / mbk) * visoNeat;
    t %= mbk;
    for(int i = 0; i < n; i++){ // einu per pirmus
        if(t - i <= 0) break;
        __int128_t kekk = (t - i) / n + ((t-i) % n != 0); // kiek pirmuju spesiu paliesti?
        __int128_t kk = kiek(i, kekk);
        kek += kk;
    }
    return kek >= (__int128_t) k;
}
void calc(){ // kiek po pilno rato bus neatitikimu?
    for(int i = 0; i < dbd; i++){ // einu per grupes
        vector<int> &A = groups[0][i];
        vector<int> &B = groups[1][i];
        for(auto &x : A) kek[x]++;
        for(auto &x : B){
            visoNeat += A.size() - kek[x];
        }
        for(auto &x : A) kek[x]--;
    }
    if(groups[1][0].size() == 1) perKiek = 0;
    else{
        for(int i = 0; i < n; i++){
            if(i % dbd != 0) continue;
            if(i % m == 1) perKiek = i / dbd;
        }
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> k;
    mbk = 1ll * n * m / gcd(n, m); dbd = gcd(n, m);
    mas[0].resize(n);
    mas[1].resize(m);
    for(int i = 0; i < 2; i++){
        for(auto &x : mas[i]) cin >> x;
        for(int j = 0; j < mas[i].size(); j++){
            groups[i][j % dbd].push_back(mas[i][j]);
            kur[i][j%dbd][mas[i][j]].push_back(groups[i][j % dbd].size()-1);
        }
    }
    calc();
    __int128_t tikraiReiks = (k / visoNeat) * mbk;
    __int128_t l = tikraiReiks-100, r = (__int128_t) l + mbk + 100, mid;
    __int128_t ans = r;
    while(l <= r){
        mid = (l + r) / 2ll;
        if(f(mid)){
            ans = min(mid, ans);
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }

    cout << (long long)ans;
    return 0;
}
