#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e7 + 1;
vector<int> primes, fac;
bool isP[dydis];
long long L, R, N, K, CP;
long long k(long long a){
    return R/a - (L-1)/a;
}
long long dbd(long long a, long long b){
    if(b == 0) return a;
    return dbd(b, a%b);
}
long long f(long long a){ // kiek intervale [L; R] yra tokiu, kuriu DBD(x, N) = a
    long long ret = 0;
    vector<long long> st;
    for(auto x : fac) if(dbd(a * x, N) == a*x) st.push_back(x);
    for(int i = 0; i < (1 << st.size()); i++){
        long long snd = 1, kek = 0;
        for(int j = 0; j < st.size(); j++){
            if(!((1 << j) & i)) continue;
            kek++;
            snd *= st[j];
        }
        ret += (kek % 2 == 0 ? 1 : -1) * k(snd*a);
    }
    return ret;
    
}
int main(){
    cin >> L >> R >> N >> K; CP = N;
    for(int i = 2; i < dydis; i++) isP[i] = 1;
    for(int i = 2; i < dydis; i++) if(isP[i]) {primes.push_back(i); for(int j = 2*i; j < dydis; j += i) isP[j] = 0;}
    for(auto x : primes) if(CP % x == 0) {while(CP%x == 0) CP /= x; fac.push_back(x);} if(CP != 1) fac.push_back(CP);
    long long sq = (sqrt(N));
    long long ans = 0;
    for(int i = 1; i <= sq; i++){
        if(N % i != 0) continue;
        if(i <= K) ans += f(i);
        if(i * i != N && N/i <= K) ans += f(N/i);
    }
    cout << ans;
    return 0;
}
