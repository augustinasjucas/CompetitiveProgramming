#include <bits/stdc++.h>
using namespace std;
const long double PI = 3.14159265358979323;
#define atk pair<pair<int, int>, pair<int, int> >
#define vek pair<int, int>
long double ans = 0;
atk toAtk(int x1, int y1, int x2, int y2){ 
    return {{x1, y1}, {x2-x1, y2-y1}};
}
bool tinka (long long skait, long long vard, bool lyguTinka = 0){
    if(vard == skait) return lyguTinka;
    if(skait == 0) return lyguTinka;
    if(skait < 0 && vard < 0) skait *= -1, vard *= -1;
    if(skait < 0 || vard < 0) return false;
    return skait < vard;
}
bool inc(atk A, int X, int Y){ // Ar atkarpai A priklauso (X, Y)?
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int vard, skait;
    if(x1 == 0){ 
        skait = Y - b1;
        vard = y1;
    }else {
        skait = X - a1;
        vard = x1;
    }
    return tinka(skait, vard, 1);
}
bool ieinaPilnai(atk A, atk B){ // patikrinti, ar A ieina pilnai i b
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    int vard = (x2 * y1 - y2 * x1);
    if(vard != 0) return false;
    if(inc(B, a1, b1) && inc(B, a1+x1, b1+y1)) {
        return true;
    }
    return false;
}
bool susikirt(atk A, atk B){
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    if(vard == 0) return false;
    return tinka(skait, vard);
}
long double kurKertasiK(atk B, atk A){      // grazina B tieses K kooficienta, kur jie kertasi
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long double skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long double vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    return skait/vard;
}
bool lyg(atk A, atk B){
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    return vard == 0;
}
bool gale(atk A, atk B){      // ar tiese A kerta atkarpa B jos gale? t.y., ar k = 1?
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    double k = 1.0 * skait / (vard*1.0);
    //cout << "kertasi taske (" << a2 + x2 * k << ", " << b2 + y2 * k << ")\n";
    return (skait == vard);
}
bool prieky(atk A, atk B){      // ar tiese A kerta atkarpa B jos prieky? t.y., ar k = 1?
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    double k = 1.0 * skait / (vard*1.0);
    //cout << "kertasi taske (" << a2 + x2 * k << ", " << b2 + y2 * k << ")\n";
    return (skait == 0);
}
long double getK(atk A, int X, int Y){
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long double vard, skait;
    if(x1 == 0){ 
        skait = Y - b1;
        vard = y1;
    }else {
        skait = X - a1;
        vard = x1;
    }
    return skait / vard;
}
vector<pair<int, int> > vec;
vector<atk> brn;
int n;
long double kampas(vek a, vek b){ // koks kampas (einant pagal laikrodzio rodykle) nuo a iki b?
    long long prm = a.first*b.second - a.second * b.first;
    long long ant =  a.first * b.first + a.second*b.second;
    long double ret = 2*PI - atan2l(prm, ant);
    if(ret > 2*PI) ret -= 2*PI;
    cout << "kampas (" << a.first << ", " << a.second << ") -> (" << b.first << ", " << b.second << ") = " << ret << "\n"; 
    return ret;
}
bool yraTarp(vek prm, vek vid, vek ant){   // Ar einant palei laikrodzio rodykle nuo prm, vid bus vidury?
//    cout << "ar eiliskumas yra toks: (" << prm.first << ", " << prm.second << ") -> (" << vid.first << ", " << vid.second << "), (" << ant.first << ", " << ant.second << ") ";
    bool ans = kampas(prm, ant) >= kampas(prm, vid);
//    cout << ans<< endl;
    return ans;
}
bool arGerai(atk tiese, atk pirmas, atk antras){
    int X = tiese.first.first;
    int Y = tiese.first.second;
    pirmas.second.first *= -1;
    pirmas.second.second *= -1;
    vek ts = {-antras.first.first + tiese.first.first, -antras.first.second + tiese.first.second};
    // ar eiliskumas yra toks: (3, 0) -> (1, 1), (0, 2) 0
    return yraTarp(pirmas.second, ts, antras.second);

}
bool arGerai(atk tiese, atk pirmas){    
    return 0;
}
set<atk> blogos, geros;
void darom(int i, int j){

    int x1 = vec[i].first;
    int y1 = vec[i].second;
    int x2 = vec[j].first;
    int y2 = vec[j].second;
    auto A = toAtk(x1, y1, x2, y2);
    auto B = toAtk(x2, y2, x1, y1);
    auto C = A;
    long double blogMn = 1e18, atsMn = 0;
    long double blogMx = -1e18, atsMx = 1;
    vector<long double> ger = {0, 1};
    for(int i = 0; i < n; i++){
        if(brn[i] == A) continue;
        if(ieinaPilnai(brn[i], A) || (susikirt(brn[i], A) && susikirt(A, brn[i])) ){
            blogos.insert(A);
            break;
        }
        if(lyg(A, brn[i]) || prieky(A, brn[i])){                 // jei lygiagrecios tieses
            continue;            
        }else if(gale(A, brn[i])) {         // Tiese kerta sita atkarpa jos gale. tai cia yra kampas!
//            cout << "imu briauna (" << brn[i].first.first << ", " << brn[i].first.second << "),(" << brn[i].second.first << "," << brn[i].second.second << "). Ji bus pirma kampe\n";    
            if(A.first.first-brn[(i+1)%n].first.first == 0 && A.first.second-brn[(i+1)%n].first.second == 0){
                C = B;    
            }else{
                C = A;
            }
            if(arGerai(C, brn[i], brn[(i+1)%n])){
//                cout << "TIESE (" << A.first.first << ", " << A.first.second << "),(" << A.second.first << ", " << A.second.second << ") kerta kampa (" << brn[(i+1)%n].first.first << ", " << brn[(i+1)%n].first.second << ") IS GEROSIOS PUSES!" << endl;
                long double k = getK(C, brn[(i+1)%n].first.first, brn[(i+1)%n].first.second);
                ger.push_back(k);
            }else{
//                cout << "TIESE (" << A.first.first << ", " << A.first.second << "),(" << A.second.first << ", " << A.second.second << ") kerta kampa (" << brn[(i+1)%n].first.first << ", " << brn[(i+1)%n].first.second << ") IS BLOGOSIOS PUSES!" << endl;
                long double k = getK(C, brn[(i+1)%n].first.first, brn[(i+1)%n].first.second);
//                cout << "darysiu k = " << k << endl;            

                if(k > 0) blogMn = min(blogMn, k);
                if(k < 0) blogMx = max(blogMx, k);               
//                cout << "k = " << k << " netinka";        
                if(0 <= k && k <= 1){
                    blogos.insert(A);
                    break;
                }
            }
//            cout << endl;
            i++; 
        }else if(susikirt(A, brn[i])){
            long double k = kurKertasiK(A, brn[i]);
            if(0 <= k && k <= 1){
                blogos.insert(A);
                break;
            }
    
            if(kampas(brn[i].second, make_pair(A.first.first-brn[i].first.first, A.first.second-brn[i].first.second)) >= PI){
                cout << "TIESE (" << A.first.first << ", " << A.first.second << "),(" << A.second.first << ", " << A.second.second << "). su (" << brn[i].first.first << ", " << brn[i].first.second << "),(" << brn[i].second.first <<  "," << brn[i].second.second << ") kertasi, kai k = " << k << " ir tai yra GERAS susikirtimas"<< endl;
                cout << "o kampas = " << kampas(brn[i].second, make_pair(A.first.first-brn[i].first.first, A.first.second-brn[i].first.second)) << endl;
    //            cout << "darysiu k = " << k << endl;
    //            cout << "o gale = " << gale(A, brn[i] )<< endl;
                ger.push_back(k);
            }else{
//                cout <<
                if(k > 0) blogMn = min(blogMn, k);
                if(k < 0) blogMx = max(blogMx, k);               
            }
        }
    }
    
    cout << "gaunu blogMn = " << blogMn << ", blogMx = " << blogMx << endl;
    for(auto &x : ger){
        if(x >= blogMn || x <= blogMx) {
//            cout << "ignoruoju " << x << endl;
            continue;
        }
        if(x < 0) atsMn = min(atsMn, x);
        if(x > 0) atsMx = max(atsMx, x);
    }
    if(!blogos.count(A)){
        geros.insert(A);
    }
   
    long double X1 = A.first.first + A.second.first * atsMn;
    long double Y1 = A.first.second + A.second.second * atsMn;
    long double X2 = A.first.first + A.second.first * atsMx;
    long double Y2 = A.first.second + A.second.second * atsMx;
    if(!blogos.count(A)){
//        cout << "bmin = " << blogMn << ", bmax = " << blogMx <<".  ";
        cout << "TIESE (" << A.first.first << ", " << A.first.second << "),(" << A.second.first << ", " << A.second.second << "). Kertasi vietose: (" <<  X1 << ", " << Y1 << ") ir (" << X2 << ", " << Y2 << ")\n";
        long double tiesK = sqrtl(A.second.first * A.second.first + A.second.second * A.second.second);
        long double a = atsMx - atsMn;
        long double pos = a * tiesK;
        cout << "pos = " << pos << endl;
        ans = max(ans, pos);
        
    }

}
int main(){
    cin >> n;

    for(int i = 0; i < n; i++){
        int x1, y1; cin >> x1 >> y1;
        vec.push_back({x1, y1});
    }
    int x1, y1, x2, y2;
    for(int i = 0; i < n; i++){
        x1 = vec[i].first;
        y1 = vec[i].second;
        x2 = vec[(i+1)%n].first;
        y2 = vec[(i+1)%n].second;
        brn.push_back(toAtk(x1, y1, x2, y2));
    }
    atk A, B;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){    
            darom(i, j);
        }
    }
    cout <<"blogos:";
    for(auto x : blogos){
        cout << "(" << x.first.first << ", " << x.first.second << "), (" << x.second.first << ", " << x.second.second << ")\n" ;
    }

    cout << setprecision(20) <<ans;
    return 0;
}
/*

10
0 -4
4 -4
4 -3
1 -3
1 -1
3 -1
3 -2
4 -2
4 0
0 0

    */
