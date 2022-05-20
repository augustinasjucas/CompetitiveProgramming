#include <bits/stdc++.h>
using namespace std;
int n, m;
const int dd = 100;
vector<int> gr[dd];
bitset<dd> bt;
bool is[dd][dd] = {};
int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
        is[a][b] = is[b][a] = 1;
    }
    vector<int> p;
    for(int i = 0; i < n; i++) p.push_back(i);
    do {
    //    cout << "perm: "; for(auto x : p) cout << x+1 << " ";
//       cout << endl;

        bool has = 0; int kel = 0;
        bool galima = 1;
        for(int i = 1; i < n; i++) {
            if(!is[p[i]][p[i-1]]) break;
            has = 0;
  //          cout << "ziuri i " << p[i]+1 << ": ";
            for(auto x : gr[p[i]]) {
//                cout << x+1 << ", ";
                if(bt[x] && x != p[i-1]){
                    galima = 0;
                    break;
                }
                if(x == p[0]) {
                    has = 1;
                }
            }
//            cout << endl;
            if(!galima) break;
            if(has && i == 2) break;
            if(has && i >= 3) {
                for(int j = 0; j <= i; j++) cout << p[j]+1 << " ";
                return 0;
            }
            bt[p[i]] = 1;
        }
        for(int i = 0; i < 10; i++) bt[i] = 0;
    }while(next_permutation(p.begin(), p.end()));
    cout << "no";
    return 0;
}

