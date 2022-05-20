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

    }
    return 0;
}
