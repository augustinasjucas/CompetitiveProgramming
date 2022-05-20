#include <bits/stdc++.h>
using namespace std;
bool empt(vector<int> &mas){
    for(auto x : mas) if(x != 0) return false;
    return true;
}
bool galima = 1;
vector<int> cur;
void daryk(vector<int> mas, int ind){
    if(mas[ind] == 0){
        if(!empt(mas)) galima = 0;
        return;
    }
    if(mas[ind-1] == 0){
        mas[ind]--;
        cur.push_back(ind);
        daryk(mas, ind+1);
        return;
    }
    if(mas[ind+1] == 0){
        mas[ind]--;
        cur.push_back(ind);
        daryk(mas, ind-1);
        return;
    }
    if(mas[ind-1] <= mas[ind] && ind == 2){
        mas[ind]--;
        cur.push_back(ind);
        daryk(mas, ind-1);
        return;
    }
    if(mas[ind+1] <= mas[ind] && ind == 3){
        mas[ind]--;
        cur.push_back(ind);
        daryk(mas, ind+1);
        return;
    }
    if(mas[ind-1] != 0){
        mas[ind]--;
        cur.push_back(ind);
        daryk(mas, ind-1);
        return;
    }
    if(mas[ind+1] != 0){
        mas[ind]--;
        cur.push_back(ind);
        daryk(mas, ind+1);
        return;
    }

}
int main(){
    vector<int> mas(6, 0);
    for(int i = 1; i <= 4; i++){
        cin >> mas[i];
    }
    vector<int> ans;
    for(int i = 0; i < 4; i++){
        cur.clear();
        galima = 1;
        daryk(mas, i+1);
        if(galima) ans = cur;
    }
    if(ans.size() == 0){
        cout << "NO";
    }else{
        cout << "YES\n";
        for(auto x : ans){
            cout << x-1 << " ";
        }
    }

    return 0;
}
