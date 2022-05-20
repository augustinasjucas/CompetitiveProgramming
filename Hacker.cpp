#include <bits/stdc++.h>
using namespace std;
struct node{
    long long val, l, r, plus;
};
struct seg_tree{
    
    vector<node> tree;
    int currInd = 0;
    int n;
    
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = currInd++;
            tree[v].val = tree[v].plus = 0;
        }else{
            build(v*2);
            build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    void apply(int v){
        tree[v].val += tree[v].plus * (tree[v].r - tree[v].l + 1);
        if(v < n) tree[v*2].plus += tree[v].plus;
        if(v < n) tree[v*2+1].plus += tree[v].plus;
        tree[v].plus = 0;
    }
    void add(int v, int l, int r, int x){
//        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].val = x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = max(tree[v*2].val, tree[v*2+1].val);
        }
//        apply(v);
    }
    long long find(int v, int l, int r){
//        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return max(find(v*2, l, r),find(v*2+1, l, r));
        }
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
int n;
long long s = 0;
vector<long long> mas;
vector<long long> vec;
seg_tree medis(1000010);
long long mx(int l, int r){
    long long ret= medis.find(1, l, r);
    return ret;
}
int main(){
    cin >> n; mas.resize(n);
    vec.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> mas[i];
        s += mas[i];
    }
    for(int i = 0; i < n; i++){
        mas.push_back(mas[i]);
    }
    vec.resize(2*n);
    int sz = n/2; long long k = 0;
    for(int i = 0; i < sz; i++){
        k += mas[i];
    }
    vec[0]  = k;
//    cout <<"vec[0] = " << k << endl;
    for(int i = 1; i < 2*n; i++){
        k -= mas[(i-1+n)%n];
        k += mas[(i+sz+n-1)%n];
        vec[i] = k;
        medis.add(1, i, i, k);
//        cout << "vec[" << i << "] = " << vec[i] << endl;
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
//        cout << "jei imu " << i << "(" << mas[i] << "), tai ats = " << s << " - mx(" <<  i+1 << "; " << i+n-sz <<") (" << mx(i+1, i+n-sz) << ") = " <<  s - mx(i+1, i + n-sz) << endl;
        ans = max(ans, s - mx(i+1, i + n-sz));
    }
    cout << ans;
    return 0;
}
