/*
Prielaida:
    1. Apskliaudžiu kiekvieną skaičių
#include <bits/stdc++.h>
    2. Apskliaudžiu šauktukus.
    3. Apskliaudžiu while'us, if'us
    Tada, paėmęs kokį nors intervalą tarp skliaustų, gausiu:
    a) ( *skaičius* )
    b) ( !(...) )
    c) ( (...) < (...) )
    d) ( (...) <= (...) )
    e) ( (...) := (...) )
    f) ( ...; (...); ...; ...; ...; (...); ... )  Vienur bus, kitur nebus skliaustų. Jei (skliaustų atžvilgiu) nuliniame yra ";", tai tuomet bus f variantas.
    g) ( while (...) do (...) )
    h) ( if (...) then (...) else (...) )
    i) ( (...) + (...) )
    j) ( (...) )
Darau prielaidą, kad niekur nebus a + b + c, o vietoj to bus (a + b) + c;
Darau prielaidą, kad visada, kai jie bus reiškiniai eilutėje, x >= y, x > y, x := y bus apskliausti.
*/ 
#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5;
int memory[dydis] = {0};
string file = "";
void scanFile(){
    ifstream in("input.txt");
    char a;
    file += "(";
    while(in >> a){
        file += a;
    }
    file += ")";
}
int findInt(int pos){ // paduodu pirma skaiciaus indeksa, grazina pati skaiciu
    int last = 0;
    for(int i = pos; i < file.size(); i++){
        if(file[i] < '0' || file[i] > '9') return last;
        last = last * 10 + (file[i]-'0');
    }
    return -1;
}

