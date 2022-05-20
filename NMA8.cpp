#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
vector<int> mas;
vector<pair<long long, int> > visi1; // sec - 1, jei liecia krasta

unordered_map<int, vector<long long> > visi2;
unordered_map<int, vector<long long> > neliec2;


long long s = 0, m, n;
int lim1 = 0; int liec = 0;
void dar1(int ind){
    if(ind >= lim1){
        visi1.push_back({s, liec});
        return;
    }
    dar1(ind+1);
    s += mas[ind];
    if(ind == lim1-1) liec = 1;
    dar1(ind+2);
    s -= mas[ind];
    if(ind == lim1-1) liec = 0;
}
void dar2(int ind){
    if(ind >= n){
        visi2[s % m].push_back(s);
        if(!liec) neliec2[s % m].push_back(s);
        return;
    }
    dar2(ind+1);
    s += mas[ind];
    if(ind == lim1) liec = 1;
    dar2(ind+2);
    s -= mas[ind];
    if(ind == lim1) liec = 0;   
}
long long viso(long long S){ // kiek viso yra poru, kuriu suma yra 0;
    long long ret = 0;
    for(auto x : visi1){
        long long mx = S - x.first;
        long long md = (m-x.first%m + m)  % m;
//        cout << "pradedu su " << x.first << "-" << x.second << "   ";
//        cout << "mx = " << mx << endl;
        if(x.second){ // liecia krasta
            auto &kur = neliec2[md];
            long long pr = upper_bound(kur.begin(), kur.end(), mx) - kur.begin();
            ret += pr;
        }else{ // neliecia krasto
            auto &kur = visi2[md];
            long long pr = upper_bound(kur.begin(), kur.end(), mx) - kur.begin();
            ret += pr;
        }
    }
//    cout << "viso " << s << "  =  " << ret << endl;
    return ret;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    mas.resize(n);
    lim1 = n/2;
    for(auto &x : mas) {
        cin >> x;
    }
    long long k;
    cin >> k >> m;

    dar1(0);
    dar2(lim1);

    sort(visi1.begin(), visi1.end());
    

    for(auto &x : visi2) {
        sort(x.second.begin(), x.second.end());
    }

/*    cout << "\npaskui = [\n\n";
    for(auto &x : visi2) {
        cout << x.first << ": ";
        for(auto y : x.second) cout << y << " ";
        cout << "\n";
    }
    cout << endl << endl;*/

    for(auto &x : neliec2){
        sort(x.second.begin(), x.second.end());
    }
    long long l = 0, r = 100000000000;
    long long ans = 1000000000000;
    while(l <= r){
        long long mid = (l+r)/2;
        if(viso(mid) >= k){
            ans = min(ans, mid);
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    viso(0);
//    cout << "viso(0) = " << viso(0) << endl;
    cout << ans;
    return 0;
}
/*

    
*/
