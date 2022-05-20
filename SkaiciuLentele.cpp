#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 500;
int n;
int ans = 0;
const int dd = dydis * dydis + 10;
vector<int> primes;
int mas[dydis][dydis];
int tevas[dd];
bool kv[dd] = {0};
bool isInMaching[dd] = {0};
vector<int> visi[dd];
pair<int, int> vt[dd];
vector<pair<int, int> > gr[dd];
vector<int> prm;
bool is[dd] = {0};
bool don[dd] = {0};
int dbInd = 0;
int fP(int v) {
    if (tevas[v] == v) {
        return v;
    }

    return tevas[v] = fP(tevas[v]);
}
map<int, int> dal[dd];
vector<pair<int, int > > go = {{ -1, 0}, {1, 0}, {0, -1}, {0, 1}};
int hsh(int e, int s) {
    vt[e * dydis + s] = {e, s};
    return e * dydis + s;
}

void conn(int e, int s) {
    for (auto x : go) {
        int pe = x.first + e;
        int ps = x.second + s;

        if (pe < 0 || ps < 0 || pe >= n || ps >= n || mas[pe][ps] == 0) {
            continue;
        }

        int v1 = hsh(e, s);
        int v2 = hsh(pe, ps);
        gr[v1].push_back({v2, dbInd});
        gr[v2].push_back({v1, dbInd});
        dbInd++;
        v1 = fP(v1);
        v2 = fP(v2);
        tevas[v1] = v2;
    }
}
void gen() {
    int sq = 1010;

    for (int i = 2; i <= sq; i++) {
        is[i] = 1;
    }

    for (int i = 2; i < sq; i++) {
        if (!is[i]) {
            continue;
        }

        for (int j = 2 * i; j < sq; j += i) {
            is[j] = 0;
        }

        primes.push_back(i);
    }
}
void prd(int ind, int sk) {
    int kek;

    for (auto x : primes) {
        kek = 0;

        while (sk % x == 0) {
            sk /= x;
            kek++;
        }

        if (kek == 0) {
            continue;
        }

        dal[ind][x] += kek;
    }

    if (sk != 1) {
        dal[ind][sk] += 1;
    }
}
int pairV[dd] = {0};
int pairU[dd] = {0};
int dist[dd] = {0};
const int inf = 1e9;
int nlN = dydis * dydis + 1;
bool bfs(vector<int> &kair) {
    queue<int> q;

    for (auto x : kair) {
        if (pairU[x] == nlN) {
            dist[x] = 0;
            q.push(x);
        }
        else {
            dist[x] = inf;
        }
    }

    dist[nlN] = inf;
    int u;

    while (!q.empty()) {
        u = q.front();
        q.pop();

        if (dist[u] < dist[nlN]) {
            for (auto v : gr[u]) {
                if (dist[pairV[v.first]] == inf) {
                    dist[pairV[v.first]] = dist[u] + 1;
                    q.push(pairV[v.first]);
                }
            }
        }
    }

    return dist[nlN] != inf;
}
bool dfs(int u) {
    if (u != nlN) {
        for (auto v : gr[u]) {
            if (dist[pairV[v.first]] == dist[u] + 1) {
                if (dfs(pairV[v.first]) == true) {
                    pairV[v.first] = u;
                    pairU[u] = v.first;
                    return true;
                }
            }
        }

        dist[u] = inf;
        return false;
    }

    return true;
}
void daryk(int v) {
//    cout << "ieskosiu matchinimo nuo " << v << ", aka " << vt[v].first << "; " << vt[v].second << endl;
    vector<int> &visiNodai = visi[v];
    vector<int> kairej;

    for (auto x : visiNodai) {
        if (((vt[x].first + vt[x].second) & 1) == ((vt[v].first + vt[v].second) & 1)) {
            kairej.push_back(x);
        }
    }

//    cout << "visiNodai = ["; for(auto x : visiNodai){
//        cout << x << " ";
//    }
//    cout << endl;
//    cout << "kaireje = ["; for(auto x : kairej) cout << x << " "; cout << endl;
    for (auto x : visiNodai) {
        pairU[x] = nlN;
        pairV[x] = nlN;
    }

    int matching = 0;

    while (bfs(kairej)) {
        for (auto u : kairej) {
            if (pairU[u] == nlN) {
                if (dfs(u) == true) {
                    matching = matching + 1;
                }
            }
        }
    }

    int viso = matching * 2;

    if (viso == visiNodai.size()) {
        if (!kv[v]) {
            viso -= 2;
        }
    }

//    cout << "viso = " << viso << endl;
    ans += viso;
}
int main() {
    gen();

    for (int i = 0; i < dd; i++) {
        tevas[i] = i;
    }

    for (int i = 0; i < dd; i++) {
        vt[i] = { -1, -1};
    }

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mas[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans += mas[i][j] == 0;

            if (mas[i][j] == 0) {
                continue;
            }

            conn(i, j);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mas[i][j] == 0) {
                continue;
            }

            int v = hsh(i, j);
            int tv = fP(v);
            visi[tv].push_back(v);
            prd(tv, mas[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mas[i][j] == 0) {
                continue;
            }

            int v = hsh(i, j);
            int tv = fP(v);

            if (v != tv) {
                continue;
            }

            bool isKv = 1;

            for (auto x : dal[v]) {
                if (x.second & 1) {
                    isKv = 0;
                }
            }
            kv[tv] = isKv;
        }
    }

    for (int i = 0; i < dd; i++) {

        if (vt[i] == make_pair(-1, -1)) {
            continue;
        }

        if (i != fP(i)) {
            continue;
        }


        daryk(i);

    }

    cout << ans;
    return 0;
}
