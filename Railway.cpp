#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, m, k;
vector<pair<int, int> > gr[dydis];
vector<int> colors[dydis];
set<pair<int, int> > pom[dydis];
int kiek[dydis] = {0};


int tevas[dydis];
int answ[dydis] = {0};

int fP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
    a = fP(a);
    b = fP(b);
    if(a == b) return ;
    if(pom[a].size() > pom[b].size()){
        swap(a, b);
    }
    tevas[a] = b;
    for(auto &x : pom[a]){
        auto kur = pom[b].lower_bound({x.first, -1});
        if(kur == pom[b].end() || kur->first != x.first){
            pom[b].insert(x);
            if(kiek[x.first] == x.second){
            
            }else{
                answ[b]++;
            }
        }else{
            int bv = kur->second;
            pom[b].erase(kur);
            pom[b].insert({x.first, x.second + bv});
            if(x.second + bv == kiek[x.first]){
                answ[b]--;
            }
        }
    }
}
void sudek(int a, int b){
    
    b = fP(b);
    for(auto x : colors[a]){
        auto kur = pom[b].lower_bound({x, -1});
        if(kur == pom[b].end() || kur->first != x){
            pom[b].insert({x, 1});
            if(kiek[x] == 1){
            
            }else{
                answ[b]++;
            }
        }else{
            int bv = kur->second;
            pom[b].erase(kur);
            pom[b].insert({x, 1 + bv});
            if(1 + bv == kiek[x]){
                answ[b]--;
            }
        }       
    }
    
}
vector<int> ats;
void dfs(int v, int came, int indd){
    for(auto x : gr[v]) {
        if(x.first == came) continue;
        dfs(x.first, v, x.second);
    }
    for(auto x : gr[v]){
        if(x.first == came) continue;
        conn(x.first, v);
    }
    sudek(v, v);
    if(answ[fP(v)] >= k && indd != -1){
        ats.push_back(indd);
    }
}

int main(){
    for(int i = 0; i < dydis; i++) tevas[i] = i;
    cin >> n >> m >> k;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
    }
    for(int i = 0; i < m; i++){
        int kek; cin >> kek;
        kiek[i] = kek;
        for(int j = 0; j < kek; j++){
            int a; cin >> a; a--;
            colors[a].push_back(i);
        }
    }
    dfs(0, -1, -1);
    sort(ats.begin(), ats.end());
    cout << ats.size() << "\n";
    for(auto x : ats){
        cout << x + 1 << " ";
    }
    return 0;
}
