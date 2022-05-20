#include <bits/stdc++.h>
using namespace std;
vector<string> kas = {
    "1110111",    //0
    "0010010",          //1
    "1011101",          //2
    "1011011",          //3
    "0111010",          //4
    "1101011",          //5
    "1101111",          //6
    "1010010",          //7
    "1111111",          //8
    "1111011",          //9

};
pair<int, int> pl(int h, int m, int x){ // prideda x minuciu prie laiko
    int viso = 60*h + m + x;
    viso %= 60*24;
    int hh = viso /60;
    int mm = viso-hh*60;
    return {hh, mm};
}
bool check(int h, int m, vector<pair<int, int> > &mas){
    if(h == 9 && m == 58)cout << "try " << h << ":" << m << endl;
    int n = mas.size();
    vector<vector<int> > rez(4);
    for(auto &x : rez){
        for(int i = 0; i < 7; i++) x.push_back(0);
    }
    for(int i = 0; i < n; i++){
        
        auto laikas = pl(h, m, i);
        int hh = laikas.first;
        int mm = laikas.second;

        vector<int> turiBut = {(h/10)%10, hh%10, (mm/10)%10, mm%10};
        vector<int> yra = {(mas[i].first/10)%10, mas[i].first%10, (mas[i].second/10)%10, mas[i].second%10};
        if(h == 9 && m == 58){
            cout << "ziuriu i laika " << hh << ": " << mm << ", turi but: " << turiBut[0] << turiBut[1] << ": " << turiBut[2] << turiBut[3] << ", o yra " <<  yra[0] << yra[1] << ": " << yra[2] << yra[3] << endl;
        }
        for(int g = 0; g < 4; g++){
            int l = g%8;

            string yr = kas[yra[l]];
            string turi = kas[turiBut[l]];
            if(h==9 && m==58)cout << "yr = " << yr << ",\ntu = " << turi << endl << endl;
            for(int j = 0; j < 7; j++){
                int sitas = 0;
                if(yr[j] == '1'){
                    if(turi[j] == '1') sitas = 1;
                    if(turi[j] == '0'){
                        if(h == 9 && m == 58) cout << j << "yra j, " << h << ". ret false\n"; 
                        
                        return false;
                    }

                }else{ // yr[j] == '0'
                    if(turi[j] == '1') sitas = -1;
                    if(turi[j] == '0') sitas = 0;
                }
                if(rez[0][j] == 0) rez[0][j] = sitas;
                else{
                    
                    if(rez[0][j] != sitas){
                        if(h == 0 && m == 58) cout << "ret falseaa\n";
                        if(sitas != 0) return false;
                    }
                    rez[0][j] = sitas;
                }
            }
        }
    }
    return true;

}
int main(){
    for(auto x : kas){
        if(x[0]=='1') cout << "---\n"; 
        else cout << "   \n";
        if(x[1]=='1') cout << "| ";
        else cout << "  ";
        if(x[2]=='1') cout << "|\n";
        else cout << "\n";
        if(x[3]=='1') cout << "---\n";
        else cout << "\n";
        if(x[4] =='1') cout << "| ";
        else cout << "  ";
        if(x[5] =='1') cout << "|\n";
        else cout << "\n";
        if(x[6] == '1') cout << "---\n";
        else cout << "\n";
        cout << endl << endl;
    }   
    int n;
    while(cin >> n){
        vector<pair<int, int> > ms;
        for(int i = 0; i < n; i++){
            int a, b; char c;
            cin >> a >> c >> b;
            ms.push_back({a, b});
        }
        vector<pair<int, int> > ans;
        for(int i = 0; i <= 23; i++){
            for(int j = 0; j <= 59; j++){
                if(check(i, j, ms)) {
                    cout << i << ", " << j << " veikia\n";
                    ans.push_back({i, j});
                }
            }
        }
        cout << "ans = [";
        for(auto x : ans){
            cout << x.first << ":" << x.second << " ";
        }
        cout << "\ndon\n";
    }
    return 0;
}
