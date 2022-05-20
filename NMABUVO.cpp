#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
const int inf = 1e9;
int n, q;
vector<int> mas;
vector<pair<int, int> > teig; // didejantys intervalai
vector<pair<int, int> > neig; // mazejantys intervalai

vector<int> vec; // skirtumai: B[i] = A[i+1] - A[i]
int prm = 0;
void print(){
    int cur = prm;
    cout << cur << " ";
    for(int i = 0; i < n-1; i++){
        cur += vec[i];
        cout << cur << " ";
    }
    cout << "\n";

}
void pridek(vector<pair<int, int> > &teig, int ind){
    int des =  upper_bound(teig.begin(), teig.end(), make_pair(ind, inf)) - teig.begin();
    int kair = des-1;
    if(0 <= kair && kair < (int)teig.size() && 0 <= des && des < (int)teig.size() && teig[kair].second == teig[des].first-2){ // sitas bus per viduriukai
        int L = teig[kair].first; int R = teig[des].second;
        teig.erase(teig.begin() + des);
        teig.erase(teig.begin() + kair);
        teig.push_back({L, R});
        sort(teig.begin(), teig.end());
    }else if(0 <= kair && kair < (int)teig.size() && teig[kair].second+1 == ind){
        int L = teig[kair].first; int R = teig[kair].second+1;
        teig.erase(teig.begin() + kair);
        teig.push_back({L, R});
        sort(teig.begin(), teig.end());
    }else if(0 <= des && des < (int)teig.size() && teig[des].first -1 == ind){
        int L = teig[des].first-1; int R = teig[des].second;
        teig.erase(teig.begin() + des);
        teig.push_back({L, R});
        sort(teig.begin(), teig.end());
    }else{
        teig.push_back({ind, ind});
        sort(teig.begin(), teig.end());
    }
}
void atimk(vector<pair<int, int> > &teig, int ind){
    int kr = upper_bound(teig.begin(), teig.end(), make_pair(ind, inf)) - teig.begin() - 1;
    int pL = teig[kr].first;
    int pR = teig[kr].second;
    teig.erase(teig.begin() + kr);
    if(pL <= ind-1) teig.push_back({pL, ind-1});
    if(ind+1 <= pR) teig.push_back({ind+1, pR});
    sort(teig.begin(), teig.end());

}
void add(int ind, int kek){ // prie i-ojo vec nario prideda kek
    if(ind >= (int)vec.size()) return;
    if(kek == 0) return ;
    if(ind == -1){
        prm += kek; return;
    }
    cout << "pries viska darant vec: "; for(auto x : vec) cout << x << " "; cout << endl;
    cout << "pliuso intervalai: "; for(auto x : teig) cout << "[" << x.first << "; " << x.second << "]";
    cout << endl << "minuso intervalai: "; for(auto x : neig) cout << "[" << x.first << "; " << x.second << "]";
    cout << "\n\npaskui vec = ;";
    int bv = vec[ind];
    vec[ind] += kek;
    if(bv == 0){
//        cout << "darau sita!" << endl;
        atimk(neig, ind);
        atimk(teig, ind);

        if(vec[ind] > 0){ // su teig
            pridek(teig, ind);
        }else{
            pridek(neig, ind);
        }
   }else if(bv < 0 && vec[ind] >= 0){ // tapo teigiamu, buvo neigiamas
        atimk(neig, ind);
        pridek(teig, ind);
        if(vec[ind] == 0) pridek(neig, ind);

    }else if(bv > 0 && vec[ind] <= 0){ // tapo neigiamu
        atimk(teig, ind);
        pridek(neig, ind);
        if(vec[ind] == 0) pridek(teig, ind);
    }
    for(auto x : vec) cout << x << " "; cout << endl;
    cout << "pliuso intervalai: "; for(auto x : teig) cout << "[" << x.first << "; " << x.second << "]";
    cout << endl << "minuso intervalai: "; for(auto x : neig) cout << "[" << x.first << "; " << x.second << "]";
    cout << endl << endl << endl;

}
long long sum(int l, int r){
    long long ret = 0;
    for(int i = l; i <= r; i++) ret += vec[i];
    return ret;
}
void shiftLeft(int l, int r){
    for(int i = l; i <= r; i++){
        if(i == vec.size()-1) continue;
        vec[i] = vec[i+1];
    }
}
void shiftRight(int l, int r){
    for(int i = r; i >= l; i--){
        if(i == 0) continue;
        vec[i] = vec[i-1];
    }
}
void kairen(int b, int a, int k){
    int tl = b-1;
    if(a == b){
        add(a, -k);
        add(a-1, +k);
        return ;
    }
    while(true){
        int i = min((int)(lower_bound(neig.begin(), neig.end(), make_pair(b, -1)) - neig.begin()), (int)neig.size()-1);
        while(i != -1 && neig[i].first >= b) i--;
        if(i == -1) break;
        if(neig[i].second < a) break;
        int R = neig[i].second;
        int L = neig[i].first;
        if(neig[i].first < a){
            L = a;
        }
        if(neig[i].second > b-1){ // sitas paskutinis ir uzbaigsiu jo viduryje
            R = b-1;
        }
        int l = L, r = R, mid;
        int tl = R+1;
        while(l <= r){
            mid = (l + r) / 2;
            if(-sum(mid, R) > k){
                l = mid+1;
            }else{
                tl = min(tl, mid);
                r = mid-1;
            }
        }
        if(tl == L){ // imsim visa
            int pr = vec[R];
            k -= -sum(L, R);
            shiftRight(L+1, R);
            add(L, -vec[L]);
            add(R+1, pr);
        }else{ // imsim dali ir cia uzbaigsim
            if(tl != R+1){
                int pr = vec[R];
                k -= -sum(tl, R);
                shiftRight(tl+1, R);
                add(tl, -vec[tl]);
                add(R+1, pr);
            }
            add(tl-1, k); // tl
            add(tl, -k); // tl+1
            k = 0;
        }
        if(k == 0) break;
        b = tl-1;

    }
    add(a-1, +k); add(a, -k);

}
void desinen(int a, int b, int k){
    int tl = b-1;
    if(a == b){
        add(a, -k);
        add(a-1, +k);
        return ;
    }
    while(true){
        int i = max((int)(lower_bound(teig.begin(), teig.end(), make_pair(a, -1)) - teig.begin() - 1), 0);
        while(i != teig.size() && teig[i].second < a) i++;
        if(i == teig.size()) break;
        if(teig[i].first >= b) break;

        int L = teig[i].first;
        int R = teig[i].second;
        if(teig[i].first < a){ // is kaires sitas yra
            L = a;
        }
        if(teig[i].second > b-1){ // sitas paskutinis ir uzbaigsiu jo viduryje
            R = b-1;
        }
        int l = L, r = R, mid;
        int tl = L-1;
        while(l <= r){
            mid = (l + r) / 2;
            if(sum(L, mid) > k){
                r = mid-1;
            }else{
                tl = max(tl, mid);
                l = mid+1;
            }
        }
        if(tl == R){ // imsim visa
            int pr = vec[L];
            k -= sum(L, R);
            shiftLeft(L, R-1);
            add(R, -vec[R]);
            add(L-1, pr);
        }else{ // imsim dali ir cia uzbaigsim
            if(tl != L-1){
                int pr = vec[L];
                k -= sum(L, tl);
                shiftLeft(L, tl-1);
                add(tl, -vec[tl]);
                add(L-1, pr);
            }
            add(tl, k);
            add(tl+1, -k);
            k = 0;
        }
        if(k == 0) break;
        a = tl+1;

    }
    add(b-1, +k); add(b, -k);
}

