#include <bits/stdc++.h>
using namespace std;
void com(vector<pair<int, int> > &mas) {
    vector<int> vec, visi;
    for(auto &x : mas) {
        vec.push_back(x.first);
        vec.push_back(x.second);
    }
    sort(vec.begin(), vec.end());
    visi.push_back(vec[0]);
    for(auto &x : vec) {
        if(visi.back() != x) visi.push_back(x);
    }
    
    for(auto &x : mas) {
        x.first = lower_bound(visi.begin(), visi.end(), x.first) - visi.begin();
        x.second = lower_bound(visi.begin(), visi.end(), x.second) - visi.begin();
    }

}    
const int dydis = 5e5 + 1;
int val[dydis];
int pref[dydis] = {};
int prf[dydis] = {};
int kek[dydis] = {};
bool has[dydis] = {};
int main () {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<pair<int, int> > mas(n);
        for(auto &x : mas) {
            cin >> x.first >> x.second;
        }
        com(mas);

        int mx = 0;
        bool isNor = 0;
        bool doub = 0;
        for(auto &x : mas){
            mx = max(mx, x.second);
            if(x.first == x.second) {
                if(has[x.first]) doub = 1;
                has[x.first] = 1;
            }else isNor = 1;
            kek[x.first]++;
            kek[x.second]++;
            val[x.first]++;
            val[x.second]--;
        }
        for(int i = 0; i <= mx; i++) {
            pref[i] = val[i];
            if(i != 0) pref[i] += pref[i-1];
        }

/*        cout << "comp mas: \n";
        for(auto x : mas) {
            cout << "[" << x.first << "; " << x.second << "], ";
        }
        cout << endl;
        cout << "pref:\n";
        for(int i = 0; i <= mx; i++) {
            cout << pref[i] << " ";
        }
        cout << endl;*/
        int sm = 0;
        for(int i = 0; i <= mx; i++) {
            sm += (pref[i] == 0);
            prf[i] = pref[i] == 1;
            if(i != 0) prf[i] += prf[i-1];
        }
        int ans = sm-1;
        if(doub) ans++;
        for(auto x : mas) {
            int sitas = sm;
            if(x.first == x.second) {
                continue;
            }
            int vienetu = prf[x.second-1];
            vienetu -= prf[x.first];
            sitas += vienetu;
            
            if(kek[x.first] > 1 && pref[x.first] == 1) {
                sitas++;
            }
            
            if(kek[x.second] == 1 && pref[x.second] == 0) {
                sitas--;
            }

            ans = max(ans, sitas);
       //     cout << "jei panaikinu [" << x.first << "; " << x.second << "], tai rez = " << sitas << ", cia vienetu = " << vienetu << ", sm = " << sm << endl;
        }
        cout << ans << "\n";
        
        for(int i = 0; i <= mx; i++) {
            val[i] = 0;
            kek[i] = 0;
            has[i] = 0;
        }
    }
    return 0;
}
