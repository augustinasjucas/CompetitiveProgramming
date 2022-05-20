#include <bits/stdc++.h>
#pragma GCC optimize("O3")
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
            tree[v].val = tree[v].plus = 0;
        }else{
            build(v*2);
            build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    void er(){
        for(int i = 0; i < 2*n; i++){
            tree[i].val = tree[i].plus = 0;
        }
    }
    void apply(int v){
        tree[v].val += tree[v].plus * (tree[v].r - tree[v].l + 1);
        if(v < n) tree[v*2].plus += tree[v].plus;
        if(v < n) tree[v*2+1].plus += tree[v].plus;
        tree[v].plus = 0;
    }
    void add(int v, int l, int r, int x){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].plus += x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
        }
        apply(v);
    }
    int find(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
    int mn(int v){
        if(tree[v].l == tree[v].r) return tree[v].l;
        if(tree[v*2].val != 0) return mn(v*2);
        return mn(v*2+1);
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};

void del(multiset<int> &setas, int x){
    auto kur = setas.find(x);
    if(kur == setas.end()) return ;
    setas.erase(kur);
}
seg_tree medis(510 + 500);
int n;
string a;
int kek(string &mas){
    medis.er();
    vector<int> vec;
    for(auto x : mas) vec.push_back(x);
    for(auto x : mas) vec.push_back(x);

    int pref[vec.size()];
    pref[0] = (vec[0] == '(' ? 1 : -1);
    for(int i = 1; i < vec.size(); i++){
        pref[i] = pref[i-1] + (vec[i] == '(' ? 1 : -1);
    }
    multiset<int> setas;
    int sm = 0, ret = 0;
    for(int i = 0; i < n; i++){
        medis.add(1, 500+pref[i], 500+pref[i], 1);
        sm += (vec[i] == '(' ? 1 : -1);
    }
    if(sm == 0 && medis.mn(1)-500 >= 0) ret++;
    for(int i = n; i < vec.size()-1; i++){
        medis.add(1, pref[i-n]+500, pref[i-n]+500, -1);
        medis.add(1, pref[i]+500, pref[i]+500, 1);
        int mn = (medis.mn(1)-500) - pref[i-n];
        sm = pref[i] - pref[i-n];
        if(mn >= 0 && sm == 0) ret++;
    }
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    pair<int, pair<int, int> > ans = {-1, {0, 0}} ;
    cin >> n >> a;
    ans = {kek(a), {0, 0}};
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(a[i] == a[j]) continue;
            swap(a[i], a[j]);
            ans = max(ans, {kek(a), {i, j}});
            swap(a[i], a[j]);
        }
    }
    cout << ans.first << "\n" << ans.second.first +1<< " " << ans.second.second+1;
    return 0;
}
