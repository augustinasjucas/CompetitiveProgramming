#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<long double> probs;
const int dydis = 68;
long double dp[dydis][dydis][dydis];
long double sm = 0;
int n;
int vnt = 0;
long double ans(int turiuVien, int siekiuVien, int turiuKeitimu) {
    if (turiuVien < 0 || turiuVien > n) {
        return 0;
    }
    if (dp[turiuVien][siekiuVien][turiuKeitimu] != -1) {
        return dp[turiuVien][siekiuVien][turiuKeitimu];
    }
    if (turiuKeitimu == 0) {
        return turiuVien == siekiuVien;
    }

    long double pataikysiuIVien = ((long double)turiuVien) / ((long double) n);
    long double pataikysiuINuli = 1.0 - pataikysiuIVien;
    return dp[turiuVien][siekiuVien][turiuKeitimu] = pataikysiuIVien * ans(turiuVien - 1, siekiuVien,
            turiuKeitimu - 1) + pataikysiuINuli * ans(turiuVien + 1, siekiuVien, turiuKeitimu - 1);
}

vector<vector<long double> > daug(vector<vector<long double> > &a, vector<vector<long double> > &b){
    vector<vector<long double> > ret(a.size());
    for(auto &x : ret) x.resize(b[0].size());
    for(auto &x : ret) for(auto &y : x) y = 0;
    for(int i = 0; i < ret.size(); i++){
        for(int j = 0; j < ret[i].size(); j++){
            for(int h = 0; h < a.size(); h++){
                ret[i][j] += a[i][h] * b[h][j];
            }
        }
    }
    return ret;
}
auto kelk(vector<vector<long double> > a, int kek){
    if(kek == 1){
        return a;
    }
    auto klk = kelk(a, kek/2);
    klk = daug(klk, klk);
    if(kek & 1){
        klk = daug(klk, a);
    }
    return klk;
}
int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < dydis; i++) {
        for (int j = 0; j < dydis; j++) {
            for (int h = 0; h < dydis; h++) {
                dp[i][j][h] = -1;
            }
        }
    }

    string a;
    cin >> a;

    for (auto x : a) {
        vnt += x == '1';
    }

    n = a.size();
    probs.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> probs[i];
        sm += probs[i];
    }

    probs[0] = 1.0 - sm;
    int k;
    cin >> k;
    vector<vector<long double> > dg;
    dg.resize(n+1);
    for(auto &x : dg) x.resize(n+1);
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            dg[j][i] = 0;
            for(int h = 0; h <= n; h++){
                dg[j][i] += probs[h] * ans(j, i, h);
            }
        }
    }
    dg = kelk(dg, k);
    vector<vector<long double> > pr;
    pr.resize(n+1);
    for(auto &x : pr){
        x.resize(n+1);
        for(auto &y : x) y = 0;
    }
    pr[0][vnt] = 1;
    pr = daug(pr, dg); 
    for(int i = 0; i <= n; i++){
        cout << setprecision(100) << pr[0][i] << "\n"; // del viso pikto 100
    }
    return 0;
}
