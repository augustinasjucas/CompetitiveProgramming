#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, m, k;
vector<string> pats;
string turi[dydis];
bool galima = 1;
void mer(int ind, string a){
    for(int i = 0; i < k; i++){
        if(turi[ind][i] != a[i]){
            turi[ind][i] = '_';
        }
    }
}
int kek[dydis] = {0};
int mn[dydis];
vector<int> gr[dydis];
set<pair<string, int> > setas;
void sujungiam(int ind){
    string cp;
    for(int i = 0; i < (1 << k); i++){
        cp = turi[ind];
        for(int j = 0; j < k; j++){
            if(i & (1 << j)) cp[j] = '_';
        }
        auto kur = setas.lower_bound({cp, -1});
        if(kur == setas.end() || kur->first != cp) continue;
        gr[ind].push_back(dydis + kur->second);
        mn[kur->second] = min(ind, mn[kur->second]);
    }
}
set<int> visi;
int main(){
    for(auto &x : mn) x = 1d9;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> k;
    pats.resize(n);
    for(int i = 0; i < n; i++){
        cin >> pats[i];
        setas.insert({pats[i], i});
    }
    for(int i = 0; i < m; i++){
        string a; int ind; cin >> a >> ind; ind--;
        visi.insert(ind);
        if(turi[ind].size() == 0) turi[ind] = a;
        else{
            mer(ind, a);
        }
    }
    for(int i = 0; i < n; i++){
        if(turi[i].size() == 0) continue;
        sujungiam(i);
    }
    set<int> gali;
    vector<int> ans;
    for(int i = 0; i < n; i++){
        if(gr[i].size() == 0){
            galima = 0;
        }else{
            ans.push_back(gr[i][0]);
            for(int j = 1; j < gr[i].size(); i++) gali.push_back()
        }
    }

    return 0;
}
