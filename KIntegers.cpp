#include <bits/stdc++.h>
using namespace std;
struct tree1 {
    vector<int> l, r;
    vector<long long> val;
    vector<int> kek;
    int n;
    int dbInd = 0;
    void build(int v) {
        if(v >= n) {
            l[v] = r[v] = dbInd++;
        }else {
            build(v*2);
            build(v*2+1);
            l[v] = l[v*2];
            r[v] = r[v*2+1];
        }
    }
    tree1(int dd) {
        n = dd;
        l.resize(2*n);
        r.resize(2*n);
        val.resize(2*n);
        kek.resize(2*n);
        build(1);
    }
    long long getSum(int v, int L, int R) {
        if(L <= l[v] && r[v] <= R){
            return val[v];
        }else if(L > r[v] || R < l[v]){
            return 0;
        }else {
            return getSum(v*2, L, R) + getSum(v*2+1, L, R);
        }
    }
    int getKek(int v, int L, int R) {
        if(L <= l[v] && r[v] <= R){
            return kek[v];
        }else if(L > r[v] || R < l[v]){
            return 0;
        }else {
            return getKek(v*2, L, R) + getKek(v*2+1, L, R);
        }
    }
    void change(int v, int L, int R, int x, int y) {
         if(L <= l[v] && r[v] <= R){
            val[v] = x;
            kek[v] = y;
         }else if(L > r[v] || R < l[v]){
            return;
        }else {
            change(v*2, L, R, x, y);
            change(v*2+1, L, R, x, y);
            val[v] = val[v*2] + val[v*2+1];
            kek[v] = kek[v*2] + kek[v*2+1];
        }
    }
    int getKel(int v, int kel) {    // reikia rasti i-aji elementa
        if(l[v] == r[v]) return l[v];
        if(kek[v*2] > kel) {
            return getKel(v*2, kel);
        }else {
            return getKel(v*2+1, kel - kek[v*2]);
        }
    }
};
const int dydis = 2e5 + 10;
tree1 medis(dydis);
tree1 med(dydis);
void idek(int x) {
    medis.change(1, x, x, x, 1);
}
long long getVal(long long x) {
    
    long long kairSum = medis.getSum(1, 0, x);
    int kekKair = medis.getKek(1, 0, x);

    long long desnSum = medis.getSum(1, x+1, dydis-1);
    int kekDesn = medis.getKek(1, x+1, dydis-1);

    long long rez = (x * kekKair - kairSum) + (desnSum - x * kekDesn);
    
  //  cout << "x = " << x << ", kairSum = " << kairSum << ", kekKair = " << kekKair << ",   desnSum = " << desnSum << ", kekDesn = " << kekDesn << endl;

    return rez;
}

long long calcJei (int kur, long long kaireje, long long desineje) {
    long long ret = getVal(kur);
//    cout << "kalkuliuoju, kas butu, jei reiktu visiems susirinkti i " << kur << ", tai kaireje butu " << kaireje <<", desineje - " << desineje << endl;
    ret -= kaireje * (kaireje+1) / 2ll;
    ret -= desineje * (desineje+1) / 2ll;
    //cout << "ret = " << ret << endl << endl;
    return ret;
}

int n;

long long inv[dydis] = {};
int kur[dydis] = {};
vector<int> mas;
int main () {
    cin >> n;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    
    int ind = 0;
    for(auto &x : mas) {
        x--;
        kur[x] = ind++;
    }

    long long viso = 0;
    for(int i = 0; i < n; i++) {
        viso += med.getSum(1, kur[i], n-1);
        med.change(1, kur[i], kur[i], 1, 1);
        inv[i] = viso;
    }

    for(int i = 0; i < n; i++) {
        idek(kur[i]);
        long long ats = 0;
        if(i % 2 == 0) {
            ats = calcJei(medis.getKel(1, i / 2), i / 2, i / 2);
        }else {
            ats = max(ats, calcJei(medis.getKel(1, i/2), i / 2, i/2+1));
            ats = max(ats, calcJei(medis.getKel(1, i/2+1), i / 2+1, i/2));
        }
        ats += inv[i];
        cout << ats << " ";
    }


    return 0;
}
