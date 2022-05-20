#include <bits/stdc++.h>
using namespace std;
int n, k;
const int dydis = 1e6 + 1;
int enter[dydis];
set<pair<int, int> > sar;
int kiek[dydis] = {};
bool jauSalintas[dydis] = {};
int answ[dydis] = {};
void add(int a, int i){
    if(sar.count({enter[a], a})){
        sar.erase({enter[a], a});
        kiek[a] += i - enter[a];
        enter[a] = i;
        sar.insert({enter[a], a});
        return;
    }
    if(sar.size() < k){
        enter[a] = i;
        sar.insert({enter[a], a});
    }else if(sar.size() == k){
        enter[a] = i;
        sar.insert({enter[a], a});

        int b = sar.begin() -> second;
        kiek[b] += i - enter[b];
        answ[b] = max(answ[b], kiek[b]);
        kiek[b] = 0;
        sar.erase(*sar.begin());
        jauSalintas[b] = 1;
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        add(a, i); 
    }
    pair<int, int> ans = {0, 1};
    for(int i = 0; i <= n; i++){
        if(sar.count({enter[i], i}) && !jauSalintas[i]){
            sar.erase({enter[i], i});
            kiek[i] += n - enter[i] ;
            answ[i] = max(answ[i], kiek[i]);
        }
        ans = max(ans, make_pair(answ[i] , -i));
    }

//    cout << "viso " << ans.first << endl;
    cout << ans.second * -1 ;
    return 0;
}
/*
    i = 0 -> idedu.
    i = 1 -> +1, enter = 1;
    i = 2 -> +1, enter = 2;
    i = 3 -> +1, enter = 3;

    i = 0 -> idedu
    i = 1 -> isimu
         
*/
