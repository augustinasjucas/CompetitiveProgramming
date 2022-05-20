#include <bits/stdc++.h>
using namespace std;
int visoLight = 0;
int visoFire = 0;
int prieMxLight = 0;
int prieMxFire = 0;
set<int> fires;
set<int> lights;
set<int> maxai;
long long curMaxSm = 0;
long long allSm = 0;
void idekDidziausiaNeideta(){
    int firesMx = -1;
    int lightsMx = -1;
        
    int mxx = (maxai.size() ? *maxai.begin() : 1000000000);
    if(fires.size()){
        auto kur = fires.lower_bound(mxx);
        if(kur == fires.end()) kur--;
        if(maxai.count(*kur)){
            if(kur != fires.begin()){
                kur--;
                firesMx = *kur;
            }
        }else{
            firesMx = *kur;
        }
    }
    if(lights.size()){
        auto kur = lights.lower_bound(mxx);
//        cout << "ieskosiu nuo " << mxx << endl;
        if(kur == lights.end()) kur--;
        if(maxai.count(*kur)){
            if(kur != lights.begin()){
                kur--;
                lightsMx = *kur;
            }
        }else{
            lightsMx = *kur;
        }       
    }
    if(firesMx > lightsMx){
        prieMxFire++;
        curMaxSm += firesMx;
        maxai.insert(firesMx);
    }else{
        prieMxLight++;
        curMaxSm += lightsMx;
        maxai.insert(lightsMx);
    }

}
void idekFire(int x){
    if(maxai.size() && x > *maxai.begin()){
        if(lights.count(*maxai.begin())){
            prieMxLight--;
            prieMxFire++;
        }
        curMaxSm -= *maxai.begin();
        curMaxSm += x;
        maxai.erase(*maxai.begin());
        maxai.insert(x);
    }
    visoFire++;
    allSm += x;
    fires.insert(x);
}
void idekLight(int x){
    visoLight++;
    allSm += x;
    lights.insert(x);
    if(maxai.size() && x > *maxai.begin()){
        curMaxSm += x;
        prieMxLight++;
        maxai.insert(x);
    }else{
        idekDidziausiaNeideta();
    }
}

void isimkFire(int x){
    fires.erase(x);
    allSm -= x;
    visoFire--;
    if(maxai.count(x)){
        maxai.erase(x);
        curMaxSm -= x;
        prieMxFire--;
        idekDidziausiaNeideta();    
    }
}
void isimkLight(int x){
    lights.erase(x);
    allSm -= x;
    visoLight--;
    if(maxai.count(x)){
        curMaxSm -= x;
        prieMxLight--;
        maxai.erase(x);
    }else{
        int mn = *maxai.begin();
        maxai.erase(mn);
        curMaxSm -= mn;
        if(lights.count(mn)){
            prieMxLight--;
        }else{
            prieMxFire--;
        }
    }
}
long long getAns(){
    if(visoFire + visoLight == 0) return 0;
    if(lights.size() == 0) return allSm;
    if(prieMxLight == visoLight){
        if(visoFire == 0) return allSm + curMaxSm - *maxai.begin();
        return allSm + curMaxSm + *fires.rbegin() - *maxai.begin();
    }else{
        return allSm + curMaxSm;
    }
}
void print(){
    cout << "situcija tokia: \n";
    cout << "lights: ["; for(auto x : lights) cout << x << " "; cout << "], ju yra " << visoLight << "\n";
    cout << "fires: ["; for(auto x : fires) cout << x << " "; cout << "], ju yra " << visoFire << "\n";
    cout << "tada mx : ["; for(auto x : maxai) cout << x << " "; cout << "], ju suma = " << curMaxSm << "\n";
    cout << "tarp ju lightu yra " << prieMxLight << ", o fire'u yra " << prieMxFire << ". Na o visu visu suma bus " << allSm << endl;
    cout << endl << endl;
}
int main(){
    int q; cin >> q;
    while(q--){
        int type; cin >> type;
        int a; cin >> a;
        if(type == 0){ // fire
            if(a < 0) isimkFire(abs(a));
            else idekFire(a);
        }else{
            if(a < 0) isimkLight(abs(a));
            else idekLight(a);
        }
//        print();
        cout << getAns() << "\n";

    }
    return 0;
}
