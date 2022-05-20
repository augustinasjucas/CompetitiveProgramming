#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e6 + 10;
int n, m;
vector<vector<int> > mas;
vector<vector<pair<int, int> > > pref, suf;
int cnt[dydis] = {};
bool marked[dydis] = {};
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n >> m;
        
        mas.resize(n); pref.resize(n); suf.resize(n);
        for(auto &x : mas) x.resize(m);
        for(auto &x : pref) x.resize(m);
        for(auto &x : suf) x.resize(m);
        

        for(auto &x : mas) for(auto &y : x) cin >> y;
        
        bool fd = 0;
        
        for(int i = 0; i < n; i++){
            pref[i][0] = {mas[i][0], mas[i][0]};
            for(int j = 1; j < m; j++){
                pref[i][j] = {min(pref[i][j-1].first, mas[i][j]), max(pref[i][j-1].second, mas[i][j])};
            }
            suf[i][m-1] = {mas[i][m-1], mas[i][m-1]};
            for(int j = m-2; j > -1; j--){
                suf[i][j] = {min(suf[i][j+1].first, mas[i][j]), max(suf[i][j+1].second, mas[i][j])};
            }
        }
        
        for(int j = 0; j < m-1; j++){ // viskas intervale [0; j] priklauso kairiajai pusei
            vector<pair<pair<int, int>, int> > kair, des;
            for(int i = 0; i < n; i++){
                kair.push_back({pref[i][j], i});
                des.push_back({suf[i][j+1], i});
            }
            sort(kair.begin(), kair.end());
            sort(des.begin(), des.end());
            
            vector<vector<int> > k, d; 
            int R = kair[0].first.second;
            k.push_back({kair[0].second});
            for(int i = 1; i < kair.size(); i++){
                if(kair[i].first.first <= R){
                    k[k.size()-1].push_back(kair[i].second);
                }else{
                    k.push_back({kair[i].second});
                }
                R = max(kair[i].first.second, R);
            }
            R = des[0].first.second;
            d.push_back({des[0].second});
            for(int i = 1; i < des.size(); i++){
                if(des[i].first.first <= R){
                    d[d.size()-1].push_back(des[i].second);
                }else{
                    d.push_back({des[i].second});
                }
                R = max(des[i].first.second, R);
            }
            reverse(d.begin(), d.end());
            
/*            cout << "jei dedu linija ant j = " << j << ", tai kair: ";
            for(auto x : k) {
                cout << "{";
                for(auto y : x) cout << y << " ";
                cout << "}, ";
            }
            cout << endl << "o des: ";
            for(auto x : d) {
                cout << "{";
                for(auto y : x) cout << y << " ";
                cout << "}, ";
            }
            cout << endl << endl;*/
            int l = 0; int r = 0;
            int lsz = k[0].size();
            int rsz = d[0].size();
            int blogu = 0;
            vector<int> yra;
            bool galima = 0;
            for(auto x : k[0]){
                yra.push_back(x);
                cnt[x]++;
                if(cnt[x] == 1) blogu++;
                if(cnt[x] == 0) blogu--;
            }
            for(auto x : d[0]){
                cnt[x]--;
                if(cnt[x] == 0) blogu--;
                if(cnt[x] == -1) blogu++;
            }
            while(true){
//                cout << "l = " << l << ", r = " << r << endl;
                if(l == k.size()-1 && r == d.size() - 1) break;
                if(blogu == 0){
                    galima = 1;
                    break;
                }
                if(lsz <= rsz){
                    l++;
                    lsz += k[l].size();
                    for(auto x : k[l]){
                        yra.push_back(x);
                        cnt[x]++;
                        if(cnt[x] == 1) blogu++;
                        if(cnt[x] == 0) blogu--;
                    }
                }else{
                    r++;
                    rsz += d[r].size();
                    for(auto x : d[r]){
                        cnt[x]--;
                        if(cnt[x] == 0) blogu--;
                        if(cnt[x] == -1) blogu++;                    
                    }
                }
            }
            if(galima){
                for(auto x : yra) marked[x] = 1;
                cout << "YES\n";
                for(int i = 0; i < n; i++){
                    if(marked[i]) cout << "B";
                    else cout << "R";
                }
                cout << " " << j + 1 << "\n";
                fd = 1;
                break;
            }
            for(int i = 0; i < n; i++){
                cnt[i] = 0;
                marked[i] = 0;
            } 
        }
        for(int i = 0; i < n; i++){
            cnt[i] = 0;
            marked[i] = 0;
        } 

        if(!fd){
            cout << "NO\n";
        }
    }
    return 0;
}
// 11:45
