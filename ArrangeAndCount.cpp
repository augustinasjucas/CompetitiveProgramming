#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
__int128_t mod1 = 3000000001234121341;
__int128_t mod2 = 1000000000000000009;
void br(int n, __int128_t mas[]){
    set<vector<int> > st;
    for(int i = 0; i < n; i++){
        vector<int> ret;
        int ind = i;
        while(ind != -1) ret.push_back(mas[ind--]);
        ind = n-1;
        while(ind != i) ret.push_back(mas[ind--]);
        st.insert(ret);
    }
    cout << st.size() << "\n";

}
int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; 
    while(cin >> n){
        __int128_t mas[2*n];
        __int128_t brt[n];
        set<pair<__int128_t, __int128_t> > hs; 
        for(int i = 0; i < n; i++){
            long long a; cin >> a;
            mas[i] = a;
            brt[i] = a;
        }
       // br(n, brt); continue;
        reverse(mas, mas+n);
        for(int i = 0; i < n; i++) mas[i+n] = mas[i];
 //       cout << "mas = [";
//        for(int i = 0; i < 2*n; i++) cout << (long long)mas[i] << " "; cout << "]\n";
        __int128_t s1 = 0, s2 = 0;  __int128_t kek = n;
        for(int i = 0; i < n; i++){
            s1 = ((s1 * kek)%mod1 + mas[i])%mod1;
            s2 = ((s2 * kek)%mod2 + mas[i])%mod2;
        }
        hs.insert({s1, s2});
        __int128_t pw1 = 1, pw2 = 1;
        for(int i = 0; i < n-1; i++) pw1 = pw1 * kek % mod1, pw2 = pw2 * kek % mod2;

        for(int i = n; i < 2*n; i++){
            s1 = (s1 - mas[i-n] * pw1  %mod1 + mod1) % mod1; 
            s1 = s1 * kek % mod1 + mas[i]; s1 = (s1 %mod1 + mod1) % mod1;
            s2 = (s2 - mas[i-n] * pw2  %mod2 + mod2) % mod2; 
            s2 = s2 * kek % mod2 + mas[i]; s2 = (s2%mod2 + mod2) % mod2;
 
            hs.insert({s1, s2});
        }
        reverse(mas, mas+n);
        for(int i = 0; i < n; i++) mas[i+n] = mas[i];       
        s1 = 0, s2 = 0;  kek = n;
        for(int i = 0; i < n; i++){
            s1 = ((s1 * kek)%mod1 + mas[i])%mod1;
            s2 = ((s2 * kek)%mod2 + mas[i])%mod2;
        }
        hs.insert({s1, s2});
        pw1 = 1, pw2 = 1;
        for(int i = 0; i < n-1; i++) pw1 = pw1 * kek % mod1, pw2 = pw2 * kek % mod2;

        for(int i = n; i < 2*n; i++){
            s1 = (s1 - mas[i-n] * pw1  %mod1 + mod1) % mod1; 
            s1 = s1 * kek % mod1 + mas[i]; s1 = (s1 %mod1 + mod1) % mod1;
            s2 = (s2 - mas[i-n] * pw2  %mod2 + mod2) % mod2; 
            s2 = s2 * kek % mod2 + mas[i]; s2 = (s2%mod2 + mod2) % mod2;
 
            hs.insert({s1, s2});
        }
        cout << hs.size() << "\n";
    }

    return 0;
}
