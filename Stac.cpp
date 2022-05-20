#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
using namespace std;
const int dydis = 1e3 + 10;
char mas[dydis][dydis];
int r[dydis][dydis];
int n, m;
set<pair<int, int> > setas[dydis];
multiset<int> dydziai;
vector<pair<int, pair<int, int> > > vec;
void idek(int s, int L, int R){
    if(L > R) return ;
    setas[s].insert({L, R});
    dydziai.insert(R - L + 1);
}
void ismesk(int x){
    while(vec.size() && vec.back().first <= x){
        int e = vec.back().second.first;
        int s = vec.back().second.second;
        vec.pop_back();
        auto kur = setas[s].lower_bound({e, -1});
        if(kur == setas[s].end()) kur--;
        if(kur->first > e){
            kur--; 
        }
        int L = kur->first;
        int R = kur->second;
        dydziai.erase(dydziai.find(R-L+1));
        setas[s].erase({L, R});
        idek(s, L, e-1);
        idek(s, e+1, R);
    }
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char a; cin >> a;
            mas[i][j] = a;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mas[i][j] == '.'){
                r[i][j] = 0;
                continue;
            }
            for(int h = j; h <= m; h++){
                if(h == m || mas[i][h] == '.'){
                    for(int k = j; k < h; k++){
                        r[i][k] = h - k;
                        vec.push_back({r[i][k], {i, k}});
                    }
                    j = h-1;
                    break;
                }
            }
        }
    }
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    for(int j = 0; j < m; j++){
        for(int i = 0; i < n; i++){
            if(mas[i][j] == '.') continue;
            for(int h = i; h <= n; h++){
                if(h == n || mas[h][j] == '.'){
                    setas[j].insert({i, h-1});
                    dydziai.insert(h-i);
                    i = h - 1;
                    break;                    
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ismesk(i-1);
        int did = 0;
        if(dydziai.size() != 0) did = *dydziai.rbegin();
        ans = max(ans, did * i);
    }
    cout << ans;
    return 0;
}

