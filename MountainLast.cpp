#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
struct seg_tree{
    struct node{
        int l, r;
        long long sm = 0;
        long long maxPref = 0;
        long long lazy = -inf;
    };
    vector<node> tree;
    int n; int dbInd = 0;
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = dbInd++;
        }else{
            build(v*2); build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    seg_tree (int dd){
        tree.resize(dd*2 + 1);
        n = dd;
        build(1);
    }
    
    void apply(int v){
        if(tree[v].lazy == -inf) return;
        tree[v].sm = (tree[v].r - tree[v].l + 1) * tree[v].lazy;
        if(tree[v].lazy < 0){
            tree[v].maxPref = tree[v].lazy;  
        }else{
            tree[v].maxPref = tree[v].sm;
        }
        if(v >= n){
        }else{
            tree[v*2].lazy = tree[v].lazy;
            tree[v*2+1].lazy = tree[v].lazy;
        }
        tree[v].lazy = -inf;
    }
    void change(int v, int l, int r, int x){
        apply(v);
        if(l <= tree[v].l && tree[v].r <= r){
            tree[v].lazy = x;
            apply(v);
        }else if(tree[v].r < l || r < tree[v].l){
            return;    
        }else{
            change(v*2, l, r, x);
            change(v*2+1, l, r, x);
            tree[v].sm = tree[v*2].sm + tree[v*2+1].sm;
            tree[v].maxPref = max(tree[v*2].maxPref, tree[v*2+1].maxPref + tree[v*2].sm);
        }
    }
    long long getMaxPref(int v, int l, int r, int kSm){
        apply(v);
        if(l <= tree[v].l && tree[v].r <= r){
            return kSm + tree[v].maxPref;
        }else if(tree[v].r < l || r < tree[v].l){
            return 0; 
        }else{
            return max(getMaxPref(v*2, l, r, kSm), getMaxPref(v*2+1, l, r, tree[v*2].sm + kSm));
        }       
    }

};
vector<int> mas;
int ind(int x){
    return lower_bound(mas.begin(), mas.end(), x) - mas.begin();
}
const int dydis = 2e5 + 100;
seg_tree medis(dydis);
int main(){
    int n; cin >> n;
    vector<pair<int, pair<int, int > > > vec;
    while(true){
        char a; cin >> a;
        if(a == 'E') break;
        if(a == 'Q'){
            int a; cin >> a;
            vec.push_back({a, {-1, -1}});
        }else{
            int a, b, c; cin >> a >> b >> c;
            mas.push_back(a); mas.push_back(b);
            vec.push_back({a, {b, c}});
        }
    }
//    mas.push_back(-1);
    sort(mas.begin(), mas.end());
    for(auto x : vec){
        if(x.second.first == -1){ // Q
            int a = x.first;
            int l = 0; int r = dydis-1; int mid;
            int ans = -1;
            while(l <= r){
                mid = (l + r) / 2;
                if(medis.getMaxPref(1, 0, mid, 0) <= a){
                    l = mid+1;
                    ans = max(ans, mid);
                }else{
                    r = mid-1;
                }
            }
            if(ans == dydis-1){
                cout << n << "\n";
            }else{
                cout << mas[ans+1]-1 << "\n";
            }
//            cout << min(ans+1, n) << "\n";
        }else{ 
            int l = ind(x.first);
            int r = ind(x.second.first);
            int k = x.second.second;
            medis.change(1, l, r, k);
        }
    }
    return 0;
}
