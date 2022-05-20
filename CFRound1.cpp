#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        int m; cin >> m;
        bool galima = 1;
        vector<pair<int, int> > ans;
        vector<int> mas(n), turi(n);
        set<int> tinka;
        vector<int> spl;
        for(auto &x : mas) {
            cin >> x; x--;
        }
        for(auto &x : turi) {
            cin >> x; x--;
            tinka.insert(x);
        }
        vector<int> netink[n];

        for(auto &x : netink) x.clear();
        int tsg[n];
        for(int i = 0; i < n; i++) tsg[i] = -1;
        for(int i = 0; i < n; i++){
            tsg[turi[i]] = i;
            if(mas[i] != turi[i]){
                netink[turi[i]].push_back(i);
            }
        }
        for(int i = 0; i < m; i++){
            int a;
            cin >> a; a--;
            spl.push_back(a);
            if(i == m-1){
                if(tinka.count(a) == 0){
                    galima = 0;
                }else{
                }
            }
        }
        if(!galima){
            cout << "NO\n";
            continue;
        }
        int ns = tsg[spl.back()];
        for(int i = 0; i < n; i++){
            if(turi[i] != spl.back()) continue;
            if(turi[i] != mas[i]){
                ns = i;
            }
        }
        for(int i = 0; i < netink[spl.back()].size(); i++){
            if(netink[spl.back()][i] == ns){
                swap(netink[spl.back()][i], netink[spl.back()][0]);
                break;
            }
        }
        tsg[spl.back()] = ns;
        vector<int> ats;
        vector<int> cur = mas;
//        netink[spl.back()].pop_back();
        for(auto x : spl){
//            cout << "imu " << x << " splace\n";
            if(tsg[x] == -1){
                ats.push_back(ns);
                cur[ns] = x;
//                cout << "dedu " << ns << endl;
            }else{
                if(netink[x].size() == 0){
                    ats.push_back(tsg[x]);
                    cur[tsg[x]] = x;
//                    cout << "dedu tsg " << tsg[x] << endl;
                }else{
                    ats.push_back(netink[x].back());
                    cur[netink[x].back()] = x;
//                    cout << "dedu " << netink[x].back() << ", su st\n";
                    netink[x].pop_back();
                }
            }
        }
        galima = galima && (cur == turi) ;
        if(galima){
            cout <<"YES\n";
            for(auto x : ats){
                cout << x+1 << " ";
            }
            cout << "\n";
        }else{
            cout << "NO\n";
        }
        
    }
    return 0;
}
