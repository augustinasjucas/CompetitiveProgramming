#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 1e5 + 10;
const int dyd = 3155;
int n, m, q;
int sq;
vector<int> didieji[dydis];
vector<vector<int> > grupes;
int didInd[dydis] = {0};
int dbInd = 0;
int common[dyd][dyd] = {0};
//bitset<dydis> turi[dyd];
//short bendriKiti[dydis][dyd] = {0};
vector<int> visi[dydis];

short bend[dydis][dyd] = {0};
long long val[dydis] = {0};
long long bigVal[dydis] = {0};
long long additional[dydis] = {0};
int main(){
    //cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> q;
    grupes.resize(m);
    sq = sqrt(n);
    for(int i = 0; i < m; i++){
        int k; cin >> k;
        if(k >= sq) didInd[i] = dbInd++;

        vector<int> sitas;
        for(int i = 0; i < k; i++){
            int a; cin >> a;
            sitas.push_back(a);
            if(k >= sq) didieji[a].push_back(dbInd-1);
        }
        grupes[i] = sitas;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < didieji[i].size(); j++){
            for(int h = 0; h < didieji[i].size(); h++){
                if(j == h) continue;
                common[didieji[i][j]][didieji[i][h]]++;
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(grupes[i].size() >= sq) continue;
        for(auto x : grupes[i]){
            for(auto y : didieji[x]){
                bend[i][y]++;
            }
        }
    }
    for(int i = 0; i < q; i++){
        char a; cin >> a;
        if(a == '+'){
            long long a, b; cin >> a >> b;
            if(grupes[a].size() >= sq){
                bigVal[didInd[a]] += b;
            }else{
                for(auto x : grupes[a]){
                    val[x] += b;
                }
                for(int i = 0; i < dbInd; i++){
                    additional[i] += ((long long)bend[a][i])*b;
                }
            }
        }else{
            long long a; cin >> a;
            if(grupes[a].size() >= sq){
                long long ret = 0;
                int pa = a;
                a = didInd[a];
                ret += bigVal[a] * grupes[pa].size() + additional[a];
                for(int i = 0; i < dbInd; i++){
                    if(i == a) continue;
                    ret += common[a][i] * bigVal[i];
                }
                cout << ret << "\n";
            }else{
                long long ret = 0;
                for(auto x : grupes[a]){
                    ret += val[x];
                }
                for(int i = 0; i < dbInd; i++){
                    ret += bend[a][i] * bigVal[i];
                }
                cout << ret << "\n";

            }
        }
    }
    return 0;
}
