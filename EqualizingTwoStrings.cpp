#include <bits/stdc++.h>
using namespace std;
bool isVal(string a, string b){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}
int kiekReiks(string a){
    bool taken[a.size()];
    for(auto &x : taken) x = 0;
    string cp = a;
    sort(cp.begin(), cp.end());
    int s = 0;
    for(int i = 0; i < cp.size(); i++){
        for(int j = i; j < cp.size(); j++){
            if(a[j] == cp[i]){
                s += j-i;
                for(int h = j; h > i; h--){
                    swap(a[h], a[h-1]);
                }
                break;
            }
        }
    }
    return s;
}
int main(){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        string a, b; cin >> a >> b;
        if(n > 26 || n == 1){
            if(isVal(a, b)) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }
        if(!isVal(a, b)){
            cout << "NO\n";
            continue;
        }
        int prm = kiekReiks(b);
        if(prm & 1){
            swap(a[a.size()-1], a[a.size()-2]);
        }
        int ant = kiekReiks(a);
        if(ant & 1){
            string cp1 = a;
            string cp2 = b;
            sort(cp1.begin(), cp1.end());
            sort(cp2.begin(), cp2.end());
            swap(cp2[cp2.size()-1], cp2[cp2.size()-2]);
            string ans = "NO";
            for(int i = 0; i < n-1; i++){
                if(cp1[i] == cp1[i+1] || cp2[i] == cp2[i+1]) ans = "YES";
            }
            cout << ans << "\n";
        }else{
            cout << "YES\n";
        }
    }
    return 0;
}
