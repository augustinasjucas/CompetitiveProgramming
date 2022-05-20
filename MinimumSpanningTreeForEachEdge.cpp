#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
const int lg = 20;
int n, m;
long long ans = 0;
vector<pair<int, pair<int, int> > > brn, all;
vector<pair<int, int> > gr[dydis];
int tevas[dydis];
int vl[dydis] = {};
int kur[dydis][lg];
long long sm[dydis][lg];
int he[dydis];
int enter[dydis];
int leave[dydis];
int dbInd = 0;
int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    tevas[a] = b;
}
void dfs(int v, int came, int h = 0){
    enter[v] = dbInd++;
    tevas[v] = came;
    he[v] = h;
    for(auto x : gr[v]){
        if(x.first == came) continue;
        vl[x.first] = x.second;
        dfs(x.first, v, h+1);
    }
    leave[v] = dbInd++;
}
void precalc(){
    for(int i = 0; i < n; i++){
        kur[i][0] = tevas[i];
        sm[i][0] = vl[i];
    }
    for(int j = 1; j < lg; j++){
        for(int i = 0; i < n; i++){
            kur[i][j] = kur[kur[i][j-1]][j-1];
            sm[i][j] = max(sm[i][j-1], sm[kur[i][j-1]][j-1]);
        }
    }
}

bool isAnc(int a, int b){
    return enter[a] <= enter[b] && leave[b] <= leave[a];
}
int getLow(int a, int b){
    if(isAnc(a, b)) {
        return a;
    }
    if(isAnc(b, a)) {
        return b;
    }
    for(int i = lg-1; i > -1; i--){
        if(!isAnc(kur[a][i], b)){
            a = kur[a][i];
        }
    }
    return tevas[a];
}


long long getMax(int v, int brn){
    long long ret = 0;
    for(int i = lg-1; i > -1; i--){
        if((1 << i) <= brn) {
            brn -= (1 << i);
            ret = max(ret, sm[v][i]);
            v = kur[v][i];
        }
    }
    return ret;
}
long long getMx(int a, int b){
    int anc = getLow(a, b);
    return max(getMax(a, he[a]-he[anc]), getMax(b, he[b]-he[anc]));
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i++) tevas[i] = i;
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w; a--; b--;
        brn.push_back({w, {a, b}});
        all.push_back({w, {a, b}});
    }

    sort(brn.begin(), brn.end());

    for(auto x : brn){
        int a = x.second.first;
        int b = x.second.second;
        int w = x.first;
        if(fP(a) == fP(b)) continue;
        conn(a, b);
        gr[a].push_back({b, w});
        gr[b].push_back({a, w});
        ans += w;
    }
    dfs(0, 0);
    precalc();
    for(auto x : all){
        int mx = getMx(x.second.first, x.second.second);
        cout << ans + x.first - mx << "\n";
    }
    return 0;
}
