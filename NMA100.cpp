#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int dydis = 1e5 + 10;
vector<int> gr[dydis];
int inc[dydis] = {0};
bool del[dydis] = {0};
int dist[dydis] = {0};
int came[dydis] = {0};
int n;
vector<int> topoSort(vector<pair<int, int> > &G) {
    for (int i = 0; i < n; i++) {
        inc[i] = 0;
    }

    for (auto x : G) if (!del[x.first] && !del[x.second]) {
            inc[x.second]++;
        }

    priority_queue<pair<pair<int, int>, int> > q;

    for (int i = 0; i < n; i++) {
        if (del[i]) {
            continue;
        }

        q.push({{ -inc[i], rand()}, i});
    }

    vector<int> ans;

    while (!q.empty()) {
        int v = q.top().second;
        int d = -q.top().first.first;
        q.pop();

        if (d != inc[v]) {
            continue;
        }

        ans.push_back(v);

        for (auto x : gr[v]) {
            if (del[x]) {
                continue;
            }

            inc[x]--;
            q.push({{ -inc[x], rand()}, x});
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
vector<pair<int, int> > makeE(vector<pair<int, int> > &G, vector<int> prm) {
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
    for(int i = 0; i < n; i++){
        inc[i] = 0;
        del[i] = 0;
    }
    for (auto x : G) {
        inc[x.second]++;
    }

    vector<int> RET;
    int sq = sqrt(n) + 500;

    for (int i = 0; i < sq; i++) {
        bfs();
        pair<int, int> mx = { -1, -1};

        for (int i = 0; i < n; i++) {
            if (del[i]) {
                continue;
            }

            mx = max(mx, {dist[i], i});
        }

        if (mx == make_pair(-1, -1)) {
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
    }

    vector<pair<int, int> > ret(n + 1);
    vector<int> st;

    for (int i = 0; i < 13; i++) {
        auto br = topoSort(G);
        vector<pair<int, int> > pos = makeE(G, br);

        if (pos.size() < ret.size()) {
            ret = pos;
            st = br;
        }
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
        pair<int, int> mx = { -1, -1};

        for (int i = 0; i < n; i++) {
            if (del[i]) {
                continue;
            }

            mx = max(mx, {dist[i], i});
        }

        if (mx == make_pair(-1, -1)) {
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
vector<pair<int, int> > solve(int nn, vector<pair<int, int> > G) {
    n = nn;
    int m = G.size();
    sort(G.begin(), G.end());

    for (auto x : G) {
        gr[x.first].push_back(x.second);
    }
    vector<pair<int, int> > ms1(n+1), ms2(n+1);
    if (n > 30001) {
        ms1 = brute(G);
    }else{
        ms1 = brute(G);
        ms2 = smart(G);
    }
    if(ms1.size() < ms2.size()) return ms1;
    else return ms2;
}

