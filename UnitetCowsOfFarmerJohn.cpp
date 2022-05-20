#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
vector<pair<int, int> > ints;
int n;
int nxt[dydis] = {0};
int last[dydis];
int mas[dydis];
int rez[dydis] = {};
int block;
int kek[dydis] = {0};
int dbRz = 0;
int L = 0, R = -1;
bool maz(pair<int, int> &a, pair<int, int> &b){
    if(a.first/block == b.first/block) return a.second < b.second;
    return a.first < b.first;
}
void del(int ind){
    kek[mas[ind]]--;
    if(kek[mas[ind]] == 0) dbRz--;
}
void prd(int ind){
    kek[mas[ind]]++;
    if(kek[mas[ind]] == 1) dbRz++;
}
void move(int l, int r){
    while(L < l){
        del(L);
        L++;
    }
    while(L > l){
        L--;
        prd(L);
    }
    while(R > r){
        del(R);
        R--;
    }
    while(R < r){
        R++;
        prd(R);
    }
}
int main(){
    cin >> n; block = sqrt(n);
    for(auto &x : last) x = n;
    for(int i = 0; i < n; i++) cin >> mas[i];
    for(int i = n-1; i > -1; i--){
        nxt[i] = last[mas[i]];
        last[mas[i]] = i;
        if(i != nxt[i]-1) ints.push_back({i, nxt[i]-1}); // kiek yra skirtingu sitame intervale?
    }

    sort(ints.begin(), ints.end(), maz);
    
    for(auto x : ints){
        move(x.first, x.second);
        rez[x.first] = dbRz;
//        cout << "intervale " << x.first+1 << "; " << x.second+1 << " yra " << dbRz << " skirtingu reiksmiu!" << endl ;
    }
    long long ret = 0;
    for(int i = 0; i < n; i++){
        if(i == nxt[i]-1) continue;
        ret += rez[i]-1;
    }
    cout << ret;



    return 0;
}
