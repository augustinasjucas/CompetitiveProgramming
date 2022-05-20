#include <bits/stdc++.h>
using namespace std;
int n;

const int dydis = 1e5 + 10;
int L[dydis], R[dydis];
int val[dydis];
vector<int> children[dydis];
int ifLeft[dydis];
int ifRight[dydis];
long long sum[dydis] = {};
int he[dydis] = {};
void dfs(int v, int h = 0) {
    he[v] = h;
    for(auto x : children[v]) {
        if(val[x] > val[v]) {
            R[v] = x;
        }else {
            L[v] = x;
        }
        dfs(x, h+1);
    }
//    cout << "L[" << v << "] = " << L[v] << ", R[" << v << "] = " << R[v] << endl;

}
void dfs1(int v) {
    if(L[v] == -1) {
        ifLeft[v] = v;
        ifRight[v] = v;
        return ;
    } 
    dfs1(L[v]);
    dfs1(R[v]);
    ifLeft[v] = ifLeft[L[v]];
    ifRight[v] = ifRight[R[v]];
}
long long sm = 0;
void dfs2(int v) {
    if(L[v] == -1) {
        sum[v] = sm;
        return ;
    }
//    cout << "ESU " << v << endl;
    sm += val[ifLeft[R[v]]];
//    cout << "pridedu val[" << ifLeft[R[v]] << "] = " << val[ifLeft[R[v]]] << endl;
    dfs2(L[v]);
//    cout << "issimu val[" << ifLeft[R[v]] << "] = " << val[ifLeft[R[v]]] << endl;
    sm -= val[ifLeft[R[v]]];
    sm += val[ifRight[L[v]]];
//    cout << "pridedu val[" << ifRight[L[v]] << "] = " << val[ifRight[L[v]]] << endl;
    dfs2(R[v]);
//    cout << "isimu val[" << ifRight[L[v]] << "] = " << val[ifRight[L[v]]] << endl;
    sm -= val[ifRight[L[v]]];
//    cout << "NEBESU " << v << endl;
}
int main(){
    for(int i = 0; i < dydis; i++) {
        L[i] = R[i] = -1;
        ifLeft[i] = ifRight[i] = -1;
    }
    cin >> n;
    vector<pair<int, int> > mas;
    int rt = 0;
    for(int i = 0; i < n; i++) {
        int pr, vl; cin >> pr >> vl;
        pr--;
        val[i] = vl;
        if(pr != -2)
            children[pr].push_back(i);
        if(pr == -2) rt = i;
        mas.push_back({vl, i});
    }
    dfs(rt);
    dfs1(rt);
    dfs2(rt);
    sort(mas.begin(), mas.end());
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int a; cin >> a;
        int vt = lower_bound(mas.begin(), mas.end(), make_pair(a, -1)) - mas.begin();
        int kur = 0;
        if(vt == mas.size()) {
            kur = mas.back().second;
        }else if(vt == 0) {
            kur = mas[0].second;
        }else {
            int i1 = mas[vt].second;
            int i2 = mas[vt-1].second;
            if(L[i1] == -1) kur = i1;
            else kur = i2;
        }
        cout << setprecision(20) << ((long double)sum[kur]) / (1.0 * he[kur] ) << "\n";
    }

    return 0;
}
/*
7
-1 20
1 10
1 30
2 5
2 15
3 25
3 35

7
-1 12
1 6
1 14
2 1
2 8
5 7
5 10
*/
