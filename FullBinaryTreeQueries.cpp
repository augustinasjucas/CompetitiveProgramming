#include <bits/stdc++.h>
using namespace std;
__int128_t shifted[65] = {0};
int lg2(long long a){
    int ret = 0;
    while(a != 0){
        a = a >> 1;
        ret++;
    }
    return ret-1;

}
__int128_t pashiftink(long long ka, long long kur, __int128_t kiek){
    __int128_t ret = 0;
    __int128_t plotis = 1ll << kur;
    kiek = (kiek%plotis + plotis)%plotis;
    ka += kiek;
    ka = ((ka-plotis) % plotis + plotis)%plotis + plotis;
    return ka;
}
void quer(long long a){
    cout << a << " ";
    if(a == 1) return;
    long long lev = lg2(a);
    quer(pashiftink((pashiftink(a, lev, shifted[lev]) >> 1), lev-1, -shifted[lev-1]));
}

int main(){
    int q; cin >> q;
    while(q--){
        int t; cin >> t;
        if(t == 1){
            long long a, b; cin >> a >> b;
            long long auk = lg2(a);
            shifted[auk] = pashiftink(shifted[auk], auk, b);
        }else if(t == 2){
            long long a, b; cin >> a >> b;
            int lev = lg2(a);
            b %= (1ll << lev);
            for(int i = lev; i < 61; i++){
                shifted[i] = pashiftink(shifted[i], i, (__int128_t)b * (1ll << (i-lev)));
            }
        }else if(t == 3){
            long long a; cin >> a;
            quer(a);
            cout << "\n";
//            cout << endl;
        }
    }
    return 0;
}
