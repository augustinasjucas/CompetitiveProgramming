#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int inv;
long long mas[2][20];
int n;
long long inf = 1e10;
vector<bool> toBit(int a){
    vector<bool> ret;
    for(int i = 0; i < n; i++) {
        ret.push_back(a&1);
        a = a >> 1;
    }
    return ret;
}
long long sm(vector<bool> ms, int ind){
    long long s = 0;
    for(int i = 0; i < n; i++){
        if(!ms[i]) continue;
        s += mas[ind][i];
    }
    return s;
}
long long sm1(vector<bool> ms, int ind){
    long long s = 0;
    for(int i = 0; i < n; i++){
        if(mas[!ind][i] == 0) s += mas[ind][i];
        if(!ms[i]) continue;
        if(mas[!ind][i] != 0)s += mas[ind][i];
    }
    return s;
}
void del(multiset<long long> &a, long long b){
    auto kur = a.find(b);
    if(kur == a.end()) return;
    a.erase(kur);
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            cin >> mas[i][j];
        }
    }
    inv = (1 << n)-1;
    pair<long long, pair<long long, long long> >  ret = {1000000000000, {-1, -1}};
    long long s = 0;
    long long mn = 1;
    for(int i = 0; i < n; i++){
        if(mas[1][i] == 0) mn += mas[0][i];
    }
    long long l = mn;
//    cout << "mn = " << mn << endl;
    vector<pair<pair<long long, int>, long long> > vec;
    for(int i = 0; i < (1 << n); i++){
        auto sit = toBit(i); bool cont = 0;
        long long mn = 0;
        for(int i = 0; i < n; i++){
            if(sit[i] && mas[0][i] == 0) cont = 1;
            mn += sit[i];
        }
        if(cont) continue;
        if(sm(sit, 1) == 0) continue;
//        cout << "sm = ["; for(auto x : sit) cout << x << " "; cout << endl;
        long long mx = sm(sit, 0);
        /// sita intervala galima gauti kai pirmame yra [mn, mx]
        long long kt = sm(toBit(i^inv), 1) + 1;
//        cout << "cia yra ["<< mn << "; " << mx << "], kitame tai kainuos " << kt << endl; 
        vec.push_back({{mn, 1}, kt});
        vec.push_back({{mx+1, 0}, kt});
        vec.push_back({{mx, 2}, kt});
        vec.push_back({{mn, 2}, kt});
//        vec.push_back({{mx-1, 2}, kt});
        vec.push_back({{mx+1, 2}, kt});
        //        cout << endl;
    }
    sort(vec.begin(), vec.end());
    multiset<long long> setas;
    pair<long long, pair<long long, long long> > ans = {10000000000000, {-1, -1}} ;
//    cout << "mn = " << mn << endl;
    for(int i = 0; i < vec.size(); i++){
        auto x = vec[i];
        long long sk = x.first.first;
        int dl = x.first.second;
        long long val = x.second;
//        cout << "gaunu sk = " << sk << "; dl = " << dl << "; val = " << val << endl;
        if(dl == 0){ // sita reiks isimti
            del(setas, val);
        }else if(dl == 1){
            setas.insert(val);
//            cout << "cia " << sk << " vs " << mn << endl;
        }
        if(dl == 2 && setas.size() > 0){
            ans = min(ans, {max(sk, mn) + (*setas.rbegin()), {max(sk, mn), (*setas.rbegin())}});
        }
 
    }
    cout << ans.second.first << "\n" << ans.second.second;
    return 0;
}
/*
 
5 4
 
 
4
0 2 2 4
2 0 1 4
 
*/
