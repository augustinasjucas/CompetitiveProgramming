#include <bits/stdc++.h>
using namespace std;
int n, m, k;
const int dydis = 3e5 + 19;
void del(multiset<long long> &a, long long b){
    auto kur = a.find(b);
    if(kur != a.end()) a.erase(kur);
    else {
    }
}
multiset<long long> vals[11];
vector<long long> pref[11];
vector<long long> kas[11];
vector<long long> mas;
long long kair[11] = {0};
long long kel[11] = {0};
long long minu[dydis] = {0};
long long ideta[11][dydis];
int main(){
    cin >> n >> m >> k;
    mas.resize(n);
    for(int i = 0; i < n; i++){
         cin >> mas[i];
    }
    for(int i = 0; i < m; i++){
        pref[i].resize(n, 0);
        kas[i].resize(n);
        long long cur = 0;
        for(int j = i; j < n; j++){
            if((j) % m == i) cur++;
            pref[i][j] += mas[j];
            kas[i][j] = mas[j] ;
            if(j != 0) pref[i][j] += pref[i][j-1];
            vals[i].insert(pref[i][j] - cur*k);
            ideta[i][j] = pref[i][j] - cur*k;
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        int kur = i%m;
        while(kair[kur] != i){
            del(vals[kur], ideta[kur][kair[kur]]);
            minu[kur] += kas[kur][kair[kur]];
            kair[kur]++;
        }
        ans = max(ans, (*vals[kur].rbegin() - minu[kur]) + k * kel[kur]);
        kel[kur]++;
    }
    cout << ans;
    return 0;
}
