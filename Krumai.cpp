#include <bits/stdc++.h>
using namespace std;
const int dydis = 501;
int n, m;
bool jau[dydis][dydis] = {0};
bool turi[dydis][dydis] = {0};
int up[dydis][dydis];
int leftt[dydis][dydis];
int rightt[dydis][dydis];
int down[dydis][dydis];
int upMost(int e, int s){
 //   cout << e << "; " << s << endl;
    if(e == -1) return e;
    if(!jau[e][s]) return e;
    return up[e][s] = upMost(up[e][s], s);
}
int downMost(int e, int s){
    if(e == n) return e;
    if(!jau[e][s]) return e;
    return down[e][s] = downMost(down[e][s], s);
}
int it = 0;
int leftMost(int e, int s){
    if(s == -1) return s;
    if(!jau[e][s]) return s;
    if(it++ > 50) return 0;
    int ret = leftMost(e, leftt[e][s]);
    return leftt[e][s] = ret;
}
int rightMost(int e, int s){
    if(s == n) return s;
    if(!jau[e][s]) return s;
    return rightt[e][s] = rightMost(e, rightt[e][s]);
}
vector<pair<char, pair<int, int> > > ans;
vector<pair<int, pair<int, int> > > tik;
vector<pair<int, int> > kryp = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int kek (int e, int s){
    int ret = 0;
    for(auto x : kryp){
        int pe = x.first + e;
        int ps = x.second + s;
        if(pe < 0 || ps < 0 || pe >= n || ps >= n) continue;
        if(turi[pe][ps]) ret ++;
    }
    return ret;
}
int main(){
    freopen ("0.txt", "r", stdin);
    freopen ("0-out.txt", "w", stdout);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            up[i][j] = i-1;
            down[i][j] = i+1;
            leftt[i][j] = j-1;
            rightt[i][j] = j+1;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> turi[i][j];
        }
    }
    vector<pair<int, int> > like;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(turi[i][j]) {
                like.push_back({i, j});
            }
        }
    }
    shuffle(like.begin(), like.end(), default_random_engine(seed));
    int left = like.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(turi[i][j]) tik.push_back({kek(i, j), {i, j}});
        }
    }
    sort(tik.begin(), tik.end());
    for(int i = 0; i < n * n; i++){
        if(left == 0) break;
        bool don = 0;
        for(int i = like.size()-1; i > -1; i--){
            int e = like[i].first;
            int s = like[i].second;
            if(!jau[e][s]) continue;
            int virs = upMost(e, s);
            int apac = downMost(e, s);
            int kair = leftMost(e, s);
            int desn = rightMost(e, s);
  //          cout << "virs = " << virs  << " apac = " << apac << ", kair = " << kair << ", desn = " << desn << endl;
            if(virs == -1 || apac == n || kair == -1 || desn == n) continue;
            if(!turi[virs][s] || !turi[apac][s] || !turi[e][kair] || !turi[e][desn]) continue;
            jau[virs][s] = jau[apac][s] = jau[e][kair] = jau[e][desn] = 1;
            ans.push_back({'d', {e, s}});
            left -= 4;
            don = 1; break;
        }
        if(!don){
            while(true){
                int e = tik.back().second.first;
                int s = tik.back().second.second;
                if(jau[e][s]){
                    tik.pop_back();
                    continue;
                }
                jau[e][s] = 1;
                ans.push_back({'s', {e, s}});
                left--;
                tik.pop_back();
                break;
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto x : ans){
        cout << x.first << " " << x.second.first << " " << x.second.second << "\n";
    }
    return 0;
}
