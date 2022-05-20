#include <bits/stdc++.h>
using namespace std;
const int dydis = 5e5 + 19;
int n;
int kek[dydis] = {0};
void print(){
    for(int i = 1; i <= n; i++)  cout << i << ": " << kek[i] << ",  ";
    cout << endl;
}
multiset<int> setas;
vector<int> isimti[dydis];
void calc(){
    int viso = n;
    for(int i = 2; i <= n; i++){
        for(int j = i * 2; j <= n; j += i){
            kek[j]++;
            if(kek[j] == 1) viso--;
        }
    }
    setas.insert(1);
    isimti[viso].push_back(1);
  //  cout << "jei noriu, kad dbd butu " << 1 << ", tai skaiciu gali buti " << viso << ", tai isimt " << viso << " pb " << 1 <<  endl << endl;
   // print(); cout << endl;
    for(int i = 2; i <= n; i++){
        // dabar turiu suzymejes atsakyma i-1, tai dabar atzymesiu i-1
        if(kek[i-1] != 0) viso++;
        for(int j = (i)*2; j <= n; j += i){
            kek[j]--;
            if(kek[j] == 0) viso++;
        }
        
     //   print();
//        cout << "jei noriu, kad dbd butu " << i << ", tai skaiciu gali buti " << viso << endl << endl;
        setas.insert(i);
        isimti[viso].push_back(i);
    }
}

int rez[dydis];
void del(multiset<int> &setas, int x){
    if(setas.find(x) == setas.end()) return ;
    setas.erase(setas.find(x));
}
int main(){
    cin >> n;
    
    calc();
/*    cout << "isimti: \n";
    for(int i = 1; i <= n; i++)    {
        cout << i << ": "; for(auto x : isimti[i]) cout << x<< " ";
        cout << endl;
    }*/
    for(int i = 1; i <= n; i++){
        if(i != 1) cout << *setas.begin() << " ";
        for(auto x : isimti[i]){
            del(setas, x);
        }
    }
    

    return 0;
}
