#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n;
vector<long double> a, b;
long double pref[dydis];
int main(){
    cin >> n;
    a.resize(n);
    b.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    sort(a.begin(), a.end()); reverse(a.begin(), a.end());
    sort(b.begin(), b.end()); reverse(b.begin(), b.end());
    if(a[0] == 1 || b[0] == 1) {
        cout << 0;
        return 0;
    }
    while(a.back() == 0) a.pop_back();
    while(b.back() == 0) b.pop_back();
    n = a.size();
    int m = b.size();
    pref[0] = b[0];
    for(int i = 1; i < m; i++) {
        pref[i] = pref[i-1] + b[i];
    }
    long double s = 0, ats = 0;
    for(int i = 0; i < n; i++) {
        s += a[i];
    

        int l = 0; int r = m-1; int mid;
        long double A, B, viso;
        int ans = 0;
        while(l <= r) {
            mid = (l + r) / 2;
            
            viso = i + mid + 1;
            A = s - viso;
            B = pref[mid] - viso;
            if(A >= B) {
                l = mid+1;
                ans = mid;
            }else {
                r = mid-1;
            }
        }
        long double f1 = 0, f2 = 0;
        f1 = min(s-(i+ans+2), pref[ans]-(i+ans+2));
        if(ans + 1 < m) {
            f2 = min(s - (i+ans+3), pref[ans+1]-(i+ans+2));
        }
        ats = max(ats, max(f1, f2));
    }
    cout << setprecision(4) << fixed << ats;
    return 0;
}
