#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> nxt, ans;
bool galima = 1;
int it = 0;
void f(int l, int r, int mn, int mx){
    if(it++ > 15) return;
    if(r < l) return;
    if(!galima) return;
    cout << l << "; " << r << "; " << mn << "; " << mx << endl;
    for(int i = l; i <= r; i++){
        if(nxt[i] == -1){
            ans[i] = mx; mx--;
            continue;
        }
        if(nxt[i] == r+1){
            ans[i] = mx;
            mx--;
            f(i+1, r, mn, mx);
            i = r;
        }else if(nxt[i] > r+1){
            galima = 0; return;
        }else{

            ans[i] = mn + (nxt[i]-i)-1;
            ans[nxt[i]] = mn + nxt[i] - i;
            f(i+1, nxt[i]-1, mn, ans[i]-1);
            mn = ans[nxt[i]] + 1;
            i = nxt[i]-1;
        }
    }
}
int main(){
    int t; cin >> t;
    while(t--){
        cin >> n; nxt.resize(n); ans.resize(n);
        for(auto &x : ans) x = -1;
        it = 0;
        galima = 1;
        for(auto &x : nxt){
            cin >> x; x--;
        }
        cout << "cioned!" << endl;
        f(0, n-1, 0, n-1);
        if(!galima){
            cout << -1 << "\n";
        }else{
            for(auto x : ans){
                cout << x+1 << " ";
            }
            cout << "\n";
        }


    }
    return 0;
}
