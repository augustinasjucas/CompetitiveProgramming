#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct node{
    int l, r;
    long long mx = 0, val, plus = 0;
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
        tree[v].mx += tree[v].plus;
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
            tree[v].mx = max(tree[v*2].mx, tree[v*2+1].mx);
        }
        apply(v);
    }
    long long find(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
    long long findMx(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].mx;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return max(findMx(v*2, l, r), findMx(v*2+1, l, r));
        }
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
const int dydis = 1e5 + 1;
int n;
vector<int> gr[dydis];
int tevas[dydis];
int enter[dydis] = {0};
int leave[dydis] = {0};
int dbInd = 0;
vector<int> trav;
int lift[dydis][20]; // is i, kylu 2^j
int lev[dydis];
seg_tree medis(3);
void dfs(int v, int came, int au){
    tevas[v] = came;
    enter[v] = dbInd++;
    trav.push_back(v);
    lev[v] = au;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, au+1);
    }
    leave[v] = dbInd;
}
void calc(){
    for(int i = 0; i < n; i++){
        lift[i][0] = (max(tevas[i], 0));
    }
    for(int j = 1; j < 20; j++){
        for(int i = 0; i < n; i++){
            lift[i][j] = lift[lift[i][j-1]][j-1];
        }
    }
}
bool isAnc(int a, int b){ // ar a yra b tevas?
    return enter[a] <= enter[b] && leave[b] <= leave[a];
}
int lca(int a, int b){
    if(isAnc(a, b)) return a;
    if(isAnc(b, a)) return b;
    for(int i = 19; i > -1; i--){
        if(!isAnc(lift[b][i], a)){
            b = lift[b][i];
        }
    }
    return max(tevas[b], 0);
}
long long rask(int a, int b, bool skp, long long kn){
    long long ret = 0;
    while(true){
        if((a == b && !skp) || a != b)ret = max(ret, medis.findMx(1, enter[a], enter[a]));
        
        if((a == b && !skp) || a != b){
            medis.add(1, enter[a], enter[a], kn);
//            cout << "pridedu " << a+1 << " \n";
        }
        if(a == b) break;
        a = max(tevas[a], 0);
    }
    return ret;
}
long long kelias(int a, int b, long long v){
    long long prm = rask(a, lca(a, b), 0, v) ;
    long long ant = rask(b, lca(a, b), 1, v) ;
    return max(prm, ant);
}
long long drk(int l, int r, long long kn){
//    cout << "gaunu " << l << "; " << r << ", prd " << kn << endl;
    if(l < 0 || l > r) return 0;
    long long rt = medis.findMx(1, l, r);
    medis.add(1, l, r, kn);
    return rt;
}
long long pomedis(int v, int cm, long long kn){
    if(tevas[v] == cm){
        return drk(enter[v], leave[v], kn);
    }else{
        return max(drk(0, enter[cm]-1, kn), drk(leave[cm], n-1, kn));
    }
}
bool priklausoPomedziui(int kas, int v, int cm){
     if(cm == tevas[v]){
        return lca(kas, v) == v;
     }
     return lca(cm, kas) != cm;
}
void print(){
    for(int i = 0; i < n; i++){
        cout << i  + 1 << " virsuneje uzkrato yra " << medis.find(1, enter[i], enter[i]) << "\n";
    }
    cout << endl;
}
int main(){
//    freopen("int.txt", "r", stdin);
//    cin.tie(NULL);
//    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    medis = seg_tree(n + 2);
    dfs(0, -1, 0);
//    cout << "tr = ["; for(auto x : trav) cout << x+1 << " "; cout << "]\n";
    calc();
    int q; cin >> q;
    while(q--){
        char a; cin >> a;
        if(a == 'M'){
            int b, c, d; cin >> b >> c >> d;
            b--; c--;
            cout << kelias(b, c, d) << "\n";
        }else{
            int b, c, d, e; cin >> b >> c >> d >> e;
            b--; c--; d--;
            if(priklausoPomedziui(d, b, c)){ // ar d priklauso pomedziui is b, neinant i c
                long long sitas = pomedis(b, c, e);
                cout << sitas << "\n";
            }else{
                long long sitas = pomedis(b, c, e);             
                medis.add(1, enter[b], enter[b], -e);
//                cout << "pomedzio maxas = " << sitas << endl;
                sitas = max(sitas, kelias(b, d, e));
                cout << sitas << "\n";
            }
        }
//       print();
    }

    return 0;
}
