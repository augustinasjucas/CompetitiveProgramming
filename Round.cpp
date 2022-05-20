#include <bits/stdc++.h>
using namespace std;

const int dydis = 1e5 + 10;
const long long inf = 1e18;
struct node {
    long long val, l, r, plus = inf;
    long long mn = inf;
};
struct seg_tree {

    vector<node> tree;
    int currInd = 0;
    int n;

    void build(int v) {
        if (v >= n) {
            tree[v].l = tree[v].r = currInd++;
            tree[v].val = tree[v].plus = inf;
            tree[v].mn = inf;
        }
        else {
            build(v * 2);
            build(v * 2 + 1);
            tree[v].l = tree[v * 2].l;
            tree[v].r = tree[v * 2 + 1].r;
        }
    }
    void apply(int v) {
        if(tree[v].plus == inf) return ;
        tree[v].mn = min(tree[v].mn, tree[v].plus);
        if (v < n) {
            tree[v * 2].plus = min(tree[v * 2].plus, tree[v].plus);
        }

        if (v < n) {
            tree[v * 2 + 1].plus = min(tree[v * 2 + 1].plus, tree[v].plus);
        }

        tree[v].plus = inf;
    }
    void add(int v, int l, int r, long long x) {
        apply(v);

        if (tree[v].l >= l && tree[v].r <= r) { /// sitas pilnai telpa intervale
            tree[v].plus = min(tree[v].plus, x);
        }
        else if (tree[v].l > r || tree[v].r < l) {

        }
        else {
            add(v * 2, l, r, x);
            add(v * 2 + 1, l, r, x);
            tree[v].mn = min(tree[v * 2].mn, tree[v * 2 + 1].mn);
        }

        apply(v);
    }
    long long find(int v, int l, int r) {
        apply(v);

        if (tree[v].l >= l && tree[v].r <= r) { /// sitas pilnai telpa intervale
            return tree[v].mn;
        }
        else if (tree[v].l > r || tree[v].r < l) {
            return inf;
        }
        else {
            long long ret = min(find(v * 2, l, r), find(v * 2 + 1, l, r));
//            cout << tree[v].l << "; " << tree[v].r <<", ret = " << ret << endl;
            return ret;
        }
    }
    seg_tree(int dydis) {
        tree.resize(dydis * 2 + 10);
        n = dydis;
        build(1);
    }
};
int n;
seg_tree dp1(dydis), dp2(dydis);
vector<pair<pair<int, int>, int> > mas;
long long ans = 0;
long long fd(){ // nuo kaires iki desines
    dp1.add(1, 0, 0, 0);
    dp2.add(1, 0, 0, 0);
    for(int i = 0; i < n; i++){
        long long prm = inf, ant = inf;
        prm = dp1.find(1, i, i);
        ant = dp2.find(1, i, i) + i;
        dp1.add(1, i+1, i+mas[i].first.second, min(prm, ant) + mas[i].first.second);
        dp2.add(1, i+mas[i].first.second+1, n-1, min(prm, ant) - i);
    }
    return dp1.find(1, n-1, n-1);
}
int kur = -1;
long long zemAuk(){ // nuo `kur` iki n-1 ir tada nuo 0 iki kur
    long long ret = 0;
    int ind = kur;
    for(int i = kur+1; i < n; i++){
        ret += max(mas[i-1].first.second, mas[i].first.first - mas[i-1].first.first);
    }
    ret += mas[n-1].first.second;
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        mas.push_back({{a, b}, i});
        ans += b;
//        if(i == n-1) ans -= b;
    }
    sort(mas.begin(), mas.end());
    for(int i = 0; i < n; i++){
        if(mas[i].second == 0) kur = i;
    }
    ans += zemAuk();  
    for()
    cout << ans;
    return 0;
}
