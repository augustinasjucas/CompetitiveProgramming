#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int A, B, C;
int kr(int a, int dal){
    if(a % dal == 0) return a;
    return (a/dal) * dal;
}
int des(int a, int dal){
    if(a % dal == 0) return a;
    return (a/dal+1) * dal;
}
pair<int, pair<int, int> > band(int a, int b, int x){

    int mx = max(a, b);
    pair<int, pair<int, int> > ret = {(int)1e9, {-1, -1}};
    for(int i = x; i <= mx; i += x){
        int pos = abs(i-a);
        ret = min(ret, {pos + abs(kr(b, i)-b), {i, kr(b, i)}});
        ret = min(ret, {pos + abs(des(b, i)-b), {i, des(b, i)}});
    }
    ret.first += abs(a-B) + abs(b-C);
    return ret;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> A >> B >> C;
        int mx = max(A, max(B, C));
        pair<int, pair<pair<int, int>, int> > ans = {1e9, {{-1, -1}, -1}};
        for(int i = 1; i <= mx; i++){
            // jei a taps i
            int pos = abs(i-A);
            auto p1 = band(kr(B, i), kr(C, i), i);
            auto p2 = band(kr(B, i), des(C, i), i);
            auto p3 = band(des(B, i), kr(C, i), i);
            auto p4 = band(des(B, i), des(C, i), i);
            auto st = min(min(p1, p2), min(p3, p4));
            auto kt = make_pair(st.first + pos, make_pair(st.second, i));
            ans = min(ans, kt);
        }
        cout << ans.first << "\n" << ans.second.second << " " << ans.second.first.first << " " << ans.second.first.second << "\n";
    }
    return 0;
}
