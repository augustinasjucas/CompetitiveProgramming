#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
const int dydis = 2e5 + 10;
const int dd = 410000;
bitset<dd> yra;
bitset<dd> vis;
int vs[dd] = {0};
bitset<dd> inC;
vector<int> inc[dd];
int n, k;
vector<pair<int, int> > mas;
vector<int> indai[dd];
vector<int> gr[dd];
int id[dd];
vector<int> stekas;
bool fd = 0;
bitset<dd> onS;
vector<int> ckl[dd];
int tv[dd];
int cSz[dd];
int dst[dd] = {0};
int ats[dd] = {0};
int hsh(int ind, int s){
    yra[ind*2 + s] = 1;
    return ind*2 + s;
}
bitset<dd> btst;
vector<int> vec, setas;
int un = 0;
void dfs1(int v) { // ieskau ciklo
    if(fd) return;
    if (vis[v]) {
        if (!onS[v]) {
            fd = 1;
            return;
        }
        vec.clear();
        setas.clear();
        while (true) {
            inC[stekas.back()] = 1;
            vec.push_back(stekas.back());
            setas.push_back(id[stekas.back()]);
            tv[stekas.back()] = v;
            if (stekas.back() == v) {
                break;
            }
            stekas.pop_back();
        }
        un = 0;
        for (int i = 0; i < setas.size(); i++) {
            if(!btst[setas[i]]) un++;
            btst[setas[i]] = 1;
        }
        for(auto x : setas){
            btst[x]  =0;
        }
        ckl[v] = vec;
        for (auto x : vec) {
            cSz[x] = un;
        }
        fd = 1;
        return ;
    }

    vis[v] = 1;
    onS[v] = 1;
    stekas.push_back(v);
    dfs1(gr[v][0]);
    stekas.pop_back();
    onS[v] = 0;
}
void dfs2(int v, int came) {
    if (vs[id[v]]) {
        dst[v] = dst[came];
    }else{
        dst[v] = dst[came] + 1;
    }
    vs[id[v]] += 1;
    for (auto x : inc[v]) {
        dfs2(x, v);
    }
    vs[id[v]] -= 1;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dd; i++) yra[i] = 1;
    cin >> n >> k;
    for(int i = 0; i < k; i++){
        int a, b; cin >> a >> b; a--; b--;
        mas.push_back({a, b});
        indai[a].push_back(i);
        indai[b].push_back(i);
    }
    for(int i = 0; i < k; i++){
        // is pirmo
        int v = mas[i].first;
        int u = mas[i].second;
        int ind1 = i * 2;
        int j = indai[u][(lower_bound(indai[u].begin(), indai[u].end(), i + 1) - indai[u].begin())%indai[u].size()];
        // is i suolis i j
        int ind2 = j * 2 + (u == mas[j].first ? 0 : 1);
        gr[ind1].push_back(ind2);
        inc[ind2].push_back(ind1);
        id[ind1] = v;
  //      cout << ind1 << "(" << v +1<< ")" << " -> " << ind2 << "\n";


        v = mas[i].second;
        u = mas[i].first;
        ind1 = i * 2 + 1;
        j = indai[u][(lower_bound(indai[u].begin(), indai[u].end(), i + 1) - indai[u].begin())%indai[u].size()];
        ind2 = j * 2 + (u == mas[j].first ? 0 : 1);
        gr[ind1].push_back(ind2);
        inc[ind2].push_back(ind1);
        id[ind1] = v;
//        cout << ind1 <<"(" << v+1 << ")" <<  " -> " << ind2 << endl;
    }
    for(int i = 0; i < 2*k; i++){
        if (!yra[i]) continue;
        if(vis[i]) continue;
//        cout << "pradesiu nuo " << i << endl;
        fd = 0;
        stekas.clear();
        dfs1(i);
    }

   for(int i = 0; i < dd; i++) {
        if (!yra[i]) continue;
        if (!inC[i]) continue;
        int tev = tv[i];
        for (auto x : ckl[tev]) {
            vs[id[x]] = 1;
        }
        for(auto y : ckl[tev]) {
            dst[y] = cSz[y];
            for (auto x : inc[y]) {
                if (inC[x]) {
                    continue;
                }
                dfs2(x, y);
            }
            yra[y] = 0;
        }

        for (auto x : ckl[tev]) {
            vs[id[x]] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        if(indai[i].size() == 0){
            cout << 1 << "\n";
        }else{
            int kr = indai[i][0];
            int pl = 0;
            if(mas[kr].second == i) pl = 1;
            cout << dst[kr * 2 + pl] << "\n";
        }
    }
    return 0;
}
