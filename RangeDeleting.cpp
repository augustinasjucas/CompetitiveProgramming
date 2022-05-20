#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct node{
    int val, l, r, plus;
};
struct seg_tree{
    
    vector<node> tree;
    int currInd = 0;
    int n;
    
    void build(int v){
        if(v >= n){
            tree[v].l = tree[v].r = currInd++;
            tree[v].val = tree[v].plus = 0;
        }else{
            build(v*2);
            build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    void apply(int v){
        tree[v].val += tree[v].plus * (tree[v].r - tree[v].l + 1);
        if(v < n) tree[v*2].plus += tree[v].plus;
        if(v < n) tree[v*2+1].plus += tree[v].plus;
        tree[v].plus = 0;
    }
    void add(int v, int l, int r, int x){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            tree[v].plus += x;
        }else if(tree[v].l > r || tree[v].r < l){
            
        }else {
            add(v*2, l, r, x);
            add(v*2+1, l, r, x);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
        }
        apply(v);
    }
    int find(int v, int l, int r){
        apply(v);
        if(tree[v].l >= l && tree[v].r <= r){ /// sitas pilnai telpa intervale
            return tree[v].val;
        }else if(tree[v].l > r || tree[v].r < l){
            return 0;
        }else {
            return find(v*2, l, r) + find(v*2+1, l, r);
        }
    }
    seg_tree(int dydis){
        tree.resize(dydis*2+10);
        n = dydis;
        build(1);
    }
};
const int dydis = 1e6 + 10;
vector<int> mas;
vector<int> kur[dydis];
int n, mx;
long long invs = 0; // inversiju kiekis
seg_tree kaire(dydis);
seg_tree desine(dydis);
void pridK(int sk){ // kaireje puseje idesiu sk
    // sk bus didesnis uz visus kaire masyvo elementus ir mazesnis uz visus desine masyvo elementus
    for(auto x : kur[sk]){
   //     cout << "inversiju bv " << invs << "\n"; 
        invs += kaire.find(1, x, dydis-1); // kiek 'kaire'je yra desiniau esanciu mazesniu elementu
        invs += desine.find(1, 0, x); // kiek desine'je yra kairiau esanciu didesniu
     //   cout << "pridejus, inversiju kiekis pakito per " << kaire.find(1, x, dydis-1) + desine.find(1, 0, x) << endl;
    }
    for(auto x : kur[sk]){
        kaire.add(1, x, x, 1);
    }
}
void atD(int sk){
    for(auto x : kur[sk]){
        desine.add(1, x, x, -1);
    }
    for(auto x : kur[sk]){
        invs -= kaire.find(1, x, dydis-1);;
        invs -= desine.find(1, 0, x);
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> mx;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    for(int i = 0; i < n; i++){
        kur[mas[i]].push_back(i);
    }
    int ind = mx;
    long long ans = 0;
    while(invs == 0 && ind != 0){

        for(auto x : kur[ind]){
            invs += desine.find(1, 0, x); // as esu maziausias, reiskias as turiu buti kairiausiai
        }
        for(auto x : kur[ind]){
            desine.add(1, x, x, 1);
        }
//        cout << "pridejau " << ind << ", inversiju yra " << invs << endl;
        if(invs == 0)ind--;
    }
    atD(ind);
    ind++;
    if(ind == mx+1){
//        cout << "cia!" << endl;
        cout << 0;
        return 0;
    }
    ans += mx - ind + 2 - (ind == 1);
//    cout << "pradzioje, kai kairysis intervalas tuscias, desinysis gali plestis iki " << ind << endl;
//    cout << "tada desine = ["; for(int i = 0; i < n; i++) cout << desine.find(1, i, i) << " "; cout << "]\n";

    for(int i = 1; i <= mx; i++){
        pridK(i) ;
//        cout << "pridejau i kaire " << i << ", dabar inversiju yra " << invs << endl;
        while((invs != 0 || ind <= i) && ind <= mx){
            atD(ind++);
        }
        if(ind > mx){
            if(invs != 0) break;
        }
//        cout << "intervalu [1; " << i << "] U [" << ind << "; " << mx << "] suma yra " << invs << endl;
        ans += mx-ind + 2 - (abs(ind-i) <= 1) - (abs(ind-i) == 0);
//        cout << endl;
   }
    cout << ans;
    return 0;
}
