#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int n;
vector<int> vec;
const int dydis = 3e5 + 10;
int dp[dydis][33] = {0};
int toNext(int mas[2][2], int m0, int m1){
    return mas[0][1]*8 + m0*4 + mas[1][1]*2 + m1;
}
int f(int ind, int last){
    int mas[2][2] = {{((bool)(last&8)), ((bool)(last&4))}, {((bool)(last&2)), ((bool)(last&1))}}; // 1 jei ideta figura
    if(vec[ind] == 0){
        if(mas[0][1] == 1 || mas[1][1] == 1) return -inf;
    }
    if(vec[ind] == 1){
        if(mas[0][1] == 1) return -inf;
    }
//    if(ind == n)cout << "f(" << ind << "), db turiu: " << endl << mas[0][0] << " " << mas[0][1] << "\n" << mas[1][0] << " " << mas[1][1] << endl << endl;
    if(ind == n) return 0;
    if(dp[ind][last] != -1) return dp[ind][last];
    if(vec[ind] == 0){
        mas[0][1] = 1;
        mas[1][1] = 1;
    }
    if(vec[ind] == 1){
        mas[0][1] = 1;
    }
    int pos = -inf;
    if(mas[1][0] == 0 && mas[1][1] == 0 && vec[ind] >= 1){
        mas[1][0] = mas[1][1] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 0, 0))+1);
        mas[1][0] = mas[1][1] = 0;
    }
    if(mas[1][1] == 0 && vec[ind] >= 1){
        // mas[1][2] = 1;
        mas[1][1] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 0, 1))+1);
        mas[1][1] = 0;
    }
    if(mas[0][1] == 0 && mas[1][1] == 0 && vec[ind] >= 2){
        mas[0][1] = mas[1][1] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 0, 0))+1);
        mas[0][1] = mas[1][1] = 0;
    }
    if(mas[0][1] == 0 && mas[0][0] == 0 && vec[ind] >= 2){
        mas[0][1] = mas[0][0] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 0, 0))+1);
        mas[0][1] = mas[0][0] = 0;
    }
    if(mas[0][1] == 0 && vec[ind] >= 2){
        mas[0][1] = 1;
        //mas[0][2] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 1, 0))+1); 
        mas[0][1] = 0;
    }
    if(mas[0][0] == 0 && mas[0][1] == 0 && mas[1][1] == 0){
        // mas[1][2] = 1
        mas[0][0] = mas[0][1] = mas[1][1] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 0, 1))+2);
        mas[0][0] = mas[0][1] = mas[1][1] = 0; 
    }
    if(mas[0][1] == 0 && mas[1][0] == 0 && mas[1][1] == 0){
        // mas[0][2] = 1
        mas[0][1] = mas[1][0] = mas[1][1] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 1, 0))+2);
        mas[0][1] = mas[1][0] = mas[1][1] = 0; 
    }
    if(mas[0][0] + mas[0][1] + mas[1][0] + mas[1][1] == 0){
        mas[0][1] = mas[1][1] = mas[0][0] = mas[1][0] = 1;
        pos = max(pos, f(ind+1, toNext(mas, 0, 0))+2);
        mas[0][1] = mas[1][1] = mas[0][0] = mas[1][0] = 0;
    }
    pos = max(pos, f(ind+1, toNext(mas, 0, 0)));
    return dp[ind][last] = pos;
}

int main(){
    for(auto &x : dp){
        for(auto &y: x){
            y = -1;
        }
    }
    cin >> n; vec.resize(n);
    long long s = 0;
    for(auto &x : vec){
        cin >> x;
        if(x <= 2) continue;
        int take = x/2;
        int left = x-take*2;
        if(left == 0) {
            take--;
        }
        x = x-take*2;
        s += take;
    }
    vec.push_back(0);
    cout << s+f(0, 10);


    return 0;
}
