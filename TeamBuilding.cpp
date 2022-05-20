#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e5 + 10;
int n, m, k;
int mas[dydis];
int color[dydis];
int tevas[dydis];
bool can[dydis];
vector <int> gr[dydis];
vector <pair<int, int> > gr1[dydis];
bool flp[dydis] = {};
bool decided[dydis] = {};
long long ans = 0;
set<pair<int, int> > don;
bool outOfGame[dydis] = {};
int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    tevas[b] = a;
}

void dfs(int v, int c, int tv){
    if(color[v] == -1) color[v] = c;
    else if(color[v] == c) return ;
    else {
        can[tv] = 0;
    }
    if(!can[tv]) return ;
    for(auto x : gr[v]){
        if(fP(x) != tv) continue;
        dfs(x, !c, tv);
    }
}
map<pair<int, int >, vector<pair<int, int > > > mapas;
bool galima = true;
int clr[dydis];
void dfs1(int v, int cll) {
//    cout << "esu " << v+1 << ", noriu deti " << cll << " spalva!\n";
    if(clr[v] == -1){
//        cout << "cia dar niekas nedeta, tai dedu " << cll << "spalva" << endl;
        clr[v] = cll;
    }else if(clr[v] == cll){
//        cout << "cia jau ideta " << cll << " spalva!" << endl;
        return ;
    }else{
//        cout << "cia jau ideta kita spalva!" << endl;
        galima = false;
    }
//    cout << endl;
    if(!galima) return ;
    for(auto x : gr1[v]){
        dfs1(x.first, x.second ^ cll);
    }
}
void darom(int A, int B, int v) {
    if(A > B) swap(A, B);
    if(outOfGame[A] || outOfGame[B]) {
        return ;
    }
    if(don.count({A, B})) return ;
    don.insert({A, B});
//    cout << "darom " << A << " su " << B << endl;
    vector<pair<int, int> > &br = mapas[{A, B}];
    galima = true;
    for(auto x : br){
        gr1[fP(x.first)].clear();
        gr1[fP(x.second)].clear();
        clr[fP(x.first)] = -1;
        clr[fP(x.second)] = -1;
    }
    for(auto x : br){
        int a = x.first;
        int b = x.second;
        int eq = !(color[a] ^ color[b]);

        gr1[fP(a)].push_back({fP(b), eq});
        gr1[fP(b)].push_back({fP(a), eq});
        //cout << "taigi, " << fP(a)+1 << " su " << fP(b)+1 << " sujungiami (per " << a << " ir " << b << "), ir jie tures buti skirtis: " << eq << endl;
    }
    for(auto x : br){
        int a = fP(x.first);
        int b = fP(x.second);
        if(clr[a] == -1) dfs1(a, 0);
        if(clr[b] == -1) dfs1(b, 0);
        if(!galima) break;
    }
    //cout << "sitas galima = " << galima << endl;
    ans -= !galima;
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dydis; i++) tevas[i] = i, can[i] = 1, color[i] = -1;
    vector<pair<int, int> > brn;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++){
        cin >> mas[i];
    }
    ans = 1ll * k * (k - 1) / 2ll;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        if(mas[a] == mas[b]) conn(a, b);
        brn.push_back({a, b});
        pair<int, int> pr = {min(mas[a], mas[b]), max(mas[a], mas[b])};
        mapas[pr].push_back({a, b});
        gr[a].push_back(b);
        gr[b].push_back(a);
    }  
    int nera = 0;  
    for(int i = 0; i < n; i++){
        if(fP(i) != i) continue;
        dfs(i, 0, i);
        if(!can[i]) {
            if(!outOfGame[mas[i]]) nera++;
            outOfGame[mas[i]] = 1;
        }
    }
    ans = 1ll * (k-nera) * (k-nera-1) / 2ll;
    for(int i = 0; i < n; i++){
//        cout << i+1 << ", root = " << fP(i)+1 << ", color = " << color[i] << endl;
    }
    for(auto x : brn) {
        int a = x.first;
        int b = x.second;
            
        if(mas[a] == mas[b]) continue;
        darom(mas[a], mas[b], a);
    }
    cout << ans << "\n";
    return 0;
}
