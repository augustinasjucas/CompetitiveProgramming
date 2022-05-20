#include <bits/stdc++.h>
using namespace std;
int n;
const int dydis = 3e5 + 10;
vector<pair<int, int> > a, b;
vector<pair<int, int> > des, kair;
int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    b.resize(n);

    for(auto &x : a) cin >> x.first;
    for(auto &x : b) cin >> x.first;
    
    for(int i = 0; i < n; i++) {
        a[i].second = b[i].second = i;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long galiuKairen = 0;
    bool galima = 1;
    for(int i = 0; i < n; i++) {
        int asEsu = a[i].first;
        int reikiaButi = b[i].first;
//        cout << i << "-asis yra " << asEsu << ", o turi buti " << reikiaButi << endl;
        if(asEsu-galiuKairen > reikiaButi) {
            galima = 0;
            break ;
        }
        if(asEsu < reikiaButi) {
            // einu i desine per (reikiaButi-asEsu)
            galiuKairen += reikiaButi - asEsu;
            des.push_back({a[i].second, reikiaButi-asEsu});
        }else if(asEsu > reikiaButi){
            // einu i kaire per (asEsu-reikiaButi)
            galiuKairen -= asEsu - reikiaButi;
            kair.push_back({a[i].second, asEsu-reikiaButi});
        }
        if(galiuKairen < 0) {
            galima = 0;
            break;
        }
    }
    if(galiuKairen != 0) {
        galima = 0;
    }
    if(!galima) {
        cout << "NO";
        return 0;
    }
    vector<pair<pair<int, int>, int> > ans;
    int ind = 0;
    for(auto &x : des) {
 //       cout << "esu x = " << x.first << ", sz = " << x.second << endl;

        while(x.second != 0) {
            if(ind == kair.size()) {
                galima = 0;
                break;
            }
            int tenLiko = kair[ind].second;
            int nuimsiu = min(tenLiko, x.second);
            kair[ind].second -= nuimsiu;
            x.second -= nuimsiu;
            ans.push_back({{x.first, kair[ind].first}, nuimsiu});
            if(kair[ind].second == 0) ind++;
        }
    }
    if(!galima) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    cout << ans.size() << "\n";
    for(auto &x : ans) {
        cout << x.first.first+1 << " " << x.first.second+1 << " " << x.second << "\n";
    } 
    return 0;
}
