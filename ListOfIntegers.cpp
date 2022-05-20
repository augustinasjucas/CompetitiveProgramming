#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 100;
set<long long> dls[10]; // dls[i] sudaro visi skaiciai, kuriuose yra i pirm dalikliu
vector<int> st;
vector<int> primes;
bool isP[dydis] = {0};
void genPrimes(){
    for(int i = 2; i < dydis; i++) isP[i] = 1;
    for(int i = 2; i < dydis; i++) {
        if(!isP[i]) continue;
        primes.push_back(i);
        for(int j = 2*i; j < dydis; j+=i) isP[j] = 0;
    }
}
vector<int> factorize(int a){
    vector<int> ret;
    for(auto x : primes){
        if(a % x != 0) continue;
        while(a % x == 0) a /= x;
        ret.push_back(x);
    }
    if(a != 1) ret.push_back(a);
///    cout << "ret = "; for(auto x : ret ) cout << x << " "; cout << endl;
    return ret;
}
void gen(int sand, int ind, int kek){
    dls[kek].insert(sand);
    if(ind == st.size()) return;
    gen(sand, ind+1, kek);
    gen(sand*st[ind], ind+1, kek+1);
}
int f(long long r, long long x){ // kiek intervale [1; r] yra x kartotiniu?
    return r/x;
}
int f(long long l, long long r, long long x){ // kiek intervale [l; r] yra x kartotiniu
    return f(r, x) - f(l-1, x);
}
long long viso(long long l, long long r){ // kiek intervale [l; r] yra su x bendru dalikliu turinciu skaiciu
    long long ret = 0;
    for(int i = 1; i < 10; i++){
        for(auto x : dls[i]){
            ret += (i % 2 == 0 ? -1 : 1) * f(l, r, x);
        }
    }
    return ret;
}
long long stt = 0;
long long g(long long l, long long r){
    long long ret =  r - l + 1 - viso(l, r);
//    cout << "intervale " << l << "; " << r << " su " << stt << " tarp pirminiu yra " << ret << endl;
    return ret;
}
int dbd(int a, int b){
    if(b == 0) return a;
    return dbd(b, a%b);
}
long long brt(int x, int p, int k){
    int kek = 0;
    x++;
    while(true){
        if(dbd(x, p) == 1){
            kek++;
        }
        if(kek == k) return x;
        x++;
    }
    return -1;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    genPrimes();
    int t; cin >> t;
    while(t--){
        for(auto &x : dls) x.clear();
        int x, p, k; cin >> x >> p >> k;
        stt = p;
        st = factorize(p);
        gen(1, 0, 0);
        long long ans = x;
        long long l = x; long long r = 1e12 + 10, mid;

        while(l <= r){
            mid = (l + r) / 2;
  //          cout << l << "; " << r << ", ";
            if(g(x+1, mid) < k){
//                cout << mid << ", tinka\n";
                ans = max(ans, mid);
                l = mid+1;
            }else{
    //            cout << mid << ", netinka\n";
                r = mid-1;
            }
        }
        /*
        while(true){
            int l, r; cin >> l >> r;
            int st = viso(l, r);
//            cout << "intervale [" << l << "; " << r << "] yra " << st << " su " << p << " turinciu bendra dalikli!" << endl;
        }*/
   //     cout << ans+1 << " vs " << brt(x, p, k) << endl;
        cout << ans+1 << "\n";
    }
    return 0;
}
