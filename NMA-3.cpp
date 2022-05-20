#include <bits/stdc++.h>
using namespace std;
const int dydis = 510;
const int inf = 1e9;
const int dd = dydis * dydis;
bool vis[dydis][dydis] = {0};
int mn[dd];
int mas[dydis][dydis];
int tevas[dd];
int n, m;
vector<pair<int, int> > vec = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int hsh(int e, int s){
    return e * dydis + s;
}
int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    int vl = min(mn[a], mn[b]);
    tevas[a] = b;
    mn[b] = vl;
}
void dar(int e, int s){
    for(auto x : vec){
        int pe = x.first + e;
        int ps = x.second + s;
        if(pe < 0 || ps < 0 || pe >= n || ps >= m) continue;
        if(abs(mas[pe][ps]) / mas[pe][ps] != abs(mas[e][s]) / mas[e][s]){
            continue;
        }
        conn(hsh(e, s), hsh(pe, ps));
    }

}
int main(){
    for(int i = 0; i < dd; i++){
        tevas[i] = i;
    }
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> mas[i][j];
            mn[hsh(i, j)] = mas[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            dar(i, j);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << mn[fP(hsh(i, j))] << " ";
        }
        cout << "\n";
    }    
    return 0;
}
