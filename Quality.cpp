//#include "quality.h"
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 3e3 +  1;
int mas[dydis][dydis];
int n, m, w, h;
int pref[dydis][dydis];
int sm(int e1, int s1, int e2, int s2){
    int vk = 0, vd = 0, ak = 0, ad = 0;
    if(e1 != 0 && s1 != 0) vk = pref[e1-1][s1-1];
    if(e1 != 0) vd = pref[e1-1][s2];
    if(s1 != 0) ak = pref[e2][s1-1];
    ad = pref[e2][s2];
    return ad - vd - ak + vk;
}
bool f(int x){
    for(int i = 0; i < n; i++){
        int sm = 0;
        for(int j = 0; j < m; j++){
            sm += mas[i][j] <= x;
            pref[i][j] = (i == 0 ? 0 : pref[i-1][j]) + sm;
        }
    }

    for(int i = 0; i <= n-h; i++){
        for(int j = 0; j <= m-w; j++){
            if(sm(i, j, i+h-1, j+w-1) >= w * h / 2 + 1) return true;
        }
    }
    return false;
}
int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	n = R, m = C, w = W, h = H;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) mas[i][j] = Q[i][j];
     int l = 1; int r = n * m;

    int ans = 1e9;
    while(l <= r){
        int mid = (l + r) / 2;
        if(f(mid)){
            r = mid-1;
            ans = min(ans, mid);
        }else{
            l = mid+1;
        }
    } 
    return ans;

}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> w >> h;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> mas[i][j];
    cout << rectangle(n, m, h, w, mas);
    return 0;

}
