#include <bits/stdc++.h>
using namespace std;
struct medis{
    struct node{
        long long l, r, val = 0, pl = -1, kek = 0, kekPl = -1;
    };
    int n; int dbInd = 0;
    vector<node> mas;
    void build(int v){
        if(v >= n){
            mas[v].l = mas[v].r = dbInd++;
        }else{
            build(v*2); build(v*2+1);
            mas[v].l = mas[v*2].l;
            mas[v].r = mas[v*2+1].r;
        }
    }
    medis(int sz){
        n = sz;
        mas.resize(n*2 + 10);
        build(1);
    }
    void apply(int v){
        if(mas[v].pl == -1) return;
        mas[v].val = mas[v].pl;
        mas[v].kek = mas[v].kekPl;
        if(v < n){
            mas[v*2].pl = mas[v*2+1].pl = mas[v].pl;
            mas[v*2].kekPl = mas[v*2+1].kekPl = mas[v].kekPl;
        }
        mas[v].pl = mas[v].kekPl = -1;
    }
    int findKek(int v, int l, int r){
        apply(v);
//        cout << mas[v].l << "-" << mas[v].r << ".esu " << v << "; " << l << "; " << r << ". val = " << mas[v].val << endl;
        if(l <= mas[v].l && mas[v].r <= r){
            return mas[v].kek;
        }else if(mas[v].l > r || mas[v].r < l){
            return 0;
        }else{
            return findKek(v*2, l, r) + findKek(v*2+1, l, r);
        }
        apply(v);
    }
    void del(int v, int l, int r){
        apply(v);
        if(l <= mas[v].l && mas[v].r <= r){
            mas[v].pl = 0; mas[v].kekPl = 0;
        }else if(mas[v].l > r || mas[v].r < l){
            return;
        }else{
            del(v*2, l, r); del(v*2+1, l, r);
            mas[v].val = mas[v*2].val + mas[v*2+1].val;
            mas[v].kek = mas[v*2].kek + mas[v*2+1].kek;
        }
        apply(v);
    }
    void add(int v, int l, int r, long long x, long long kek){
        apply(v);
        if(l <= mas[v].l && mas[v].r <= r){
            mas[v].pl = x*kek; mas[v].kekPl = kek;
        }else if(mas[v].l > r || mas[v].r < l){
            return;
        }else{
            add(v*2, l, r, x, kek);
            add(v*2+1, l, r, x, kek);
            mas[v].kek = mas[v*2].kek + mas[v*2+1].kek;
            mas[v].val = mas[v*2].val + mas[v*2+1].val;
        }
        apply(v);
    }
    void print(int v){
        cout << v << ": [" << mas[v].l << "; " << mas[v].r << "].  val = " << mas[v].val << ", kek = " << mas[v].kek << ".  pl = " << mas[v].pl << ", kekPl = " << mas[v].kekPl << "\n";
        if(v < n) {print(v*2); print(v*2+1);}
    }

};
const int dydis = 5e5 + 100;
int n;
vector<int> mas;
vector<int> dubl, st;
map<int, int> tik;
long long pref[dydis], suf[dydis];
vector<int> calcAns(int ind){
    vector<int> ret(n);
    ret[ind] = mas[ind];
    for(int i = ind+1; i < n; i++){
        ret[i] = min(ret[i-1], mas[i]);
    }
    for(int i = ind-1; i > -1; i--){
        ret[i] = min(ret[i+1], mas[i]);
    }
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n; mas.resize(n); dubl.resize(n);
    medis tree(n);
    for(int i = 0; i < n; i++){
        cin >> mas[i];
        dubl[i] = mas[i];
    }
    sort(dubl.begin(), dubl.end());
    st.push_back(dubl[0]);
    for(int i = 1; i < dubl.size(); i++){
        if(dubl[i] == st.back()) continue;
        st.push_back(dubl[i]);
    }
    for(int i = 0; i < st.size(); i++){
        tik[st[i]] = i;
    }
    for(int i = 0; i < n; i++){
        int tikr = mas[i];
        int vt = tik[mas[i]];
        int didesniu = tree.findKek(1, vt+1, n-1);
        int jauYra = tree.findKek(1, vt, vt);
        tree.del(1, vt+1, n-1);
        tree.add(1, vt, vt, tikr, jauYra+didesniu+1);
        pref[i] = tree.mas[1].val;
    }
    medis tree1(n);
    tree = tree1;
    for(int i = n-1; i > -1; i--){
        int tikr = mas[i];
        int vt = tik[mas[i]];
        int didesniu = tree.findKek(1, vt+1, n-1);
        int jauYra = tree.findKek(1, vt, vt);
        tree.del(1, vt+1, n-1);
        tree.add(1, vt, vt, tikr, jauYra+didesniu+1);
        suf[i] = tree.mas[1].val;   
    }
    pair<long long, long long> mx = {-1, -1};
    for(int i = 0; i < n; i++){
        mx = max(mx, make_pair(pref[i]+suf[i]-mas[i], (long long)i));
    }
    vector<int> ans = calcAns(mx.second);
    for(auto x : ans) cout << x << " ";

    return 0;
}
