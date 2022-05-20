#include <bits/stdc++.h>
using namespace std;
int n, m;
const int dydis = 2e5  +100;
pair<int, int> kur[dydis];
pair<int, int> turiBut(int kas){
    if(kas > n*m) return {-1, -1};
    return kur[kas];
}
vector<int> col[dydis];
int main(){
    cin >> n >> m;
    int ind = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            kur[ind++] = {i, j};
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int a; cin >> a;
            col[j].push_back(a);
        }
    }
    if(n == 1 && m == 1){
        if(col[0][0] == 1) cout << 0;
        else cout << 1;
        return 0;
    }
    long long ans = 0;
    int pos[n];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) pos[j] = 0;
        for(int j = 0; j < n; j++){
            int yra = col[i][j];
            pair<int, int> turiButi = turiBut(yra); // kelintoj eilutej
            if(turiButi.second == i){
                int e = turiButi.first;
                int reiks = abs(e-j);
                if(e > j) reiks = j+n-e;
                pos[reiks]++;
            }
        }
        int sitas = n+1;
        for(int j = 0; j < n; j++){
            sitas = min(sitas, j + n-pos[j]);
        }
        ans += sitas;
    }
    cout << ans;
    return 0;
}
