#include <bits/stdc++.h>
//#pragma GCC optimize("O3")
using namespace std;
const long long inf = 1e18;
const int dydis = 2e5 + 10;
const int ddd = 1010;
long long dist[dydis] = {0};
int came[dydis] = {0};
int prij[dydis] = {0};
long long dst[dydis][6];
long long ktDst[ddd][ddd];
vector<pair<int, int> > gr[dydis];
long long mem[dydis];
int n, m, k;
long long dij(int a, int b){
    priority_queue<pair<long long, int> > q;
    for(int i = 0; i < n; i++){
        dist[i] = inf;
        came[i] = -1;
    }
    dist[a] = 0;
    q.push({0, a});
    while(!q.empty()){
        int v = q.top().second;
        long long dst = -q.top().first;
        q.pop();
        if(dst != dist[v]) continue;
        for(auto x : gr[v]){
            if(dist[x.first] > 1ll * x.second + dist[v]){
                dist[x.first] = dist[v] + 1ll * x.second;
                came[x.first] = v;
                q.push({-dist[x.first], x.first});
            }
        }
    }
    return dist[b];
}
void multi(vector<pair<int, long long> > &vec){
    priority_queue<pair<long long, int> > q;
    for(int i = 0; i < n; i++){
        dist[i] = inf;
        came[i] = -1;
    }
    for(auto x : vec){
        dist[x.first] = x.second;
        q.push({-x.second, x.first});
    }
    long long dst; int v;
    while(!q.empty()){
        v = q.top().second;
        dst = -q.top().first;
        q.pop();
        if(dst != dist[v]) continue;
        for(auto x : gr[v]){
            if(dist[x.first] > 1ll * x.second + dist[v]){
                dist[x.first] = dist[v] + 1ll * x.second;
                came[x.first] = v;
                q.push({-dist[x.first], x.first});
            }
        }
    }
}
vector<int> mas;
void k3(){
    sort(mas.begin(), mas.end());
    long long ans = inf;
    for(int i = 0; i < k; i++){
        dij(mas[i], 0);
        for(int j = 0; j < n; j++){
            dst[j][i] = dist[j];
        }
    }
    for(int i = 0; i < n; i++){
        long long st = 0;
        for(int j = 0; j < k; j++){
            st += dst[i][j];
        }
        ans = min(ans, st);
    }
    cout << ans;

}
pair<int, int> kt(int a, int b){
    pair<int, int> ret = {-1, -1};
    for(int i = 0; i < 4;i ++){
        if(i == a) continue;
        if(i == b) continue;
        if(ret.first == -1) ret.first = i;
        else ret.second = i;
    }
    return ret;
}
void ak2(){
    for(int i = 0; i < k; i++){
        dij(mas[i], 0);
        for(int j = 0; j < n; j++){
            dst[j][i] = dist[j];
        }
    }
    long long ans = inf;
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(j == i) continue;
            pair<int, int> kiti = kt(i, j);
//            cout << "pora (" << mas[i] +1<< ", " << mas[j]+1 << "), kita pora (" << mas[kiti.first]+1 << ", " << mas[kiti.second]+1 << ").\n";
            vector<pair<int, long long> > prd;
            for(int h = 0; h < n; h++){
                prd.push_back({h, dst[h][i] + dst[h][j]});
            }
            multi(prd);
            for(int h = 0;  h < n; h++){
                ans = min(ans, dist[h] + dst[h][kiti.first] + dst[h][kiti.second]);
            }
        }
    }
    cout << ans;
    exit(0);
}
pair<int, int> kiti3(int a, int b, int c){
    pair<int, int> ret = {-1, -1};
    for(int i = 0; i < 5; i++){
        if(i == a || i == b || i == c) continue;
        if(ret.first == -1) ret.first = i;
        else ret.second = i;
    }
    return ret;
}
void ak41(){
    long long ans = inf;
    if(k == 4){
        ak2();
        return ;
    }else{
        for(int i = 0; i < k; i++){
            dij(mas[i], 0);
            for(int j = 0; j < n; j++){
                dst[j][i] = dist[j];
            }
        }
        set<vector<int> > bv;
        for(int C = 0; C < k; C++){
            for(int E = C+1; E < k; E++){

                for(int D = 0; D < k; D++){
                    if(C == E || C == D || E == D) continue;
                    pair<int, int> kit = kiti3(C, E, D);
                    int A = kit.first;
                    int B = kit.second;
                    vector<int> st = {A, B, C, D, E};
                    vector<int> kt = {C, E, A, D, B};
                    if(bv.count(st)) continue;
                    if(bv.count(kt)) continue;
                    bv.insert(kt);
                    bv.insert(st);
                    vector<pair<int, long long> > prm, ant;
                    for(int i = 0; i < n; i++){
                        prm.push_back({i, dst[i][C] + dst[i][E]});
                        ant.push_back({i, dst[i][A] + dst[i][B]});
                    }
                    multi(prm);
                    for(int i = 0; i < n; i++) mem[i] = dist[i];
                    multi(ant);
                    for(int i = 0; i < n; i++) ans = min(ans, dist[i] + mem[i] + dst[i][D]);
                }
            }
        }
    }
    cout <<  ans;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k >> m;
    mas.resize(k);
    for(auto &x : mas){
        cin >> x; x--;
    }
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c});
    }
    if(k <= 3){
        k3();
    }else if(k <= 5){
        ak41();
    }
    return 0;
}
/*
   9 5 9
6 8 4 1 2
8 9 10
7 9 5
8 6 3
6 7 1
5 7 2
4 5 4
3 5 3
1 3 2
2 3 2
*/
