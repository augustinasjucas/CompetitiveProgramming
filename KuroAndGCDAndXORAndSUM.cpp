#include <bits/stdc++.h>
using namespace std;
const int dd = 17;
const int inf = 1e9;
vector<int> nulinis (2, -1);
struct trie{
    vector<vector<int> > medis;
    int dbInd = 0;
    int newN(){
        return dbInd++;
    }
    void rsz(int kek){
        if(kek == 0) return;
        dbInd = 1;
        medis.resize((kek)*dd + 2);
        for(auto &x : medis) x = nulinis;
    }
    vector<int> getBin(int x){
        vector<int> ret;
        for(int i = 0; i < dd; i++){
            ret.push_back(x&1);
            x = x >> 1;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
    void prd(vector<int> &vec, int v, int ind){
        if(ind == vec.size()) return;
        if(medis[v][vec[ind]] == -1) medis[v][vec[ind]] = newN();
        prd(vec, medis[v][vec[ind]], ind+1);
    }
    void add(int x){
        vector<int> bin = getBin(x);
        prd(bin, 0, 0);
    }
    long long fd(vector<int> &maz, vector<int> &xr, int v, int ind, bool jauMazesnis){
        if(ind == xr.size()) return 0;
        if(medis[v][0] == -1 && medis[v][1] == -1) return -inf;
        if(!jauMazesnis){
            if(maz[ind] == 0){
                // tuomet galiu imti tik 0
                if(medis[v][0] == -1) return -inf;
                return (xr[ind] == 1 ? (1 << (dd-ind-1)) : 0) + fd(maz, xr, medis[v][0], ind+1, jauMazesnis);
            }else{
                if(xr[ind] == 0){ // noriu deti 1
                    if(medis[v][1] != -1){
                        int pos = (1 << (dd-ind-1)) + fd(maz, xr, medis[v][1], ind+1, 0);
                        if(pos > 0) return pos;
                    }
                    if(medis[v][0] != -1) return fd(maz, xr, medis[v][0], ind+1, 1); 
                    return -inf;
               
                }else{ // noriu deti 0
                    if(medis[v][0] != -1){
                        int pos = (1 << (dd-ind-1)) + fd(maz, xr, medis[v][0], ind+1, 1);
                        return pos;
                    }else{
                        return fd(maz, xr, medis[v][1], ind+1, 0);
                    }           
                }
            }
        }else{ // kuo didesnio noriu
            if(xr[ind] == 0){ // noresiu paimt vienetuka
                if(medis[v][1] != -1){
                    return (1 << (dd-ind-1)) + fd(maz, xr, medis[v][1], ind+1, 1);
                }else if(medis[v][0] != -1){
                    return fd(maz, xr, medis[v][0], ind+1, 1);
                }
            }else{ // noresiu nuliuko
                if(medis[v][0] != -1){
                    return (1 << (dd-ind-1)) + fd(maz, xr, medis[v][0], ind+1, 1);
                }else if(medis[v][1] != -1){
                    return fd(maz, xr, medis[v][1], ind+1, 1);
                }
            }
        }
        return -inf;
    }
    int find(int x, int y){ // rasti toki, maksimalu xora su y, kad skaicius butu mazesnis uz x
        vector<int> bin1 = getBin(x);
        vector<int> bin2 = getBin(y);
//        cout << "x = " << x << ", y  =" << y << endl;
//        cout << "gaunu: \nmaz = ["; for(auto x : bin1) cout << x << " "; cout << endl << "xor = ["; for(auto x : bin2) cout << x  << " "; cout << endl;
        long long ret = fd(bin1, bin2, 0, 0, 0);
        if(ret < 0) return -1;
        return ret;
    }
};
const int dydis = 1e5 + 10;
vector<trie> vec(dydis);
set<int> setas[dydis];
void prd(int x){
    int sq = sqrt(x);
    for(int i = 1; i <= sq; i++){
        if(x % i != 0) continue;
        setas[i].insert(x);
        setas[x/i].insert(x);
    }
}
int main(){
    vector<pair<pair<int, int>, pair<int, int> > > quers;
    int q; cin >> q;
    for(int i = 0; i < q; i++){
        int t; cin >> t;
        if(t == 1){
            int b; cin >> b;
            quers.push_back({{t, b}, {-1, -1}});
            prd(b);
        }else{
            int b, c,d; cin >> b >> c >> d;
            quers.push_back({{t, b}, {c, d}});
//            prd(b);
        }
    }
    for(int i = 1; i < dydis; i++){
        vec[i].rsz(setas[i].size() + 1);
    }
    for(int h = 0; h < q; h++){
        int t; t = quers[h].first.first;
        if(t == 1){
            int a= quers[h].first.second;
            // prideti a;
            int sq = sqrt(a);
            for(int i = 1; i <= sq; i++){
                if(a % i != 0) continue;
                vec[i].add(a);
                if(i*i != a) vec[a/i].add(a);
            }
        }else{
            int k, x, s; 
            x = quers[h].first.second;
            k = quers[h].second.first;
            s = quers[h].second.second;
            if(s <= x){
                cout << "-1\n";
                continue;
            }
            int sq = sqrt(x);
            int ret = -1;
            for(int i = 1; i <= sq; i++){
                if(x % i != 0) continue;
                int prm = -1, ant = -1;
                if(i % k == 0){
                    prm = vec[i].find(s-x, x);
                }
                if((x/i) % k == 0 && i * i != x){
                    ant = vec[x/i].find(s-x, x);
                }
                ret = max(ret, max(prm, ant));
            }
            if(ret == -1) cout << ret << "\n";
            else cout << (ret ^ x) << "\n";
        }
//        cout << endl;
    }
    
    return 0;
}
