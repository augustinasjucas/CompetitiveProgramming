#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target ("avx2")
using namespace std;
const int kek = 3;
const int szz = kek * 640 * 2;
const int maxN = 2e5 + 1;
int n, m;
bitset<maxN> bigAdj[szz];
int deg[maxN];
int bigInd[maxN];
int grsz[maxN] = {};
vector<int> bigNodes;
vector<int> gr[maxN];
long long ans = 0;
int ret = 0;
int bigCommon[szz][szz] = {};
int i1, i2 ;
int i = 0, j;
void fastscan(int &x)
{
//    cin >> x;
//    return ;
    int c;
    x =0;
    c=getchar();
    while (c == '\n' || c == ' ') c = getchar(); 
    for(;(47 < c); c = getchar())
        x = (x << 1) + (x << 3) + c -48;

}
void insrt(int ind, int a){
    for(i = 0; i < grsz[ind]; i++){
        if(gr[ind][i] < a) continue;
        swap(gr[ind][i], a);
    }
    gr[ind][grsz[ind]] = a;
    grsz[ind]++;
}
void eras(int &ind, int &a){
    for(i = 0; i < grsz[ind]-1; i++){
        if(gr[ind][i] >= a) swap(gr[ind][i], gr[ind][i+1]);
    }
    grsz[ind]--;
}
int commonSS(int a, int b){
    i1 = 0;
    i2 = 0;
    ret = 0;
    while(true){
        if(i1 == grsz[a] || i2 == grsz[b]) break;
        if(gr[a][i1] == gr[b][i2]) ret++, i1++, i2++;
        else if(gr[a][i1] < gr[b][i2]) i1++;
        else i2++;
    }
    return ret;
}
bool has(int i, int x){
    for(int j = 0; j < grsz[i]; j++){
        if(gr[i][j] == x) return 1;
    }
    return 0;
}
void SS(int a, int b){
//    return ;
    if(grsz[a] != 0 && has(a, b)){
        ans -= commonSS(a, b);
        eras(a, b);
        eras(b, a);
    }else{
        ans += commonSS(a, b);
        insrt(a, b);
        insrt(b, a);
    }
}
int commonSL(int a, int b){
    ret = 0;
    for(int i = 0; i < grsz[a]; i++){
        if(bigAdj[bigInd[b]][gr[a][i]]) ret++;
    }
    return ret;
}
void addBigCommon1(int mazas, int didelis, int kek){
    if(bigNodes.size() < grsz[mazas]){
        for(auto &x : bigNodes){
            if(x == mazas || x == didelis) continue;
            if(bigAdj[bigInd[x]][mazas]){
                bigCommon[bigInd[x]][bigInd[didelis]] += kek;
                bigCommon[bigInd[didelis]][bigInd[x]] += kek;
            }
        }
    }else{
        for(int i = 0; i < grsz[mazas]; i++){
            auto &x = gr[mazas][i];
            if(x == mazas || x == didelis) continue;
            if(bigInd[x] != -1){
                bigCommon[bigInd[x]][bigInd[didelis]] += kek;
                bigCommon[bigInd[didelis]][bigInd[x]] += kek;
            }
        }
    }
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
//    return ;
    if(bigAdj[bigInd[b]][a]){
        ans -= commonSL(a, b);
        eras(a, b);
        bigAdj[bigInd[b]][a] = 0;
        addBigCommon1(a, b, -1);
    }else{
        ans += commonSL(a, b);
        insrt(a, b);
        bigAdj[bigInd[b]][a] = 1;
        addBigCommon1(a, b, 1);
    }
}
int commonLL(int a, int b){
    return bigCommon[bigInd[a]][bigInd[b]];
}
void LL(int a, int b){
//    return ;
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
    for(int i = 0; i < maxN; i++){
        bigInd[i] = -1;
    }
//    cin >> n >> m;
    fastscan(n);
    fastscan(m);
    int xx;
    pair<int, int>  brn[m];
    for(int i = 0; i < m; i++){
        int a, b;
        fastscan(a);
        fastscan(b);
//        cin >> a >> b;
        brn[i] = {a, b};
        deg[a]++;
        deg[b]++;
    }
    for(int i = 0; i < n; i++) gr[i].resize(deg[i]);
    int sq = sqrt(m) * kek;
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

