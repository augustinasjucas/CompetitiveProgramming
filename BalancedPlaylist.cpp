#include <bits/stdc++.h>
using namespace std;
struct node{
    int val, l, r, plus;
};
struct seg_tree{
    
    vector<node> tree;
    int currInd = 0;
    int n;
    
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = currInd++;
            tree[v].val = 1000000000;
        }else{
            build(v*2);
            build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    void add(int v, int l, int r, int x){
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].val = x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = min(tree[v*2].val, tree[v*2+1].val);
        }
    }
    int find(int v, int l, int r){
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 1000000000;
        }else {
            return min(find(v*2, l, r),find(v*2+1, l, r));
        }
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
const int inf = 1e9;
const int dydis = 3e5 + 10;
long long mn = 1e9;
long long mx = 0;
int n;
vector<long long> mas;
vector<long long> vec;
int lg[dydis] = {0};
long long st[dydis][30] = {0};
void build(){
    
    int m = vec.size();
    int k = log2(m) + 1;
    for (int i = 0; i < m; i++)
        st[i][0] = vec[i];

    for (int j = 1; j <= k; j++)
        for (int i = 0; i + (1 << j) <= m; i++)
            st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
    lg[1] = 0;
    for (int i = 2; i < dydis; i++)
        lg[i] = lg[i/2] + 1;
}
long long quer(int L, int R){
    int j = lg[R - L + 1];
    long long minimum = min(st[L][j], st[R - (1 << j) + 1][j]);
    return minimum;
}
seg_tree medis(dydis);
void daryk(int ind){
    int m = vec.size();
    int l = ind, r = vec.size()-1;
    int pos = inf;
    while(l <= r){
        int mid = (l+r)/2;
        if(quer(ind, mid)*2 < vec[ind]){
            pos = min(pos, mid);
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    if(pos == inf) {
        pos = vec.size();
    }
    if(pos == ind){
        medis.add(1, ind, ind, inf);
    }else{
        long long mn = min(medis.find(1, ind, pos-1), pos-1);
        medis.add(1, ind, ind, mn);
    }
}
int main(){
    cin >> n;
    mas.resize(n);
    for(auto &x : mas) {
        cin >> x; x *= 2;
        mn = min(x, mn);
        mx = max(x, mx);
    }
    if(mn*2 >= mx){
        for(int i = 0; i < n; i++){
            cout << "-1 ";
        }
        return 0;
    }
    
    for(auto x : mas) vec.push_back(x);
    for(auto x : mas) vec.push_back(x);
    for(auto x : mas) vec.push_back(x); 
    build();    
    for(int i = vec.size()-1; i > -1; i--){
        daryk(i);
    }
    for(int i = 0; i < n; i++){
        int p1 = medis.find(1, i, i)-i;
        int p2 = medis.find(1, i+n, i+n)-i-n;
        int p3 = medis.find(1, i+n+n, i+n+n)-i-n-n;
        if(p1 >= 3*n) p1 = 1;
        if(p2 >= 3*n) p2 = 1;
        if(p3 >= 3*n) p3 = 1;
        cout << max(max(p1, p2), p3) +1<< " ";
    }
    return 0;
}
