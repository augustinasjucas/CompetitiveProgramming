#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
vector<pair<int, int> > di = {{ -1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int dd = 4100100;
bitset<dd> yra;
bitset<dd> vis;
bitset<dd> inC;
vector<vector<int> > inc;
const int dydis = 1e3 + 10;
vector<int> cSz;
int hsh(int e, int s, int dir) {
    yra[(e * 1001 + s) * 4 + dir] = 1;
    return (e * 1001 + s) * 4 + dir;
}
int ans = 0;
vector<vector<int> >  gr;
int n, m;
vector<char> mas[dydis];
vector<int> dst ;
short vs[dd / 4] = {0};
bitset<dd> btst;
void suj(int e, int s, int dir) {
    int j = 0;
    int i = (j + dir) % 4;
    int pe = di[i].first + e;
    int ps = di[i].second + s;

    if (mas[pe][ps] == '#') {
        gr[hsh(e, s, dir)].push_back(hsh(e, s, (i + 1) % 4));
        inc[hsh(e, s, (i + 1) % 4)].push_back(hsh(e, s, dir));
    }
    else {
        inc[hsh(pe, ps, i)].push_back(hsh(e, s, dir));
        gr[hsh(e, s, dir)].push_back(hsh(pe, ps, i));
    }
}
vector<int> stekas;
bool fd = 0;
bitset<dd> onS;
vector<vector<int> > ckl;
vector<int> tv;
void dfs1(int v) { // ieskau ciklo
    if (fd) {
        return;
    }

    if (vis[v]) {
        if (!onS[v]) {
            fd = 1;
            return;
        }

        vector<int> vec;
        vector<int> setas;

        while (true) {
            inC[stekas.back()] = 1;
            vec.push_back(stekas.back());
            setas.push_back(stekas.back() / 4);
            tv[stekas.back()] = v;

            if (stekas.back() == v) {
                break;
            }

            stekas.pop_back();
        }

        int un = 0;

//btst
        for (int i = 0; i < setas.size(); i++) {
            if (!btst[setas[i]]) {
                un++;
            }

            btst[setas[i]] = 1;
        }

        for (auto x : setas) {
            btst[x] = 0;
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
    if (vs[v / 4]) {
        dst[v] = dst[came];
    }
    else {
        dst[v] = dst[came] + 1;
    }

    vs[v / 4] += 1;

    for (auto x : inc[v]) {
        dfs2(x, v);
    }

    vs[v / 4] -= 1;
    ans = max(ans, dst[v]);
}
int main() {
    for(auto &x : mas)  x.resize(dydis);
    tv.resize(dd);
    ckl.resize(dd);
    gr.resize(dd);
    inc.resize(dd);
    cSz.resize(dd);
    dst.resize(dd);
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    ifstream in("lmio_2016_3e2_robotas_vyr.in");
    ofstream out("lmio_2016_3e2_robotas_vyr.out");
    in >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> mas[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mas[i][j] == '#') {
                continue;
            }

            for (int h = 0; h < 4; h++) {
                suj(i, j, h);
            }
        }
    }

    for (int i = yra._Find_first(); i < dd; i = yra._Find_next(i)) {
        if (vis[i]) {
            continue;
        }

        fd = 0;
        stekas.clear();
        dfs1(i);
    }

    for (int i = yra._Find_first(); i < dd; i = yra._Find_next(i)) {
        if (!inC[i]) {
            continue;
        }

        int tev = tv[i];

        for (auto x : ckl[tev]) {
            vs[x / 4] = 1;
        }

        for (auto y : ckl[tev]) {
            dst[y] = cSz[y];
            ans = max(ans, cSz[y]);

            for (auto x : inc[y]) {
                if (inC[x]) {
                    continue;
                }

                dfs2(x, y);
            }

            yra[y] = 0;
        }

        for (auto x : ckl[tev]) {
            vs[x / 4] = 0;
        }
    }

    out << ans;
    return 0;
}

