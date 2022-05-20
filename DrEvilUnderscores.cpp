#include <bits/stdc++.h>
using namespace std;
struct node{
    int kaim[2] = {-1, -1};
};
const int inf = 1000000000;
const int bitu = 30;
const int dydis = 1e5 + 10;
node medis[dydis * bitu];
vector<int> mas;
int n; 
int dbInd = 0;
int newN(){
    return dbInd++;
}
vector<bool> toB(int a){
    vector<bool> ret;
    for(int i = 0; i < bitu; i++){
        ret.push_back(a&1);
        a = a >> 1;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
void pridek(vector<bool> &vec, int ind, int v){
    if(ind == vec.size()) return;
    if(medis[v].kaim[vec[ind]] == -1){
        medis[v].kaim[vec[ind]] = newN();
    }
    pridek(vec, ind+1, medis[v].kaim[vec[ind]]);
}
int bfs(int v, int lev){
    if(v == -1) return inf;
    if(medis[v].kaim[0] == -1 && medis[v].kaim[1] == -1){
        return 0;
    }
    if(medis[v].kaim[0] == -1){
        return bfs(medis[v].kaim[1], lev-1);
    }else if(medis[v].kaim[1] == -1){
        return bfs(medis[v].kaim[0], lev-1);
    }else{
        return min(bfs(medis[v].kaim[1], lev-1), bfs(medis[v].kaim[0], lev-1)) + (1 << lev);
    }
}
int main(){
    cin >> n;
    mas.resize(n);
    newN();
    for(int i = 0; i < n; i++){
        cin >> mas[i];
        vector<bool> bits = toB(mas[i]);
        pridek(bits, 0, 0);
    }
    cout << bfs(0, bitu-1);
    return 0;
}
