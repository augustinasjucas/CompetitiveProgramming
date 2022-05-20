#include <bits/stdc++.h>
using namespace std;
const int dydis = 4e5 + 10;
int n, m;
vector<int> gr[dydis];
int low[dydis];
int ind[dydis];
bool has[dydis] = {};
bool onS[dydis] = {};
int dbInd = 0;
int sz[dydis] = {};
vector<int> st;
bool vis[dydis] = {};
int vl[dydis] = {};
int inc[dydis] = {};
int cnt[dydis] = {};
void dfs(int v){
    if(ind[v] == -1){
        ind[v] = dbInd++;
        low[v] = ind[v];
        st.push_back(v);
        onS[v] = 1;
    }
    for(auto x : gr[v]){
        if(low[x] == -1){
            dfs(x);
            low[v] = min(low[x], low[v]);
        }else if(onS[x]){
            low[v] = min(low[v], ind[x]);
        }
    }
    if(ind[v] == low[v]){
        while(true){
            int u = st.back();
            st.pop_back();
            low[u] = low[v];
            onS[u] = 0;
            sz[low[v]]++;
            if(u == v) break;
        }
    }
}
void dfs1(int v){
    
    for(auto x : gr[v]){
        if(cnt[v] == 2 && cnt[x] != 2){
            cnt[x] = 2;
            dfs1(x);
        }else if(cnt[x] == 0){
            cnt[x]++;
            dfs1(x);
        }else if(cnt[x] == 1){
            cnt[x]++;
            dfs1(x);
        }
    }
    if(cnt[v] == 2) vl[v] = 2;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n >> m;
        dbInd = 0;
        for(int i = 0; i < n; i++){
            low[i] = -1;
            ind[i] = -1;
            onS[i] = 0;
            sz[i] = 0;
            vl[i] = 0;
            has[i] = 0;
            vis[i] = 0;
            inc[i] = 0;
            cnt[i] = 0;
        }
        for(int i = 0; i < m; i++){
            int a, b; cin >> a >> b; a--; b--;
            gr[a].push_back(b);
            if(a == b) has[a] = 1;
            inc[b]++;

        }
        for(int i = 0; i < n; i++){
            if(ind[i] == -1) dfs(i);
        }
        queue<int> q;
        q.push(0);
        while(q.size()){
            int v = q.front();
            q.pop();
            vl[v] = 1;
            if(vis[v]) continue;
            vis[v] = 1;
            for(auto x : gr[v]){
                if(vis[x]) continue;
                q.push(x);
            }
        }
        /// CIAA
        cnt[0] = 1;
        dfs1(0);
/*        for(int i = 0; i < n; i++){
            vis[i] = 0;
            if(vl[i] == 0) continue;
            if(i != 0 && inc[i] >= 2){
                q.push(i);
            }
        }
        while(q.size()){
            int v = q.front();
            q.pop();
            vl[v] = 2;
            if(vis[v]) continue;
            vis[v] = 1;
            for(auto x : gr[v]){
                if(vis[x]) continue;
                q.push(x);
            }
        }*/


        for(int i = 0; i < n; i++){
            vis[i] = 0;
            if(vl[i] != 0 && (sz[low[i]] > 1 || has[i])){
                vl[i] = 3;
                q.push(i);
            }
        }
        while(q.size()){
            int v = q.front();
            q.pop();
            if(vis[v]) continue;
            vis[v] = 1;
            for(auto x : gr[v]){
                if(vis[x]) continue;
                vl[x] = 3;
                q.push(x);
            }
        }

        for(int i = 0; i < n; i++){
            gr[i].clear();
        }
        for(int i = 0; i < n; i++){
            cout << (vl[i] == 3 ? -1 : vl[i]) << " ";
        }
        cout << "\n";
    }    
    return 0;
}

