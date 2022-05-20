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
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
vector<int> vec;
int kur[5001] ={0};
int n;
seg_tree medis(801);
int kainuos(vector<int> &mas, int l, int r){
    for(int i = l; i < mas.size(); i++){
        kur[vec[i]] = i;
        int kiek = medis.find(1, i, i);
        medis.add(1, i, i, -kiek);
    }
    int ret = 0;
//    cout << l << ", " << r << ", ziuresim kiek kainuos nueiti iki "; for(auto x : mas) cout << x<< " "; cout << "\n";
    for(int i = 0; i <= r; i++){
        int kr = kur[mas[i]] + medis.find(1, kur[mas[i]], kur[mas[i]]);
        medis.add(1, 0, kur[mas[i]]-1, 1);
        if(l <= i && i <= r) {
            ret += kr - i;
//            cout << i << ", pridedu " << kr << " - " << i << endl;
        }
    }
    return ret;
}
int vl(int l, int r, int prm){
    int ret = 0;
    vector<int> sitas(n);
    for(int i = 0; i < l; i++) sitas[i] = i;
    for(int i = l; i <= r; i++){
        int ka = prm -(i - l);
        sitas[i] = ka;
    }
    for(int j = r+1; j < n; j++) sitas[j] = j;
    return kainuos(sitas, l, r);
}
int dp[5001][5001] = {0};
int mn[5001][5001] = {0};

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < 5001; i++){
        for(int j = 0; j < 5001; j++){
            dp[i][j] = -1;
            mn[i][j] = 1e9;
        }
    }
    cin >> n;
    vector<int> mas(n);
    vec.resize(n);
    for(int i = 0; i < n; i++){
        cin >> vec[i]; vec[i]--;
        kur[vec[i]] = i;
    }
    int ans = 1e9;

    for(int ind = n-1; ind > -1; ind--){
        for(int db = n-1; db >= ind; db--){
            int pask = db; // uzbaigsiu padedamas ind i pask
            int ret = vl(ind, pask, db);
            int pl = 1e9;
            if(pask == n-1) pl = 0;
            pl = min(mn[pask+1][db+1], pl);
            mn[ind][db] = pl + ret;
            mn[ind][db] = min(mn[ind][db], mn[ind][db + 1]);
            dp[ind][db] = pl + ret;
        }
    }
    for(int i = 0; i < n; i++){
        ans = min(ans, dp[0][i]);
    }

    cout << ans;
    return 0;
}

