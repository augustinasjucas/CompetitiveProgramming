#include <bits/stdc++.h>
using namespace std;
int inv;
int mas[2][20];
int n;
long long inf = 1e10;
vector<bool> toBit(int a){
    vector<bool> ret;
    for(int i = 0; i < n; i++) {
        ret.push_back(a&1);
        a = a >> 1;
    }
    return ret;
}
long long sm(vector<bool> ms, int ind){
    long long s = 0;
    for(int i = 0; i < n; i++){
        if(!ms[i]) continue;
        s += mas[ind][i];
    }
    return s;
}
long long sm1(vector<bool> ms, int ind){
    long long s = 0;
    for(int i = 0; i < n; i++){
        if(mas[!ind][i] == 0) s += mas[ind][i];
        if(!ms[i]) continue;
        if(mas[!ind][i] != 0)s += mas[ind][i];
    }
    return s;
}
pair<long long, pair<long long, long long> > f(long long kek){ // is kaires imu kek
    long long ret = 0;
    for(int i = 1; i < (1 << n); i++){
        vector<bool> imu = toBit(i);
//        cout << "imu  = "; for(auto x : imu) cout << x << " ";
//        cout << endl;
        int vnt = 0;
        for(auto x : imu) vnt += x;
        if(vnt > kek) continue; // per daug pasirinkau
        if(sm(imu, 0) == 0 || sm(imu, 1) == 0) continue;
        if(sm(imu, 0) < kek) continue; // per mazai pasirinkau
        ret = max(sm1(toBit(i ^ inv), 1) + 1, ret);
    }
    if(ret == 0){
        return {inf + kek, {-1, -1}};
    }
    return {ret + kek, {kek, ret}};
}
int main(){
    cin >> n;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            cin >> mas[i][j];
        }
    }
    inv = (1 << n)-1;
//    cout << "f(2) = " << f(2) << endl;
    long long l = 0, r = 2e9;
    pair<long long, pair<long long, long long> >  ret = {1000000000000, {-1, -1}};
    long long s = 0;
    long long mn = 1;
    for(int i = 0; i < n; i++){
        if(mas[1][i] == 0) mn += mas[0][i];
    }
    for(auto x : mas[0]) s += x;
    for(int i = mn; i <= s; i++){
 
        auto ff = f(i);
        ret = min(ret, ff);
//        cout << i << ": " << ff.first << ". " << ff.second.first << " " << ff.second.second << endl;
 
    }
/*    while(l <= r){
        long long mid1 = l + (r-l)/3;
        long long mid2 = r - (r-l)/3;
        auto f1 = f(mid1);
        auto f2 = f(mid2);
//        cout << l << "; " << r << ", f(" << mid1 <<") = " << f1.first << ", f(" <<mid2<<") = " << f2.first << endl;
        ret = min(ret, min(f1, f2));
        if(f1.first < f2.first){
            r = mid2-1;
        }else{
            l = mid1+1;
        }
    }*/
    cout << ret.second.first << "\n" << ret.second.second;
    return 0;
}
