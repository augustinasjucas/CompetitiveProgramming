#include <bits/stdc++.h>
using namespace std;
const int dydis = 3e3 + 10;
int n;
vector<int> mas;
long long total[dydis], cnt[dydis];
void nul(){
    for(int i = 0; i <= n; i++) cnt[i] = 0;
}
int main(){
//    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n;
        mas.resize(n);
        for(auto &x : mas) cin >> x;
        for(int i = 0; i <= n; i++){
            cnt[i] = total[i] = 0;
        }
        for(int i = 0; i < n; i++) total[mas[i]]++;
        long long ans = 0;
        for(int i = 0; i < n-3; i++){
            nul();
            long long s = 0;
            total[mas[i]]--;
            for(int j = i+1; j < n-1; j++){ /// 0 1 2 3 4 n = 5
//                cout << "imu " << i << " ir " << j << endl;
                s -= cnt[mas[j]] * (total[mas[j]] - cnt[mas[j]]);
                total[mas[j]]--;
                s += cnt[mas[j]] * (total[mas[j]]-cnt[mas[j]]);
                if(mas[i] == mas[j] && j-i != 1) ans += s;
                s -= cnt[mas[j]] * (total[mas[j]]-cnt[mas[j]]);
                total[mas[j]]++;
                s += cnt[mas[j]] * (total[mas[j]]-cnt[mas[j]]);
//                cout << " s = " << s << ", o isemus, s = ";
                s -= cnt[mas[j]] * (total[mas[j]]-cnt[mas[j]]);
                cnt[mas[j]]++;
                s += cnt[mas[j]] * (total[mas[j]]-cnt[mas[j]]);
//                cout << s << ". cia nuo " << mas[j] << " viso yra " << total[mas[j]] << ", o cnt = " << cnt[mas[j]] << " \n";
            }
//            cout << endl;
        }
        cout << ans << "\n";
    }
    return 0;
}
