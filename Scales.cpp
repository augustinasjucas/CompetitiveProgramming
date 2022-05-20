#include <bits/stdc++.h>
using namespace std;
vector<int> A;

int getLightest(int a, int b, int c){
    vector<pair<int, int> > ms = {{A[a-1], a}, {A[b-1], b}, {A[c-1], c}};
    sort(ms.begin(), ms.end());
    return ms[0].second ;
}
int getHeaviest(int a, int b, int c){
    vector<pair<int, int> > ms = {{A[a-1], a}, {A[b-1], b}, {A[c-1], c}};
    sort(ms.begin(), ms.end());
    return ms.back().second ;
}
void answer(vector<int> mas){
    cout << "answ!" << endl;
    cout << "ans = "; for(auto x : mas) cout << x << " ";
    exit(0);
}
map<set<int> , int> zinauL, zinauH;
void init(int t){

}
int getL(int a, int b, int c){
    set<int> st = {a, b, c};
    if(zinauL.count(st)) return zinauL[st];
    return zinauL[st] = getLightest(a, b, c);
}
int getH(int a, int b, int c){
    set<int> st = {a, b, c};
    if(zinauH.count(st)) return zinauH[st];
    return zinauH[st] = getHeaviest(a, b, c);
}
int ne(vector<int> vec, vector<int> pos){
//    cout << "vec=  "; for(auto x : vec) cout << x  << " "; cout << endl;
//    cout << "pos = "; for(auto x : pos) cout << x << " ";cout << endl;
    for(int i = 0; i < pos.size(); i++){
        bool st = 1;
        for(auto x : vec) if(pos[i] == x) st = 0;
        if(st) {
            
            return pos[i];
        }
    }
//    cout << "mn!" << endl;
    return -1;
}
int fMax(vector<int> mas){
    int cur = getHeaviest(1, 2, 3);
    cur = getHeaviest(cur, 4, 5);
    cur = getHeaviest(cur, 6, ne({cur, 6}, mas));
    return cur;
}
int fMin(vector<int> mas){
    int cur = getL(mas[0], mas[1], mas[2]);
    cur = getL(cur, mas[3], mas[4]);
    return cur;
}
int fMin4(vector<int> mas){
    int cur = getL(mas[0], mas[1], mas[2]);
    cur = getL(mas[3], ne({cur, mas[3]}, mas), cur);
    return cur;
}
vector<int> f3(vector<int> mas){
    int mn = getL(mas[0], mas[1], mas[2]);
    int mx = getH(mas[0], mas[1], mas[2]);
    int vd = ne({mn, mx}, mas);
    return {mn, vd, mx};
}
void orderCoins() {
    zinauL.clear(); zinauH.clear();
    vector<int> mas = {1, 2, 3, 4, 5, 6};
    int mx = fMax(mas);
    vector<int> lik;
    for(auto x : mas) if(x != mx) lik.push_back(x);
    int mn = fMin(lik);
    lik.clear();
    for(auto x : mas) if(x != mx && x != mn) lik.push_back(x);
    int an = fMin4(lik);
    lik.clear();
    for(auto x : mas) if(x != mn && x != mx && x != an) lik.push_back(x);
    vector<int> rest = f3(lik);
    answer({mn, an, rest[0], rest[1], rest[2], mx});
}
int main(){
    for(int i = 0; i < 6; i++){
        int a; cin >> a;
        A.push_back(a);
    }
    orderCoins();
    return 0;
}
