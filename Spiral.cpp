#include <bits/stdc++.h>
using namespace std;
void print(vector<long double> f){
    for(int i = 0; i < f.size(); i++){
        cout << f[i] << "x^" << i;
        if(i != f.size()-1) cout << " + ";
    }
}
long long pw(long long x, long long y){
    long long ret = 1;
    for(int i = 0; i < y; i++) ret = ret * x;
    return ret;
}
/*long long f(double k, double h){ // staciakampis [k; h] dydzio, k - plotis, h - aukstis
    h--;
    return k * ((4 / 3.0) * h*h*h + 7/2.0 * h*h + 13/6.0 * h) + k * (k + 1) * (h + 1) / 2.0;
}*/
long long kvad(int x){  // kvadrato krastines aukstis h, plotis h+1;
    x--;
    return 2 * x*x*x*x + 28/3.0 *x*x*x + 31/2.0*x*x + 67/6.0 * x + 3;
}

vector<long double> smF2(vector<long double> f){    // g(x) = f(0) + f(1) + f(2) + ... + f(x)
                                                    // ax^2 + bx + c
    vector<long double> ret(4, 0);
    long double a = f[2];
    long double b = f[1];
    long double c = f[0];
    ret[0] = c;
    ret[1] = c + (a + b) / 2.0 - a / 3.0;
    ret[2] = (a + b) / 2.0;
    ret[3] = a / 3.0;
    cout << "f = ";
    print(f);
    cout << ", F = ";
    print(ret);
    cout << endl;
    return ret;
}

vector<long double> smF3(vector<long double> f){
    vector<long double> ret(5, 0);
    long double a = f[3];
    long double b = f[2];
    long double c = f[1];
    long double d = f[0];
    ret[0] = d;
    ret[1] = a / 4.0 - (3*a / 2.0 + b) / 3.0 + (a / 2.0 + b + c) / 2.0 + d;
    ret[2] = (a / 2.0  + b + c) / 2.0 ;
    ret[3] = (3*a/2.0 + b) / 3.0;
