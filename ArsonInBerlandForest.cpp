#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int> > mas, pref; 
int kv, ka, dv, da;
int quer(int e1, int s1, int e2, int s2){
    kv = 0, ka = 0, dv = 0, da = 0;
    if(e1 != 0 && s1 != 0) kv = pref[e1-1][s1-1];
    if(s1 != 0) ka = pref[e2][s1-1];
    if(e1 != 0) dv = pref[e1-1][s2];
    da = pref[e2][s2];
    return da - ka - dv + kv;
}
queue<pair<int, int> > q;
vector<vector<int> > dst;
vector<pair<int, int> > dir = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
auto daug(vector<vector<bool> > &prm, int range){
    while(q.size()) q.pop();
    for(auto &x : dst) for(auto &y : x) y = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!prm[i][j]) continue;
            dst[i][j] = range;
            q.push({i, j});
        }
    }
    int e, s, dist, pe, ps;
    while(!q.empty()){
        e = q.front().first;
        s = q.front().second;
        dist = dst[e][s];
        q.pop();
        if((e == 0 || s == 0 || e == n-1 || s == m-1) && dist != 0) return false;
        if(!mas[e][s]) return false;
        if(dist == 0) continue;
        for(auto &x : dir){
            pe = x.first + e;
            ps = x.second + s;
            if(dst[pe][ps] < dist){
                dst[pe][ps] = dist - 1;
                q.push({pe, ps});
            }
        }
    }
/*    cout << "tada paskui dst : \n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << setw(3) << dst[i][j] << "";
        }
        cout << endl;
    }   */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mas[i][j] && dst[i][j] == -1) return false;
            if(dst[i][j] != -1 && !mas[i][j]) return false;
        }
    }
    return true;
}
vector<vector<bool> > st;

bool f(int a){
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) st[i][j] = 0;
    for(int i = 0; i < n-a +1 ; i++){
        for(int j = 0; j < m-a+1; j++){
            if(quer(i, j, i+a-1, j+a-1) == a * a){
                st[i+a/2][j+a/2] = 1;
            }
        }
    }

    return daug(st, a/2);
}
void calc(){
    for(int i = 0; i < n; i++){
        int sm = 0;
        for(int j = 0; j < m; j++){
            sm += mas[i][j];
            pref[i][j] = sm + (i != 0 ? pref[i-1][j] : 0);
        }
    }
}
void padar(int a){
    a = a * 2 + 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) st[i][j] = 0;
    for(int i = 0; i < n-a +1 ; i++){
        for(int j = 0; j < m-a+1; j++){
            if(quer(i, j, i+a-1, j+a-1) == a * a){
                st[i+a/2][j+a/2] = 1;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << (st[i][j] ? 'X' : '.');
        }
        cout << "\n";
    }
}
int main(){
    cin >> n >> m;
    mas.resize(n); pref.resize(n); st.resize(n);
    for(auto &x : pref) x.resize(m);
    for(auto &x : mas) x.resize(m);
    for(auto &x : st) x.resize(m);
    dst = pref;
    for(auto &x : mas){ 
        for(auto &y : x) {
            char a; cin >> a;
            if(a == 'X') y = 1;
            else y = 0;
        }
    }
    calc();
    int l = 0; int r = min(n, m) / 2, mid;
    int ans = 0;
    while(l <= r){
        mid = (l + r);
        if(f(2 * mid + 1)){
            ans = mid; 
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
    cout << ans << endl;
    padar(ans);
    return 0;

}
/*

.######...
.#XXXX#...
.#XXXX#...
.#XXXX#...
.###XX###.
...#XXXX#.
...#XXXX#.
...#XXXX#.
...######.
..........
*/
