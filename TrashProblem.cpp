#include <bits/stdc++.h>
using namespace std;
multiset<int> setas;
multiset<int> skrt;
void del(multiset<int> &setas, int x){
    auto kur = setas.find(x);
    if(kur != setas.end()) setas.erase(kur);
}
void add(int x){
    if(setas.size() == 0){
        setas.insert(x);
    }else if(setas.size() == 1){
        int past = *setas.begin();
        setas.insert(x);
        skrt.insert(abs(past-x));
    }else{
        auto kur = setas.lower_bound(x);
        if(kur == setas.end()){ // jisai bus desiniausias
            kur--;
            skrt.insert(abs(*kur - x));
            setas.insert(x);
        }else if(kur == setas.begin()){ // kariausias
            skrt.insert(abs(*kur - x));
            setas.insert(x);
        }else{ // perVid
            int R = *kur;
            skrt.insert(abs(*kur-x));
            kur--;
            int L = *kur;
            skrt.insert(abs(*kur-x));
            del(skrt, abs(R-L));
            setas.insert(x);
        }
    }
}
void er(int x){
    if(setas.size() == 1){
        setas.erase(x);
    }else if(setas.size() == 2){
        auto kur = setas.begin();
        int pr, an;
        pr = *kur; kur++; an = *kur;
        del(skrt, abs(an- pr));
        setas.erase(x);
    }else{
        auto pvz = setas.lower_bound(x);
        auto kur = pvz; pvz++;
        if(pvz == setas.end()){ // sitas yra desinej
            auto kair = kur; kair--;
            del(skrt, abs(*kair-x));
            setas.erase(x);
        }else if(kur == setas.begin()){ // sitas yra kairej
            auto des = kur; des++;
            del(skrt, abs(*des-x));
            setas.erase(x);
        }else{
            auto kair = kur, des = kur;
            kair--; des++;
            del(skrt, abs(*kair-x));
            del(skrt, abs(*des-x));
            skrt.insert(abs(*kair-*des));
            setas.erase(x);
        }
    }
}
int getR(){
    if(setas.size() <= 2) return 0;
    return *setas.rbegin()-*setas.begin()-*skrt.rbegin();
}
int n, q; 
int main(){
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        add(a);
    }
    cout << getR() << "\n";
    while(q--){
        int a, b; cin >> a >> b;
        if(a == 0){
            er(b);
        }else{
            add(b);
        }
        cout << getR() << "\n";
    }
    
    return 0;
}
