#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
const int dd = 30;
const long long inf = 1e18;
int lft[dydis][dd];
long long vl[dydis][dd];
long long arc[dydis];
long long mdA[dydis];
int tevas[dydis];
bool pabegs[dydis] = {0}; 
vector<pair<int, int> > quers[dydis]; 
vector<pair<int, int> > Q;
int n, s, q, e;
long long h[dydis];
vector<pair<pair<int, int>, int> > gr[dydis];
set<int> briaunosVirs;
vector<pair<int, int> > briaunos;
int kek[dydis] = {0};
void dfs(int v, int came, long long he, int lg){
    h[v] = he;
    tevas[v] = came;
    kek[v] = lg;
    for(auto x : quers[v]){
        if(briaunosVirs.count(x.first)){
            pabegs[x.second] = 0;
        }else{
            pabegs[x.second] = 1;
        }
    }
    for(auto x : gr[v]){
        if(x.first.first == came) continue;
        briaunosVirs.insert(x.second);
        dfs(x.first.first, v, he + 1ll *  x.first.second, lg+1);
        arc[v] = min(arc[v], arc[x.first.first] + x.first.second);
        briaunosVirs.erase(x.second);
    }
    mdA[v] = arc[v] - he;
}
void precalc(){
    dfs(e, e, 0, 0);
    for(int i = 0; i < n; i++){
        lft[i][0] = tevas[i];
    }
    for(int j = 1; j < dd; j++){
        for(int i = 0; i < n; i++){
            lft[i][j] = lft[lft[i][j-1]][j-1];
        }
    }

    for(int i = 0; i < n; i++){
        vl[i][0] = min(mdA[i], mdA[tevas[i]]);
    }
    for(int i = 1; i < dd; i++){
        for(int j = 0; j < n; j++){
            vl[j][i] = min(vl[j][i-1], vl[lft[j][i-1]][i-1]);
        }
    }
}
long long getVl(int v, int aukstis){
    if(aukstis == 0) {
        return mdA[v] + h[v];
    }
    long long ret = inf;
    int vv = v;
    for(int j = dd-1; j > -1; j--){
        if((1 << j) <= aukstis){
            ret = min(ret, vl[v][j]);
            v = lft[v][j];
            aukstis -= (1 << j);
        }
    }
    return ret + h[vv];
}
int main(){
    for(int i = 0; i < dydis; i++){
        arc[i] = inf;
    }
    cin >> n >> s >> q >> e; e--;
    for(int i = 0; i < n-1; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        gr[a].push_back({{b, c}, i});
        gr[b].push_back({{a, c}, i});
        briaunos.push_back({a, b});
    }
    for(int i = 0; i < s; i++){
        int a; cin >> a; a--;
        arc[a] = 0;
    }
    for(int i = 0; i < q; i++){
        int a, b; cin >> a >> b; a--; b--;
        Q.push_back({a, b});
        quers[b].push_back({a, i}); // ar tarp rooto ir a yra i-asis
    }
    precalc();
    for(int i = 0; i < n; i++){
//        cout << i+1 << ", atstumas iki artimiausio, mano pomedyje esancio miesto = " << arc[i] << ", o mano vl = " << mdA[i] << endl;
    }
/*    while(true){
        int a, b; cin >> a >> b; a--;
        cout << "jei pomedi sudaro visos virsunes, kurios yra zemiau tos, iki kurios atstumas " << b << ", tai artimiausias iki pomedzio yra " << getVl(a, b) << "\n";
    }*/
    int db = 0;
    for(auto x : Q){
        int v = x.second;
        int ind = x.first;
        if(pabegs[db]){
            cout << "escaped\n";
            db++;
            continue;
        }
        int apac = -1;
        int A = briaunos[ind].first;
        int B = briaunos[ind].second;
        if(h[A] < h[B]) swap(A, B); // a bus zemiau
        int kilti = kek[v] - kek[A];
        long long vl =  getVl(v, kilti);
        if(vl > 1e14) cout << "oo\n";
        else cout << vl  << "\n";
        db++;
    }
    return 0;
}
/*
14 3 10 1
1 2 3
2 3 4
3 4 1
4 5 5
4 6 6
2 7 2
7 8 1
1 10 1
10 9 8
10 11 7
10 12 2
12 13 4
13 14 4
11
7
13
*/
