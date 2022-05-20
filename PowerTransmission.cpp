#include <bits/stdc++.h>

using namespace std;

#define frac pair<long long, long long>
#define line pair<frac, frac>
long long gcd(long long a, long long b){
    if(b == 0) return a;
    return gcd(b, a%b);
}
frac simplify(frac a){
    auto dbd = gcd(a.first, a.second);
    a.first /= dbd;
    a.second /= dbd;
    return a;
}
__float128 inf = 1e10;
map<frac, long long> kek;
set<line> btai;
int n;
int main(){
    cin >> n;
    vector<frac> vec(n);

    for(int i = 0; i < n; i++){
        long long a, b; cin >> a >> b;
        vec[i].first = a;
        vec[i].second = b;
    }
    long long viso = 0;
    sort(vec.begin(), vec.end());
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            long long x1 = vec[i].first, y1 = vec[i].second, x2 = vec[j].first, y2 = vec[j].second;
            frac k;
            frac b;
            if(x1-x2 == 0){
                if(btai.count(make_pair(make_pair(inf, 1ll), make_pair(x1, 1ll)))) continue;
                btai.insert(make_pair(make_pair(inf, 1ll), make_pair(x1, 1ll)));
                kek[make_pair(inf, 1ll)]++;
                viso++;
            }else{
                k = simplify(make_pair(y1-y2, x1-x2));
                b = simplify(make_pair(k.first*x1, k.second));
                b = simplify(make_pair(y1*b.second-b.first, b.second));
                if(btai.count(make_pair(k, b))) continue;
                btai.insert(make_pair(k, b));
                viso++;
                kek[k]++;
            }
        }
    }
    long long ans = 0;
    for(auto x : kek){
        ans += (viso-x.second) * (x.second);
    }
    cout << ans/2ll;
    return 0;
}

