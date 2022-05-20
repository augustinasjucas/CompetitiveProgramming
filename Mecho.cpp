#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 10;
const int inf = 1e9;
int n, S;
char mas[dydis][dydis];
int dist[dydis][dydis];
vector<pair<int, int> > dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
void bfs(){
    for(int i = 0; i < dydis; i++) for(int j = 0; j < dydis; j++) dist[i][j] = inf;
    queue<pair<int, int> > q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mas[i][j] != 'H') continue;
            dist[i][j] = 0;
            q.push({i, j});
        }
    }
    while(!q.empty()){
        int e = q.front().first;
        int s = q.front().second;
        int pe, ps;
        q.pop();
        for(auto x : dir){
            pe = x.first + e;
            ps = x.second + s;
            if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
            if(mas[pe][ps] == 'D' || mas[pe][ps] == 'T') continue;
            if(dist[pe][ps] > dist[e][s] + 1){
                dist[pe][ps] = dist[e][s] + 1;
                q.push({pe, ps});
            }
        }
    }
}
int d[dydis][dydis];
int sE, sS, eE, eS;
bool f(int X){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            d[i][j] = inf;
        }
    }
    if(X >= dist[sE][sS]) return false;
    queue<pair<int, int> > q;
    d[sE][sS] = 0;
    q.push({sE, sS});
    while(!q.empty()){
        int e = q.front().first;
        int s = q.front().second;
        int pe, ps;
        q.pop();
        for(auto x : dir){
            pe = e + x.first;
            ps = s + x.second;
            if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
            if(mas[pe][ps] == 'H' || mas[pe][ps] == 'T') continue;
            int bus = d[e][s] + 1;
            int b1 = bus / S;
            if(b1 >= dist[pe][ps] - X) continue;
            if(d[pe][ps] > bus){
                d[pe][ps] = bus;
                q.push({pe, ps});
            }
        }
    }
    return d[eE][eS] < inf;
}
int main(){
    cin >> n >> S;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> mas[i][j];
            if(mas[i][j] == 'M') sE = i, sS = j;
            if(mas[i][j] == 'D') eE = i, eS = j;
        }
    }
    bfs();
    int l = 0, r = 1e9, mid, ans = -1; 
    while(l <= r){
        mid = (l + r) / 2;
        if(f(mid)){
            ans = max(ans, mid);
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
    cout << ans;
    return 0;
}