int sign(int a){
    return a / abs(a);
}
void precalc(){
    teig.clear();
    neig.clear();
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] < 0) continue;
        for(int j = i; j <= vec.size(); j++){
            if(j == vec.size() || vec[j] < 0){
                teig.push_back({i, j-1});
                i = j-1;
                break;
            }
        }
    }
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] > 0) continue;
        for(int j = i; j <= vec.size(); j++){
            if(j == vec.size() || vec[j] > 0){
                neig.push_back({i, j-1});
                i = j-1;
                break;
            }
        }
    }
}
int main(){
    cin >> n >> q;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    vec.resize(n-1);
    for(int i = 0; i < mas.size()-1; i++){
        vec[i] = mas[i+1] - mas[i];
    }
    prm = mas[0];
    precalc();
    for(int i = 0; i < q; i++){
        int a, b, c; cin >> a >> b >> c;
        if(a <= b){
            desinen(a, b, c);
        }else{
            kairen(a, b, c);
        }
    }
    int cur = prm;
    cout << cur << " ";
    for(int i = 0; i < n-1; i++){
        cur += vec[i];
        cout << cur << " ";
    }
    return 0;
}
/*
2 1
1 2 2

5 1
10 4 9 1 3
4 4 4
10 4 9 1 7

7 2
4 7 6 10 8 9 9
3 4 7
4 5 5


8 24
10 4 9 1 3 5 9 4
5 5 6
4 6 8
7 7 10
0 4 4
1 2 8
0 5 10
6 6 6
1 4 3
3 3 4
3 7 10
5 6 3
1 1 6
1 5 2
2 3 2
1 1 5
4 6 5
4 6 4
2 6 10
0 1 4
1 1 9
5 6 2
3 6 6
6 7 7
1 6 6

pries 23 queri(1, 6, 6) , mas = 14 36 16 18 21 23 24 27
8 1
14 36 16 18 21 23 24 27
1 6 6

7 4
10 4 9 1 3 5 9
2 1 1
4 2 3
5 0 8
5 4 3

8 10
10 4 9 1 3 5 9 4
5 5 6
6 4 8
7 7 10
4 0 4
2 1 8
5 0 10
6 6 6
4 1 3
3 3 4
7 3 10

8 1
13 12 12 16 9 11 17 14
7 3 10

6 6 6 3 2 1 8 9 3 14 9 7 9 9 9 10 10 10 6 7 4 8 8 9 9 9 8 8 13 16 16 16 13 13 12 12 12 11 13 19 19 19 18 17 17 17 16 16 13 13 13 13 13 22 19 19 18 16 15 13 14 21 21 21 19 19 19 24 24 24 16 22 22
6 6 6 3 2 1 8 9 3 14 9 7 9 9 9 10 10 10 6 7 4 8 6 9 9 9 8 8 13 16 16 16 13 12 12 12 11 8 11 16 16 16 16 15 15 15 14 12 10 8 8 8 8 17 14 14 13 11 9 7 8 15 15 15 13 13 13 18 18 18 10 16 16
*/
