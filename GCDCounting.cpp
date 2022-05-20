#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 2e5 + 10;
const int inf = 1e9;
bool don[dydis] = {0};
bool vis[dydis] = {0};
int dist[dydis] = {0};
vector<int> primes;
vector<int> gr[dydis];
vector<int> mas;
vector<int> indec[dydis];
int n;
bool is = 0;
void gen(){
    for(int i = 2; i < 3000; i++){
        bool is = 1;
        for(auto x : primes){
            if(i % x == 0) is = 0;
        }
        if(is) primes.push_back(i);
    }
}
vector<int> toP(int a){
    vector<int> ret;
    for(auto x : primes){
        if(a % x == 0) {
            ret.push_back(x);
            while(a % x == 0) a /= x;
        }
        if(a == 1) break;
    }
    if(a != 1) ret.push_back(a);
    return ret;
}
pair<int, int> bfs(int v, int sk){
    vector<int> visi ;
    queue<int> q;
    dist[v] = 0;
    q.push(v);
    while(!q.empty()){
        v = q.front(); q.pop(); 
        vis[v] = 1;
        if(!don[v]){
            visi.push_back(v);
            don[v] = 1;
        }
        for(auto x : gr[v]){
            if(mas[x] % sk != 0){
                continue;
            }
            if(dist[x] > dist[v]+1){
                dist[x] = dist[v] + 1;
                q.push(x);
            }
        }
    }
    pair<int, int> ans = {0, v};
    for(auto x : visi){
        ans = max(ans, {dist[x], x});
    }
    for(auto x : visi){
        dist[x] = inf;
        don[x] = 0;
    }
    return ans;
}
int mxG(int v, int sk){
    auto prm = bfs(v, sk);
    auto ant = bfs(prm.second, sk);
    return ant.first;
}
int main(){
    for(int i = 0; i < dydis; i++) dist[i] = inf;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    gen();
    cin >> n;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        mas.push_back(a);
        auto kas = toP(a);
        for(auto x : kas){
            indec[x].push_back(i);
        }
        if(a != 1) is = 1;
    }
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }

    int ans = 0;
    for(int i = 2; i < dydis; i++){
        if(indec[i].size() == 0) continue;
        for(auto x : indec[i]){
            if(vis[x]) continue;
            ans = max(ans, mxG(x, i));
        }
        for(auto x : indec[i]) vis[i] = 0;
        for(auto x : indec[i]) dist[i] = inf;
    }
    if(!is){
        cout << 0;
        return 0;
    }
    cout << ans+1;
    return 0;
}

/*
    Per skaiciu eisiu tiek kartu, kiek jis turi pirminiu dalikliu. 
    Briauna tikrinsiu tiek kartu, kiek jos virsunes turi prminiu dalikliu KARTU.
*/
