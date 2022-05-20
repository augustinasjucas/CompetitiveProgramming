#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e3 + 10;
int mas[dydis][dydis];
int vl[dydis][dydis] = {0};
int taken[dydis][dydis] = {0};
int delK[dydis][dydis] = {0};
vector<pair<int, int> >  vc = {{-1, -1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
void atn(int e, int s){
    for(auto x : vc){
        int pe = e + x.first;
        int ps = s + x.second;
        if(pe < 0 || ps < 0 || pe >= n || ps >= n){
            continue;
        }
        if(taken[pe][ps]){
            continue;
        }
        if(delK[pe][ps] == 1){
            vl[e][s] -= mas[pe][ps];
        }
    }
   
}

void dlt(int e, int s){
    for(auto x : vc){
        int pe = e + x.first;
        int ps = s + x.second;
        if(pe < 0 || ps < 0 || pe >= n || ps >= n){
            continue;
        }
        if(taken[pe][ps]) continue;
        delK[pe][ps]++;
        if(delK[pe][ps] == 1){
            atn(pe, ps);
        }else if(delK[pe][ps] == 2){
            taken[pe][ps] = 1;
        }
    }
}
int main(){
    priority_queue<pair<int, pair<int, int> > > q; 
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> mas[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            q.push({mas[i][j], {i, j}});
            vl[i][j] = mas[i][j];
        }
    }
    while(!q.empty()){
    
    }
    return 0;
}
