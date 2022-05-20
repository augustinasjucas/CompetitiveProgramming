#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int> > kampai = {{4, 5}, {4, 11}, {4, 17}, {7, 8}, {7, 14}, {10, 5}, {10, 11}, {10, 17}, {13, 8}, {13, 14}, {16, 5}, {16, 11}, {16, 17}};
vector<pair<int, int> > visi;
int n;
pair<long long, long long> daug(pair<long long, long long> a, long long x){
    return {a.first*x, a.second*x};
}
bool ask(long long x, long long y){
    if(x > n || y > n || y <= 0 || x <= 0) return false;
/*    for(auto z : visi) if(z.first == x && z.second == y) {
        cout << x << ", " << y << " = true\n";
        return true;
    }
    return false;*/
    cout << "examine " << x << " " << y  << endl; 
    string a; cin >> a;
    return a == "true";
}
pair<long long, long long> daryk(int x, int y, pair<int, int> dir){ 
    for(long long i = 30; i > -1; i--){
        long long sk = (1 << i);
        auto busiu = daug(dir, sk);
        long long px = x + busiu.first; long long py = y + busiu.second;
        if(ask(px, py)){
            x = px; y = py;
        }
    }
    return {x, y};
}
int main(){
    for(auto x : kampai){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                visi.push_back({j + x.second, i + x.first});
//                cout << "dedu " << j + x.second << "; " << i + x.first << endl;
            }
        }
    }
    int x, y; cin >> n >> x >> y;
    pair<int, int> st = {x, y};
    auto bs = daryk(st.first, st.second, make_pair(-1, 1));
    if(ask(bs.first - 1, bs.second)){ // reiks eiti i kaire
        for(int j = 0; j < 3; j++) bs = daryk(bs.first, bs.second, make_pair(-1, 0));
    }else if(ask(bs.first, bs.second + 1)){
        for(int j = 0; j < 3; j++) bs = daryk(bs.first, bs.second, make_pair(0, 1));
    }
//    cout << "X = " <<x << ", Y = " << y << endl;
    st = bs;
    auto prm = daryk(st.first, st.second, make_pair(1, -1));
    auto ant = daryk(st.first, st.second, make_pair(-1, 1));
    x = (prm.first + ant.first) / 2ll;
    y = (prm.second + ant.second) / 2ll;
    st = {x, y};
    prm = daryk(st.first, st.second, make_pair(-1, -1));
    ant = daryk(st.first, st.second, make_pair(1, 1));
    x = (prm.first + ant.first) / 2ll;
    y = (prm.second + ant.second) / 2ll;
    cout <<"solution " <<  x << " " << y;

    return 0;
}
