#include <bits/stdc++.h>
using namespace std;
const int dydis = 70000 + 4;
const int dd = 1400000 + 10;
const int lg = 18;
int n, m;
int tevas[dydis];
int sz[dydis] = {};
int he[dydis] = {};
int retP;
int curV = 0, curU;

void fP(int &v) {
    curV = v;
    while(tevas[curV] != curV) curV = tevas[curV];
    retP = curV;
    curV = v;
    while(tevas[curV] != curV) {
        curU = tevas[curV];
        tevas[curV] = retP;
        curV = curU;
    }
}

int A, B;
void conn(int &a, int &b) {
//    fP(a); A = retP;
//    fP(b); B = retP;
    A = a; B = b;
    if(sz[A] > sz[B]) swap(A, B);
    tevas[A] = B;
    sz[B] += sz[A];
}

int aa, bb, pa, pb;
int ind = 0;

vector<int> gr[dydis];
bool vis[dydis] = {};
int anc[dydis] = {};
int enter[dydis] = {};
int leave[dydis] = {};
int dbInd = 0;
void dfs(int v, int came) {
    anc[v] = came;
    enter[v] = dbInd++;
    vis[v] = 1;
    for(auto x : gr[v]) {
        if(x == came) continue;
        he[x] = he[v] + 1;
        dfs(x, v);
    }
    leave[v] = dbInd++;
}
int lft[dydis][lg] = {};
void precalc(){
    for(int i = 0; i < n; i++) {
        lft[i][0] = anc[i];
    }
    for(int j = 1; j < lg; j++) {
        for(int i = 0; i < n; i++) {
            lft[i][j] = lft[lft[i][j-1]][j-1];
        }
    }
}
bool ISANC = 0;
void isAnc(int &a, int &b) {
    ISANC = enter[a] <= enter[b] && leave[b] <= leave[a];
}
int LCA;
void lca(int &a, int &b) {
    isAnc(a, b);
    if(ISANC){
        LCA = a;
        return;
    }
    isAnc(a, b);
    if(ISANC){
        LCA = b;
        return ;
    }
    LCA = a;
    for(int i = lg-1; i > -1; i--) {
        isAnc(lft[LCA][i], b);
        if(!ISANC) {
            LCA = lft[LCA][i];
        }
    }
    LCA = anc[LCA];
}
int mark[dydis] = {};
int dfs1(int v, int came) {
    vis[v] = 1;
    int st = 0;
    for(auto &x : gr[v]) {
        if(x == came) continue;
        st = max(st, dfs1(x, v) - 1);
    }
    st = max(st, mark[v]);
    if(st == 0) {
        if(v != came) cout << v + 1 << " " << came+1 << "\n";
    }
    return st;
}


long long brn[dd];
int id = 0;
long long sitas;
void putIn(int &a) {
    brn[id/3] = brn[id/3] * n + a;
    id++;
}

int OUT;
__int128_t OUT1;
void takeOut(int &ind) {
    OUT1 = brn[ind/3];
    for(int i = 0; i < 2-ind%3; i++) OUT1 /= n;
    OUT = OUT1 % n;
}
int kaPut;
int main() {
    for(int i = 0; i < dydis; i++) {
        tevas[i] = i;
        sz[i] = 1;
    }
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> aa >> bb; aa--; bb--;
        fP(aa); pa = retP;
        fP(bb); pb = retP;
        if(pa != pb) {
            gr[aa].push_back(bb);
            gr[bb].push_back(aa);
//            cout << "briauna " << aa+1 << " -- " << bb+1 << endl;
        }else {
            kaPut = aa;
            putIn(kaPut);
            kaPut = bb;
            putIn(kaPut);
            ind++;
        }
        conn(pa, pb);
    }
    int nl = 0;
    while(id % 3 != 0) putIn(nl);
    int indd;   
/*    cout << "ISIMU IS EILES:\n";
    for(int i = 0; i < ind; i++) {
        takeOut(indd = i*2); aa = OUT;
        takeOut(indd = i*2+1); bb = OUT;
        cout << "briauna " << aa+1 << " -- " << bb+1 << endl;
    }
    cout << endl;*/

    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        dfs(i, i);
    }
    precalc();

    for(int i = 0; i < ind; i++) {
        takeOut(indd = i*2); aa = OUT;
        takeOut(indd = i*2+1); bb = OUT;
        lca(aa, bb);
        mark[aa] = max(mark[aa], he[aa] - he[LCA]);
        mark[bb] = max(mark[bb], he[bb] - he[LCA]);
    }
    for(int i = 0; i < n; i++) vis[i] = 0;
 //   cout << endl;
    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        dfs1(i, i);
    }
    return 0;
}
