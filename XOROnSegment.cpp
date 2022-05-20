#include <bits/stdc++.h>
using namespace std;

struct seg_tree{
    struct node{
        int l, r, val;
        int pl = 0;
    };
    vector<int> vec;
    vector<node> medis;
    int n;
    int dbInd = 0;
    void build(int v){
        if(v >= n){
            medis[v].l = medis[v].r = dbInd++;
            medis[v].val = (dbInd-1 >= vec.size() ? 0 : vec[dbInd-1]);
        }else{
            build(v * 2); build(v * 2 + 1);
            medis[v].l = medis[v * 2].l;
            medis[v].r = medis[v * 2 + 1].r;
            medis[v].val = medis[v * 2].val + medis[v * 2 + 1].val;
        }
    }
    seg_tree(int dydis, vector<int> a){
        vec = a;
        n = dydis;
        medis.resize(2 * n + 1);
        build(1);
    }
    
    void apply(int v){
        if(medis[v].pl == 0) return;
        if(v < n){
            medis[v*2].pl = !medis[v*2].pl;
            medis[v*2+1].pl = !medis[v*2+1].pl;
        }
        medis[v].val = medis[v].r - medis[v].l + 1 - medis[v].val;
        medis[v].pl = 0;
    }
    
    int find(int v, int l, int r){
        apply(v);
        if(l <= medis[v].l && medis[v].r <= r){
            return medis[v].val;
        }else if(medis[v].r < l || medis[v].l > r){
            return 0;
        }else{
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
    void change(int v, int l, int r){
        apply(v);
        if(l <= medis[v].l && medis[v].r <= r){
            medis[v].pl = !medis[v].pl;
            apply(v);
        }else if(medis[v].r < l || medis[v].l > r){
            return;
        }else{
            change(v*2, l, r);
            change(v*2+1, l, r);
            medis[v].val = medis[v*2].val + medis[v*2+1].val;
        }
    }
};
const int dydis = 1e5  +10;
vector<seg_tree> medziai;
int n;
vector<int> mas[21];
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        for(int j = 0; j < 21; j++){
            mas[j].push_back(((1 << j) & a) > 0);
        }
    }
    for(int j = 0; j < 21; j++){
        seg_tree st(dydis, mas[j]);
        medziai.push_back(st);
    }
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if(t == 1){
            int a, b; cin >> a >> b; a--; b--;
            long long sm = 0;
            for(int i = 0; i < 21; i++){
                sm += 1ll * medziai[i].find(1, a, b) * (1ll << i);
            }
            cout << sm << "\n";
        }else{
            int a, b, c; cin >> a >> b >> c; a--; b--;
            for(int i = 0; i < 21; i++){
                if(!(c & (1 << i))) continue;
                medziai[i].change(1, a, b);
            }
        }

    }
    
    return 0;
}
