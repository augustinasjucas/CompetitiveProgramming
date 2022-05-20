#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<vector<long long> > val;
vector<vector<long long> > pref;
int n, m, p, q;
bool swp = 0;
void precalc(){
    for(int i = 0; i < n; i++) {
        long long s = 0;
        for(int j = 0; j < m; j++) {
            s += val[i][j];
            pref[i][j] = (i == 0 ? 0ll : pref[i-1][j]) + s;
        }
    }
}
long long getSum(int e1, int s1, int e2, int s2) {
    long long ret = 0;
    ret += pref[e2][s2];
    if(e1 != 0) {
        ret -= pref[e1-1][s2];
    }
    if(s1 != 0){
        ret -= pref[e2][s1-1];
    }
    if(e1 != 0 && s1 != 0) {
        ret += pref[e1-1][s1-1];
    }
    return ret;
}
long long rnd(long long x, long long y) {
    long long maz = x / y;
    x %= y;

    if(2ll*x >= y) maz++;
    return maz;
}
void maz () {
    for(int h = 0; h < p; h++) {
        long long e, s, a, b;
        cin >> s >> e >> a >> b; e--; s--;
        if(swp) swap(e, s);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                val[i][j] += max(0ll, 1ll * a - 1ll * b * max(abs(i-e), abs(s-j)));
            }
        }
    }

    precalc();
    
    cin >> q;
    while(q--) {
        int e1, s1, e2, s2;
        cin >> s1 >> e1 >> s2 >> e2; s1--; e1--; s2--; e2--;
        if(swp) {
            swap(e1, s1);
            swap(e2, s2);
        }
        long long sm = getSum(e1, s1, e2, s2);
        long long S = sm;
        long long pl = (1+abs(e1-e2)) * (abs(s1-s2)+1);
        long long ans = rnd(S, pl);
        cout << ans << "\n";

    }
}
int nl, prm, le, mid, ri;
int vL, vR;
void doEil(int eil, int s, int nutol, long long a, long long b, vector<vector<long long> > &A, vector<vector<long long> > &B){
    nl = a / b;
    prm = a % b;

    le = max(s - nl, 0);
    mid = s;
    ri = min(s + nl, m-1);
    
    vL = a - b * max(abs(le - s), nutol);
    vR = a - b * max(abs(ri - s), nutol);
    
    A[eil][le] += vL;
    A[eil][ri+1] -= vR;

    
    if(le <= mid-nutol){
        B[eil][le] += b;
        B[eil][mid-nutol] -= b;
    }
    
    if(mid+nutol <= ri){
        B[eil][mid+nutol] -= b;
        B[eil][ri] += b;
    }
}
void h1(){
//    vector<long long> A(m+2, 0), B(m+2, 0);
    vector<vector<long long> > A(n, vector<long long> (m+2, 0)), B(n, vector<long long> (m+2, 0));
    for(int h = 0; h < p; h++) {
        long long e, s, a, b;
        cin >> s >> e >> a >> b; e--; s--;
        if(swp) {
            swap(e, s);
        }
        long long nl = a / b;
        
        for(int i = max(0ll, e-nl); i <= min(1ll*n-1, e+nl); i++) {
            doEil(i, s, abs(i-e), a, b, A, B);
        } 
    }
    for(int j = 0; j < n; j++){
        long long sitas = 0;
        long long delta = 0;
        for(int i = 0; i < m; i++) {
            sitas += A[j][i];
            sitas += delta;
            val[j][i] = sitas;
            delta += B[j][i];
        }
    }

    precalc();
    
    cin >> q;
    while(q--) {
        int e1, s1, e2, s2;
        cin >> s1 >> e1 >> s2 >> e2; s1--; e1--; s2--; e2--;
        if(swp) {
            swap(e1, s1);
            swap(e2, s2);
        }
        long long sm = getSum(e1, s1, e2, s2);
        long long S = sm;
        long long pl = (1+abs(e1-e2)) * (abs(s1-s2)+1);
        long long ans = rnd(S, pl);
        cout << ans << "\n";

    }
   
}
int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> m >> n >> p;
    // noriu visada eiti per eilutes. t.y., n <= m turi galioti!
    if(n > m){
        swap(n, m);
        swp = 1;
    }
    vector<vector<long long> > iden(n, vector<long long> (m, 0));
    val = iden; pref = iden;
    h1();
    return 0;
    if(n == 1) {
        h1();
        return 0;
    }else if(1ll * m * n * p <= 100000000ll) {
        maz();
        return 0;
    }
    return 0;
}
