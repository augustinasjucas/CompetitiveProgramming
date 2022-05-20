#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

const long long inf = 100000000000000;
set<int> don;
vector<pair<int, pair<int, int> > > vec;
int n;
bool galima = 0;
bool yra[3] = {0};
int yr[5010] = {0};
vector<pair<pair<int, int>, int> >  srt[2];
long long fix(long long a){ // pirmas bus a
    if(don.count(a)) return -inf;
    don.insert(a);
    a = max(a, 0ll);
//    cout << "bandau pirma daryt " << a << endl;
    
    vector<pair<int, int> > mas[2];
    for(int i = 0; i < n; i++) yr[i] = 0;
    int ind = 0;
    long long mx1 = inf, mx2 = inf;
    for(auto x : vec){
        if(a >= x.first) { // jisai gali atlikti x spella
            ind++;
            if(x.second.second == 0) mx1 = min(mx1, 1ll * x.second.first);
            if(x.second.first == 0) mx2 = min(mx2, 1ll * x.second.second);
        }

    }
    for(auto x : srt[0]){
        if(a >= x.second){
            mas[0].push_back({x.first.first, x.first.second});
        }
    }
    for(auto x : srt[1]){
        if(a >= x.second){
            mas[1].push_back({x.first.first, x.first.second});
        }
    }
//    sort(mas[0].begin(), mas[0].end());
//    sort(mas[1].begin(), mas[1].end());
//    cout << "mas[0] = "; for(auto x : mas[0]) cout << x.first <<"-"<<x.second << "  ";

//    cout << "\nmas[1] = "; for(auto x : mas[1]) cout << x.first <<"-"<<x.second << "  ";
//    cout << endl << endl;
//    if(ind == 0) return mx1+mx2-1;
    for(int i = 0; i < ind; i++){
        yr[mas[1][i].second]++;
    }
    int ind1 = ind; 
    int viso = ind; 
    long long ans = -inf;
//    cout << "mxai = " << mx1 << " ir " << mx2 << "\n";
    if(mx1 != 0) ans = max(ans, mx1-1);
    if(mx2 != 0) ans = max(ans, mx2-1);
//    cout << "ind = " << ind << "\n";
    for(int i = 0; i < ind-1; i++) { // einu per pirmus elementus
        yr[mas[0][i].second]--;
        if(yr[mas[0][i].second] == 0) viso--;
//        cout << i << ", numazinu " << mas[0][i].second << ", viso tampa " << viso << "\n";
        while(viso != ind){
            ind1--;
            yr[mas[1][ind1].second]++;
            if(yr[mas[1][ind1].second] == 1) viso++;
//            cout << "ind1 = " << ind1  << ", viso = " << viso<< "\n";
        }
        long long st = mas[1][ind1].first-1 + mas[0][i+1].first-1;
//        cout << "turiu " << mas[1][ind1].first << " ir " << mas[0][i].first << endl;
        if(mas[1][ind1].first != 0 && mas[0][i+1].first != 0){
            ans = max(ans, st);
        }//else cout << "nemaxinu!\n";
//        cout << "i = " << i << ", tai ind1 = " << ind1 <<",st = " << mas[1][ind1].first << " + " << mas[0][i+1].first << "-1"<< "\n"; 
    }
//    cout << "ret ans = " << ans << endl;
    return ans;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;

    for(int i = 0; i < n; i++){
        int a, b, c; cin >> a >> b >> c;
        if(b == 0 && c == 0) yra[0] =  true;
        if(a == 0 && c == 0) yra[1] = true;
        if(a == 0 && b == 0) yra[2] = true;
        vec.push_back({a, {b, c}});
        srt[0].push_back({{b, i}, a});
        srt[1].push_back({{c, i}, a});
    }
    sort(srt[0].begin(), srt[0].end());
    sort(srt[1].begin(), srt[1].end());
    if(!yra[0] || !yra[1] || !yra[2]){
        cout << "Infinity";
        return 0;
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        long long pos = fix(vec[i].first-1) + vec[i].first-1;
        ans = max(ans, pos);
//        cout << "ans = " << pos << "\n\n\n";
    }
    cout << ans;
    return 0;
}
