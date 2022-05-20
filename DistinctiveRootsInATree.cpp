#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int colors[dydis];
vector<int> visi[dydis];
vector<int> gr[dydis];
vector<int> sp[dydis];
int h[dydis];
bool del[dydis] = {0};
int n;
int dbInd = 0;
bool galima = 1;
map<int, int> mapas;
int tevas[dydis] = {0};
int lft[dydis][30] = {0};
int realP[dydis] = {0};
int enter[dydis], leave[dydis];
int t;
int hsh(int c){
    if(mapas.count(c)) return mapas[c];
    return mapas[c] = dbInd++;
}
void dfs(int v, int came, int he){
    tevas[v] = came;
    h[v] = he;
    enter[v] = t++;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, he + 1);
    }
    leave[v] = t++;
}
void preCalc(){
    t = 0;
    dfs(0, -1, 0);
    tevas[0] = 0;
    for(int i = 0; i < n; i++){
        lft[i][0] = tevas[i];
    }
    for(int j = 1; j < 30; j++){
        for(int i = 0; i < n; i++){
            lft[i][j] = lft[ lft[i][j-1] ][j-1];
        }
    }
}
int isAnc(int a, int b){
    return enter[a] < enter[b] && leave[b] < leave[a];
}
int lca(int a, int b){
    if(isAnc(a, b)) return a;
    if(isAnc(b, a)) return b;
    for(int i = 29; i > -1; i--){
        if(isAnc(lft[a][i], b)){
        
        }else{
            a = lft[a][i];
        }
    }
    return tevas[a];
}

int firstInPath(int a, int b){
    int tv = lca(a, b);
    if(h[tv] < h[a]) return tevas[a];
    for(auto x : gr[a]){
        if(lca(x, b) == x) return x;
    }
    return -2;
}
vector<int> incoms[dydis];
bool hasDown[dydis] = {0};
bool isDelFromTop[dydis] = {0};
bool hasUp[dydis] = {0};
int visoDown = 0;
void pridek(int v, int inc){
    incoms[v].push_back(inc);
    if(tevas[inc] == v){
        visoDown++;
        hasUp[inc] = 1;
    }
    if(tevas[v] == inc){
        isDelFromTop[v] = 1;
    }
}
int curSm = 0;
int ans = 0;
void dfs1(int v, int came){
    if(isDelFromTop[v]) return ;
    curSm += hasUp[v];   
    if(curSm == visoDown) ans++;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs1(x, v);
    }
    curSm -= hasUp[v]; 
}
int main(){
    for(int i = 0; i < dydis; i++){
        realP[i] = i;
    }
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> colors[i];
        colors[i] = hsh(colors[i]);
 //       cout << i << " spalva yra " << colors[i] << endl;
        visi[colors[i]].push_back(i);
        sp[i] = {colors[i]};
    }
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    preCalc();
    for(int i = 0; i < n; i++){
        if(visi[i].size() <= 1) continue;
        if(visi[i].size() >= 3){
            cout << 0;
            return 0;
        }else{ // visi[i].size() == 2
        }
    }
    for(int i = 0; i < n; i++){ // einu per spalvas
        if(visi[i].size() <= 1) continue;
        if(!galima) break;
        int v1 = visi[i][0];
        int v2 = visi[i][1];
        if(v1 == v2){
            continue;
        }
        int ms1 = firstInPath(v1, v2);
        int ms2 = firstInPath(v2, v1);
        pridek(v1, ms1);
        pridek(v2, ms2);
    }
    
    if(!galima){
        cout << 0;
        return 0;
    }
    dfs1(0, -1);
//    cout << "ans = [";
    cout << ans;
    return 0;
}
