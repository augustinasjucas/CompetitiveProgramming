#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<long double> probs;
const int dydis = 68;
long double dp[dydis][dydis][dydis];
long double sm = 0;
int n;
int vnt = 0;
long double ans(int turiuVien, int siekiuVien, int turiuKeitimu){
    if(turiuVien < 0 || turiuVien > n) return 0;
//    cout << turiuVien << ", " << siekiuVien << "" << endl;
    if(dp[turiuVien][siekiuVien][turiuKeitimu] != -1) return dp[turiuVien][siekiuVien][turiuKeitimu];
    // Kokia tikimybe, kad turedamas 'turiuVien' vienetu, per 'turiuKeitimu' pakeitimu pasieksiu siekiuVien vienetu?
    if(turiuKeitimu == 0){
        return turiuVien == siekiuVien;
    }
    long double pataikysiuIVien = ((long double)turiuVien) / ((long double) n);
    long double pataikysiuINuli = 1.0 - pataikysiuIVien;
    return dp[turiuVien][siekiuVien][turiuKeitimu] = pataikysiuIVien * ans(turiuVien-1, siekiuVien, turiuKeitimu-1) + pataikysiuINuli * ans(turiuVien+1, siekiuVien, turiuKeitimu-1);
}

vector<long double> daryk(vector<long double> &prm){
    vector<long double> ret(prm.size(), 0);
    int vnt, nul, busvnt, busnul;
    long double tik;
    for(int i = 0; i <= n; i++){ // jei yra i vienetuku pirmame
        vnt = i;
        nul = n-i;
        for(int j = 0; j <= n; j++){ // j bituku bus pakeisti
            for(int h = -vnt; h <= min(nul, j); h++) { // is tu j pakeitimu, h taps vienetais
                busvnt = h + vnt;
                busnul = n - busvnt;
                tik = ans(vnt, busvnt, j); // tikimybe, kad turint (vnt, nul), ir random pakeitus j, gausim (busvnt, busnl)
                ret[busvnt] += prm[i] * probs[j] * tik;
            }
        }
    }
    return ret;
}
int main(){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < dydis; i++){
        for(int j = 0; j < dydis; j++){
            for(int h = 0; h < dydis; h++){
                dp[i][j][h] = -1;
            }
        }
    }
    string a; cin >> a;
    for(auto x : a) vnt += x == '1';
    n = a.size();
    probs.resize(n+1);
    for(int i = 1; i <= n; i++){
        cin >> probs[i];
        sm += probs[i];
    }
    probs[0] = 1.0 - sm;
    int k; cin >> k;
    vector<long double> sans(n+1, 0);
    sans[vnt] = 1;
    for(int i = 0; i < k; i++){
        sans = daryk(sans);
        if(i < 100) continue;
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int sk =  std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        if((vnt == 0 || (i % vnt == 0)) && sk >= 500){
            break;
        }
    }
    for(auto x : sans){
        cout << setprecision(100) << x << "\n";
    }
    

    return 0;
}
