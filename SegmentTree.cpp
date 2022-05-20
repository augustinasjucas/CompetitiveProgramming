#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e5 + 10;
int n;
vector<pair<int, pair<int, int> > > mas;
int l[dydis], r[dydis];
string ans = "YES";
set<pair<int, int> > setas;
int tevas[dydis];
int comp;
int fd(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = fd(tevas[v]);
}
void conn(int a, int b){
    a = fd(a);
    b = fd(b);
    if(a == b) return;
    tevas[a] = b;
    comp--;
}
int main(){
    for(int i = 0; i < dydis; i++) tevas[i] = i;
    cin >> n;
    comp = n;
    for(int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        mas.push_back({a, {1, i}});
        mas.push_back({b, {-1, i}});
    }
    int s = 0;
    sort(mas.begin(), mas.end());
    for(int i = 0; i < 2*n; i++){
        if(mas[i].second.first == 1){
            l[mas[i].second.second] = i;
        }
        if(mas[i].second.first == -1){
            r[mas[i].second.second] = i;
        }
    }
    set<pair<int, int> > cur;
    for(auto x : mas){
        int v = x.second.second;
        int pr = x.second.first;
        
        if(pr == 1){ // atidaro
            auto kure = cur.lower_bound({r[v], v});
            for(auto kur = cur.begin();kur != kure; kur++){
                int x = kur->second;
                setas.insert({min(x, v), max(x, v)});
                conn(x, v);
            }
            cur.insert({r[v], v});
        }else{
            cur.erase({r[v], v});
        }
        if(setas.size() > n-1) break;
    }
    if(comp != 1) ans = "NO";
    if(setas.size() != n-1) ans = "NO";
    cout << ans;
    return 0;
}
