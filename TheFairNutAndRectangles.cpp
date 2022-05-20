
#include <bits/stdc++.h>
using namespace std;
long double k1, k2, b1, b2;
const long long inf = 1e18;
pair<long long, long long> inter(pair<long long, long long> a, pair<long long, long long> b){
    k1 = a.first;
    k2 = b.first;
    b1 = a.second;
    b2 = b.second;
    // k1x + b1 = k2x + b2
    // x(k1-k2) = b2-b1
    // x = 
    return {b2-b1, k1-k2};
//    return (b2 - b1) / (k1 - k2);
}
struct hull{
    deque<pair<long long, long long> > vec;
 
    void insert(pair<long long, long long> a){  // k visad mazes!
        long long k = a.first;
        long long b = a.second;
        while(true){
            if(vec.size() <= 1){
                vec.push_front(a);
                break;
            }
            auto kur1 = inter(vec[0], vec[1]);
            auto kur2 = inter(vec[0], a);
            if(((__int128_t)kur2.first )* ((__int128_t)kur1.second) < ((__int128_t) kur1.first) *((__int128_t)kur2.second)){
                vec.push_front(a);    
                break;
            }else{
                vec.pop_front();
            }
        }
   /*     cout << "vec lieka: ";
        for(auto x : vec){
            cout << "{" << x.first << "x + " << x.second << "}, ";
        }
        cout << endl;*/
    }
    long long f(pair<long long, long long> a, long long b){
        return 1ll * b * a.first + 1ll * a.second;
    }
    long long getVal(long long x){
        if(vec.size() == 1) return f(vec[0], x);
        long long l = 0; long long r = vec.size()-1; long long mid;
        long long mid1, mid2, f1, f2, ret = -inf;
 
        while(l <= r){
            mid1 = l + (r - l + 1) / 3;
            mid2 = r - (r - l + 1) / 3;
            f1 = f(vec[mid1], x);
            f2 = f(vec[mid2], x);
            ret = max(ret, max(f1, f2));
            if(f1 >= f2){
                r = mid2-1;
            }else{
                l = mid1+1;
            }
        }
        return ret;
    }
};
 
long long n;
hull hul;
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
/*    while(true){
        long long k, b; cin >> k >> b;
        if(k == 0){
            long long ans = hul.getVal(b);
            cout << ans << "\n";
        }else{
            hul.insert({k, b});
            cout << endl;
        }
    }
*/
    cin >> n;
    vector<pair<long long, pair<long long, long long> > >  vec(n);
    for(long long i = 0; i < n; i++){
        cin >> vec[i].first >> vec[i].second.first >> vec[i].second.second;
    }
    sort(vec.begin(), vec.end());
    long long dp[n];
    dp[0] = 1ll * vec[0].first * vec[0].second.first - 1ll * vec[0].second.second;
    hul.insert({-vec[0].first, dp[0]});
    for(long long i = 1; i < n; i++){
        dp[i] = 1ll * vec[i].first * vec[i].second.first - 1ll * vec[i].second.second;
        dp[i] = max(dp[i], hul.getVal(vec[i].second.first) + 1ll * vec[i].first * vec[i].second.first - 1ll * vec[i].second.second);
        hul.insert({-vec[i].first, dp[i]});
    }
    long long ans = 0;
    for(long long i = 0; i < n; i++) ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}

