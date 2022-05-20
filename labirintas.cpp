#include <bits/stdc++.h>
using namespace std;
const int dydis = 20;
char ans[dydis][dydis];
int dist[dydis][dydis];
int n, m, k;
vector<pair<int, int> > kryp = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void bfs(int e, int s){
    queue<pair<int, int> > q;
    q.push({e, s});
    for(int i = 0; i < n; i++){
        for(int j =0 ; j < m; j++){
            dist[i][j] = dydis * dydis;
        }
    }
    dist[e][s]  =0;
    while(!q.empty()){
        int e = q.front().first;
        int s = q.front().second;
        q.pop();
        for(auto x : kryp){
            int pe = x.first + e;
            int ps = x.second + s;
            if(pe < 0 || ps < 0 || pe >= n || ps >= m) continue;
            if(ans[pe][ps] == '#') continue;
            if(dist[pe][ps] > dist[e][s] + 1){
                dist[pe][ps] = dist[e][s] + 1;
                q.push({pe, ps});
            }
        }
    }
}
int main(){

    ifstream in("in.txt");
    ofstream out("out.txt");
    int t;
    cin >> t;
    while(t--){
        bool don = 0;
        cin >> n >> m >> k;
        if(n < m) {
            don = 1;
            swap(n, m);
        }

        // sitas veikia kai yra ilgas, t.y. m > n
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ans[i][j] = '.';
            }
        }
        ans[0][0] = 'x';
        for(int i = 0; i < m; i++){
            if(!(i & 1)) continue;
            for(int j = 0; j < n; j++){
                ans[j][i] = '#';
            }
            if(i % 4 == 1) { // apacioj skyle
                ans[n-1][i] = '.';
            }else{
                ans[0][i] = '.';
            }
            if(k > 4 && i != m-1 && i != 0){
                if(i % 4 == 1) { // apacioj skyle
                    ans[n-1][i] = 'o';
                    ans[n-2][i] = 'o';
                    ans[n-1][i+1] = 'o';
                    ans[n-1][i-1] = 'o';
                }else{
                    ans[0][i] = 'o';
                    ans[1][i] = 'o';
                    ans[0][i+1] = 'o';
                    ans[0][i-1] = 'o';

                }
                k -= 4;
            }
        }
        bfs(0, 0);
        vector<pair<int, pair<int, int> > > ms;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(ans[i][j] == '.')
                    ms.push_back({dist[i][j], {i, j}});
            }
        }
        sort(ms.begin(), ms.end()); reverse(ms.begin(), ms.end());
        for(int i = 0; i < n * m + 1; i++){
            if(k == 0) break;
            if(ans[ms[i].second.first][ms[i].second.second] == 'o') continue;
            ans[ms[i].second.first][ms[i].second.second] = 'o';
            k--;
        }
        if(!don){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    out << ans[i][j];
                }
                out << "\n";
            }
            out << "\n";
        }else{
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    out << ans[j][i];
                }
                out << "\n";
            }
            out << endl;
        }
    }
}
