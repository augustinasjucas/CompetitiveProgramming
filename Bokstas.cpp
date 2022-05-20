#include <bits/stdc++.h>
using namespace std;
struct node{
    int l, r;
    int kas = -1, kek = -1;
    bool del = 0;
};
int dbInd = 0, n, k;
const int dydis = 1e6;
node mas[dydis];
int newN(){
    return dbInd++;
}
int K = 0;
vector<int> vec;
int findL(int v){
    int L = mas[v].l;
    if(mas[L].del) return mas[v].l = findL(L);
    else{
        return mas[v].l = L;
    }
}
int findR(int v){
    int R = mas[v].r;
    if(mas[R].del) return mas[v].r = findR(R);
    else{
        return mas[v].r = R;
    }
}
void idek(int kas, int kek){
    int nd = newN();
    mas[K].r = nd;
    mas[nd].l = K;
    mas[nd].kas = kas;
    mas[nd].kek = kek;
    if(mas[nd].kek >= k) vec.push_back(nd);
    K = nd;
}
vector<int> ans;
void fix(int v){
    mas[v].l = findL(v);
    mas[v].r = findR(v);
}
void dfs(int v){
    if(v == 1) return ;
    if(v > 1) fix(v);
    for(int i = 0; i < mas[v].kek; i++){
        ans.push_back(mas[v].kas);
    }
    dfs(mas[v].r);
}
pair<int, int> del(int v){
    int L = mas[v].l;
    int R = mas[v].r;
    mas[v].del = 1;
    mas[L].r = R;
    mas[R].l = L;
    return {L, R};
}


void print(int v){
    if(v == 1) return ;
    if(v > 1) fix(v);
    cout << "{" << mas[v].kek << ";" << mas[v].kas << "}   ";
    print(mas[v].r);
}
int main(){
    newN(); newN(); // 0 - kaire, 1 - desine
    cin >> n >> k;
    int last = -1;
    int kek = 0;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        if(last == -1) last = a;
        if(last != a){
            idek(last, kek);
            kek = 0;
        }
        last = a;
        kek++;
    }
    idek(last, kek); mas[K].r = 1;
    while(!vec.empty()){
//        print(0);
//        cout << endl << endl;
        vector<int> kt;
        vector<int> suj;
        for(auto x : vec){
            if(mas[x].del) continue;
            fix(x);
            auto kas = del(x);
            suj.push_back(kas.first);
            suj.push_back(kas.second);
        }

        for(auto x : suj){
            if(x <= 1 || mas[x].del) continue;

            fix(x);
            int L = mas[x].l;
            int R = mas[x].r;
            if(mas[L].kas == mas[x].kas){
                mas[x].kek += mas[L].kek;
                del(L);
            }
            if(mas[R].kas == mas[x].kas){
                mas[x].kek += mas[R].kek;
                del(R);
            }
            if(mas[x].kek >= k){
                kt.push_back(x);
            }

        }
        vector<int> kti;
        for(auto x : kt) if(!mas[x].del) kti.push_back(x);
        vec = kti;
    }
    dfs(0);
    cout << ans.size() << "\n";
    for(auto x : ans) cout << x << "\n";
    return 0;
}
