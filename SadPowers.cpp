#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
unordered_set<int> kek[61];
__int128_t inf = 1000000000000000010;
long long kelk(long long ka, int kek){
    if(kek == 0) return 1;
    __int128_t sakn = kelk(ka, kek/2);
    sakn *= sakn;
    if(sakn >= inf) return inf;
    if(kek & 1) sakn *= ka;
    if(sakn >= inf) return inf;
    return sakn;
}
long long trauk(long long isKo, int ka){
    //return pow(isKo, (1.0)/ka);

    if(isKo == 0) return 0;
    long long l = pow(isKo, 1.0/((long double)ka))-2, r = pow(isKo, 1.0/((long double)ka))+2, mid; 
    long long ret = 0;
    while(l <= r){
        mid = (r+l)/2;
//        cout << mid << " ^ " << ka << " = " << kelk(mid, ka) << endl;
        if(kelk(mid, ka) <= isKo) {
            ret = max(mid, ret);
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
//    cout << ka << "-oji saknis is " << isKo << " yra " << ret << " vs " << (long long) pow(isKo, (1.0)/ka) << endl;
    return ret;
}
/*long long trauk(long long isKo, long long ka){
//    cout << isKo << " istraukta " << ka << "-oji saknis = " << (long long)pow(isKo, (1.0)/((long double)ka)) << endl;
    return pow(isKo, ((long double)1.0)/((long double)ka));
}*/
long long kekk(long long r, int pw){ // kiek
  //  cout << "kekk [" << 1 << "; " << r << "] " << pw << " reiksmiu yra " << trauk(r, pw) <<endl;
    if(r == 0) return 0;
    return trauk(r, pw)-1;
}

long long kiek(long long l, long long r, int pw ){
    long long ret = kekk(r, pw) - kekk(l-1, pw);
//    cout << "intervale [" << l << "; " << r << "], " << pw << " laipsniu yra " << ret << endl;
//    cout << endl;
    return ret;
}

long long quer(long long l, long long r){
    long long ans = 0;
    for(int i = 1; i <= 4; i++){
        long long st = 0;
        for(auto x : kek[i]){
            ans += (i % 2 == 0 ? 1 : -1) * kiek(l, r, x);
        }
    }
    return ans;
}

void formuok(long long sand, long long ind, int paimta){
    if(ind >= primes.size()){
        if(sand <= 60) kek[paimta].insert(sand);
        return;
    }
    if(sand > 60) return ;
    kek[paimta].insert(sand);
    formuok(sand, ind+1, paimta);
    formuok(sand*primes[ind], ind+1, paimta+1);
}

int main(){
//    cout << (1ll << 59) << endl;
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    formuok(1, 0, 0);
//    cout << "kek: ";
    for(int i = 0; i < 4; i++){
//        cout << i << ": ["; for(auto x : kek[i]) cout << x << " " ; cout << "]\n";
    }
    int q; cin >> q;
    while(q--){
        long long a, b; cin >> a >> b;
        cout << -quer(a, b) + (a == 1)<< "\n";
//        cout << endl;
    }
    return 0;
}
