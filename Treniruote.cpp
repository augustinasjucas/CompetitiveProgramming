#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 10;
const int inf = 1e9;
int dist[dydis][(1 << 15)] = {0};
vector<pair<int, int> > mas;
int n;
long long ans = inf;
void bfs(){
    queue<pair<int, long long> > q;
    for(int i = 0; i < n; i++){
        q.push({i, (1 << i)});
    }
    while(!q.empty()){
        long long sk = q.front().second;
        int ind = q.front().first;
        if(sk == (1 << n) - 1){
            ans = min((int)ans, dist[ind][sk]);
        }
        q.pop();
        long long dst = dist[ind][sk];
        for(int i = 0; i < n; i++){
            if(sk & (1 << i)) continue;
            long long ps = sk | (1 << i);
            if(dist[i][ps] > max(dist[ind][sk] + abs(mas[ind].first - mas[i].first), mas[i].second)){
                dist[i][ps] = max(dist[ind][sk] + abs(mas[ind].first - mas[i].first), mas[i].second);
                q.push({i, ps});
            }
            
        }
    }
}
int main(){
    for(int i =0; i < dydis; i++){
        for(int j = 0; j < (1 << 15); j++){
            dist[i][j] = inf;
        }
    }
    cin >> n;
    mas.resize(n);
    int ind = 0;
    for(auto &x : mas) {
        cin >> x.first >> x.second;
        long long sk = 1 << ind;
        dist[ind][sk] = max(x.second, x.first-1);
        ind++;
    }

    bfs();
    
    cout << ans;
    return 0;
}
