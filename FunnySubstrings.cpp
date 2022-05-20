#include <bits/stdc++.h>
using namespace std;
map<string, pair<long long, string> > mapas;
long long calc(string a){
    int ans = 0;
    for(int i = 0; i+3 < a.size(); i++){
        if(a[i] == 'h' && a[i+1] == 'a' && a[i+2] == 'h' && a[i+3] == 'a') ans++;
    }
    return ans;
}
string minimize(string &a, string &b){
    string ret = a + b;
    if(ret.size() > 8){
        ret = ret.substr(0, 4) + ret.substr(ret.size()-4, 4);
    }
    return ret;
}
long long conn(string &a, string &b){
    int ret = 0;
    int n = a.size();
    int m = b.size();
    if(n >= 3 && m >= 1) ret += (a[n-3] == 'h') && (a[n-2] == 'a') && (a[n-1] == 'h') && (b[0] == 'a');
    if(n >= 2 && m >= 2) ret += (a[n-2] == 'h') && (a[n-1] == 'a') && (b[0] == 'h') && (b[1] == 'a');
    if(n >= 1 && m >= 3) ret += (a[n-1] == 'h') && (b[0] == 'a') && (b[1] == 'h') && (b[2] == 'a');
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        mapas.clear();
        long long ans = 0 ;
        for(int i = 0; i < n; i++){
            string var, a; 
            cin >> var >> a;
            if(a == ":="){
                string x; cin >> x;
                mapas[var] = {calc(x), x};
                ans = mapas[var].first;
            }else{
                string b, c, e;
                cin >> b >> e >> c;
                mapas[var] = {mapas[b].first + mapas[c].first + conn(mapas[b].second, mapas[c].second), minimize(mapas[b].second, mapas[c].second)};
                ans = mapas[var].first;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
