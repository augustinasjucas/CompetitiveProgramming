#include <bits/stdc++.h>
#pragma GCC optimize("O2")
using namespace std;
const int kek = 10;
const int szz = kek * 640.0;
const int maxN = 2e5 + 1;
int n, m;
bitset<maxN> bigAdj[szz];
int deg[maxN];
int bigInd[maxN];
vector<int> bigNodes;
unordered_set<int> gr[maxN];
long long ans = 0;
int ret =0 ;
int bigCommon[szz][szz] = {};
int i1, i2 ;
int i = 0, j;

int commonSS(int a, int b){
    if(gr[a].size() > gr[b].size()) swap(a, b);
    int ret = 0;
    for(auto &x : gr[a]){
        ret += gr[b].count(x);
    }
    return ret;
}

void SS(int a, int b){
    if(gr[a].count(b)){
        ans -= commonSS(a, b);
        gr[a].erase(b);
        gr[b].erase(a);
    }else{
        ans += commonSS(a, b);
        gr[a].insert(b);
        gr[b].insert(a);
    }
}
int commonSL(int a, int b){
    ret = 0;
    for(auto &x : gr[a]){
        if(bigAdj[bigInd[b]][x]) ret++;
    }
    return ret;
}
void addBigCommon(int mazas, int didelis, int kek){
    for(auto &x : bigNodes){
        if(x == mazas || x == didelis) continue;
        if(bigAdj[bigInd[x]][mazas]){
            bigCommon[bigInd[x]][bigInd[didelis]] += kek;
            bigCommon[bigInd[didelis]][bigInd[x]] += kek;
        }
    }
    
}
void SL(int a, int b){
    if(bigAdj[bigInd[b]][a]){
        ans -= commonSL(a, b);
        gr[a].erase(b);
        bigAdj[bigInd[b]][a] = 0;
        addBigCommon(a, b, -1);
    }else{
        ans += commonSL(a, b);
        gr[a].insert(b);
        bigAdj[bigInd[b]][a] = 1;
        addBigCommon(a, b, 1);
    }
}
int commonLL(int a, int b){
    return bigCommon[bigInd[a]][bigInd[b]];
}
void LL(int a, int b){
    if(bigAdj[bigInd[b]][a]){
        ans -= commonLL(a, b);
        bigAdj[bigInd[a]][b] = 0;
        bigAdj[bigInd[b]][a] = 0;
        addBigCommon(a, b, -1);
        addBigCommon(b, a, -1);
    }else{
        ans += commonLL(a, b);
        bigAdj[bigInd[a]][b] = 1;
        bigAdj[bigInd[b]][a] = 1;
        addBigCommon(a, b, 1);
        addBigCommon(b, a, 1);
    }    
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < maxN; i++){
        bigInd[i] = -1;
    }
    cin >> n >> m;
    pair<int, int>  brn[m];
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        brn[i] = {a, b};
        deg[a]++;
        deg[b]++;
    }
    int sq = sqrt(m)*kek;
    sq = sq ;
    for(int i = 0; i < n; i++){
        if(deg[i] > sq){
            bigNodes.push_back(i);
            bigInd[i] = bigNodes.size()-1;
        }
    }
    
    int a, b;
    pair<int, int> x;
    for(int i = 0; i < m; i++){
        x = brn[i];
        a = x.first, b = x.second;
        if(bigInd[a] == -1 && bigInd[b] == -1) SS(a, b);
        if(bigInd[a] == -1 && bigInd[b] != -1) SL(a, b);
        if(bigInd[a] != -1 && bigInd[b] == -1) SL(b, a);
        if(bigInd[a] != -1 && bigInd[b] != -1) LL(a, b);
        cout << ans << "\n";
    }
    return 0;
}

