#include <bits/stdc++.h>
using namespace std;
const long double PI = 3.14159265358979323;
#define atk pair<pair<long long, long long>, pair<long long, long long> >
#define vek pair<long long, long long>
long double ans = 0;
void print(atk A){
    cout << "([" << A.first.first << ", " << A.first.second << "], [" << A.second.first << "," << A.second.second << "])";
}
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
bool inc(atk A, long long X, long long Y){ // Ar atkarpai A priklauso (X, Y)?
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;   
    long long vard, skait;
    /*
       a1 + x1 * c = X
       b1 + y1 * c = Y
       */
    if(x1 == 0){ 
        skait = Y - b1;
        vard = y1;
    }else {
        skait = X - a1;
        vard = x1;
    }
    return a1*vard + x1 * skait == X*vard && b1*vard + y1 * skait == Y*vard && tinka(skait, vard, 1);
}
bool inc1(atk A, long long X, long long Y){
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;   
    long long vard, skait;
    /*
       a1 + x1 * c = X
       b1 + y1 * c = Y
       */
    if(x1 == 0){ 
        skait = Y - b1;
        vard = y1;
    }else {
        skait = X - a1;
        vard = x1;
    }
    return a1*vard + x1 * skait == X*vard && b1*vard + y1 * skait == Y*vard;

}
bool ieinaPilnai(atk A, atk B){ // patikrinti, ar A ieina pilnai i b
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long long a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long vard = (x2 * y1 - y2 * x1);
/*    cout << "ar ";
    print(A);
    cout << " ieina pilnai i ";
    print(B);
    cout <<"?\n";*/
    if(vard != 0) return false;
    if(inc(B, a1, b1) && inc(B, a1+x1, b1+y1)) {
//        cout << "return true!" << endl;
        return true;
    }
    return false;
}
bool susikirt(atk A, atk B){
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long long a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    if(vard == 0) return false;
    return tinka(skait, vard);
}
long double kurKertasiK(atk B, atk A){      // grazina B tieses K kooficienta, kur jie kertasi
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long long a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long double skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long double vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
//    cout << "turiu TIESE B ([" << B.first.first << ", " << B.first.second << "],[" << B.second.first << "," << B.second.second << "]) \nir ji kertasi su KRASTINE";
//    cout << "([" << A.first.first <<", " << A.first.second << "],[" << A.second.first << "," << A.second.second << "]), kai k = " << skait / vard << endl << endl;
    return skait/vard;
}
bool lyg(atk A, atk B){
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long long a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    return vard == 0;
}
bool gale(atk A, atk B){      // ar tiese A kerta atkarpa B jos gale? t.y., ar k = 1?
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    int a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    long double k = 1.0 * skait / (vard*1.0);
    //cout << "kertasi taske (" << a2 + x2 * k << ", " << b2 + y2 * k << ")\n";
    return (skait == vard);
}
bool prieky(atk A, atk B){      // ar tiese A kerta atkarpa B jos prieky? t.y., ar k = 1?
    long long a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long long a2 = B.first.first, b2 = B.first.second, x2 = B.second.first, y2 = B.second.second;
    long long skait = (1ll * x1 * 1ll*(b2 - b1) + 1ll * y1 *1ll* (a1 - a2));
    long long vard = 1ll * (1ll*x2 * y1 -1ll* y2 * x1);
    long double k = 1.0 * skait / (vard*1.0);
    //cout << "kertasi taske (" << a2 + x2 * k << ", " << b2 + y2 * k << ")\n";
    return (skait == 0);
}
long double getK(atk A, int X, int Y){
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long double vard, skait;
    // a1 + c*x1 = X
    // b1 + c*y1 = Y
    // c = (X - a1) / x1
    // c = (Y - b1) / y1
    if(x1 == 0){ 
        skait = Y - b1;
        vard = y1;
    }else {
        skait = X - a1;
        vard = x1;
    }
//    cout << "getK([" << A.first.first << ", " << A.first.second << "][" << A.second.first << ", " << A.second.second << "]) su tasku (" << X << ", " << Y << ")   = " << skait / vard << endl;
    return skait / vard;
}
bool isBad(atk A, int X, int Y){
    int a1 = A.first.first, b1 = A.first.second, x1 = A.second.first, y1 = A.second.second;
    long long vard, skait;
    if(x1 == 0){ 
        skait = Y - b1;
        vard = y1;
    }else {
        skait = X - a1;
        vard = x1;
    }
    return abs(skait) < abs(vard);
}
vector<pair<int, int> > vec;
vector<atk> brn;
int n;
long double kampas(vek a, vek b){ // koks kampas (einant pagal laikrodzio rodykle) nuo a iki b?
    long long prm = a.first*b.second - a.second * b.first;
    long long ant =  a.first * b.first + a.second*b.second;
    long double ret = 2*PI - atan2l(prm, ant);
    if(ret > 2*PI) ret -= 2*PI;
//    cout << "kampas (" << a.first << ", " << a.second << ") -> (" << b.first << ", " << b.second << ") = " << ret << "\n"; 
    return ret;
}
bool yraTarp(vek prm, vek vid, vek ant){   // Ar einant palei laikrodzio rodykle nuo prm, vid bus vidury?
//    cout << "ar eiliskumas yra toks: (" << prm.first << ", " << prm.second << ") -> (" << vid.first << ", " << vid.second << "), (" << ant.first << ", " << ant.second << ") ";
    bool ans = kampas(prm, ant) >= kampas(prm, vid);
//    cout << "RETURN " << ans ;
//    cout << ans<< endl;
    return ans;
}
bool arGerai(atk tiese, atk pirmas, atk antras){
    int X = tiese.first.first;
    int Y = tiese.first.second;
    pirmas.second.first *= -1;
    pirmas.second.second *= -1;
    vek ts = {-antras.first.first + tiese.first.first, -antras.first.second + tiese.first.second};
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

    // ar sita tiese eina vidumi?
  /*  cout << "pirmiausiai check, arGERAI: tiese-";
    print(A);
    cout << "pirma briauna-"; 
    print(brn[(i-1+n) % n]);
    cout << ",  antra briauna-";
    print(brn[i]);
    cout << endl;*/
    if(!arGerai(B, brn[(i-1+n)%n], brn[(i+n)%n]) && (i + 1) % n != j && (j + 1) % n != i){
//        cout << "INSERT HERE" << endl;
        blogos.insert(A);
    }
    if(!arGerai(A, brn[(j-1+n)%n], brn[(j+n)%n]) && (i + 1) % n != j && (j + 1) % n != i){
//                cout << "INSERT HERE" << endl;
        blogos.insert(A);
    }

    for(int i = 0; i < n; i++){
  /*      print(A);
        cout << " vs ";
        print(brn[i]);
        cout << endl;*/
        if(brn[i] == A) continue;
//        cout << 
        if(ieinaPilnai(brn[i], A)) {
/*            cout << "ieina pilnai!" << endl;
            cout << "A = ";
            print(A);
            cout << ", o brn = ";
            print(brn[i]);
            cout << endl;*/
            blogos.insert(A);
            break;
        }else if((susikirt(brn[i], A) && susikirt(A, brn[i])) ){
//            cout << "kertasi!" << endl;
            blogos.insert(A);
            break;
        }

        if(lyg(A, brn[i])){

            if(inc1(A, brn[i].first.first, brn[i].first.second)) {       // inc1 -> 
//                cout << "taip pat jos yra toje pacioje tieseje!" << endl;
                long double k = getK(A, brn[i].first.first, brn[i].first.second);
                print(A);
                cout << " yra lygiagreti su ";
                print(brn[i]);
                cout << "o k = " << k << endl;
                if(!arGerai(A, brn[i], brn[(i+1)%n])){
                    if(k > 0) blogMn = min(blogMn, k);
                    if(k < 0) blogMx = max(blogMx, k);  
                    k = getK(A, brn[i].first.first + brn[i].second.first, brn[i].first.second + brn[i].second.second);
                    if(k > 0) blogMn = min(blogMn, k);
                    if(k < 0) blogMx = max(blogMx, k);
                }
                if(0 < k && k < 1) {
                    cout << "TAI BREAKINU!" << endl;
                    blogos.insert(A);
                    break;
                } 
            }
            continue;
        }else if(prieky(A, brn[i])){ // jei lygiagrecios 
            continue;             
        }else if(gale(A, brn[i])) {         
//            cout << "GALEE" << endl;
            long double times = 1;
            if(A.first.first-brn[(i+1)%n].first.first == 0 && A.first.second-brn[(i+1)%n].first.second == 0){
                C = B;    
//                times = -1;
            }else{
                C = A;
            }
    /*        cout << "ZIURMIEEEEE check, arGERAI: tiese-";
            print(C);
            cout << "pirma briauna-"; 
            print(brn[(i+n) % n]);
            cout << ",  antra briauna-";
            print(brn[(i+1)%n]);
            cout << endl << endl;*/

            if(arGerai(C, brn[i], brn[(i+1)%n])){
                long double k = getK(A, brn[(i+1)%n].first.first, brn[(i+1)%n].first.second);
//                cout << "TIESE (" << C.first.first << ", " << C.first.second << "),(" << C.second.first << ", " << C.second.second << "). su (" << brn[i].first.first << ", " << brn[i].first.second << "),(" << brn[i].second.first <<  "," << brn[i].second.second << ") kertasi, kai k = " << k << " ir tai yra GERAS susikirtimas"<< endl;
//                cout << "o kampas = " << kampas(brn[i].second, make_pair(A.first.first-brn[i].first.first, A.first.second-brn[i].first.second)) << endl;
                ger.push_back(k);
            }else{
                long double k = getK(A, brn[(i+1)%n].first.first, brn[(i+1)%n].first.second) ;
                if(isBad(A, brn[(i+1)%n].first.first, brn[(i+1)%n].first.second)){
                    blogos.insert(A);
                    break;
                }
//                cout << "NETINKA KAI k = " << k << endl;
                if(k > 0) blogMn = min(blogMn, k);
                if(k < 0) blogMx = max(blogMx, k);               
            }
//            i++; 
        }else if(susikirt(A, brn[i])){
            long double k = kurKertasiK(A, brn[i]);
            if(kampas(brn[i].second, make_pair(A.first.first-brn[i].first.first, A.first.second-brn[i].first.second)) >= PI){
//                cout << "tiese kerta krastine, kai k = " << k << endl;
                ger.push_back(k);
            }else{
                if(k > 0) blogMn = min(blogMn, k);
                if(k < 0) blogMx = max(blogMx, k);               
            }
        }
    }
//    cout << "tures buti intervale [" << blogMx << "; " << blogMn << "]\n";
    
    for(auto &x : ger){
        if(x >= blogMn || x <= blogMx) {
            continue;
        }
//        cout << "bandau " << x << endl;
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
        long double tiesK = sqrtl(A.second.first * A.second.first + A.second.second * A.second.second);
        long double a = atsMx - atsMn;
        long double pos = a * tiesK;
        ans = max(ans, pos);
        cout << "jei sujungiu (" << x1 << ", " << y1 << ") su (" << x2 << ", " << y2 << "), tai pratesus , pos = " << setprecision(10) << pos << endl;
    }else{
        cout << "negaliu sujungti (" << x1 << ", " << y1 << ") su (" << x2 << ", " << y2 << ")" << endl;
    }
//    cout << endl;
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
/*        cout << "idedu ";
        print(brn.back());
        cout << endl;*/
    }
    atk A, B;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){    
            darom(i, j);
        }
        cout << endl;
    }
