#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int d;
vector<int> sk;
int kek[10] = {0};
vector<deque<short> > tinka[20];
long long pw[18] = {0};
unordered_set<long long> setas[18];
vector<deque<short> > galima(deque<short> a, int ind){
    int cp[10];
    for(int i = 0; i < 10; i++) cp[i] = kek[i];
    for(auto x : a) cp[x]--;
    long long kas = 0; long long pw = 1;
    for(int i = a.size()-1; i > -1; i--){
        kas += 1ll * a[i] * pw;
        pw *= 10;
    }
    vector<deque<short> > ret;
    for(int i = 0; i < 10; i++){
        if(cp[i] == 0) continue;
        long long cP = kas + pw*i;
        if((cP & ((1ll << ind)-1) ) != 0) continue;
        if(setas[ind].count(cP)) continue;
        setas[ind].insert(cP);
        auto kur = a.begin();
        a.push_front(i);
        ret.push_back(a);
        a.pop_front();
    }
    return ret;
}
int main(){
    pw[0] = 1;
    for(int i = 1; i <=17; i++) pw[i] = pw[i-1] * 10ll;
    cin >> d;
    for(int i = 0; i < d; i++){
        char a; cin >> a;
        sk.push_back((a-'0'));
        kek[(a-'0')]++;
    }
    for(int i = 0; i < d; i++){
        if(sk[i] & 1 && sk[i] != 1) continue;
        tinka[1].push_back({(short)sk[i]});
    }
    if(tinka[1].size() == 0){
        cout << "SUCCESS\n";
        for(auto x : sk) cout << x;
        cout << "\n" << 1;
        return 0;
    }
    for(int i = 2; i < d+1; i++){
        if(tinka[i-1].size() == 0){
            break;
        }
        for(auto x : tinka[i-1]){
            auto kas = galima(x, i);
            if(kas.size()){
                for(auto x : kas){
                    tinka[i].push_back(x);
                }
            }
        }
    }
//    cout << "viskas\n";
    pair<long long, long long> ans = {0, 0};

    for(int i = 19; i > -1; i--){
        if(tinka[i].size() == 0) continue;
        bool don = 0;
        for(auto x : tinka[i]){
            int cp[10];
            for(int i = 0; i < 10; i++) cp[i] = kek[i];
            long long ps = 0; long long daug = 1;
            for(int i = x.size()-1; i > -1; i--){
                cp[x[i]]--;
                ps += daug * x[i];
                daug *= 10;
            }
            bool yra = 0;
            for(int i = 1; i < 10; i++) if(cp[i]) yra = 1;
            if(yra){
                if(cp[0]) continue;
                for(int j = 0; j < 10; j++){
                    for(int i = 0; i < cp[j]; i++) {
                        ps += daug*j;
                        daug *= 10;
                    }
                }
            }else{
                if(x[0] == 0) continue;
            }
            don = 1;
            ans = max(ans, {ps&-ps, ps});
        }
        if(don) break;
    }
    cout << "SUCCESS\n";
    cout << ans.second<< "\n" << ans.first;
    return 0;
}
