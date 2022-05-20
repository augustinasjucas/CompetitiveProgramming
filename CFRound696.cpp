#include <bits/stdc++.h>
using namespace std;
int kek[1000010] = {0};
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> mas(n*2);
        for(auto &x : mas) cin >> x;
        sort(mas.begin(), mas.end());
        bool fd = 0;
        for(int i = 0; i < 2*n-1; i++){
            for(auto x : mas) kek[x] = 0;
            for(auto x : mas) kek[x]++;
            kek[mas[i]]--;
            kek[mas.back()]--;
            int s = mas.back();
            bool st = 1;
            vector<pair<int, int> > vc;
            for(int j = 2*n-1; j > -1; j--){
                if(i == j) continue;
                if(kek[mas[j]] == 0) continue;
                kek[mas[j]]--;
                if(s - mas[j] < 0 || s-mas[j] > 1000000 || kek[s-mas[j]] == 0) st = false;
                if(!st) break;
                kek[s-mas[j]]--;
                vc.push_back({mas[j], s-mas[j]});
                s = mas[j];
            }
            if(st){
                cout << "YES\n";
                cout << mas[i] + mas.back() << "\n";
                cout << mas[i] << " " << mas.back() << "\n";
                for(auto x : vc){
                    cout << x.first << " " << x.second << "\n";
                }
                fd = 1;
                break;
            }
        }
        if(!fd){
            cout << "NO\n";
        }
        
        for(auto x : mas) kek[x] = 0;

    }
    return 0;
}
