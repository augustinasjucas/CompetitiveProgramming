#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
struct m{
    long long a;
    m(long long x = 0){
        a = x;
    }
    m operator - (m x) const {
        m ret = {a};
        ret.a = (ret.a - x.a + mod) % mod;
        return ret;
    }
    m operator - (long long x) const {
        m ret = {a};
        ret.a = (ret.a - x + mod) % mod;
        return ret;
    }
    m operator + (long long x) const {
        m ret = {a};
        ret.a = (ret.a + x) % mod;
        return ret;
    }
    m operator * (long long x) const {
        m ret = {a};
        ret.a = (ret.a * x) % mod;
        return ret;
    }
    m operator + (m x) const {
        m ret = {a};
        ret.a = (ret.a + x.a) % mod;
        return ret;
    }
    m operator * (m x) const {
        m ret = {a};
        ret.a = ret.a * x.a % mod;
        return ret;
    }
    m operator % (m x) const {
        m ret = {a};
        ret.a = ret.a % x.a % mod;
        return ret;
    }
    m operator % (long long x) const {
        m ret = {a};
        ret.a = ret.a % x % mod;
        return ret;
    }
    m operator = (long long x){
        a = x;
        return *this;
    }
    m operator = (m x){
        a = x.a;
        return *this;
    }
    m operator = (int x){
        a = x;
        return *this;
    }
    bool operator < (long long x) const {
        return a < x;
    }
    bool operator < (m x) const {
        return a < x.a;
    }
    bool operator == (long long x) const {
        return a == x;
    }
    bool operator == (m x) const {
        return a == x.a;
    }
    bool operator != (long long x) const {
        return a != x;
    }
    bool operator != (m x) const {
        return a != x.a;
    }
    bool operator >= (long long x) const {
        return a >= x;
    }
    bool operator >= (m x) const {
        return a >= x.a;
    }

    void print(){
        cout << a;
    }
};

m pw(m x, m y){
    if(y == 0) return 1;
    auto s = pw(x, y.a / 2);
    s = s * s % mod;
    if(y % 2 == 1) s = s * x % mod;
    return s;
}

m inv(m a){
    return pw(a, mod-2);
}
vector<m> smF2(vector<m> f){    // g(x) = f(0) + f(1) + f(2) + ... + f(x)                                                    // ax^2 + bx + c
    vector<m> ret(4, 0);
    m a = f[2];
    m b = f[1];
    m c = f[0];
    ret[0] = c;
    ret[1] = c + (a + b) * inv(2) - a * inv(3);
    ret[2] = (a + b) * inv(2);
    ret[3] = a * inv(3);
    return ret;
}

vector<m> smF3(vector<m> f){
    vector<m> ret(5, 0);
    m a = f[3];
    m b = f[2];
    m c = f[1];
    m d = f[0];
    ret[0] = d;
    ret[1] = a * inv(4) - (a * 3ll * inv(2) + b) * inv(3) + (a * inv(2) + b + c) * inv(2) + d;
    ret[2] = (a * inv(2) + b + c) * inv(2);
    ret[3] = (a*3ll * inv(2) + b) * inv(3);
    ret[4] = a * inv(4);
    return ret;
}


m f(vector<m> F, m x){
    m ret = 0;
    for(m i = 0; i < F.size(); i = i + 1){
        ret = ret + pw(x, i) * F[i.a];
    }
    return ret;
}
m getSum(vector<m> F, m h, m k){
    m n1 = (h+1) * k * (k-1) * inv(2ll);
    m n2 = f(smF2(F), h) * k;
    return n1 + n2;
}

m getKvad1(){
    return 0;

}
m fff(m a, m b, m c, m d, m x){
    return pw(x, 3)*(a*2ll) + pw(x, 2)*(b*2ll+a+a*d+2) + x*(c*2ll+d*2ll+d*b+b+1) + (c*d + d + c);
}
m FFF(m a, m b, m c, m d, m x){
    if(x == -1) return 0;
    m A = a * inv(2);
    m B = (a*4ll + b*2ll + a*d + 2ll) * inv(3);
    m C = (b + a*2ll + b*2ll + a*d + 2ll + c*2ll + d*2ll + b*d + 1ll) * inv(2);
    m E = c + d + c*d;
    m D = A - B + C + E;
    return pw(x, 4)*A + pw(x, 3) * B + pw(x, 2) * C + pw(x, 1) * D + E;
}

