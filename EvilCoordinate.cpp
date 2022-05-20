#include <bits/stdc++.h>
using namespace std;
char ch[4] = {'L', 'R', 'U', 'D'};
int main(){
    int t; cin >> t;
    while(t--){
        int x, y; cin >> x >> y;
        string a; cin >> a;
        int n = a.size();
        int X = 0, Y = 0;
        bool ans = 1;
        int kek[4] = {0}; // 0-L, 1-R, 2-U, 3-D
        for(auto z : a){
            if(z == 'U') {
                Y--;
                kek[2]++;
            }
            if(z == 'D') {
                Y++;
                kek[3]++;
            }
            if(z == 'L'){
                X--;
                kek[0]++;
            }
            if(z == 'R'){
                X++;
                kek[1]++;
            }
        }
        
        if((X == x && y == Y) || (X == 0 && Y == 0)){
            cout << "Impossible";
            return 0;
        }
        if(Y == 0) {
            int pX = kek[0] + kek[1];
            if( (pX > 0 && pX >= x) || (pX < 0 && pX <= x) ){
                if(kek[2] == 0 && kek[3] == 0){
                    cout << "Impossible";
                    return 0;
                }
                string ret = "";
                if(kek[2] > 0){
                    ret.push_back('U');
                    kek[2]--;
                }else if(kek[3] > 0){
                    ret.push_back('D');
                    kek[3]--;
                }
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < kek[i]; j++){
                        ret.push_back(ch[i]);
                    }
                }
                cout << ret;
                return 0;
            }else{
                string ret = "";
                if(pX < 0){ // pirmiau R
                    for(int i = 0; i < kek[1];i++){
                        ret.push_back('R');
                    }
                    kek[1] = 0;
                }else{ // pirmiau L
                    for(int i = 0; i < kek[0]; i++){
                        ret.push_back('L');
                        kek[0] = 0;
                    }
                }
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < kek[i]; j++){
                        ret.push_back(ch[i]);
                    }
                }
                cout << ret;
                return 0;
            }

        }else{
            if(X == x){
                if(kek[0] + kek[1] == 0){
                    if((Y < 0 && Y <= y) || (Y > 0 && Y >= y)){
                        cout << "Impossible";
                        return 0;
                    }else{
                        if(Y < 0){ // pirma U
                            
                        }
                        if(Y > 0){ // pirma D
                        
                        }
                    }
                }else{
                    string ret = "";
                    for(int i = 0; i < kek[0]; i++){
                        ret.push_back('L');
                    }
                    if(kek[1] == 0){
                        ret.pop_back();
                        kek[0]++;
                    }

                }
            }else{
                cout << a;
                return 0;
            }
        }
    }
    return 0;
}
