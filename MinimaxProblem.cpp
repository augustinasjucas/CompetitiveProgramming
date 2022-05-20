#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 3e5 + 10;
vector<int> mx[257];
int kas[257];
vector<int> base(8, 0);
int curAns = -1, x1 = -1, x2 = -1;
int n, m;
void process(vector<int> &mas, int ind){
    int mn = 1e9;
    for(auto x : mas) mn = min(mn, x);
    if(mn > curAns){
        x1 = ind; x2 = ind; curAns = mn;
    }
    int kek = (1 << m);
    for(int i = 0; i < kek; i++){
        int mano = 1e9;
        for(int j = 0; j < m; j++){
            mano = min(mano, max(mx[i][j], mas[j]));
        }
        if(mano > curAns && kas[i] != -1){
            curAns = mano;
            x1 = kas[i];
            x2 = ind;
        }
    }
    for(int i = 0; i < kek; i++){
        int cp = i;
        bool tinka = 1;
        int db = (1 << (m-1));
        int manoMn = 1e9;
        int joMn = 1e9;
        for(int j = 0; j < m; j++){
            bool st = (cp&db); db /= 2;
            if(!st) continue;
            manoMn = min(manoMn, mas[j]);
            joMn = min(joMn, mx[i][j]);
        }
        if(manoMn > joMn){
            mx[i] = mas;
            kas[i] = ind;
        }
    }

}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(auto &x : kas) x = -1;
    cin >> n >> m;
    base.resize(m);
    for(auto &x : mx) x = base;
    for(int i = 0; i < n; i++){
        vector<int> st(m);
        for(auto &x : st) cin >> x;
        process(st, i);
    }
    cout << x1+1 << " " << x2+1;
    return 0;
}
