#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto start = high_resolution_clock::now();
const int dydis = 1e5 + 10;
const int inf = 1e9;
vector<int> gr[dydis];
int inc[dydis] = {0};
bool del[dydis] = {0};
int dist[dydis] = {0};
int came[dydis] = {0};
int n;
vector<int> topoSort(vector<pair<int, int> > &G) {
    for (int i = 0; i < n; i++) {
        inc[i] = 0;
        del[i] = 0;
    }

    for (auto x : G) if (!del[x.first] && !del[x.second]) {
            inc[x.second]++;
        }

    priority_queue<pair<pair<int, int>, int> > q;

    for (int i = 0; i < n; i++) {
        if (del[i]) {
            continue;
        }

        q.push({{ -inc[i], rng()}, i});
    }

    vector<int> ans;
    vector<int> curCheck;

    while (!q.empty()) {
        int fd = -1;

        for (auto x : curCheck) {
            if (del[x]) {
                continue;
            }

            if (inc[x] == 0) {
                fd = x;
                break;
            }
        }

        curCheck.clear();
        int v, d;

        if (fd != -1) {
            v = fd;
            d = inc[v];
        }
        else {

        }

        if (fd == -1) {
            v = q.top().second;
            d = -q.top().first.first;
            q.pop();
        }

        if (d != inc[v]) {
            continue;
        }

        if (del[v]) {
            continue;
        }

        ans.push_back(v);
        del[v] = 1;

        for (auto x : gr[v]) {
            if (del[x]) {
                continue;
            }

            inc[x]--;

            if (inc[x] == 0) {
                if (curCheck.size() == 0) {
                    curCheck.push_back(x);
                }
            }

            q.push({{ -inc[x], rng()}, x});
        }
    }

    return ans;
}
vector<int> getP(int v) {
    vector<int> ret;

    while (v != -1) {
        ret.push_back(v);
        v = came[v];
    }

    reverse(ret.begin(), ret.end());
    return ret;
}
void bfs() {
    for (int i = 0; i < n; i++) {
        dist[i] = -1, came[i] = -1;
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (del[i]) {
            continue;
        }

        if (inc[i] == 0) {
            q.push(i);
            dist[i] = 0;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto x : gr[v]) {
            if (del[x]) {
                continue;
            }

            if (inc[x] > 1) {
                continue;
            }

            if (dist[x] < dist[v] + 1) {
                dist[x] = dist[v] + 1;
                came[x] = v;
                q.push(x);
            }
        }
    }
}
vector<pair<int, int> > makeE(vector<pair<int, int> > &G, vector<int> &prm) {
    vector<pair<int, int> > pos;

    for (int i = 0; i < prm.size() - 1; i++) {
        pair<int, int> st = make_pair(prm[i], prm[i + 1]);
        auto kur = lower_bound(G.begin(), G.end(), st);

        if (kur != G.end() && *kur == st) {
        }
        else {
            pos.push_back(st);
        }
    }

    return pos;
}
vector<pair<int, int> > brute(vector<pair<int, int> > &G) {
    for (auto x : G) {
        inc[x.second]++;
    }

    vector<int> RET;/*
    int sq = sqrt(n) + 500;

    for (int i = 0; i < sq; i++) {
        bfs();
        pair<pair<int, int>, int> mx = {{ -1, -1}, -1};

        for (int i = 0; i < n; i++) {
            if (del[i]) {
                continue;
            }

            mx = max(mx, {{dist[i], rng()}, i});
        }

        if (mx == make_pair(make_pair(-1, -1), -1)) {
            break;
        }

        auto kas = getP(mx.second);

        for (auto x : kas) {
            RET.push_back(x);
            del[x] = 1;

            for (auto y : gr[x]) {
                inc[y]--;
            }
        }
    }*/

    vector<pair<int, int> > ret(n + 1);
    vector<int> st;
    int sq = 4300000 / n;
    sq = max(sq, 1);

    if (n <= 5000) {
        sq = max(1000, sq);
    }
    double pirmas = 0;
    for (int i = 0; i < 1000000000; i++) {
        auto br = topoSort(G);
        vector<pair<int, int> > pos = makeE(G, br);

        if (pos.size() < ret.size()) {
            ret = pos;
            st = br;
        }
        auto fnsh = high_resolution_clock::now();
        auto elap = duration_cast<milliseconds>(fnsh-start);
        if(elap.count() >= 3800) break;
        if(i == 0) pirmas = elap.count();
        if(elap.count() +pirmas >= 3800) break;
    }

    for (auto x : st) {
        RET.push_back(x);
    }

    return makeE(G, RET);
}
vector<pair<int, int> > smart(vector<pair<int, int> > &G) {
    for (int i = 0; i < n; i++) {
        del[i] = 0;
        inc[i] = 0;
    }

    for (auto x : G) {
        inc[x.second]++;
    }

    vector<int> perm;

    while (true) {
        bfs();
        pair<pair<int, int> , int> mx = {{ -1, -1}, -1};

        for (int i = 0; i < n; i++) {
            if (del[i]) {
                continue;
            }

            mx = max(mx, {{dist[i], rng()}, i});
        }

        if (mx == make_pair(make_pair(-1, -1), -1)) {
            break;
        }

        auto kas = getP(mx.second);

//        cout << "kas = ["; for(auto x : kas) cout << x<< " "; cout << "]" << endl;
        for (auto x : kas) {
            perm.push_back(x);
            del[x] = 1;

            for (auto y : gr[x]) {
                inc[y]--;
            }
        }
    }

    return makeE(G, perm);
}
vector<pair<int, int> > smartt(vector<pair<int, int> > &G) {
    for (int i = 0; i < n; i++) {
        inc[i] = del[i] = 0;
        came[i] = -1;
        dist[i] = inf;
    }

    vector<pair<int, int> > ret(n + 1);
    double pirmas;
    for (int i = 0; i < 1000000000; i++) {
        auto sitas = smart(G);

        if (sitas.size() < ret.size()) {
            ret = sitas;
        }
        auto fnsh = high_resolution_clock::now();
        auto elap = duration_cast<milliseconds>(fnsh-start);
        if(i == 0) pirmas = elap.count();
        if(elap.count() +pirmas >= 3800) break;
    }

    return ret;

}
vector<pair<int, int> > solve(int nn, vector<pair<int, int> > GG) {
    start = high_resolution_clock::now();
    vector<pair<int, int> > G;
    sort(GG.begin(), GG.end());
    G.push_back(GG[0]);

    for (int i = 1; i < GG.size(); i++) {
        if (GG[i] == GG[i - 1]) {
            continue;
        }

        G.push_back(GG[i]);
    }

    srand(time(0));
    n = nn;
    int m = G.size();
    sort(G.begin(), G.end());

    for (auto x : G) {
        gr[x.first].push_back(x.second);
    }

//    return brute(G);
    if (n > 30001) {
        return brute(G);
    }

//    else if (n > 2000) {
//        return smart(G);
//    }

    return smartt(G);
}
