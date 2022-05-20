#include <bits/stdc++.h>
using namespace std;
int n, q;
const long long inf = 1e18;
const int dydis = 1e5 + 10;
int l[dydis * 4 + 1], r[dydis * 4 + 1];
bool rot[dydis * 4 + 1] = {};
long long val[dydis * 4 + 1] = {};
long long min1[dydis * 4 + 1] = {};
long long min2[dydis * 4 + 1] = {};
int minCnt[dydis * 4 + 1] = {};
long long pl[dydis * 4 + 1] = {};
long long mx[dydis * 4 + 1] = {}; // max(mx[i], x) + pl[i]
pair<long long, long long> conn(long long a, long long b, long long c, long long d) {  // virsuje yra max(x, A) + B, apacioje yra max(x, C) + D

    /*
        max(x, A) + B
        max(x, C) + D
          max(max(x, C) + D, A) + B         = 
        = max(max(x + D, C + D), A) + B     = 
        = max(x + D, C + D, A) + B          =
        = max(x + D, C + D, A - D + D) + B  = 
        = max(x, C, A-D) + D + B            =
        = max(x, max(C, A-D) ) + (D + B). 
     */

    return {max(c, a - d), d + b};
}
void apply(int v, int L, int R){
    if(v == -1) return ;    
    if(min1[v] >= mx[v]) {

    }else if(min1[v] < mx[v] && mx[v] < min2[v]) {
        val[v] += (mx[v] - min1[v]) * minCnt[v];
        min1[v] = mx[v];
    }else{
        
    }

    val[v] += 1ll * (R - L + 1) * pl[v];
    min1[v] += pl[v];
    min2[v] += pl[v];    
    if(l[v] != -1 && L != R){
        auto A = conn(mx[v], pl[v], mx[l[v]], pl[l[v]]);
        mx[l[v]] = max(A.first, mx[l[v]]);
        pl[l[v]] = A.second;
    }
    if(r[v] != -1 && L != R){
        auto A = conn(mx[v], pl[v], mx[r[v]], pl[r[v]]);
        mx[r[v]] = A.first;
        pl[r[v]] = A.second;
    }

    mx[v] = -inf;
    pl[v] = 0;

}

void merge(int v, int L, int R){ // tarkim v jau yra pa'applyintas
//    cout << "merge [" << L << "; " << R << "]\n";
    apply(l[v], L, (L+R)/2);
    apply(r[v], (L+R)/2+1, R);
    
    val[v] = val[l[v]] + val[r[v]];
    
    min1[v] = min(min1[l[v]], min1[r[v]]);
    if(min1[r[v]] == min1[l[v]]) min2[v] = min(min2[l[v]], min2[r[v]]);
    else min2[v] = min(min1[l[v]], min1[r[v]]);
    
    minCnt[v] = (min1[l[v]] == min1[v] ? minCnt[l[v]] : 0) + (min1[r[v]] == min1[v] ? minCnt[r[v]] : 0);
}

void add(int v, int qL, int qR, int nL, int nR, int x){
    apply(v, nL, nR);
    if(qL <= nL && nR <= qR){
        pl[v] += x;
        apply(v, nL, nR);
    }else if(qL > nR || nL > qR){
        return ;
    }else{
        int mid = (nL + nR) / 2;
        add(l[v], qL, qR, nL, mid, x);
        add(r[v], qL, qR, mid+1, nR, x);
        merge(v, nL, nR);
    }
}
void maxi(int v, int qL, int qR, int nL, int nR, int x){
    apply(v, nL, nR);
//    cout << "v = " << v << ", intervalas [" << nL << "; " << nR << "], min1 = " << min1[v] << ", min2 = " << min2[v] << ", val[v] = " << val[v] << endl;
    if(qL <= nL && nR <= qR && min1[v] < x && x < min2[v]){
//        cout << endl << endl << "sitas pilnai tinka!" << endl;
        mx[v] = x;
        apply(v, nL, nR);
    }else if(qL > nR || nL > qR || min1[v] >= x){
        return ;
    }else{
        int mid = (nL + nR) / 2;
        maxi(l[v], qL, qR, nL, mid, x);
        maxi(r[v], qL, qR, mid+1, nR, x);
        merge(v, nL, nR);
    }
}

long long quer(int v, int qL, int qR, int nL, int nR){
    apply(v, nL, nR);
//    cout << "quer(" << nL << ", " << nR << ")\n";
    if(qL <= nL && nR <= qR){
//        cout << "esu [" << nL << "; " << nR << "], returninu " << val[v] << endl; 
        return val[v];
    }else if(qL > nR || nL > qR){
        return 0;
    }else{
        int mid = (nL + nR) / 2;
        return quer(l[v], qL, qR, nL, mid) + quer(r[v], qL, qR, mid+1, nR);
    }
}
void print(){
    for(int i = 0; i < n; i++){
        cout << quer(1, i, i, 0, n-1) << " ";
    }
}
int closestPower(int n){
    int lg2 = 0;
    n--;
    while(n != 0){
        lg2++;
        n /= 2;
    }
    return (1 << lg2);
}
int main(){
    cin >> n >> q;

    for(int i = 0; i < dydis*4 + 1; i++){
        l[i] = i * 2;
        r[i] = i * 2 + 1;
        mx[i] = -inf;
        min1[i] = 0;
        min2[i] = inf;
        minCnt[i] = 1;
    }
//    n = closestPower(n);
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        add(1, i, i, 0, n-1, a);
    }

    for(int i = 0; i < q; i++){
        int t; cin >> t;
        int l, r, x;
        if(t == 1){
            cin >> l >> r >> x; l--; r--;
            add(1, l, r, 0, n-1, x);
        }
        if(t == 2){
            cin >> l >> r >> x; l--; r--;
            maxi(1, l, r, 0, n-1, x);
        }
        if(t == 4){
            cin >> l >> r; l--; r--;
            cout << quer(1, l, r, 0, n-1) << "\n";
        }
//        cout << "mas: [";
//        print();
//        cout << "]\n";
    }
    return 0;
}
