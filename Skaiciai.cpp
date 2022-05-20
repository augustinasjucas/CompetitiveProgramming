#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")

using namespace std;
bool used[65] = {};
int n, k;
vector<int> pos(vector<int> &eil){
    for(int i = 0; i <= n; i++) used[i] = 0;
    vector<int> ret;
    for(auto x : eil){
        bool galima = 1;
        for(int i = 1; i < x; i++){
            if( ((x << 1) - i <= 64) && used[i] && used[(x << 1) - i]){
                galima = false;
                break;
            }
        }
        if(galima)
            for(int i = 0; i <= n; i++){
                if(used[i]  && (i + x) % 2 == 0 && used[(i + x)/2]){
                    galima = false;
                    break;
                }
            }
        if(galima){
            used[x] = 1;
            ret.push_back(x);
        }
    }
    return ret;
}
vector<int> answ[65];
int main(){
    srand(time(0));
    for(int i = 1; i <= 64; i++){
        n = i;
        vector<int> ms(n);
        for(int i = 0; i < n; i++) ms[i] = i + 1;
        vector<int> ans;
        for(int i = 0; i < 1000000; i++){
            int seed = rand();
            shuffle(ms.begin(), ms.end(), default_random_engine(seed));
            auto rt = pos(ms);
            if(rt.size() > ans.size()) ans = rt;
        }
        sort(ans.begin(), ans.end());
        cout << ans.size() << "\n";
        for(auto x : ans) cout << x << " ";
        bool gd = 1;
        for(int i = 0; i < ans.size(); i++){
            for(int j = 0; j < ans.size(); j++){
                for(int h = 0; h < ans.size(); h++){
                    if(i == j || j == h || i == h) continue;
                    if(ans[i] + ans[j] == ans[h] * 2){
                        cout << ans[i] << " + " << ans[j] << " = " << ans[h] << endl;
                        gd = 0;
                    }
                }
            }
        }
        answ[n] = ans;
        cout << endl << "good: " << gd << endl;
    }
    cout << "{\n";
    for(int i = 1; i <= 64; i++){
        cout << "{";
        for(int j = 0; j < answ[i].size(); j++){
            cout << answ[i][j];
            if(j != answ[i].size()-1) cout << ", ";
        }
        cout << "}, // n = " << i <<", ans = " << answ[i].size() << "\n";
    }
    cout << "}";
    return 0;
}
