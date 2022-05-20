#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
int n, k;
vector<int> mas;
long long inf = 1000000000000000000;
vector<pair<long long, long long> > vec;
long long pref[dydis] = {0}, suf[dydis] = {0};
long long pK[dydis] = {0}, sK[dydis] = {0};
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    sort(mas.begin(), mas.end());
    vec.push_back({mas[0], 1});
    for(int i = 1; i < n; i++){
        if(mas[i] == mas[i-1]){
            vec[vec.size()-1].second++;
        }else{
            vec.push_back({mas[i], 1});
        }
    }
    int m = vec.size();
    pref[0] = vec[0].first * vec[0].second;
    pK[0] = vec[0].second;
    for(int i = 1; i < m; i++){
        pref[i] = pref[i-1] + vec[i].first * vec[i].second;
        pK[i] = pK[i-1] + vec[i].second;
    }
    suf[m-1] = vec[m-1].first * vec[m-1].second;
    sK[m-1] = vec[m-1].second;
    for(int i = m-2; i > -1; i--){
        suf[i] = suf[i+1] + vec[i].first * vec[i].second;
        sK[i] = sK[i+1] + vec[i].second;
    }

    long long ans = inf;
    if(m == 1){
        cout << 0;
        return 0;
    }


    for(int i = 0; i < m; i++){
        long long prm = inf, ant = inf;
        if(i != 0) {
            long long K = k - vec[i].second;
            if(K <= 0){
                prm = 0;
            }else{
                prm = pK[i-1]*(vec[i].first -1)- pref[i-1]; // kiek reiks kad visi butu a-1
                prm += min(K, pK[i-1]);
                K -= min(K, pK[i-1]);
                if(K != 0){
                    prm += suf[i+1] - sK[i+1] *( vec[i].first+1);
                    prm += min(K, sK[i+1]);
                }
            }
        }
        if(i != m-1){
            long long K = k - vec[i].second;
            if(K <= 0){
                ant = 0;
            }else{
                ant = suf[i+1] - sK[i+1]*(vec[i].first+1) ; // kiek reiks kad visi butu a-1
                ant += min(K, sK[i+1]);
                K -= min(K, sK[i+1]);
                if(K != 0){
                    ant += pK[i-1] * (vec[i].first-1) - pref[i-1];
                    ant += min(K, pK[i-1]);
                }
            }
        }
        ans = min(ans, min(prm, ant));
    }
    cout << ans;
    return 0;
}
