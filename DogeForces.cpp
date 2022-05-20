#include <bits/stdc++.h>
using namespace std;
int n;
const int dydis = 501;
int tevas[dydis];
int topInd[dydis] = {};
int ans[dydis * 3] = {};
int fP(int v) {
    if(v == tevas[v]) return v;
    return tevas[v] = fP(tevas[v]);
}
vector<pair<int, int> > susijunge;
vector<int> gr[dydis * 3];
void conn(int a, int b) {
    a = fP(a);
    b = fP(b);
    if(a == b) return ;
    susijunge.push_back({a, b});
    tevas[a] = b;
}
vector<pair<int, int> > duomenys[5001];
vector<pair<int, int> > brn;

bool vis[dydis*3] = {};
int super[dydis*3];
vector<int> comp;
void dfs(int v) {
    if(vis[v]) return ;
    vis[v] = 1;
    comp.push_back(v);
    for(auto &x : gr[v]) {
        dfs(x);
    }
}
void dfs1(int v, int came) {
    super[v] = came;
    for(auto &x : gr[v]) {
        if(x == came) continue;
        dfs1(x, v);
    }
}
int main() {
    for(int i = 0; i < dydis; i++) {
        tevas[i] = i;
        topInd[i] = i;
    }
    cin >> n;
    int mx = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int a; cin >> a;
            mx = max(mx, a);
            if(i < j) continue;
            if(i == j){
                ans[i] = a;
//                cout << "ans[" << i << "] = " << a << endl; 
            }
            else {
                duomenys[a].push_back({i, j});
            }
        }
    }
    int ind = n;
    for(int i = 0; i <= mx; i++) {
//        cout << "ziuriu i skaiciu " << i << endl;
//        cout << "duomenys: ";
        for(auto &x : duomenys[i]) {
            if(fP(x.first) == fP(x.second)) continue;
            conn(x.first, x.second);
//            cout << "(" << x.first << ", " << x.second << "), ";
        }
//        cout << endl;
//        cout << "susijunge: ";
        for(auto &x : susijunge) {
            gr[x.first].push_back(x.second);
            gr[x.second].push_back(x.first);
//            cout << x.first << " su " << x.second << ", ";
        }
//        cout << endl;
        for(auto &x : susijunge) {
            int v = x.first;
            if(vis[v]) continue;
            dfs(v);
//            cout << "komponentas: ";
//            for(auto x : comp) cout << x << "(" << topInd[x] << ")" << " ";
//            cout << endl;
            for(auto x : comp) {
//                cout << "briauna " << ind << " - " << topInd[x] << endl;
                brn.push_back({ind, topInd[x]});
            }
            topInd[fP(comp[0])] = ind;
//            cout << endl;
            ans[ind] = i;
            ind++;
            comp.clear();
        }
        for(auto &x : susijunge) {
            gr[x.first].clear();
            gr[x.second].clear();
            vis[x.first] = vis[x.second] = 0;
        }
        susijunge.clear();
//        cout << endl;
    }
    cout << ind << "\n";
    for(int i = 0; i < ind; i++) {
        cout << ans[i] << " ";
    }
    for(auto x : brn) {
        gr[x.first].push_back(x.second);
        gr[x.second].push_back(x.first);
    }
    dfs1(ind-1, -1);
    cout << endl;
    cout << ind << endl;
    for(int i = 0; i < ind-1; i++) {
        cout << i+1 << " " << super[i]+1 << endl;
    }


    return 0;
}
