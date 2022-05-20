#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
vector<int> mas;
struct seg_tree{
    struct node{
        int l, r;
        long long sm = 0;
        long long maxPref = 0;
        long long lazy = -inf;
        long long last = 0;
    };
    vector<node> tree;
    int n; int dbInd = 0;
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = mas[dbInd++];
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
        tree[v].last = tree[v].lazy;
        tree[v].lazy = -inf;
    }
    bool change(int v, int l, int r, int x){
        apply(v);
        if(l <= tree[v].l && tree[v].r <= r){
            tree[v].lazy = x;
            apply(v);
        }else if(tree[v].r < l || r < tree[v].l){
            return false; 
        }else{
            bool st = change(v*2, l, r, x);
            st &= change(v*2+1, l, r, x);
            
            if(st) tree[v].last = x;
            long long pl = 0;
            pl = tree[v].last * (tree[v*2+1].l-tree[v*2].r-1);
//            cout << "last = " << tree[v].last << endl;
            tree[v].sm = tree[v*2].sm + tree[v*2+1].sm + pl;
            tree[v].maxPref = max(max(tree[v*2].sm + pl, tree[v*2].maxPref), tree[v*2+1].maxPref + tree[v*2].sm + pl);
        }
//        cout << "dabar [" << tree[v].l << "; " << tree[v].r << "].sm = " << tree[v].sm << ", o maxPref = " << tree[v].maxPref << endl;
        return true;
    }
    long long getMaxPref(int v, int l, int r, long long kSm){
//        cout << "v = " << v << ", ";
        apply(v);
//        cout << "ieskau max pref [" << l << "; " << r << "] intervale, kSm =" << kSm << ", dabar [" << tree[v].l << "; " << tree[v].r << "].sm = " << tree[v].sm << ", o maxPref = " << tree[v].maxPref << endl;
        if(l <= tree[v].l && tree[v].r <= r){
            return kSm + max(tree[v].maxPref, 0ll);
        }else if(tree[v].r < l || r < tree[v].l){
            return -inf; 
        }else{
            long long pl = 0;
            pl = tree[v].last * (tree[v*2+1].l-tree[v*2].r-1);
//            kSm += pl;
            long long retl = getMaxPref(v*2, l, r, kSm);
            long long retr = getMaxPref(v*2+1, l, r, tree[v*2].sm + kSm + pl);
            if(retr == -inf && tree[v].r > r && l <= tree[v*2].l && tree[v*2].r <= r){
//                cout << "returninu " << kSm << " + " << retl 
                return max(retl, tree[v*2].sm + kSm + max((r-tree[v*2].r) * tree[v].last, 0ll));
            }else{
                return max(retl, retr);
            }
        }       
    }

};
set<int> vs;

int ind(int x){
    return lower_bound(mas.begin(), mas.end(), x) - mas.begin();
}
const int dydis = 2e5 + 10;
vector<int> cr(dydis);
int n;
void brt(int a, int b, int x){
    for(int i = a; i <= b; i++) cr[i] = x;
}
int gt(int x){
    int sm = 0;
    for(int i = 1; i <= n; i++) {
        sm += cr[i];
        if(sm > x) return i-1;
    }
    return n;
}
int main(){
    cin >> n;
    vector<pair<int, pair<int, int > > > vec;
    while(true){
        char a; cin >> a;
        if(a == 'E') break;
        if(a == 'Q'){
            int a; cin >> a;
            vec.push_back({a, {-1, -1}});
        }else{
            int a, b, c; cin >> a >> b >> c;
            vs.insert(a); vs.insert(b);
            vec.push_back({a, {b, c}});
        }
    }
    vs.insert(n);
    vs.insert(1);
    for(auto x : vs) mas.push_back(x);
    sort(mas.begin(), mas.end());
    seg_tree medis(mas.size());
    for(auto x : vec){
        if(x.second.first == -1){ // Q
            long long a = x.first;
            int l = 1; int r = n; int mid;
            int ans = 0;
            while(l <= r){
                mid = (l + r) / 2;
                auto kk = medis.getMaxPref(1, 1, mid, 0);
//                cout << "intervalo [1; " << mid << "] maxPref = " << kk << endl; 
                if(kk <= a){
                    l = mid+1;
                    ans = max(ans, mid);
                }else{
                    r = mid-1;
                }
            }
            cout << ans ;
     //       cout << " vs " << gt(a);
            cout << "\n";
            //            cout << min(ans+1, n) << "\n";
        }else{ 
            int l = x.first;
            int r = x.second.first;
            int k = x.second.second;
//            brt(l, r, k);
//            cout << "keiciam [" << l << "; " << r << "] i " << k << endl;
            medis.change(1, l, r, k);
        }
    }
    return 0;
}