m getFullSum4(m h, m w){ 
    if(h < 0 || w < 0) return 0;
    m ret = FFF(4, 3, 1, 1, min(h.a, w.a-1));
    if(h.a+1 >= w.a){
        ret = ret + getSum({1, 3, 4}, h, w+1) - getSum({1, 3, 4}, w-1, w+1);

    }else{
        ret = ret + getSum({m(1) - h, -3, 4}, w, h + 1) - getSum({m(1) - h, -3, 4}, h+m(1), h+1);
    }
    return ret;
}
m getFullSum2(m h, m w){
    if(h < 0 || w < 0) return 0;
    m ret = FFF(4, -3, 1, 0, min(h, w));;
    if(h.a >= w.a){
        ret = ret + getSum({m(1)-w, -1, 4}, h, w+1) - getSum({m(1)-w, -1, 4}, w, w+1);
    }else{
        ret = ret + getSum({1, -3, 4}, w, h+1) - getSum({1, -3, 4}, h, h+1);
    }
    return ret;
}
m getFullSum1(m h, m w){
    if(h < 0 || w < 0) return 0;
    m ret = FFF(4, -1, 1, 0, min(w, h));
    if(h.a >= w.a){
        ret = ret + getSum({1, -1, 4}, h, w+1) - getSum({1, -1, 4}, w, w+1);
    }else{
        ret = ret + getSum({m(1) - h, 1, 4}, w, h+1) - getSum({m(1) - h, 1, 4}, h, h+1);
    }
    return ret;
}
m getFullSum3(m h, m w){
    if(h < 0 || w < 0) return 0;
    m ret = FFF(4, 1, 1, 0, min(w, h));
    if(h.a >= w.a){
        ret = ret + getSum({m(1) - w, 3, 4}, h, w+1) - getSum({m(1)-w, 3, 4}, w, w+1);
    }else{
        ret = ret + getSum({1, 1, 4}, w, h+1) - getSum({1, 1, 4}, h, h+1);
    }
    return ret;   
}

m getSum2(int x1, int y1, int x2, int y2){
    if(x2 < 0 || y2 < 0) return 0;
    x1 = max(x1, 0);
    x2 = max(x2, 0);
    y1 = max(y1, 0);
    y2 = max(y2, 0);
    swap(x1, y1);
    swap(x2, y2);
    return getFullSum2(x2, y2) - getFullSum2(x1-1, y2) - getFullSum2(x2, y1-1) + getFullSum2(x1-1, y1-1);
}
m getSum1(int x1, int y1, int x2, int y2){
    swap(x1, x2);
    if(x2 > -1 || y2 < 0) return 0;
    x1 = min(x1, -1);
    x2 = min(x2, -1);
    y1 = max(y1, 0);
    y2 = max(y2, 0);
    x1 *= -1;
    x2 *= -1;
    swap(x1, y1);
    swap(x2, y2);
    return getFullSum1(x2, y2) - getFullSum1(x1-1, y2) - getFullSum1(x2, y1-1) + getFullSum1(x1-1, y1-1);
}
m getSum4(int x1, int y1, int x2, int y2){
    swap(y1, y2);
    if(x2 < 0 || y2 > -1) return 0;
    x1 = max(x1, 0);
    x2 = max(x2, 0);
    y1 = min(y1, -1);
    y2 = min(y2, -1);
    y1 *= -1;
    y2 *= -1;
    swap(x1, y1);
    swap(x2, y2);
    return getFullSum4(x2, y2) - getFullSum4(x1-1, y2) - getFullSum4(x2, y1-1) + getFullSum4(x1-1, y1-1);
}
m getSum3(int x1, int y1, int x2, int y2){
    swap(y1, y2);
    swap(x1, x2);
    if(x2 > -1 || y2 > -1) return 0;
    x1 = min(x1, -1);
    x2 = min(x2, -1);
    y1 = min(y1, -1);
    y2 = min(y2, -1);
    y1 *= -1;
    y2 *= -1;
    x1 *= -1;
    x2 *= -1;
    swap(x1, y1);
    swap(x2, y2);
    return getFullSum3(x2, y2) - getFullSum3(x1-1, y2) - getFullSum3(x2, y1-1) + getFullSum3(x1-1, y1-1);
}
int main() {
    int n, t; cin >> n >> t;
    while(t--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << (getSum1(x1, y1, x2, y2) + getSum2(x1, y1, x2, y2) +  getSum3(x1, y1, x2, y2) + getSum4(x1, y1, x2, y2)).a << endl;
    }
    return 0;
}
