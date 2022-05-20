#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3  +10;
vector<pair<int, int> > brn;
vector<int> rem;
vector<pair<int, int> > gr[dydis];
int reikPaimt;
vector<int> taken;
vector<int> cur;
int n;
void dfs(int v){
    if(reikPaimt == 0) return;
//    cout << "dfs " << v << ":";
    for(auto x : gr[v]){
        if(taken[x.second] || rem[x.second]) continue;
        if(reikPaimt == 0) break;
        taken[x.second] = 1;
        reikPaimt--;
        cur.push_back(x.second);
//        cout << "idedu briauna " << v + 1 << " -- " << x.first + 1 << endl;
        dfs(x.first);
    }
}
int wanted = 0;
int ask(set<int> mas){
    cout << "? " << mas.size() << " ";
    for(auto x : mas) cout << x + 1 << " ";
    cout << endl;
    int ret; cin >> ret;
    return ret;
}
void paband(vector<int> &cur){
    set<int> nodes;
    for(auto x : cur) {
        nodes.insert(brn[x].first);
        nodes.insert(brn[x].second);
    }
    int rez = ask(nodes);
    if(rez == wanted) {
        for(int i = 0; i < n-1; i++) rem[i] = 1;
        for(auto x : cur) rem[x] = 0;
    }else{
        for(auto x : cur) rem[x] = 1;
    }
}
int main(){
    cin >> n;

    rem.resize(n-1);
    taken.resize(n-1);
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back({b, i});
        gr[b].push_back({a, i});
        brn.push_back({a, b});
    }
    set<int> visi;
    for(int i = 0; i < n; i++) visi.insert(i);
    wanted = ask(visi);
    int left = n-1;
    while(true){
        for(int i = 0; i < n; i++) taken[i] = 0;
        reikPaimt = left / 2;
        cur.clear();
        for(int i = 0; i < n-1; i++){
            if(reikPaimt == 0) break;
            if(rem[i]) continue;
            if(taken[i]) continue;
//            cout << "turiu briauna " << brn[i].first + 1 << "; " << brn[i].second + 1<< endl; 
            cur.push_back(i);
            taken[i] = 1;
            reikPaimt--;
            dfs(brn[i].first);
            dfs(brn[i].second);
        } 
        paband(cur);
        left = 0;
        for(int i = 0; i < n-1; i++) left += !rem[i];
        if(left == 1) break;
    }
    int ret = -1;
    for(int i = 0; i < n-1; i++) if(!rem[i]) ret = i;
    cout << "! " << brn[ret].first + 1 << " " << brn[ret].second  + 1;
    return 0;
}
