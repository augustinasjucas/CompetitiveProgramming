#include <bits/stdc++.h>
using namespace std;
int w, h;
long long mod= 1e9 + 7;
map<int, vector<pair<int, int> > > eil, stul;
int kasVirsuj = -1, kasKairej = -1;
bool can(map<int, vector<pair<int, int> > > &mas, bool isVirsus){
    bool galima = 1;
    for(auto &x : mas){
        vector<pair<int, int> > &vec = x.second;
        int kasLyg = 0;
        kasLyg = vec[0].second ^ (vec[0].first&1);
        int kkkaslyg = kasLyg ^ (x.first&1);
        if(isVirsus){
            if(kasVirsuj == -1){
                kasVirsuj = kkkaslyg;
            }else{
                if(kasVirsuj != kkkaslyg) kasVirsuj = -2;
            }
        }else{
            if(kasKairej == -1){
                kasKairej = kkkaslyg;
            }else{
                if(kasKairej != kkkaslyg) kasKairej = -2;
            }
        }

        for(auto x : vec){
            if(x.first % 2 == 0) if((x.second & 1) != kasLyg) galima = 0;
            if(x.first % 2 == 1) if((x.second & 1) != !kasLyg) galima = 0;
            if(!galima) break;
        }
    }
    return galima;
}
long long pw(long long x, long long y){ // x^y
    if(y == 0) return 1;
    auto sakn = pw(x, y/2);
    sakn = sakn * sakn % mod;
    if(y & 1) sakn = sakn * x % mod;
    return sakn;
}
int n;
int main(){
    cin >> h >> w >> n; 
    for(int i = 0; i < n; i++){
        char a; cin >> a;
        int e = (a == '-' ? 0 : 1);
        int b, c; cin >> b >> c;
        eil[b].push_back({c, e}) ;
        stul[c].push_back({b, e});
    }
    if(n == 0){
        cout << ((pw(2, h) + pw(2, w))%mod - 2 + mod) % mod;
        return 0;
    }
    // jei eilutese alternuoja
    long long kek = 0;
    long long ans = 0;
    if(can(eil, 0)){
//        cout << "eilutes gali!" << endl;
//        cout << "prd 2^" << h << " - " << eil.size() << endl; 
        ans = (ans + pw(2, h-eil.size())) % mod;
    }
    if(can(stul, 1)){
//        cout << "stulepliai gali!" << endl;
//        cout << "prd 2^" << w-stul.size() << endl;
        ans = (ans+ (pw(2, w-stul.size())) % mod);
    }
    if(can(eil, 0) && can(stul, 1)){
        // abu gali. kiek bendru?
        // jei galiu virsuje padaryti alternuojanti 10101010 ir galiu kaireje padaryti alternuojanti 10101010, tai -1
        if(kasVirsuj == kasKairej && kasVirsuj != -2){
            ans = (ans - 1 + mod )%mod;
        }

        // jei galiu virsuje daryti 01010101010 ir kaireje galiu daryti 010101001, tai -1
        
    }
    cout << ans;
    return 0;
}
