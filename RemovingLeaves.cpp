#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
vector<int> gr[dydis];
bool rem[dydis] = {};
int deg[dydis] = {};
int leaveCount[dydis] = {};
vector<int> leaves[dydis];
int n, k;
void solve(){
    cin >> n >> k;
    for(int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
        deg[a]++; deg[b]++;
    }
    if(n == 2) {
        for(int i = 0; i < n; i++) {
            gr[i].clear();
            deg[i] = 0;
            leaveCount[i] = 0;
            leaves[i].clear();
            rem[i] = 0;
        }

        if(k == 1) {
            cout << "1\n";
        }else {
            cout << "0\n";
        }
        return ;
    }
    if(k == 1) {
        for(int i = 0; i < n; i++) {
            gr[i].clear();
            deg[i] = 0;
            leaveCount[i] = 0;
            leaves[i].clear();
            rem[i] = 0;
        }

        cout << n-1 << "\n";
        return ;
    }
    for(int i = 0; i < n; i++) {
        if(deg[i] == 1) {
            leaves[gr[i][0]].push_back(i);
        }
    }
    priority_queue<pair<int, int> > q; 
    for(int i = 0; i < n; i++) {
        if(leaves[i].size() >= k) {
            q.push({leaves[i].size(), i});
        }
    }
    int ans = 0;
    while(q.size()){
        int v = q.top().second;
        int cnt = q.top().first;
        q.pop();
        if(cnt != leaves[v].size()) continue;
        if(rem[v]) continue;
        if(leaves[v].size() < k) break;
//        cout << "v = " << v+1 << endl;
        int kek = leaves[v].size() / k;
        ans += kek;
        for(int i = 0; i < kek; i++) {
            for(int j = 0; j < k; j++) {
                rem[leaves[v].back()] = 1;
                deg[v]--;
                leaves[v].pop_back();
            }
        }
        if(deg[v] == 1) {
            for(auto x : gr[v]) {
                if(!rem[x]) {
                    leaves[x].push_back(v);
                    q.push({leaves[x].size(), x});
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        gr[i].clear();
        deg[i] = 0;
        leaveCount[i] = 0;
        leaves[i].clear();
        rem[i] = 0;
    }
    cout << ans << "\n";
}
int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
