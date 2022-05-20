#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int> > mas;
int n;
long long fak [51];
const long long mod = 1e9 + 7;
const int dydis = 42;
int dp[dydis][dydis][dydis][dydis] = {0}; // convexa sudaro i, j, k, o jau paimta h, kiek budu tokia situacija pasiekt?
long long sign (pair<int, int> p1, pair<int, int> p2, pair<int, int> p3){
    return 1ll * (p1.first - p3.first) * 1ll * (p2.second - p3.second) - 1ll * (p2.first - p3.first) * 1ll * (p1.second - p3.second);
}

bool incl (pair<int, int> pt, pair<int, int> v1, pair<int, int> v2, pair<int, int> v3){
    long long d1, d2, d3;
    bool neg, pos;
    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);
    neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(neg && pos);
}
int kek(int i1, int i2, int i3){ // kek tasku yra sitame trikampyje
    int ret = 0;
    for(int i = 0; i < n; i++){
        if(i1 == i || i2 == i || i3 == i) continue;
        if(incl(mas[i], mas[i1], mas[i2], mas[i3])){
            ret++;
        }
    }
    return ret;
}
bool comp(pair<pair<int, int>, int> &a, pair<pair<int, int>, int> &b){
    return a.first.first * (-b.first.second) + a.first.second * b.first.first > 0;
}
int vid(int k, int i1, int i2, int i3){
    vector<pair<pair<int, int>, int> > vec;
    vec.push_back({{mas[i1].first-mas[k].first, mas[i1].second-mas[k].second}, i1});
    vec.push_back({{mas[i2].first-mas[k].first, mas[i2].second-mas[k].second}, i2});
    vec.push_back({{mas[i3].first-mas[k].first, mas[i3].second-mas[k].second}, i3});
    sort(vec.begin(), vec.end(), comp);
    return vec[1].second;
}
pair<long double, long double> krt(pair<int, int> t1, pair<int, int> t2, pair<int, int> t3, pair<int, int> t4){
    // kur kertasi tieses t1-t2, t3-t4?
    long double A1 = t1.second-t2.second;
    long double B1 = t2.first-t1.first;
    long double C1 = 1ll*t1.first*t2.second - 1ll*t1.second*t2.first;

    long double A2 = t3.second-t4.second;
    long double B2 = t4.first-t3.first;
    long double C2 = 1ll*t3.first*t4.second - 1ll*t3.second*t4.first;

    long double y = (C1*A2 - A1*C2) / (A1*B2 - A2*B1);
    long double x = (B1*C2 - B2*C1) / (B2*A1 - B1*A2);
    return make_pair(x, y);
}
long double dst(pair<long double, long double> a, pair<long double, long double> b){
    return (a.first-b.first) * (a.first-b.first) + (a.second-b.second) * (a.second-b.second);
}
int main(){
    fak[0] = 1;
    for(int i = 1; i <= n; i++) fak[i] = fak[i-1] * 1ll * i % mod;
    cin >> n;
    mas.resize(n);
    for(int i = 0; i < n; i++){
        cin >> mas[i].first >> mas[i].second;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            for(int h = j+1; h < n; h++){
                dp[i][j][h][3] = 3;
            }
        }
    }
    long long ans = 0;
    for(int l = 3; l <= n; l++){ // jau paimta l tasku
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                for(int h = j+1; h < n; h++){
                    // paimta l tasku, convexa sudaro i, j, h
                    if(dp[i][j][h][l] == 0) continue;
                    int viduje = kek(i, j, h);
                    long long liko = viduje-(l-3);
                    if(liko > 0){ // dar galiu taskeliu paimt
                        dp[i][j][h][l+1] = (dp[i][j][h][l] * liko % mod + dp[i][j][h][l+1]) % mod;
                    }
                    if(l == n) ans = (ans + dp[i][j][h][l] + ans) % mod;
                    for(int k = 0; k < n; k++) {
                        if(k == i || k == j || k == h) continue;
                        if(incl(mas[k], mas[i], mas[j], mas[h])) continue;
                        // ar sitas taskas nekerta briaunos?
                        int vidurinis = vid(k, i, j, h);
                        int ne1 = -1;
                        int ne2 = -1;
                        if(i != vidurinis)
                            ne1 = i;
                        if(j != vidurinis){
                            if(ne1 == -1) ne1 = j;
                            else ne2 = j;
                        }
                        if(h != vidurinis)
                            ne2 = h;

                        auto kur = krt(mas[k], mas[vidurinis], mas[ne1], mas[ne2]);
//                        cout << "tiese is (" << mas[k].first << ", " << mas[k].second << ")-("<< mas[vidurinis].first << ", " << mas[vidurinis].second << ") kertasi su (" << mas[ne1].first << ", " << mas[ne1].second << ")-" << mas[ne2].first << ", " << mas[ne2].second << ") taske (" << kur.first << ", " << kur.second << ")\n";
//                        cout << "kai trikampis yra (" <<  mas[i].first << ", " << mas[i].second << "), (" << mas[j].first << ", " << mas[j].second << "), (" << mas[h].first << ", " << mas[h].second << "), o taskas yra (" << mas[k].first << ", " << mas[k].second << "), tai: ";
                        if(dst(kur, make_pair((long double)mas[k].first, (long double)mas[k].second)) < dst(make_pair(mas[vidurinis].first * 1.0, mas[vidurinis].second * 1.0), make_pair((long double)mas[k].first * 1.0, (long double)mas[k].second * 1.0))){ // uzdengia
//                            cout << "taskas nemato visu nodu!" << endl << endl;
                            continue;
                        }
//                        cout << "taskas mato visus nodus!\n\n";

                        vector<int> liks = {ne1, ne2, k};
                        sort(liks.begin(), liks.end());
                        dp[liks[0]][liks[1]][liks[2]][l+1] = (dp[liks[0]][liks[1]][liks[2]][l+1] + dp[i][j][h][l]) % mod;
                    }


                }
            }
        }
    }
    cout << ans * 2ll % mod;
    return 0;
}
