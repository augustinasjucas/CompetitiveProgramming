#include <bits/stdc++.h>
using namespace std;
vector<int> gr[51];
bool C[51][51] = {};
int main () {
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        if(a >= 50 || b >= 50) continue;
        gr[a].push_back(b);
        gr[b].push_back(a);
        C[a][b] = C[b][a] = 1;
    }
    n = min(n, 50);
    for(int a = 0; a < n; a++) {
        for(int b = a+1; b < n; b++) {
            for(int c = b+1; c < n; c++) {
                for(int d = c+1; d < n; d++) {
                    for(int e = d+1; e < n; e++) {
                        if(C[a][b] && C[a][c] && C[a][d] && C[a][e] && C[b][c] && C[b][d] && C[b][e] && C[c][d] && C[c][e] && C[d][e]) {
                            cout << a+1 << " " << b+1 << " " << c+1 << " " << d+1 << " " << e+1;
                            return 0;
                        }
                        if(!C[a][b] && !C[a][c] && !C[a][d] && !C[a][e] && !C[b][c] && !C[b][d] && !C[b][e] && !C[c][d] && !C[c][e] && !C[d][e]) {
                            cout << a+1 << " " << b+1 << " " << c+1 << " " << d+1 << " " << e+1;
                            return 0;                           
                        }
                    }
                }
            }
        }
    }
    cout << -1;
    return 0;
}
