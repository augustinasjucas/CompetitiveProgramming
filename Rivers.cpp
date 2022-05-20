#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int dydis = 102;
const int dd = 52;
int n, k;
int val[dydis];
int tevas[dydis];
int knTv[dydis];
vector<pair<int, int> > gr[dydis];
vector<int> dp[dydis][dydis] = {}; // atsakymas, jei medi sudaro tik i pomedis ir galiu naudoti j wmilu
int st[dd];
int sum[dydis];
vector<int> add(vector<int> &a, vector<int> &b){
    vector<int> ret(dd, inf);
//    cout << "ADD({"; for(int i = 0; i <= k; i++) cout << a[i] << ", "; cout << "} + {";
//    for(int i = 0; i <= k; i++) cout << b[i] << ", ";  cout << "} = {";
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            if(i + j < ret.size()) ret[i+j] = min(ret[i+j], a[i] + b[j]);
        }
    }
//    for(int i = 0; i <= k; i++) cout << ret[i] << ", ";  cout << "}" << endl << endl;
    return ret;
}
void f(int v, int last){
    if(dp[v][last].size() != 0) return ;
//    cout << "esu " << v << "; " << last << endl;
    int st = 0;
    int cr = v;
    for(int i = 0; i < last; i++){
        st += knTv[cr];
        cr = tevas[cr];
    }
    long long pl = 1ll * st * val[v];
    dp[v][last] = vector<int> (dd, inf);
    vector<int> p1(dd, 0), p2(dd, 0);

    // jei cia nededu wmillo
    for(auto x : gr[v]){
        f(x.first, last+1);
        p1 = add(p1, dp[x.first][last+1]);
    }
    for(auto &x : p1) x += pl;

    // jei cia dedu wmilla
    for(auto x : gr[v]){
        f(x.first, 1);
        p2 = add(p2, dp[x.first][1]);
    }
    
    for(int i = dd-1; i > 0; i--) p2[i] = p2[i-1];
    p2[0] = inf;
    for(int i = 0; i < dd; i++){
        dp[v][last][i] = min(p1[i], p2[i]);
    }
/*    cout << "dp[" << v << "][" << last << "]: "; 
    for(int i = 0; i <= k; i++) cout << i << ": " << dp[v][last][i] << ",  ";
    cout << endl;
    cout << "p1: ";
    for(int i = 0; i <= k; i++) cout << i << ": " << p1[i] << ",  ";
    cout << "\np2: ";
    for(int i = 0; i <= k; i++) cout << i << ": " << p1[i] << ",  ";
    cout << endl << endl;*/


}
int main(){
    cin >> n >> k;
    n++;
    for(int i = 1; i < n; i++){
        int vl, tv, w; cin >> vl >> tv >> w;
        val[i] = vl;
        tevas[i] = tv;
        knTv[i] = w;
        gr[tv].push_back({i, w});
    }
//    cout << "ce "<< endl;
    f(0, 0);
    int ans = inf;
    for(int i = 0; i <= k; i++)  {
        ans = min(ans, dp[0][0][i]);
    }
    cout << ans;
    return 0;
}
