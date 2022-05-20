#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

const int dydis = 1e6  +10;
struct node{
    int kek = 0;
    int kaim[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
};
vector<node> medis;
int n;
int dbInd = 0;
int newN(){
    return dbInd++;
}
void add(vector<int> &vec, int ind, int v){
    medis[v].kek++;
    if(ind == vec.size()){
        return;
    }
    if(medis[v].kaim[vec[ind]] == -1){
        medis[v].kaim[vec[ind]] = newN();
    }
    add(vec, ind+1, medis[v].kaim[vec[ind]]);
}
vector<int> toV(long long a){
    vector<int> ret;
    for(int i = 0; i < 19; i++){
        ret.push_back(a%10);
        a /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
long long des[20] = {0};
long long fMx(vector<int> &vec, int ind, int v, bool don){
    if(ind == vec.size()) return 0;
    pair<int, pair<int, int> > best = {-1, {-1, -1} };
    for(int i = 0; i < 10; i++){
        if(medis[v].kaim[i] == -1) continue;
        if(i == vec[ind] && medis[medis[v].kaim[i]].kek == 1 && !don) continue;
        best = max(best, make_pair((i+vec[ind])%10, make_pair(i, medis[v].kaim[i])));
    }
    if(best.second.first != vec[ind]) don = 1;
    return des[18-ind]*best.first + fMx(vec, ind+1, best.second.second, don);
}
long long fMn(vector<int> &vec, int ind, int v, bool don){
    if(ind == vec.size()) return 0;
    pair<int, pair<int, int> > best = {11, {-1, -1}};
    for(int i = 0; i < 10; i++){
        if(medis[v].kaim[i] == -1) continue;
        if(i == vec[ind] && medis[medis[v].kaim[i]].kek == 1 && !don) continue;
        best = min(best, make_pair((i+vec[ind])%10, make_pair(i, medis[v].kaim[i])));
    }
    if(best.second.first != vec[ind]) don = 1;
    return des[18-ind]*best.first + fMn(vec, ind+1, best.second.second, don);
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    medis.resize(dydis*19);
    des[0] = 1;
    for(int i = 1; i <= 18; i++) des[i] = des[i-1] * 10ll;
    newN();
    cin >> n;
    vector<long long> mas(n);
    for(auto &x : mas){
        cin >> x;
        auto kas = toV(x);

        add(kas, 0, 0);
    }  
    long long mna = 3000000000000000000;
    long long mxa = 0;
    for(auto x : mas){
        auto kas = toV(x);
        auto mn = fMn(kas, 0, 0, 0);
        auto mx = fMx(kas, 0, 0, 0);
        mxa = max(mx, mxa);
        mna = min(mn, mna);
    }
    cout << mna << " " << mxa << endl;
    return 0;
}

