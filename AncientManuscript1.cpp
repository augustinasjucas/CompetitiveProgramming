#include <bits/stdc++.h>
using namespace std;
int isEilBals, isEilPrieb, lygBal, lygPrieb;
string prieb = "aeiou";
bool isBals(char a){
    return (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u');
}
int isEil(string &a, bool isB){
    int ret = 0;
    int cur = 0;
    for(int i = 0; i < a.size(); i++){
        if(isBals(a[i]) == isB){
            cur++;
        }else{
            ret = max(ret, cur);
            cur = 0;
        }
    }
    ret = max(ret, cur);
    return ret;
}
int lyg(string &a, bool isB){
    int ret = 0;
    int cura = 0;
    char cur = '=';
    for(auto x : a){
        if(isBals(x) == isB){
            if(x == cur){
                cura++;
            }else{
                ret = max(ret, cura);
                cura = 1;
                cur = x;
            }
        }else{
            ret = max(ret, cura);
            cur = '=';
            cura = 0;
        }
    }
    ret = max(ret, cura);
    return ret;
}
bool tinka(string &a){
    if(a.size() == 0) return 1;
    int isB = isEil(a, 1);
    int isP = isEil(a, 0);
    int lgB = lyg(a, 1);
    int lgP = lyg(a, 0);
//    cout << "a = " << a << ", is eiles balsiu daugiausia " << isB << ", \nis Eiles priebalsiu daugiausai " << isP << ", \n";
//    cout << "is eiles lygiu balsiu daugiausia " << lgB << ", \no priebalsiu lygiu is eiles - " << lgP << endl;
    return isB <= isEilBals && isP <= isEilPrieb && lgB <= lygBal && lgP <= lygPrieb;
}
string mas;
const int dydis = 460000;
long long dp[16][dydis];
long long times[4] = {26*26*26, 26*26, 26, 1};
long long has(string &a){
    long long ret = 0;
    for(int i = 3; i > -1; i--){
        if(i >= a.size()) continue;
        ret += times[i] * (a[i]-'a');
    }
    return ret;
}
long long f(int ind, string last){
    if(ind == mas.size()) return 1;
    long long hsh = has(last);
    if(dp[ind][hsh] != -1) return dp[ind][hsh];
    //    cout << "f(" << ind << ", " << last << ")\n";
    if(mas[ind] == '*'){
        string pvz = last;
        if(pvz.size() +1 > 4) pvz.erase(0, 1 );
        long long ret = 0;
        for(int i = 0; i < 26; i++){
            last.push_back('a'+i);
            pvz.push_back('a'+i);
            if(tinka(last))ret += f(ind+1, pvz);
            pvz.pop_back();
            last.pop_back();
        }
        return dp[ind][hsh] = ret;
    }else{
        last.push_back(mas[ind]);
        if(!tinka(last)) return 0;
        if(last.size() > 4) last.erase(0, 1);
        return dp[ind][hsh] = f(ind+1, last);
    }
    return 0ll;
}
int main(){
    for(auto &x : dp) for(auto &y : x) y = -1; 
    cin >> lygBal >> isEilBals >> lygPrieb >> isEilPrieb;
    cin >> mas;
    cout << f(0, "");
 
 
    return 0;
}
