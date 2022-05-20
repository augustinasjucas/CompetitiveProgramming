#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const long long inf = 1e17;
struct node{
    long long val;
    short l, r;
};
struct seg_tree{
    
    vector<node> tree;
    int currInd = 0;
    int n = 0;
    
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = currInd++;
            tree[v].val = -inf;
        }else{
            build(v*2);
            build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
            tree[v].val = -inf;
        }
    }
    void add(int v, short l, short r, long long x){
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].val = x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = max(tree[v*2].val, tree[v*2+1].val);
        }
    }
    long long find(int v, short l, short r){
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return -inf;
        }else {
            return max(find(v*2, l, r), find(v*2+1, l, r));
        }
    }
    void bld(int dydis){
        currInd = 0;
        if(dydis != n) tree.resize(dydis*2+1);
        n = dydis;
        build(1);
    }
};
const int dydis = 5001;

int n, k, x;
vector<int> mas;
bool dp[dydis][dydis] = {0};
vector<seg_tree> mn(2);
long long ret;
long long f(int ind, int taken){ // taken - kiek paimta, iskaitant ir mane
    if(ind + (x-taken) >= n) {
        return -inf;
    }
    if(taken == x){ 
        if(n-ind <= k) {
            mn[taken%2].add(1, ind, ind, mas[ind]);
            return mas[ind]; 
        }else{
            mn[taken%2].add(1, ind, ind, -inf);
            return -inf;
        }
    } 
    ret = mn[(taken+1)%2].find(1, ind+1, min(n-1, ind+k+1-1));
    ret += mas[ind];
    mn[taken%2].add(1, ind, ind, ret);
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dydis; i++){
        if(i < 2) mn[i].bld(dydis);
        for(int j = 0; j < dydis; j++){
            dp[i][j] = 0;
        }
    }
    cin >> n >> k >> x;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    long long ans = -inf;
    for(int taken = x; taken > 0; taken--){
        mn[taken%2].bld(dydis);
        for(int ind = n-1; ind > max(taken-2, -1); ind--){
            f(ind, taken);
            if(taken == 1 && ind < k) ans = max(ans, f(ind, taken));
        } 
    }
    for(int i = 0; i < k; i++) {
        ans = max(ans, f(i, 1));
    }
    if(ans <= 0){
        cout << "-1";
        return 0;
    }
    cout << ans;
    return 0;
}
