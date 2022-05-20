#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(nullptr)

const int MAXN = 1100;

int n;
int w[MAXN], l[MAXN], h[MAXN];
vector<int> adj[MAXN];
int deg[MAXN] = {};
int dp[MAXN] = {};
vector<int> seq;

void topo () {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        seq.push_back(v);
        cout << "v = " << v << endl;
        for (int u : adj[v]) {
            deg[u]--;
            if (deg[u]==0)
                q.push(u);
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> l[i] >> h[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (w[i] > w[j] && l[i] > l[j]) {
                cout << i << " -> " << j << endl;
                adj[i].push_back(j);
                deg[j]++;
            }
        }
    }
    topo();
    cout << "seq: "; for(auto x : seq) cout << x<< " ";
    cout << endl;

    for (int v : seq) {
        for (int u : adj[v])
            dp[v] = max(dp[u], dp[v]);
        dp[v] += h[v];
        cout << "dp[" << v << "] = " << dp[v] << endl;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);

    cout << ans << "\n";

    return 0;
}
