#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 1e5 + 10;
const long long inf = 2e9;
int n, m;
int sx, sy, ex, ey;
vector<pair<int, int> > mas;
vector<pair<int, int> > xai, yai;
long long ans = 0;
unordered_map<int, int> tevas;
unordered_map<int, long long> dist;
unordered_map<int, vector<int> > priklauso;
unordered_map<int, bool> was;
int fP(int v){
    if(tevas.count(v) == 0) return tevas[v] = v;
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
//    cout << "conn " << a << " su " << b << endl;
    a = fP(a);
    b = fP(b);
    if(dist.count(a) == 0) dist[a] = inf;
    if(dist.count(b) == 0) dist[b] = inf;
    dist[b] = min(dist[b], dist[a]);
    tevas[a] = b;
}
void calc(){
    priority_queue<pair<int, int> > q;
    int kr1 = lower_bound(xai.begin(), xai.end(), make_pair(sx, -1)) - xai.begin();
    int kr2 = lower_bound(yai.begin(), yai.end(), make_pair(sy, -1)) - yai.begin();
    int vn = max(kr1-1, 0);
    int an = min(kr1, (int)xai.size()-1);
    q.push({-dist[fP(xai[vn].first)], fP(xai[vn].first)});
    q.push({-dist[fP(xai[an].first)], fP(xai[an].first)});
    int tr = max(kr2-1, 0);
    int ke = min(kr2, (int)yai.size()-1);
    q.push({-dist[fP(yai[tr].first + n)], fP(yai[tr].first + n)});
    q.push({-dist[fP(yai[ke].first + n)], fP(yai[ke].first + n)});
/*    for(auto x : mas){
        int i = x.first;
        if(dist[i] == inf || fP(i) != i) continue;
        q.push({-dist[i], i});
    }
    for(auto x : mas){
        int i = x.second + n;
        if(dist[i] == inf || fP(i) != i) continue;
        q.push({-dist[i], i});
    }*/

    while(!q.empty()){
        int v = q.top().second;
        int dst = -q.top().first;
        was[v] = 1;
        q.pop();
        if(dist[v] != dst) continue;
        auto &prk = priklauso[v];
        for(auto x : prk) {
            //  vienu i virsu/zemyn/kairen/desinen
            int i1 = lower_bound(xai.begin(), xai.end(), make_pair(mas[x].first, x)) - xai.begin();
            int i2 = max(i1-1, 0); i1 = min(i1 + 1, (int)xai.size()-1);
            long long d1, d2;
            d1 = abs(xai[i1].first - mas[x].first);
            d2 = abs(xai[i2].first - mas[x].first);

            i1 = fP(xai[i1].first);
            i2 = fP(xai[i2].first);        
                
            int i3 = lower_bound(yai.begin(), yai.end(), make_pair(mas[x].second, x)) - yai.begin();
            int i4 = max(i3-1, 0); i3 = min(i3 + 1, (int)yai.size()-1);
            long long d3, d4;
            d3 = abs(yai[i3].first - mas[x].second);
            d4 = abs(yai[i4].first - mas[x].second);

            i3 = fP(yai[i3].first + n);
            i4 = fP(yai[i4].first + n);


            int ms[] = {i1, i2, i3, i4};
            long long ds[] = {d1, d2, d3, d4};
            for(int i = 0; i < 4; i++){
                long long w = ds[i];
                int u = ms[i];
                if(dist[u] > dist[v] + w || (dist[u] == dist[v] + w && !was[u])){
                    dist[u] = dist[v] + w;
                    q.push({-dist[u], u});
                }
            }
        }
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    cin >> sx >> sy >> ex >> ey;
    if(m == 0){
        cout<< abs(sx-ex) + abs(sy-ey);
        return 0;
    }
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        mas.push_back({a, b});
        xai.push_back({a, i});
        yai.push_back({b, i});
        if(dist.count(fP(a)) == 0) dist[fP(a)] = inf;
        dist[fP(a)] = min(1ll * min(abs(sx-a), abs(b-sy)), dist[fP(a)]);
        conn(a, n + b);
    }
    for(int i = 0; i < m; i++){
        priklauso[fP(mas[i].first)].push_back(i);
    }
    sort(xai.begin(), xai.end());
    sort(yai.begin(), yai.end());    
    ans = abs(sx-ex) + abs(sy-ey);
    calc();
    for(int i = 0; i < m; i++){
        int indd = fP(mas[i].first);
        ans = min(ans, dist[indd] + abs(mas[i].first - ex) + abs(mas[i].second - ey));
    }
    cout << ans;
    return 0;
}
