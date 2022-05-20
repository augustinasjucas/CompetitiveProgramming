#include <bits/stdc++.h>
using namespace std;
struct treeMin {
    vector<int> l, r;
    vector<long long> sm;
    int n;
    int dbInd = 0;
    void build(int v = 1) {
        if(v >= n) {
            l[v] = r[v] = dbInd++;
        }else {
            build(v*2);
            build(v*2+1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
    }
    treeMin(int dd) {
        l.resize(dd*2+1);
        r.resize(dd*2+1);
        sm.resize(dd*2+1);
        n = dd;
        build(1);
    }
    void change(int v, int L, int R, int x) {
        if(L <= l[v] && r[v] <= R) {
            sm[v] = x;
        }else if(R < l[v] || r[v] < L) {
            return ;
        }else {
            change(v*2, L, R, x);
            change(v*2+1, L, R, x);
            sm[v] = sm[v*2] + sm[v*2+1];
        }
    }
    long long getSum(int v, int L, int R){
        if(L <= l[v] && r[v] <= R) {
            return sm[v];
        }else if(R < l[v] || r[v] < L) {
            return 0;
        }else {
            return getSum(v*2, L, R) + getSum(v*2+1, L, R);
        }
    }

};
const int dydis = 1e5 + 10;
const int dd = 20;
vector<int> gr[dydis];
vector<pair<int, int> > gr1[dydis];
int enter[dydis];
int leave[dydis];
int dbInd = 0;
int tevas[dydis];
int lift[dydis][dd];
int sz[dydis] = {};
int n;
int c[dydis] = {};
int le[dydis] = {};
int ri[dydis] = {};
int height[dydis] = {};
vector<int> trav;
int kur[dydis] = {};
treeMin medis(dydis + 1);
void dfs1(int v, int came) {
    sz[v] = 1;
    for(auto &x : gr1[v]) {
        if(x.second == came) continue;
        dfs1(x.second, v);
        sz[v] += sz[x.second];
        x.first = sz[x.second];
    }
    sort(gr1[v].begin(), gr1[v].end());
    reverse(gr1[v].begin(), gr1[v].end());
    for(auto &x : gr1[v]) {
        if(x.second == came) continue;
        gr[v].push_back(x.second);
    }
}
void dfs2(int v, int came) {
    enter[v] = dbInd++;
    tevas[v] = came;
    for(auto x : gr[v]) {
        if(x == came) continue;
        height[x] = height[v] + 1;
        dfs2(x, v);
    }
    leave[v] = dbInd++;
}
int dfs3(int v){
    ri[v] = trav.size();
    kur[v] = trav.size();
    trav.push_back(v);  
    
    if(gr[v].size()){
        le[gr[v][0]] = le[v];
        ri[v] = dfs3(gr[v][0]);
    }
    for(int i = 1; i < gr[v].size(); i++) {
        int x = gr[v][i];
        le[x] = trav.size();
        dfs3(x);
    }
    return ri[v];
}
void precalc(){
    for(int i = 0; i < n; i++) {
        lift[i][0] = tevas[i];
    }
    for(int i = 1; i < dd; i++) {
        for(int j = 0; j < n; j++) {
            lift[j][i] = lift[lift[j][i-1]][i-1];
        }
    }
}
int isAnc(int a, int b) {
    return enter[a] <= enter[b] && leave[b] <= leave[a];
}
int lca(int a, int b) {
    if(isAnc(a, b)) return a;
    if(isAnc(b, a)) return b;
    for(int i = dd-1; i > -1; i--) {
        if(!isAnc(lift[a][i], b)) {
            a = lift[a][i];
        }
    }
    return tevas[a];
}

long long sm(int v, int h){   // randa suma nuo v, viso h virsuniu
    long long ans = 0;
    while(h != 0) {
        int r = min(ri[v], kur[v]);
        int l = max(le[v], r-h+1);
        
        ans += medis.getSum(1, l, r);

        h -= r - l + 1;

        v = tevas[trav[l]];
    }
    return ans;
}
long long raskKelia(int a, int b){
    int pr = lca(a, b);
    long long ans = 0;
    ans += sm(a, height[a]-height[pr]) * 2ll;
    ans += sm(b, height[b]-height[pr]) * 2ll;
    ans -= c[a];
    ans -= c[b];
    ans += 2ll * c[pr];
    return ans;
}


int main () {
    int q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> c[i];
        c[i] = abs(c[i]);
    }
    for(int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        gr1[a].push_back({0, b});
        gr1[b].push_back({0, a});
    } 
    dfs1(0, 0);
    dfs2(0, 0);
    
    le[0] = 0; 
    dfs3(0);
    
    precalc();

    for(int i = 0; i < n; i++) {
        medis.change(1, kur[i], kur[i], c[i]);
    }

/*    while(true) {
        int v, h; cin >> v >> h;
        
        int ans = sm(v-1, h);
        cout << "nuo " << v << " viso paemus " << h << " virsuniu aukstyn, suma = " << ans << endl;
    }


    cout << "trav: "; 
    for(auto x : trav) cout << x+1 << " ";
    cout << endl;
    for(int i = 0; i < n; i++) {
        cout << i+1 << ". tevas - " << tevas[i]+1 << ", intervalas[" << le[i] << "; " << ri[i] << "]\n";
    }
    while(true) {
        int a, b; cin >> a >> b; a--; b--;
        cout << lca(a, b) + 1 << endl;
    }*/
    while(q--) {
        int type; cin >> type;
        if(type == 2) {
            int a, b; cin >> a >> b; a--; b--;
            cout << raskKelia(a, b) << "\n";
        }else {
            int a, b; cin >> a >> b; a--;
            c[a] = abs(b);
            medis.change(1, kur[a], kur[a], c[a]);
        }
    }
    return 0;
}
