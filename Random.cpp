#include <bits/stdc++.h>

using namespace std;
int n, m;
int de, ds, me, ms;
const int dydis = 1e3 + 10;
int pref[dydis][dydis];
int mas[dydis][dydis];
int kt[dydis][dydis];
pair<int, pair<short, short> > mn[dydis][dydis];
pair<int, pair<short, short> > mnE[dydis][dydis];
const int inf = 1e9;
int sm(int e1, int s1, int e2, int s2){
    int vk = 0, vd = 0, ak = 0, ad = 0;
    if(e1 != 0 && s1 != 0) vk = pref[e1-1][s1-1];
    if(e1 != 0) vd = pref[e1-1][s2];
    if(s1 != 0) ak = pref[e2][s1-1];
    ad = pref[e2][s2];
    return ad - ak - vd + vk;
}
void calc(){
    for(int i = 0; i < n; i++){
        int sm = 0;
        for(int j = 0; j < m; j++){
            sm += mas[i][j];
            pref[i][j] = (i == 0 ? 0ll : pref[i-1][j]) + sm;
        }
    }
}
int main(){
    cin >> m >> n >> ds >> de >> ms >> me;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            kt[i][j] = -inf;
            cin >> mas[i][j];
        }
    }
   
    calc();
	for(int i = 0; i + de-1 < n; i++){
        for(int j = 0; j + ds-1 < m; j++){
            kt[i][j] = sm(i, j, i+de-1, j+ds-1);
        }
    }
    int E = de-me - 1;
    int S = ds-ms - 1;
    for(int i = 0; i < n; i++){
        multiset<pair<int, pair<short, short> > > setas;
        for(int j = 0; j < m; j++){
            setas.insert({kt[i][j], {i, j}});
            if((int)setas.size() > S) setas.erase(setas.find(make_pair(kt[i][j-S], make_pair(i, j-S))));
            mnE[i][j] = *setas.rbegin();
         //   cout << "mnE " << i << "; " << j << ".   " << mnE[i][j].first << endl;
        }
    }
    for(int j = 0; j < m; j++){
        multiset<pair<int, pair<short, short> > > setas;
        for(int i = 0; i < n; i++){
            setas.insert(mnE[i][j]);
            if((int)setas.size() > E) setas.erase(setas.find(mnE[i-E][j]));
            mn[i][j] = *setas.rbegin();
        }
    }
    pair<int, pair<pair<short, short> , pair<short, short> > > ans;
    for(short i = 1; i + me < n; i++){
        for(short j = 1; j + ms < m; j++){
            int st = mn[i-1][j-1].first - sm(i, j, i+me-1, j + ms -1);
            ans = max(ans, make_pair(st, make_pair(mn[i-1][j-1].second, make_pair(i, j))));
        }
    }
	//cout << ans.first << endl;
    cout << ans.second.first.second+1 << " " << ans.second.first.first+1 << "\n" << ans.second.second.second+1 << " " << ans.second.second.first +1;
    return 0;
}
