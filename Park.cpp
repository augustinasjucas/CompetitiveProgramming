#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 2010;
int n, m;
const int inf = 1e9;
vector<pair<int, pair<int, int> > > mas;
bool tUp[dydis];
bool tDown[dydis];
bool tLeft[dydis];
bool tRight[dydis];
int tevas[dydis];
int w, h;
void nunul(){
    for(int i = 0; i < dydis; i++){
        tevas[i] = i;
        tUp[i] = tDown[i] = tLeft[i] = tRight[i] = 0;
    }
}
int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    if(a == b) return;
    tevas[b] = a;
    tUp[a] |= tUp[b];
    tDown[a] |= tDown[b];
    tRight[a] |= tRight[b];
    tLeft[a] |= tLeft[b];
}
bool interUp(int x, int y, int r, int R){
    return y + r > h-R;
}
bool interDown(int x, int y, int r, int R){
    return y-r < R;
}
bool interLeft(int x, int y, int r, int R){
    return x-r < R;
}
bool interRight(int x, int y, int r, int R){
    return x + r > w-R;
}
long long dst(long long x1, long long y1, long long x2, long long y2){
    return (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
}
bool inter(int x1, int y1, long long r1, int x2, int y2, long long r2){
    if(dst(x1, y1, x2, y2) < r1*r1 + r2*r2 + 2ll * r1 * r2){
        return true;
    }
    return false;
}
bitset<4> fd(int r, int corn){ 
    nunul();
    for(int i = 0; i < n; i++){
        tUp[i] = interUp(mas[i].second.first, mas[i].second.second, mas[i].first + r, r);
        tDown[i] = interDown(mas[i].second.first, mas[i].second.second, mas[i].first + r, r);
        tLeft[i] = interLeft(mas[i].second.first, mas[i].second.second, mas[i].first + r, r);
        tRight[i] = interRight(mas[i].second.first, mas[i].second.second, mas[i].first + r, r);
    }
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(inter(mas[i].second.first, mas[i].second.second, mas[i].first + r, mas[j].second.first, mas[j].second.second, mas[j].first + r)){
                conn(i, j);
            }
        }
    }
    bool can[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1} };
    for(int i = 0; i < n; i++){
        if(fP(i) != i) continue;
        bool u = tUp[i];
        bool d = tDown[i];
        bool l = tLeft[i];
        bool r = tRight[i];

        if(u && r){ // desine virsus [2] izoliuotas
            can[2][0] = can[2][1] = can[2][3] = 0;
            can[0][2] = can[1][2] = can[3][2] = 0;
        }
        if(r && d){ // desine apacia [1] izoliuota
            can[1][0] = can[1][2] = can[1][3] = 0;
            can[0][1] = can[2][1] = can[3][1] = 0;
        }
        if(d && l){ // kaire apacia [0] izoliuota
            can[0][1] = can[0][2] = can[0][3] = 0;
            can[1][0] = can[2][0] = can[3][0] = 0;
        }
        if(l && u){ // kaire virsus [3] izoliuotas
            can[3][0] = can[3][2] = can[3][1] = 0;
            can[0][3] = can[2][3] = can[1][3] = 0;
        }
        if(l && r){ // apacia ([0] ir [1]) atskirta nuo virsaus ([2] ir [3])
            can[0][2] = can[0][3] = can[1][2] = can[1][3] = 0;
            can[2][0] = can[3][0] = can[2][1] = can[3][1] = 0;
        }
        if(u && d){ // kaire ([3] ir [0]) atskirta nuo desines ([2] ir [1])
            can[3][2] = can[3][1] = can[0][2] = can[0][1] = 0;
            can[2][3] = can[1][3] = can[2][0] = can[1][0] = 0;
        }
    }
    bitset<4> st;
    for(int i = 0; i < 4; i++){
        st[i] = can[corn][i];
    }
    return st;
}
int mazKaiGaliu[4][4] = {0};
int mx = 0;
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
    for(int i = 0; i < 4; i++) mazKaiGaliu[i][i] = inf;
    cin >> n >> m >> w >> h;
    for(int i = 0; i < n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        mas.push_back({c, {a, b}});
    }
    vector<pair<int, int> > visitors;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; b--;
        visitors.push_back({a, b});
        mx = max(mx, a);
    }
    for(int i = 0; i < 4; i++){
        for(int j = i+1; j < 4; j++){
            if(i == j) continue;
            int l = 0; int r = mx; int mid;
            int ans = 0;
            while(l <= r){
                mid = (l+r)/2;
                if(fd(mid, i)[j]){
                    ans = max(ans, mid);
                    l = mid+1;
                }else{
                    r = mid-1;
                }
            }
            mazKaiGaliu[i][j] = ans;
//            cout << "didziausias, su kuriuo galiu patekti is " << i << " i " << j << " yra " << ans << endl;
        }
    }
    for(int i = 0; i < m; i++){
        int a, b; a = visitors[i].first; b = visitors[i].second;
        string ats = "";
        for(int i = 0; i < 4; i++){
            if(a <= mazKaiGaliu[min(b, i)][max(i, b)]){
                ats.push_back('1' + i);
            }
        }
        
        cout << ats << "\n";

    }

    return 0;
} 
