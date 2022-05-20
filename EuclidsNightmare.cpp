#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9 + 7;
const int dydis = 5e5 + 10;
long long pw[dydis] = {0};
int n, m;
int tevas[dydis] = {0};
int tevas2[dydis] = {0};
int kek[dydis] = {0};
bool sust[dydis] = {0};
int findP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = findP(tevas[v]);
}
int findP2(int v){
    if(tevas2[v] == v) return v;
    return tevas2[v] = findP2(tevas2[v]);   
}
vector<pair<int, pair<int, int> > > brn[dydis];
vector<pair<int, int> > edges;
vector<int> answer;
void conn(int a, int b){
    a = findP(a);
    b = findP(b);
    if(a == b) return;
    kek[b] += kek[a];
    kek[a] = 0;
    tevas[a] = b;
}
void conn2(int a, int b){
    a = findP2(a);
    b = findP2(b);
    if(a == b) return;
    sust[b] = sust[a] || sust[b];
    tevas2[a] = b;
}
int main(){
    for(int i = 0; i < dydis; i++){
        kek[i] = 1;
        tevas[i] = i;
        tevas2[i] = i;
    }
    pw[0] = 1;
    for(int i = 1; i <dydis; i++) pw[i] = pw[i-1] * 2ll % mod;
    cin >> m >> n;

    for(int i = 0; i < m; i++){
        int k; cin >> k;
        if(k == 1){
            int a; cin >> a; a--;
            edges.push_back({a, a});
        }else{
            int a, b; cin >> a >> b; a--; b--;
            edges.push_back({a, b});
            conn(a, b);
        }
    }
    int ind =0;
    for(auto x : edges){
       brn[findP(x.first)].push_back({ind++, x}); 
    }
    long long ans = 1;
    for(int i = 0; i < n; i++){
        if(tevas[i] != i) continue;
        if(brn[i].size() == 0) continue;
        bool don = 0;
        for(auto x : brn[i]){
            auto y = x.second;
            if(y.first == y.second){
                if(!don){
                    answer.push_back(x.first);
                    don = 1;
                    sust[findP2(y.first)] = 1;
                }else{
                    if(!sust[findP2(y.second)]){
                        answer.push_back(x.first);
                        sust[findP2(y.second)] = 1;
                    }
                }
            }else{
                if(findP2(y.first) != findP2(y.second)){
                    if(!sust[findP2(y.first)] || !sust[findP2(y.second)]){
       //                 sust[y.first] = sust[y.second] = 1;
                        conn2(y.first, y.second);
                        answer.push_back(x.first);
                    }
                }else{
                }
            }
        }
        ans = (ans * (pw[kek[i] + don - 1]))%mod;
    }
    sort(answer.begin(), answer.end());
    cout << ans << " " << answer.size() << "\n";
    for(auto x : answer){
        cout << x+1 << " ";
    }
    return 0;
}
