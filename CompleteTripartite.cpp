#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, m;
vector<int> gr[dydis];
int color[dydis] = {0}; 
bool galima = 1;
int kek[4] = {0};
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    int v = -1;
    color[0] = 1;
    for(auto x : gr[0]){
        color[x] = 2;
        v = x;
    }
    for(int i = 0; i < n; i++){
        if(color[i] != 2) color[i] = 1;
    }
    if(v != -1){
        for(auto x : gr[v]){
            if(color[x] != 1) color[x] = 3;
        }
    }else{
        galima = 0;
    }
    for(int i = 0; i < n; i++){
        kek[color[i]]++;
    }
    for(int i = 0; i < n; i++){
        if(color[i] == 0) galima = 0;
        int kaim[4] = {0};
        for(auto x : gr[i]){
            kaim[color[x]]++;
        }
        if(kaim[color[i]] != 0) galima = 0;
        for(int j = 1; j <= 3; j++){
            if(j == color[i]) continue;
            if(kaim[j] != kek[j]) galima = 0;
        }
    }
    if(kek[1] == 0) galima = 0;
    if(kek[2] == 0) galima = 0;
    if(kek[3] == 0) galima = 0;
    if(!galima){
        cout << "-1";
        return 0;
    }
    for(int i = 0; i < n; i++){
        cout << color[i] << " ";
    }   
    return 0;
}
