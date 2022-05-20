#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, m, p;
int bal[dydis] = {};
bool vis[dydis];
vector<pair<int, int> > gr[dydis], g[dydis];
int h[dydis] = {};
bool is[dydis] = {};
int backCount[dydis] = {};
vector<pair<int, int> > brn;
int s1[dydis] = {}, s2[dydis] = {};
string ans;
void dfs(int v, int he = 0) {
    vis[v] = 1;
    h[v] = he;
    for(auto x : gr[v]) {
        if(vis[x.first]) continue;
//        cout << v + 1 << " -> " << x.first +1<< endl;
        is[x.second] = 1;
        g[v].push_back(x);
        dfs(x.first, he+1);
    }    
}
int f(int ind, int a, int b) {
    if(brn[ind].first == a && brn[ind].second == b) return 'R';
    return 'L';
}
void dfs1(int v, int cameind = -1, int came = -1) {
    s1[v] = backCount[v];
    s2[v] = bal[v];
    for(auto x : g[v]) {
        dfs1(x.first, x.second, v);
        s1[v] += s1[x.first];
        s2[v] += s2[x.first];
    }
    if(cameind != -1) {
        if(s1[v] == 0) {    // no back edges
            if(s2[v] != 0) { // there are things in the subtree
                if(s2[v] > 0) {
                    ans[cameind] = f(cameind, v, came);
                }else {
                    ans[cameind] = f(cameind, came, v);
                }
            }else { 
                ans[cameind] = 'B';
            }
        }else {
            ans[cameind] = 'B';
        }
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    ans.resize(m);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
        brn.push_back({a, b});
    }
    cin >> p;
    for(int i = 0; i < p; i++) {
        int a, b; cin >> a >> b; a--; b--;
        bal[a]++;
        bal[b]--;
    }
    vector<int> l;
    for(int i = 0; i < n; i++){
        if(vis[i]) continue;
        dfs(i);
        l.push_back(i);
    }
    for(int i = 0; i < m; i++) {
        if(is[i]) continue;
        int a = brn[i].first;
        int b = brn[i].second;
        if(h[b] < h[a]) {
            swap(a, b);
        }
        // a yra auksciau uz b
        backCount[b]++;
        backCount[a]--;
        ans[i] = 'B';
    }
    for(auto x : l)
        dfs1(x);
    cout << ans;
    return 0;
}
