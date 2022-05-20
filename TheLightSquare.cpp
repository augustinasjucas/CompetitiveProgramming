#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 1e3 * 2;
bitset<dydis> mas[dydis];
bitset<dydis> rest;
int n;
int color[dydis*3] = {0};
vector<pair<int, int> > gr[dydis * 3];
vector<pair<pair<int, int>, int> > brn;
bool vis[dydis *3] = {0};
void suj(int e, int s, int w){
    brn.push_back({{e, s+dydis}, w});
    gr[e].push_back({s+dydis, w});
    gr[s+dydis].push_back({e, w});
}
bool galima = 1;
void setC(int v, int c){
    if(color[v] == 0){
        color[v] = c;
    }else{
        if(color[v] != c){
            galima = 0;
        }
    }
}
vector<int> visited;
bool gal = 0;
int past[dydis * 3] = {0};
void dfs(int v, int c){
    if(color[v] != 0){
        if(color[v] != c){
            gal = 0;
            return ;
        }
    }
    if(vis[v]) return ;
    visited.push_back(v);
    past[v] = color[v];
    color[v] = c;
    vis[v] = 1;
    for(auto x : gr[v]){
        if(x.second == 2){
            if(color[v] == -1){
                dfs(x.first, -1);
            }else{
                dfs(x.first, 1);
            }
        }else{
            if(color[v] == -1){
                dfs(x.first, 1);
            }else{
                dfs(x.first, -1);
            }
        }
    }
    
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            char a; cin >> a;
            mas[i][j] = a == '1';
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            char a; cin >> a;
            mas[i][j] = mas[i][j] ^ (a == '1');
        }
    }
    for(int i =0; i < n; i++){
        char a; cin >> a;
        rest[i] = a == '1';
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(!mas[i][j]){
                if(rest[i] && rest[j]){
                    suj(i, j, 2);
                }else if(rest[i] && !rest[j]){
                    setC(j+dydis, -1);
                }else if(!rest[i] && rest[j]){
                    setC(i, -1);
                }else if(!rest[i] && !rest[j]){
                    /// nesvarbu kas kaip bus
                }
            }else{
                if(rest[i] && rest[j]){
                    suj(i, j, 1);
                }else if(rest[i] && !rest[j]){
                    setC(dydis+j, 1);
                }else if(!rest[i] && rest[j]){
                    setC(i, 1);
                }else if(!rest[i] && !rest[j]){
                    galima = 0;
                }
            }
        }
    }
    if(!galima){
        cout << "-1";
        return 0;
    }
    for(int i = 0; i < dydis*2; i++){
        if(!galima) break;
        gal = 1; visited.clear();
        dfs(i, -1);
        if(gal) continue;
        for(auto x : visited){
            vis[x] = 0;
            color[x] = past[x];
        }
        gal = 1;
        dfs(i, 1);
        if(!gal){
            galima = gal;
            break;
        }

    }
    if(!galima){
        cout << "-1";
        return 0;
    }
    vector<pair<string, int> > vec;
    for(int i = 0; i < n; i++) {
        if(color[i] == 1){
            vec.push_back({"row", i});
        }
    }
    for(int i = 0; i < n; i++) {
        if(color[i+dydis] == 1){
            vec.push_back({"col", i});
        }
    }
    cout << vec.size() << "\n";
    for(auto x : vec){
        cout << x.first << " " << x.second << "\n";
    }
    return 0;
}
