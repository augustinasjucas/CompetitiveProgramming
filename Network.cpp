#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
const int dydis = 5e5 + 10;
vector<int> gr[dydis];
int n;
vector<int> trav;
int lapu[dydis] = {0};
int visoLapu = 0;
int tinka = -1;
void dfs1(int v, int came){
    if(gr[v].size() == 1) lapu[v] = 1;
    int mx = 0; int s = 0;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs1(x, v);
        lapu[v] += lapu[x];
        s += lapu[x];
        mx = max(lapu[x], mx);
    }
    mx = max(mx, visoLapu - s);
    if(mx <= (visoLapu & 1) + visoLapu/2) tinka = v;
}
vector<int> visi[dydis];
vector<vector<int> > grupes;
void dfs(int v, int came, int kur){
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, kur);
    }
    if(gr[v].size() == 1) visi[kur].push_back(v);
}
bool comp(vector<int> &a, vector<int> &b){
    return a.size() < b.size();
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0 ; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    for(int i = 0; i < n; i++){
        if(gr[i].size() == 1) visoLapu++;
    }
    int st = -1;
    for(int i = 0; i < n; i++){
        if(gr[i].size() != 1) st = i;
    }
    dfs1(st, -1);
    if(tinka == -1){
//        while(true){
//            for(int i = 0; i < 10; i--){
//            
//            }
//        }
        cout << "BLOGAIII!";
        return 0;
    }
    for(auto &x : visi) x.clear();
    grupes.clear();
//    cout << "tinka = " << tinka << endl;
    for(auto x : gr[tinka]){
//        cout << "darysiu nuo " << x << endl;
        dfs(x, tinka, x);
        grupes.push_back(visi[x]);
    }
    sort(grupes.begin(), grupes.end(), comp);
    for(auto x : grupes){
//        cout << "grupe ["; for(auto y : x) cout << y << " "; cout << "]\n";  
    }
    vector<pair<int, int> > ats;
    int liko = visoLapu;
    int ind = grupes.size()-1;
    for(int i = 0; i < grupes.size(); i++){
        while(grupes[i].size()){
            pair<int, int> sitas = {grupes[i].back(), -1};
            grupes[i].pop_back();
            ind = max(ind, i + 1);
            if(liko == 1){
//                cout << "sitas ! " << endl;
                ats.push_back({sitas.first, ats.back().second});
                liko  =0;
                break;
            }
            while(grupes[ind].size() == grupes[ind-1].size()){
                ind--;
            }
            sitas.second = grupes[ind].back();
            grupes[ind].pop_back();
            if(ind != grupes.size()-1 && grupes[ind+1].size() > grupes[ind].size()) ind++;
            ats.push_back(sitas);
            liko -= 2;
        }
        if(liko == 0) break;
    }
    cout << ats.size() << "\n";
    for(auto x : ats){
        cout << x.first+1 << " " << x.second+1 << "\n";
    }
    return 0;
}
