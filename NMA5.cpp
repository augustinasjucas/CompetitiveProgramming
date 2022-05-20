#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<int> primes;
int ind[100] = {};
int dbInd = 0;
void gen(){
    for(int i = 2; i <= 90; i++) {
        bool is = 1;
        for(auto &x : primes) if(i % x == 0) is = 0;
        if(is) {
            primes.push_back(i);
            ind[i] = dbInd++;
        }
        
    }
//    for(auto x : primes) cout << x << " ";
//    cout << endl;
}
__int128_t skaicius = 1;
vector<int> cnt(100, 0);
const long long inf = 1000000000000000000ll;
__int128_t sand = 1;
vector<long long> vec;
void darom(int ind, int n) {
    if(sand > inf) return ;
    if(sand * sand > skaicius) return ;
    if(ind == n) {
        vec.push_back(sand);
        return;
    }
    darom(ind+1, n);
    for(int i = 0; i < cnt[ind]; i++) {
        sand *= primes[ind];
        darom(ind+1, n);
    }
    for(int i = 0; i < cnt[ind] ; i++) sand /= primes[ind];

}

vector<long long> gener(int l, int r){
    vec.clear();
    sand = 1;
    darom(l, r+1);
    return vec;
}
long long dumb(){
    __int128_t ats = 0;
    for(__int128_t i = 1; i*i <= skaicius; i++) {
        if(skaicius % i == 0) ats = i;
    }
    return ats;
}
int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    gen();
    int t; cin >> t;
    while(t--) {
        skaicius = 1;
        for(auto &x : cnt) x = 0;
        int n; cin >> n;
        for(int i = 0; i < n; i++) {
            int a; cin >> a;
            skaicius *= a;
            for(int j = 0; j < primes.size(); j++) {
                while(a % primes[j] == 0) {
                    cnt[j]++;
                    a /= primes[j];
                }
            }
        }
        long long dals = 1;
        int r = primes.size()-1;
        for(int i = 0; i < primes.size(); i++) {
            dals *= cnt[i] + 1;
            if(dals > 50) {
                r = i;
                break;
            }
        }
        vector<long long> a = gener(0, r+1);
        vector<long long> b = gener(r+1, primes.size());
        

        cout << "a: "; for(auto &x : a) cout << x << " "; cout << endl;
        cout << "b: "; for(auto &x : b) cout << x << " "; cout << endl;
        
//        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        __int128_t X, B;
        long long ats = 0;
        for(auto &x : a) {
            int l = 0; int r = b.size()-1, mid;
            long long ans = 0;
            while(l <= r) {
                mid = (l + r) / 2;
                X = x; B = b[mid];
                if(X*X*B*B > skaicius) {
                    r = mid-1;
                }else {
                    ans = x * b[mid];
                    l = mid+1;
                }
            }
            ats = max(ats, ans);
        }
        cout << ats;
    }
    return 0;
}
