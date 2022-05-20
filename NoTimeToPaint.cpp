#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int pref[dydis], suf[dydis] = {0};
int n, m;
string a;
int last[26] = {0};
int main(){
    cin >> n >> m >> a;
    n = a.size();
    pref[0] = 1;
    for(int i = 0; i < 26; i++) last[i] = -1;
    last[a[0]-'A'] = 0;
    for(int i = 1; i < n; i++){
        int st = a[i]-'A';
        int vl = 0;
        bool reiksNaujo = (last[st] == -1);
        for(int j = 0; j < st; j++){
            if(last[j] > last[st]) reiksNaujo = 1;
        }
        if(reiksNaujo){
            vl = 1;
            last[st] = i;
        }
        last[st] = i;
        pref[i] = pref[i-1] + vl;
    }
    suf[n-1] = 1;
    for(int i = 0; i < 26; i++) last[i] = n;
    last[a[n-1]-'A'] = n-1;
    for(int i = n-2; i > -1; i--){
        int st = a[i]-'A';
        int vl = 0;
        bool reiksNaujo = last[st] == n;
        for(int j = 0; j < st; j++){
            if(last[j] < last[st]) reiksNaujo = 1;
        }
        if(reiksNaujo){
            vl = 1;
            last[st] = i;
        }
        last[st] = i;
        suf[i] = suf[i+1] + vl;
    }   
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        int prf = (a == 0 ? 0 : pref[a-1]);
        int sff = (b == n-1 ? 0 : suf[b+1]);
        int st = prf + sff;
        cout << st << "\n";
    }
    return 0;

}
