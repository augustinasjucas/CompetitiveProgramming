#include <bits/stdc++.h>
using namespace std;
int n;
string a;
vector<int> sm;
long long ans = 0;
string pos[7] = {"xxx", "xxA", "xA/", "xAA", "A/x", "A/A", "AA-"};
bool tinka(string st, string model){
    for(int i = 0; i < 3; i++){
        if(st[i] == '?') continue;
        if(model[i] == 'A'){
            if('0' <= st[i] || st[i] <= '9') continue;
            return false;
        }
        if(model[i] == st[i]) continue;
        return false;
    } 
    return true;
}
int kek = 0;
int nzn = 20;
int skaiciuok(){

}
void darom(int ind){
    if(ind == n){
        cout << "" << a << "\n";
        kek++;
        ans += skaiciuok(0, nzn, nzn);
        return;
    }
    if(ind == n-1){
        int i1 = ind*2;
        int i2 = ind*2 + 1;
        int i3 = ind*2 + 2;
        string st = "";
        st.push_back(a[i1]);
        st.push_back(a[i2]);
        st.push_back(a[i3]);
        for(auto x : pos){
            string past = st;
            if(tinka(st, x)){
                if(x[0] != 'A') a[i1] = x[0];
                if(x[1] != 'A') a[i2] = x[1];
                if(x[2] != 'A') a[i3] = x[2];
            }
            darom(ind+1);
            a[i1] = past[0];
            a[i2] = past[1];
            a[i3] = past[2];
        }
    }else{
        int i1 = ind*2; 
        int i2 = ind*2 + 1;
        if(a[i1] == '?'){
            if(a[i2] == '?'){ // ??
//                cout << ind << ", darau klaustuka!\n";
                darom(ind+1);
                a[i1] = 'x'; a[i2] = '-';
//                cout << ind << ", darau straika!\n";
                darom(ind+1);
//                cout << ind << ", darau sparea\n"; 
                a[i1] = '?'; a[i2] = '/';
                darom(ind+1);               
                a[i1] = '?';
                a[i2] = '?';
            }else if(a[i2] == '-'){ // ?-
                a[i1] = 'x';
                darom(ind+1);
            }else if(a[i2] == '/'){ // ?/
                darom(ind+1);
            }else if('0' <= a[i2] && a[i2] <= '9'){ // ?A
                darom(ind+1);
            }else{
                // blogai!
            }
        }else if(a[i1] == 'x'){
            a[i2] = '-';
            darom(ind+1);
        }else if('0' <= a[i1] && a[i1] <= '9'){ 
            if(a[i2] == '?'){//A?
                a[i2] = '/';
                darom(ind+1);
                a[i2] = '?';
                darom(ind+1);
            }else{ // A/
                darom(ind+1);
            }
        }else{
            // blogai
        }
    }
}
int main(){
    int q; cin >> q;
    while(q--){
        cin >> n >> a;
        sm.resize(n);
        ans = 0;
        for(auto &x : sm) cin >> x;
        darom(0);
        cout << "kek = " << kek << endl;
    }
    
    return 0;
}
