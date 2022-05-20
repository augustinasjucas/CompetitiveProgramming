#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> > mas;
__int128_t mx = 1000000000000000000;
int r, s, m, d, n;
bool dont[100][100] = {0};
vector<int> ing[1011];
int brands[1011] = {0};
int main(){ 
    cin >> r >> s >> m >> d >> n;    
    for(int i = 0; i < r; i++) cin >> brands[i+1];
    for(int i = 0; i < s+m+d; i++){
        int k; cin >> k; 
        for(int j = 0; j < k; j++){
            int a; cin >> a;
            ing[i].push_back(a);
        }
    }
    for(int i = 0; i < n; i++){
        int a, b; cin >> a >> b; a--; b--; dont[a][b] = dont[b][a] = 1;
    }
    __int128_t ans = 0;
    bool galima = 1;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < m; j++){
            for(int h = 0; h < d; h++){
                int ind1 = i;
                int ind2 = s + j;
                int ind3 = s + m + h;
                if(dont[ind1][ind2] || dont[ind1][ind3] || dont[ind2][ind3]) continue;
                set<int> setas;
                for(auto x : ing[ind1]) setas.insert(x);
                for(auto x : ing[ind2]) setas.insert(x);
                for(auto x : ing[ind3]) setas.insert(x);
                __int128_t sitas = 1;
                for(auto x : setas) {
                    sitas = sitas * brands[x];
                    if(sitas > mx) galima = 0;
                }
                ans += sitas;
                if(ans > mx) galima = 0;
            }
        }
    }
    if(!galima){
        cout << "too many";
    }else cout << (long long) ans;
    return 0;
}
