#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
pair<int, int> val[dydis] = {{0, 0}};
vector<pair<int, int> > gr[dydis];
bool galima = 1;
int n, m;
bool vis[dydis] = {0};
pair<int, int> know = {-1, -1};
const pair<int, int> dontk = {-1, -1};
bool vis1[dydis] = {0};
long double ans[dydis] = {0};
vector<int> taskai;
void dfs(int v, int a, int b){
    if(!galima) return;
    if(val[v] != make_pair(0, 0)){
            if(val[v] != make_pair(a, b)){
                if(val[v].first + a == 0){
                    int dux = (val[v].second - b) / a;
                    know = {v, dux};
                }else{
                    galima = 0;
                    return;
                }
            }
    }
    if(vis[v]){
        return ;
    }
    taskai.push_back(-a * b);
    vis[v] = 1;
    val[v] = {a, b};

    for(auto x : gr[v]){
        dfs(x.first, -a, x.second - b);
    }
}
void istatyk(int v, long double x){
    if(vis1[v]){ 
        if(ans[v] != x) galima = 0;
        return;
    }
    vis1[v] = 1;
    ans[v] = x;
    for(auto y : gr[v]){
        istatyk(y.first, (long double)y.second -x);
    }
}
pair<long long, int> band(vector<int> &taskai, int kur){
    long long ret = 0;
    for(auto x : taskai){
        ret += abs(x - taskai[kur]);
    }
    return {ret, kur};
}
int main(){
    for(int i = 0; i < dydis; i++){
        val[i] = {0, 0};
    }
    cin >> n >> m;
    vector<pair<int, pair<int, int> > > brn;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c});
        brn.push_back({c, {a, b}});
    }
    for(int i = 0; i < n; i++){
        if(vis[i]) continue;
        taskai.clear();
        val[i] = {1, 0};
        know = {-1, -1};
        dfs(i, 1, 0);
        if(!galima) break;
        if(know != dontk){
            istatyk(i, 1.0 * know.second / 2.0);
            continue;
        }else{
            
        }
        if(!galima) break;
        sort(taskai.begin(), taskai.end());
        pair<long long, int> sm = {(long long)1e18, -1};
        if(taskai.size() & 1){
            sm = min(sm, band(taskai, taskai.size() / 2));
        }else{
            sm = min(sm, min(band(taskai, taskai.size()/2), band(taskai, taskai.size()/2-1)));
        }
        istatyk(i, taskai[sm.second]);
    }
    for(auto x : brn){
        if(x.first != ans[x.second.first] + ans[x.second.second]) galima = 0;
    }
    if(!galima){
        cout << "NO";
        return 0;
    }
    cout << "YES\n";

    for(int i = 0; i < n; i++){
        cout << setprecision(100) << ans[i] << " ";
    }

    return 0;
}
