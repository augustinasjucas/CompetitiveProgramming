#include <bits/stdc++.h>
using namespace std;
const int dydis = 3e5 + 10;
int when[dydis];
bool vis[dydis];
bool f(vector<int> &vec, int shift, int m){
    vector<int> mas;
    for(int i  = shift; i < vec.size(); i++){
        mas.push_back(vec[i]);
    }
    for(int i = 0; i < shift; i++){
        mas.push_back(vec[i]);
    }
    for(int i = 0; i < mas.size(); i++) vis[i] = 0;
    int ret = mas.size();
    for(int i = 0; i < mas.size(); i++){
        if(vis[i]) continue;
        ret--;
        int x = i;
        while(!vis[x]){
            vis[x] = 1;
            x = mas[x];
        }
    }
    return ret <= m;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int n, k; cin >> n >> k;
        for(int i = 0; i < n; i++){
            when[i] = 0;
        }
        vector<int> mas(n);
        int i = 0;
        for(auto &x : mas) {
            cin >> x; x--;
            when[(i - x + n)%n]++;
            i++;

        }
        vector<int> pos;
        for(int i = 0; i < n; i++){
            if(when[i] >= n / 3) pos.push_back(i);
        }
        vector<int> ans;
        for(auto x : pos){
            if(f(mas, x, k)) ans.push_back(x);
        }
        cout << ans.size() << " ";
        for(auto x : ans){
            cout << x << " ";
        }
        cout << "\n";

    }
    return 0;
}
