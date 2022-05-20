#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;

vector<vector<long long> > mult(vector<vector<long long> > a, vector<vector<long long> > b){
    vector<vector<long long> > ret(a.size());
    for(auto &x : ret) x.resize(b.size());
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            long long st = 0;
            for(int h = 0; h < min(a.size(), b.size()); h++){
                st = (st + ((a[i][h]%mod) * (b[h][j]%mod))%mod) % mod;
            }
            ret[i][j] = st;
        }
    }
    return ret;
}
vector<vector<long long> > raise(vector<vector<long long> > x, long long laip){
    if(laip == 1) return x;
    auto sak = raise(x, laip/2);
    auto st = mult(sak, sak);
    if(laip & 1) st = mult(st, x);
    return st;
}
long long klk(long long x, long long laip){
    if(laip == 0) return 1;
    long long sak = klk(x, laip/2) % mod;
    long long st = sak * sak % mod;
    if(laip & 1) st = st * x % mod;
    return st % mod;
}
int main(){
    long long n, m, l, r; cin >> n >> m >> l >> r;
    long long a = (r-l+1)/2ll;
    long long b = (r-l+1)/2ll;
    if((l & 1) == (r & 1)){
        if(l & 1){
            b++;
        }else{
            a++;
        }
    }
    if((n & 1) && (m & 1)){
        cout << klk(r-l+1ll, n*m);
        return 0;
    }
    vector<vector<long long> > prm = {{1, 0}, {0, 0}};
    vector<vector<long long> > ant = {{a, b}, {b, a}};
    vector<vector<long long> > rai = raise(ant, n*m);
    vector<vector<long long> > ans = mult(prm, rai);
    cout << ans[0][0];
    return 0;
}