bool isNum(char a){
    return '0' <= a && a <= '9';
}
int nextIndForInt(int pos){
    for(int i = pos; i < file.size(); i++) if(!isNum(file[i])) return i;
    return file.size();
}
void apskSkaicius(){
    for(int i = 0; i < file.size(); i++){
        if(isNum(file[i])){
            file.insert(i, "(");
            int lastInt = nextIndForInt(i+1);
            file.insert(lastInt, ")");
            i = lastInt;
        }
    }
}
int findNextSkliaust(int ind){
    int bal = 0;
    for(int i = ind; i < file.size(); i++){
        if(file[i] == '(') bal++;
        if(file[i] == ')') bal--;
        if(bal == 0) return i;
    }
    cout << "blogaiĄĄĄ\n";
    return 0;
}
void apskSauktukus(){
    for(int i = 0; i < file.size(); i++){
        if(file[i] == '!'){
            file.insert(i, "(");
            int end = findNextSkliaust(i+2);
            file.insert(end+1, ")");
            i++;
        }
    }
}
int endOfIf(int ind){ // ind - i raide
    int prm = findNextSkliaust(ind+2);
    int ant = findNextSkliaust(prm+5);
    int tre = findNextSkliaust(ant+5);
    return tre;
}
void apskIfus(){
    for(int i = 0; i < file.size(); i++){
        if(file[i] == 'i' && file[i+1] == 'f'){
            file.insert(i, "(");
            int gl = endOfIf(i+1);
            file.insert(gl, ")");
            i++;
        }
    }
}
int endOfWhile(int ind){ // ind - w raide
    ind = findNextSkliaust(ind+5);
    ind = findNextSkliaust(ind+3);
    return ind;
}
void apskWhileus(){
    for(int i = 0; i < file.size(); i++){
        if(file[i] == 'w' && file[i+1] == 'h'){
            file.insert(i, "(");
            int gl = endOfWhile(i+1);
            file.insert(gl, ")");
            i++;
        }
    }
}
vector<char> tipai = {'<', '=', ';', ':', '+', '!'};
bool isTyper(int i){
    char a = file[i];
    for(auto x : tipai) if(x == a) return true;
    return false;
}
char findType(int l, int r){
    int bal = 0;
    if(file[l+1] == 'w' && file[l+2] == 'h') return 'g';
    if(file[l+1] == 'i' && file[l+2] == 'f') return 'h';
    vector<char> visi;
    for(int i = l+1; i < r; i++){
        if(file[i] == ')') bal--;
        if(file[i] == '(') bal++;
        if(bal != 0) continue;
        if(file[i] == ')' || file[i] == '(') continue;
        if(isTyper(i)) visi.push_back(file[i]);
    }
    bool yraKabl = 0; // jei yra kabliataskis, tai tipas bus kabliataskio, kitu atveju lieka tik vienas variantas.
    for(auto x : visi){
        if(x == ';') yraKabl = 1;
    }
    if(yraKabl) return 'f';
    // dabar privalo visi.size() <= 2!!!!
    if(visi.size() > 2){
        cout << "BLOGAI BLOGAI BLOGAI!!!!!!";
    }
    if(visi.size() == 0){
        if(isNum(file[l+1])) return 'a';
        return 'j';
    }
    if(visi[0] == '<'){
        if(visi.size() == 2) return 'd';
        else return 'c';
    }
    if(visi[0] == ':'){
        return 'e';
    }
    if(visi[0] == '!') return 'b';
    if(visi[0] == '+') return 'i';
    cout << "BLOGAI BLOGAI BLOGAI!!!!!! - blogas tipas"; // kadangi nei vienas is pries tai buvusiu, tai privalo buti skaicius ARBA kiti skliaustai. abejais atvejais turi buti tuscias visi masyvas
    return 'z';
}
int kurYra(int ind, char kas){ // klausiu apie 'kas', esanti 0-niame lygyje
    int bal = 0;
    for(int i = ind; i < file.size(); i++){
        if(file[i] == ')') bal--;
        if(file[i] == '(') bal++;
        if(bal != 0) continue;
        if(file[i] == ')' || file[i] == '(') continue;
        if(file[i] == kas) return i;
    }   
    cout << "NERADAU!!\n";
    return -1;
}
int calc(int l, int r){
    char type = findType(l, r); // tipai is eiles kaip virsuj
    if(type == 'a'){
        return findInt(l+1);
    }
    if(type == 'b'){
        int nxt = calc(l+2, r-1);
        return memory[nxt];
    }
    if(type == 'c'){
        int kr = kurYra(l+1, '<');
        int kairP = calc(l+1, kr-1);
        int desnP = calc(kr+1, r-1);
        return kairP < desnP;
    }
    if(type == 'd'){
        int kr = kurYra(l+1, '<');
        int kairP = calc(l+1, kr-1);
        int desnP = calc(kr+2, r-1);
        return kairP <= desnP;
    }
    if(type == 'e'){
        int kr = kurYra(l+1, ':');
        int kairP = calc(l+1, kr-1);
        int desnP = calc(kr+2, r-1);
        return memory[kairP] = desnP;
    }
    if(type == 'f'){
        int kr = kurYra(l+1, ';');
        int kairP = calc(l, kr);
        int desnP = calc(kr, r);
        return desnP;
    }
    if(type == 'g'){
        int last = 0;
        int ifL = l+6;
        int ifR = findNextSkliaust(ifL);
        int doL = ifR+3;
        int doR = findNextSkliaust(doL);
        while(calc(ifL, ifR)){
            last = calc(doL, doR);
        }
        return last;
    }
    if(type == 'h'){
        int ifL = l+3;
        int ifR = findNextSkliaust(ifL);
        int thenL = ifR+5;
        int thenR = findNextSkliaust(thenL);
        int elseL = thenR+5;
        int elseR = findNextSkliaust(elseL);
        if(calc(ifL, ifR)){
            return calc(thenL, thenR);
        }else{
            return calc(elseL, elseR);
        }
    }
    if(type == 'i'){
        int kr = kurYra(l+1, '+');
        int kairP = calc(l+1, kr-1);
        int desnP = calc(kr+1, r-1);
        return kairP + desnP;
    }

    if(type == 'j'){
        return calc(l+1, r-1);
    }
    return 0;
}
int main(){
    scanFile();
    
    
    apskSkaicius();
    apskSauktukus();
    apskIfus();
    apskWhileus();
    
    cout << "ans = " << calc(0, file.size()-1);
}

/*
11 := !0;
while (0 < !2) do(
3 := (10 + !2); 4 := (30 + !2); 5 := (50 + !2);
if (!!3 <= 2) then (1 := 1; 2 := !2 - 1) else (
    if (!!4 <= 0) then (!3 + 1 := !!3 - 1; !4 + 1 := 0; 2 := !2 + 1; !4 := !!4 + 1)
    else (if (!!4 <= 1) then (!5 := !1; !4 := !!4 + 1)
    else (if (!!4 <= 2) then (!3 + 1 := !!3 - 2; !4 + 1 := 0; 2 := !2 + 1; !4 := !!4 + 1)
    else (1 := !!5 + !1; 2 := !2 - 1)))
)); !1
*/
