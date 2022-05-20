#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int n;
vector<pair<int, int> > pts;
long long rnd(int l, int r){
    long long ps = (rand() % 1000000ll) * (rand() % 1000000ll);
    return ps % (r-l+1) + l;
}
pair<long long, pair<long long, long long> > getT(int i1, int i2){
    long long y1 = pts[i1].second;
    long long x1 = pts[i1].first;
    long long y2 = pts[i2].second;
    long long x2 = pts[i2].first;
    return make_pair(y1-y2, make_pair(x2-x1, x1*y2-x2*y1));
}
bool fit(pair<long long, pair<long long, long long> > ts){
    long long A = ts.first;
    long long B = ts.second.first;
    long long C = ts.second.second;
    vector<pair<int, int> > lk;
    vector<int> ind; int db = -1;
    for(auto x : pts){
        db++;
        if(x.first * A + x.second * B + C == 0){
            continue;
        }
        ind.push_back(db);
        lk.push_back(x);
    }
    if(lk.size() <= 1) return true;
    auto t = getT(ind[0], ind[1]);
    for(auto x : lk){
        if(x.first * t.first + x.second * t.second.first + t.second.second != 0) return false;
    }
    return true;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    srand(time(0));
    cin >> n;
    if(n <= 2){
        cout << "YES";
        return 0;
    }
    pts.resize(n);
    for(auto &x : pts){
        cin >> x.first >> x.second;
    }
    string ans = "NO";
    for(int i = 0; i < 50; i++){
        int i1 = rnd(0, n-1);
        int i2 = rnd(0, n-1);
        while(i2 == i1) i2 = rnd(0, n-1);
        auto ts = getT(i1, i2);
        if(fit(ts)) ans = "YES";
    }
    cout << ans;
    return 0;
}
