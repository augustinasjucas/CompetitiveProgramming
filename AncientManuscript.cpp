#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int isEilBals, isEilPrieb, lygBal, lygPrieb;
string prieb = "aeiou";
bool isBals(char a){
    return (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u');
}

string mas;
long long dp[16][27][5][5];

long long f(int ind, short last, short streak, short lyg){
    if(last != 26 && isBals(last + 'a')){
        if(streak > isEilBals) return 0;
        if(lyg > lygBal) return 0;
    }else if(last != 26){
        if(streak > isEilPrieb) return 0;
        if(lyg > lygPrieb) return 0;
    }

    if(ind == mas.size()) return 1;
    if(dp[ind][last][streak][lyg] != -1) return dp[ind][last][streak][lyg];
    if(mas[ind] == '*'){
        long long ret = 0;
        for(int i = 0; i < 26; i++){
            char desiu = 'a' + i;
            if(last != 26 && isBals(desiu)){
                if(isBals(last+'a')){
                    if(last == i){
                        ret += f(ind+1, last, streak+1, lyg+1);
                    }else{
                        ret += f(ind+1, i, streak+1, 1);
                    }
                }else{
                    ret += f(ind+1, i, 1, 1);
                }
            }else{
                if(last != 26 && !isBals(last+'a')){
                    if(last == i){
                        ret += f(ind+1, last, streak+1, lyg+1);
                    }else{
                        ret += f(ind+1, i, streak+1, 1);
                    }
                }else{
                    ret += f(ind+1, i, 1, 1);
                }
            }
 
        } 
        return dp[ind][last][streak][lyg] = ret;
    }else{
        
        char desiu = mas[ind];
        long long ret = 0;
        if(isBals(desiu)){
            if(last != 26 && isBals(last+'a')){
                if(last == mas[ind]-'a'){
                    ret = f(ind+1, last, streak+1, lyg+1);
                }else{
                    ret = f(ind+1, mas[ind]-'a', streak+1, 1);
                }
            }else{
                ret = f(ind+1, mas[ind]-'a', 1, 1);
            }
        }else{
            if(last != 26 && !isBals(last+'a')){
                if(last == mas[ind]-'a'){
                    ret = f(ind+1, last, streak+1, lyg+1);
                }else{
                    ret = f(ind+1, mas[ind]-'a', streak+1, 1);
                }
            }else{
                ret = f(ind+1, mas[ind]-'a', 1, 1);
            }
        }
        return dp[ind][last][streak][lyg] = ret;
    }
    return 0ll;
}
int main(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 27; j++){
            for(int h = 0; h < 5; h++){
                for(int l = 0; l < 5; l++){
                    dp[i][j][h][l] = -1;
                }
            }
        }
    }
    cin >> lygBal >> isEilBals >> lygPrieb >> isEilPrieb;
    cin >> mas;
    cout << f(0, 26, 0, 0);
    return 0;
}
