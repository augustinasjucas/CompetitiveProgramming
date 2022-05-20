#include <bits/stdc++.h>
using namespace std;
struct node{
    int l, r, sm = 0, val = 0;
};
struct tree{
    int n;
    vector<node> medis;
    int dbInd = 0;
    void build(int v){
        if(v >= n){
            medis[v].l = medis[v].r = dbInd++;
        }else{
            build(v*2); build(v*2+1);
            medis[v].l = medis[v*2].l;
            medis[v].r = medis[v*2+1].r;
        }
    }
    tree(int sz){
        medis.resize(2*sz+1);
        n = sz;
        build(1);
    }
    void add(int v, int l, int r, int x){
        if(l <= medis[v].l && medis[v].r <= r){
            medis[v].sm += x;
            if(medis[v].sm == 0) medis[v].val = 0;
            else medis[v].val = 1;
        }else if(medis[v].r < l || medis[v].l > r){
            
        }else{
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            medis[v].val = medis[v*2].val + medis[v*2+1].val;
        }
    }
    long long find(int v, int l, int r){
        if(l <= medis[v].l && medis[v].r <= r){
            return medis[v].val;
        }else if(medis[v].r < l || medis[v].l > r){
            return 0;
        }else{
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
};
vector<pair<int, int> > press(vector<pair<int, int> > a){
    vector<int> sv;
    for(auto x : a) {
        sv.push_back(x.first);
        sv.push_back(x.second);
    }
    sort(sv.begin(), sv.end());
    vector<pair<int, int> > ret;
    for(auto x : a){
        pair<int,int> pb;
        int i1 = lower_bound(sv.begin(), sv.end(), x.first)-sv.begin();
        int i2 = lower_bound(sv.begin(), sv.end(), x.second)-sv.begin();
        pb = {i1, i2};
        ret.push_back(pb);
    }
    sort(ret.begin(), ret.end());
    return ret;
}
int main(){
    int n; cin >> n;
    tree medis(4e5 + 10);
    vector<pair<int, int> > mas(n);
    for(auto &x : mas){
        cin >> x.second >> x.first;
    }
    mas = press(mas);
    long long ans = 0;
    for(auto x : mas){
        medis.add(1, x.second, x.second, 1);
    }
    for(int i = 0; i < n; i++){
        for(int j = i; j <= n; j++){
            if(j == n || mas[i].first != mas[j].first){
                long long sm = 0;
                int last = 0;
                for(int h= i; h < j; h++){
                    sm += medis.find(1, last, mas[h].second) * medis.find(1, mas[h].second, 400000);
                    last = mas[h].second+1;
                }
                ans += sm;
                for(int h = i; h < j; h++) medis.add(1, mas[h].second, mas[h].second, -1);
                i = j-1; break;
            }else{
            
            }
        }
    }
    cout << ans;
    return 0;
}
