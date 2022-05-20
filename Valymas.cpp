#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e4 + 10;
const long long inf = 1e18;
int n, l, t;
int pos[dydis], price[dydis];
long long f(int ind, int isK){
    // is kaires nenuvalyta isK vietu
    if(isK * 2 > t) return inf;
    cout << "f(" << ind << "; " << isK << ")\n";
    int liko = t - isK*2;
    long long kain = 1ll * price[ind] * isK * 2ll;
    cout << "f( " << ind << ", " << isK << ") kaina =  " << kain << endl;
    if(ind == n-1){
        if((l-pos[ind]) * 2 > liko) return inf;
        else {
            cout << "f( " << ind << ", " << isK << " = " << kain + 1ll * (l-pos[ind]) * 2 * price[ind] << "\n";
            return kain + 1ll * (l-pos[ind]) * 2 * price[ind];
        }
    }

    int db = ind+1;
    long long ret = inf;
    for(int i = 0; i < min(liko/2, l); i++) { // valysiu iki pos[ind] + i
        if(i + pos[ind] > pos[db]){
            db++;
        }
        if(db == n){ // reiks man iki galo varyti
            if(2ll * (l - pos[ind]) < liko) break;
            ret = min(ret, kain + 2ll * (l - pos[ind]) * price[ind]);
            break;
        }else{
            cout << "kai i = " << i << ", soksiu i f(" << db << ", " << pos[db] - (i + pos[ind] + 1) << ", pridedamas " << kain + 2ll * i * price[ind]<< endl;
            ret = min(ret, kain + 2ll * i * price[ind] + f(db, pos[db] - (i + pos[ind] + 1)));
        }
        
    }
    return ret;
    

}
int main(){
    cin >> n >> l >> t;
    for(int i = 0; i < n; i++){
        cin >> pos[i] >> price[i];
    }
        
    long long ans = 0;
    ans = f(0, pos[0]);
    cout << ans;

    return 0;
}
