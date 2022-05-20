#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
struct node{
    long long val, l, r, plus, kek = 0;
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
    void add(int v, int l, int r, int x, int kk){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].plus += x;
            tree[v].kek += kk;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x, kk);
            add(v*2+1, l, r, x, kk);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
            tree[v].kek = tree[v*2].kek + tree[v*2+1].kek;
        }
        apply(v);
    }
    pair<long long, long long> find(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return {tree[v].val, tree[v].kek};
        }else if(tree[v].l > r || tree[v].r < l){
            return make_pair(0ll, 0ll);
        }else {
            auto prm = find(v*2, l, r);
            auto ant = find(v*2+1, l, r);
            return make_pair(prm.first + ant.first, prm.second + ant.second);
        }
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
    void print(int v){
        if(v < n){
            print(v*2);
            print(v*2+1);
        }
    }
};
int n;
vector<pair<int, int> > mas;
vector<int> xes, vs;
vector<int> compress(vector<int> a){
    vector<int> srt = a, un;
    sort(srt.begin(), srt.end());
    un.push_back(srt[0]);
    for(int i = 1; i < a.size(); i++){
        if(un.back() == srt[i]) continue;
        un.push_back(srt[i]);
    }
    for(auto &x : a){
        int kur = lower_bound(un.begin(), un.end(), x) - un.begin();
        x = kur;
    }
    return a;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    mas.resize(n);
    
    for(auto &x : mas) {
        cin >> x.first;
    }
    for(auto &x : mas){
        cin >> x.second;
    }
    sort(mas.begin(), mas.end());
    for(auto x : mas){
        xes.push_back(x.first);
        vs.push_back(x.second);
    }
    vs = compress(vs);
    seg_tree medis(n);
    for(int i = 0; i < n; i++){
        medis.add(1, vs[i], vs[i], xes[i], 1);
    }
    long long s = 0;
    long long ans = 0;
    medis.print(1);
    for(int i = 0; i < n; i++){
        auto kas = medis.find(1, vs[i], n-1);
        ans += (kas.first) - kas.second*((long long)xes[i]);
        medis.add(1, vs[i], vs[i], -xes[i], -1);
    }
    cout << ans;

    return 0;
}