/*    cout <<"blogos:";
    for(auto x : blogos){
        cout << "(" << x.first.first << ", " << x.first.second << "), (" << x.second.first << ", " << x.second.second << ")\n" ;
    }*/
    cout << setprecision(200) <<ans;
    return 0;
}


// f(x) atrodo taip (x-ui didejant):
//... 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 ... 
// ieskau maziausio x, kad f(x) = 1.

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


11
0 0
0 1
7 1
1 2
3 4
4 2
9 1
4 -4
4 -2
6 0
2 -1

11
0 0
2 -1
6 0
4 -2
4 -4
9 1
3 2
3 4
1 2
7 1
0 1


11
0 0
0 -1
8 -2
10 1
8 1
8 -1
3 -1
10 5
0 3
3 3
2 -1

12
0 0
2 -1
4 2
6 2
7 0
9 3
3 6
9 7
-1 7
3 4
1 6
5 4


negaliu sujungti (8, 1) su (8, -1)
    */
//pirmiausiai check, arGERAI: tiese-([9, 1], [-2,0])pirma briauna-([4, -4], [5,5]),  antra briauna-([9, 1], [-6,1])
/*
18
0 0
4 0
4 1
1 1
1 5
0 5
0 3
-1 3
-1 1
-3 1
-3 -4
8 -4
8 4
6 4
6 -3
-1 -3
-1 -1
0 -1
jei sujungiu (0, -4) su (4, 0), tai pratesus

  ;*/
