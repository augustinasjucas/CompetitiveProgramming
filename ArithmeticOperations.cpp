#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
const int dd = 32000000;
int n;
vector<int> mas, vec;
int sq;

int cnt[dd*2+1] = {};
vector<long long> visi[dydis*2+10];
int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    vec = mas;

    sq = sqrt(dydis);
    
    int mx = 0;

    for(int h = 0; h <= sq; h++){
        for(auto x : vec) {
            cnt[x+dd]++;
            mx = max(mx, cnt[x+dd]);
        }
        for(auto x : vec) {
            cnt[x+dd] = 0;
        } 
        for(int i = 0; i < n; i++) {
            vec[i] -= i;
        }
    }
    for(int i = 0; i <= 100000; i++) {
        mx = max(mx, cnt[i]);
        cnt[i] = 0;
    }
    vec = mas;
    for(int h = 0; h <= sq; h++){
        for(auto x : vec) {
            cnt[x+dd]++;
            mx = max(mx, cnt[x+dd]);
        }
        for(auto x : vec) {
            cnt[x+dd] = 0;
        } 
        for(int i = 0; i < n; i++) {
            vec[i] += i;
        }
    }
    vector<int> had;
    for(int i = 0; i < n; i++) {
        vector<pair<int, long long> > mano;
        for(int j = max(0, i-sq); j < min(n, i+sq+3); j++) {
            if(i == j) continue;

            int skait = mas[j] - mas[i];
            int vard = j-i;
            
            if(skait % vard != 0) continue;
            int k = skait / vard;
            if(abs(k) <= sq) continue;

            long long b = mas[i] - 1ll * k * i;
            mano.push_back({k, b});
        }
        sort(mano.begin(), mano.end());
//        cout << i << "-ajam tinka: ";
        for(int i = 0; i < mano.size(); i++) {
            if(i == 0 || mano[i] != mano[i-1]) {
//                cout << mano[i].first << "x + " << mano[i].second << ",   ";
                visi[mano[i].first+dydis].push_back(mano[i].second);
            }
        }
//        cout << endl;

    }
    for(int i = -100000; i <= 100000; i++) {
        vector<long long> &vec = visi[i+dydis];
        sort(vec.begin(), vec.end());
        for(int i = 0; i < vec.size(); i++) {
            for(int j = i+1; j <= vec.size(); j++) {
                if(j == vec.size() || vec[i] != vec[j]) {
                    mx = max(mx, j-i);
                    i = j-1;
                    break;
                }
            }
        }
    }
    cout << n-mx;
    return 0;
}
