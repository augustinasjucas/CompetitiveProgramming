#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
struct seg_tree{
    struct node{
        long long l, r, sm, mn = inf, pl = 0;
    };
    int n;
    int dbInd = 0;
    vector<node> mas;
    void build(int v){
        mas[v].sm = 0;
        mas[v].mn = inf;
        mas[v].pl = 0;
        if(v >= n){
            mas[v].l = mas[v].r = dbInd++;
        }else{
            build(v * 2);
            build(v * 2 + 1);
            mas[v].l = mas[v*2].l;
            mas[v].r = mas[v*2+1].r;
        }
    }
    void apply(int v){
        if(mas[v].pl == 0) return;
        mas[v].sm += (mas[v].r - mas[v].l + 1) * mas[v].pl;
        mas[v].mn += mas[v].pl;
        if(v < n){
            mas[v*2].pl += mas[v].pl;
            mas[v*2+1].pl += mas[v].pl;
        }
        mas[v].pl = 0;
    }
    void change(int v, int l, int r, int x) { // privalo buti l = r
        apply(v);
        if(l <= mas[v].l && mas[v].r <= r){
            mas[v].sm = x;
            mas[v].mn = x;
        }else if(mas[v].r < l || r < mas[v].l){
            return ;
        }else{
            change(v*2, l, r, x);
            change(v*2+1, l, r, x);
            mas[v].sm = mas[v * 2].sm + mas[v * 2 + 1].sm;
            mas[v].mn = min(mas[v * 2].mn, mas[v * 2 + 1].mn);
        }
    }
    void add(int v, int l, int r, int x){
        apply(v);
        if(l <= mas[v].l && mas[v].r <= r){
            mas[v].pl += x;
            apply(v);
        }else if(mas[v].r < l || r < mas[v].l){
            return ;
        }else{
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            mas[v].sm = mas[v * 2].sm + mas[v * 2 + 1].sm;
            mas[v].mn = min(mas[v * 2].mn, mas[v * 2 + 1].mn);
        }
    }
    long long findSm(int v, int l, int r){
        apply(v);
        if(l <= mas[v].l && mas[v].r <= r){
            return mas[v].sm;
        }else if(mas[v].r < l || r < mas[v].l){
            return 0;
        }else{
            return findSm(v*2, l, r) + findSm(v*2+1, l, r);
        }
    }
    long long findMn(int v, int l, int r){
        apply(v);
        if(l <= mas[v].l && mas[v].r <= r){
            return mas[v].mn;
        }else if(mas[v].r < l || r < mas[v].l){
            return inf;
        }else{
            return min(findMn(v*2, l, r), findMn(v*2+1, l, r));
        }
    }
    int rightZero(int v){ // randa desiniausia nuli, jei yra visi teigiami!
        apply(v);
        if(mas[v].mn > 0) return -1;
        if(mas[v].l == mas[v].r) return mas[v].l;
        apply(v*2); apply(v*2+1);
        if(mas[v*2+1].mn == 0) return rightZero(v*2+1);
        return rightZero(v*2);
    }
    seg_tree(int dydis){
        mas.resize(dydis * 2 + 1);
        n = dydis;
        dbInd = 0;
        build(1);
    }
};
const int dydis = 3e5 + 10;
int n, q;
vector<int> mas, vec;
seg_tree medis(dydis);
seg_tree med(dydis);
int ans[dydis + 1]; 
int main() {
    cin >> n >> q;
    mas.resize(n); for(auto &x : mas) cin >> x;

    for(int i = 0; i < n; i++){
        vec.push_back((i-mas[i]+1 < 0 ? n + 2 : i-mas[i]+1));
        medis.change(1, i, i, vec.back());
    }
    vector<int> eil;
    while(true){
        int nl = medis.rightZero(1);
        if(nl == -1) break;
        eil.push_back(nl);
        medis.change(1, nl, nl, n+2);
        medis.add(1, nl, dydis-1, -1);
    }
    vector<pair<pair<int, int>, int> > quers;
    for(int i = 0; i < n+1; i++) med.change(1, i, i, 0);
    for(int i = 0; i < q; i++){
        int a, b; cin >> a >> b; 
        quers.push_back({{a, b}, i});
    }
    sort(quers.begin(), quers.end()); reverse(quers.begin(), quers.end());
    int ind = 0;
    for(auto x : quers){
        int mn = x.first.first;
        int maziauUz = n - x.first.second; // visi, kurie mazesni uz sita!
        while(ind != eil.size() && eil[ind] >= mn){
            med.add(1, eil[ind], eil[ind], 1);
            ind++;
        }
        ans[x.second] = med.findSm(1, 0, maziauUz-1);
    }

    for(int i = 0; i < q; i++) cout << ans[i] << "\n";
    return 0;
}
