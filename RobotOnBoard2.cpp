#include <bits/stdc++.h>
using namespace std;
const int dydis = 2001;
int n, m;
int ind(int e, int s){
    if(e < 0 || s < 0 || e >= n || s >= m) return n * m;
    return e * m + s;
}
bitset<dydis * dydis + 10> inCycle;
bitset<dydis * dydis + 10> onS;
int gr[dydis * dydis + 10];
bitset<dydis*dydis + 10> vis;
vector<int> inc[dydis*dydis + 10];
int ANS[dydis * dydis + 10];
int cyc[dydis * dydis + 10];
int eil[dydis*dydis+10];
int SZ = 0;
int sz, x;
int i;
void dfs(int v){
//    cout << "esu " << v << endl;
    while(true){
        if(vis[v]){
            if(!onS[v]) return ;
            sz = 0;
            while(true){
                cyc[sz++] = eil[SZ-1];
                SZ--;
                if(sz < 0) break;
                if(cyc[sz-1] == v) break;
            }
            for(i = 0; i < sz; i++){
                x = cyc[i];
                onS[x] = 0;
                inCycle[x] = 1;
                ANS[x] = sz;

            }
            if(sz == 1 && cyc[0] == n*m) ANS[x] = 0;

            return ;
        }
        vis[v] = 1;
        onS[v] = 1;
        eil[SZ++] = v;
        v = gr[v];
    
    }
}
void dfs1(int v, int h){
//    cout << "v = " << v << ", h = " << h << endl;
    SZ = 0;
    eil[SZ++] = v;
    ANS[v] = h;
    while(SZ > 0){
        v = eil[--SZ];
        vis[v] = 1;
        for(auto &x : inc[v]){
            ANS[x] = ANS[v] + 1;
            eil[SZ++] = x;
        }     
    }
}
char b;
int j;
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    int y;
    while(t--){
        cin >> n >> m;
        for(i = 0; i <= n*m; i++) gr[i] = i, vis[i] = 0, inCycle[i] = 0, inc[i].clear(), onS[i] = 0;
        for(i = 0; i < n; i++){

            for(j = 0; j < m; j++){
                cin >> b;
                if(b == 'U'){
                   gr[ind(i, j)] = ind(i-1, j);
                   inc[ind(i-1, j)].push_back(ind(i, j));
                }
                if(b == 'L'){
                    gr[ind(i, j)] = ind(i, j-1); 
                    inc[ind(i, j-1)].push_back(ind(i, j));
                }
                if(b == 'D'){
                    gr[ind(i, j)] = ind(i+1, j);
                    inc[ind(i+1, j)].push_back(ind(i, j));
                }
                if(b == 'R'){
                    gr[ind(i, j)] = ind(i, j+1);
                    inc[ind(i, j+1)].push_back(ind(i, j));
                }
            }
        }
        for(int i = 0; i <= n*m; i++){
            if(vis[i]) continue;
            dfs(i);
            for(int j = 0; j < sz; j++){
                y = cyc[j];
                for(auto &x : inc[y]){
                    if(inCycle[x]) continue;
                    dfs1(x, ANS[y] + 1);
                }
            }
        }

        pair<int, int> ans = {0, 0};
        for(int i = 0; i < n * m; i++){
            ans = max(ans, make_pair(ANS[i], i));
        }
        cout << ans.second / m  + 1<< " " << ans.second % m + 1 << " " << ans.first << "\n";
        for(i = 0; i <= n*m; i++) gr[i] = i, vis[i] = 0, inCycle[i] = 0, inc[i].clear(), onS[i] = 0;

    }

    return 0;
}
