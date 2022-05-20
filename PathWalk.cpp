#include <bits/stdc++.h>
using namespace std;

struct seg_tree{
    struct node{
        int l, r, val;
    };
    int n, dbInd = 0;
    vector<node> medis;
    void build(int v){
        if(v >= n){
            medis[v].l = medis[v].r = dbInd++;
            medis[v].val = 0;
        }else{
            build(v*2);
            build(v*2+1);
            medis[v].l = medis[v*2].l;
            medis[v].r = medis[v*2+1].r;
            medis[v].val = 0;
        }
    }
    seg_tree(int d){
        n = d;
        dbInd = 0;
        medis.resize(n*2+1);
        build(1);
    }
    int find(int v, int l, int r){
        if(l <= medis[v].l && medis[v].r <= r){
            return medis[v].val;
        }else if(medis[v].r < l || r < medis[v].l){
            return 0;
        }else{
            return max(find(v*2, l, r), find(v*2+1, l, r));
        }
    }
    void change(int v, int l, int r, int x){
        if(l <= medis[v].l && medis[v].r <= r){
            medis[v].val = x;
        }else if(medis[v].r < l || r < medis[v].l){
            return ;
        }else{
            change(v*2, l, r, x);
            change(v*2+1, l, r, x);
            medis[v].val = max(medis[v*2].val, medis[v*2+1].val);
        }
    }
};
const int dydis = 100001;
vector<seg_tree> medziai; // atsakymai, jei kelias baigiasi i-ojoje virsuneje
int n, m;
vector<pair<int, int> > grRev[dydis];
vector<pair<int, int> > gr[dydis];
vector<pair<pair<int, int>, pair<int, int> > > brn;
int ans = 0;
int fd(int kur, int ind){ // kur medyje surasti priesdelio [0; ind] max elementa
    auto kr = lower_bound(grRev[kur].begin(), grRev[kur].end(), make_pair(ind, -1)) - grRev[kur].begin() - 1;
    if(kr == -1) return 0;
    return medziai[kur].find(1, 0, kr);
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        gr[a].push_back({i, b}); 
        grRev[b].push_back({i, a});
        brn.push_back({{c, i}, {a, b}});
    }
    for(int i = 0; i < n; i++){
        seg_tree st(grRev[i].size()+1);
        medziai.push_back(st);
    }
    sort(brn.begin(), brn.end());
    for(auto x : brn){
        int a = x.second.first;
        int b = x.second.second;
        int ind = x.first.second;
        int prm = fd(a, ind); // didziausias atsakymas, jei posekis PASIBAIGIA a virsuneje
        prm++;
        ind = lower_bound(grRev[b].begin(), grRev[b].end(), make_pair(ind, a)) - grRev[b].begin();
        medziai[b].change(1, ind, ind, prm);
        ans = max(ans, prm);
    }
    cout << ans;
    return 0;
}
