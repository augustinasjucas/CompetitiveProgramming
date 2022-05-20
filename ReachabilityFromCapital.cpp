#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e3 + 10;
int n, m;

int low[dydis];
bool don[dydis] = {0};
bool isIn[dydis] = {0};
int dbInd = 0;
stack<int> stekas;
vector<int> gr[dydis];

void tarjan(int v){
    int db = dbInd;
    if(!don[v]){
        stekas.push(v);
        isIn[v] = 1;
        low[v] = dbInd++;
    }else return;
    for(auto x : gr[v]){
        if(don[x]) continue;
        if(!isIn[x]) tarjan(x);
        low[v] = min(low[v], low[x]);
    }
    if(low[v] == db){
        don[v] = 1;
        while(true){
            int u = stekas.top(); stekas.pop();
            low[u] = low[v];
            don[u] = 1;
            isIn[u] = false;
            if(u == v) break;
        }
    }
}
int inp[dydis] = {0};
int main(){
    cout << a;
    for(int i = 0; i < dydis; i++){
        low[i] = -1;
        inp[i] = 1000000;
    }
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int c;
    cin >> n >> m >> c;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
    }
    for(int i = 0; i < n; i++){
        if(!don[i]) tarjan(i);
    }
    for(int i = 0; i < n; i++){
        inp[low[i]] = 0;
    }
    for(int i = 0; i < n; i++){
        for(auto x : gr[i]){
            if(low[x] == low[i]) continue;
            inp[low[x]]++;
        }
    }

    int viso = 0;
    for(int i = 0; i < n; i++){
        if(inp[i] == 0) viso++;
    }
    viso -= (inp[low[c-1]] == 0);
    cout << viso;
    return 0;
}
