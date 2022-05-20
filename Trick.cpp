#include <bits/stdc++.h>
using namespace std;
int f(int a, int b) {
    return a ^ b;
}
bool galima (vector<int> mas) {
    int visi = 0;
    for(auto &x : mas) visi ^= x;
    visi %= mas.size() * 2;
    for(int i = 0; i < mas.size(); i++) {
        for(int j = i+1; j < mas.size(); j++) {
            if(f(mas[i], mas[j]) == visi) {
                cout <<"f(" << mas[i] << ", " << mas[j] << ")" << endl;
                return true;
            }
        }
    }
    return false;
}
int main(){
    int n = 3;
    while(true) {
        vector<int> ms (2*n+1);
        for(int i = 0; i <= 2*n; i++) {
            ms[i] = i;
        }
        shuffle(ms.begin(), ms.end(), default_random_engine(rand()));
        ms.resize(n);
        if(!galima(ms)) {
            cout << "negalima!\n";
            for(auto x : ms) cout << x << " ";
            cout << endl;
            int xr = 0;
            for(auto x : ms) xr ^= x;
            xr %= ms.size() * 2;
            cout << "tada f(a, b) nebus lygus " << xr;
            return 0;
        }


    }
/*    int mx = 0;
    const int sz = 8;
    for(int i = 0; i < (1 << (2*sz+1)); i++) {
        if(__builtin_popcount(i) != sz) continue;
        int xr = 0;
        for(int j = 0; j <= 2*sz; j++) {
            if(i & (1 << j)) xr ^= j;
        }
        if(xr > mx) {
            mx = xr;
            cout << mx << ":\n";
            for(int j = 0; j <= 2*sz; j++) {
                if(i & (1 << j)) cout << j << " ";
            }
            cout << endl << endl;
        }
    }
  */  
    return 0;
}
