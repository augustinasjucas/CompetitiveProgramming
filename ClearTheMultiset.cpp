#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e3 + 10;
const int lg2 = 14;
int lg[dydis];
int table[dydis][lg2];
int n;
vector<int> mas;
void build(){
    lg[1] = 0;
    for(int i = 2; i < dydis; i++) lg[i] = lg[i/2] + 1;
    for(int i = 0; i < n; i++){
        table[i][0] = mas[i];
    }
    for(int j = 1; j < lg2; j++){
        for(int i = 0; i + (1 << j) - 1 < n; i++){
            table[i][j] = min(table[i][j-1], table[i + (1 << (j-1))][j-1]);
        }
    }
}
int ans(int l, int r){
    int ll = lg[r-l+1];
    return min(table[l][ll], table[r - (1 << ll) + 1][ll]);
}
map<int, vector<int> > mapas;
vector<int> nuliai;
int f(int l, int r, int sm){
    if(l > r) return 0;
    if(l == r) return 0;
    int mnEl = ans(l, r);
    int st = -(mnEl-sm);
    int last = l;
    vector<int> &vec = mapas[mnEl];
    int kr = lower_bound(vec.begin(), vec.end(), l) - vec.begin();
    for(int i = kr; i < vec.size(); i++){
        int ind = vec[i];
        if(ind > r) break;
        st += f(last, ind-1, mnEl);
        last = ind+1;
        st++;
    }
    st += f(last, r, mnEl);
    return max(st, 0);
}
int main(){
    cin >> n;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    build();
    for(int i = 0; i < n; i++){
        mapas[mas[i]].push_back(i);
        if(mas[i] == 0) nuliai.push_back(i);
    }
    int st = nuliai.size();
    int last = 0;
    for(auto x : nuliai) {
        st += f(last, x-1, 0);
        last = x + 1;
    }
    st += f(last, n-1, 0);
    cout << n - st;
    return 0;
}
