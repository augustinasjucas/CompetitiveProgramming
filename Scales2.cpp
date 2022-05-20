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
int getMedian(int a, int b, int c){
    vector<pair<int, int> > ms = {{A[a-1], a}, {A[b-1], b}, {A[c-1], c}};
    sort(ms.begin(), ms.end());
    return ms[1].second ;
}
int getNextLightest(int a, int b, int c, int d){
    vector<pair<int, int> > ms = {{A[a-1], a}, {A[b-1], b}, {A[c-1], c}};
    sort(ms.begin(), ms.end());
    for(int i = 0; i < 3; i++) if(ms[i].first > A[d-1]) return ms[i].second;
    return ms[0].second ;
}
void answer(vector<int> mas){
    cout << "answ!" << endl;
    cout << "ans = "; for(auto x : mas) cout << x << " ";
    exit(0);
}
void init(int t){

}
vector<int> gr[7];
int isMore[7][7] = {0};
vector<int> mas = {1, 2, 3, 4, 5, 6};
void normalize(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            for(int h = 0; h < 7; h++){
                if(isMore[j][i] == 1 && isMore[i][h] == 1) isMore[j][h] = 1;
            }
        }
    }
}
void doMin(int a, int b, int c){
    int mn = getLightest(a, b, c);
    isMore[a][mn] = 1;
    isMore[b][mn] = 1;
    isMore[c][mn] = 1;
    isMore[mn][mn] = 0;
}
void doMax(int a, int b, int c){
    int mx = getHeaviest(a, b, c);
    isMore[mx][a] = 1;
    isMore[mx][b] = 1;
    isMore[mx][c] = 1;
    isMore[mx][mx] = 0;
}
void doMedian(){

}
void doNextLightest(int a, int b, int c, int d){ // d->a, d->b. d nera i c
    int nxt = getNextLightest(a, b, c, d);
    isMore[nxt][a] = 1;
    isMore[nxt][b] = 1;
    isMore[nxt][c] = 1;
    isMore[nxt][nxt] = 0;
}
vector<int> yraGrand(){
    vector<int> ms;
    for(int i = 1; i <= 6; i++) ms.push_back(i);
    do{
        bool sitas = 1;
        for(int i = 0; i < 5; i++) if(isMore[ms[i]][ms[i+1]] != 1) sitas = 0;
        if(sitas) return ms;
    }while(next_permutation(ms.begin(), ms.end()));
    return {-1};
}
void orderCoins() {
    for(int i = 0; i < 7; i++) for(int j = 0; j < 7; j++) isMore[i][j] = -1;
    for(auto &x : gr) x.clear();
    int kekkk = 0;
    while(true){
        if(kekkk++ > 10) break;
        normalize();
        auto grd = yraGrand();
//        cout << "darau" << endl;
        if(grd != (vector<int>){-1}){
            reverse(grd.begin(), grd.end());
//            cout << "jau! " <<endl;
            answer(grd);
        }
        srand(time(0));
        vector<int> eil = {1, 2};
        shuffle(eil.begin(), eil.end(), default_random_engine(rand()));
        
        for(auto x : eil){
//            cout << "bandau " << x << endl;
            if(x == 1){ // maxas
                pair<int, vector<int> > ps = {3, {}};
                for(int i = 1; i <= 6; i++){
                    for(int j = i+1; j <= 6; j++){
                        for(int h = j+1; h <= 6; h++){
                            if(isMore[i][j] == 1 && isMore[i][h] == 1) continue;
                            if(isMore[j][i] == 1 && isMore[j][h] == 1) continue;
                            if(isMore[h][i] == 1 && isMore[h][j] == 1) continue;
                            ps = min(ps, {isMore[i][j] + isMore[i][h], {i, j, h}});
                        }
                    }
                }
                if(ps.first != 3){
                    doMax(ps.second[0], ps.second[1], ps.second[2]);
                    break;
                }
            }else if(x == 2){ // minas
                pair<int, vector<int> > ps = {3, {}};
                for(int i = 1; i <= 6; i++){
                    for(int j = i+1; j <= 6; j++){
                        for(int h = j+1; h <= 6; h++){
                            if(isMore[j][i] == 1 && isMore[h][i] == 1) continue;
                            if(isMore[i][j] == 1 && isMore[h][j] == 1) continue;
                            if(isMore[i][h] == 1 && isMore[j][h] == 1) continue;
                            ps = min(ps, {isMore[j][i] + isMore[h][i], {i, j, h}});
                        }
                    }
                }
                if(ps.first != 3){
                    doMin(ps.second[0], ps.second[1], ps.second[2]);
                    break;
                }
            }else if(x == 3){ // antras
                pair<int, vector<int> > ps = {3, {}};
                for(int i = 1; i <= 6; i++){
                    for(int j = i+1; j <= 6; j++){
                        for(int h = j+1; h <= 6; h++){
                            for(int l = 1; l <= 6; l++){
                                if(l == i || l == j || l == h) continue;
                                if(!isMore[l][i] || !isMore[l][j] || isMore[l][h]) continue;
                                ps = min(ps, {1, {i, j, h, l}});
                            }
                        }
                    }
                }
                if(ps.first != 3){
                    doNextLightest(ps.second[0], ps.second[1], ps.second[2], ps.second[3]);
                    break;
                }
           
            }
        }
    }
}
int main(){
    for(int i = 0; i < 6; i++){
        int a; cin >> a;
        A.push_back(a);
    }
    orderCoins();
    return 0;
}
