#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
__int128_t mod = 1ll << 32;
__int128_t inf = 1ll << 62;


int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        long long n, l, r, x, y, z, b1, b2;
        cin >> n >> l >> r >> x >> y >> z >> b1 >> b2;
        vector<__int128_t> b(n);
        b[0] = b1; b[1] = b2;
        for(int i = 2; i < n; i++){
            b[i] = ((b[i-2] * x) % mod + (b[i-1]*y) % mod + z) % mod;
        }
        __int128_t mx = -inf, mn = inf, ans = inf;
        vector<__int128_t> ms(n); int ind = 0;
        for(int i = 0; i < n; i++){
            __int128_t st = (b[i] % (r-l+1)) + l;
            if(i == 0){
                if(st < 0){
                    ms[ind++] = st;
                }
                mx = st;
                mn = st;
                continue;
            }
            if(st == 0) ans = min(ans, (__int128_t)0ll);
            else if(st > 0){
                if(st > mn) ans = min(ans, mn*st);
            }else if(st < 0){ // reiks kuo artimesnio
                while(ind != 0 && ms[ind-1] < st){
                    ans = min(ans, st * ms[ind-1]);
                    ind--;
                }
                ms[ind++] = st;
            }
            mx = max(mx, st);
            mn = min(mn, st);
        }
        /// jei dabar ner ans, tai ji sudarys nebent neigiamu pora
        if(ans == inf) cout << "IMPOSSIBLE\n";
        else cout << (long long)ans << "\n";
    }
    return 0;
}
