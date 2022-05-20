#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5; // reikia daugiau
struct treap{
    struct node{
        int l = -1, r = -1;
        int sz = 1;
        long long val;
        long long teigSum = 0;
        long long neigSum = 0;
        long long prior;
        node(){
            prior = rand();
        }
    };
    int dbInd = 0;
    vector<node> tryp;
    const int dydis = 1e5;
    int newN(int x){
        tryp[dbInd].val = x;
        if(x >= 0) tryp[dbInd].teigSum += x;
        else tryp[dbInd].neigSum += -x;
        return dbInd++;
    }
    void updateTryp(int v){
        tryp[v].sz = 1;
        tryp[v].neigSum = tryp[v].teigSum = 0;
        if(tryp[v].val >= 0) tryp[v].teigSum = tryp[v].val;
        else tryp[v].neigSum += -tryp[v].val;
        if(tryp[v].l != -1) {
            tryp[v].sz += tryp[tryp[v].l].sz;
            tryp[v].teigSum += tryp[tryp[v].l].teigSum;
            tryp[v].neigSum += tryp[tryp[v].l].neigSum;
        }
        if(tryp[v].r != -1){
            tryp[v].sz += tryp[tryp[v].r].sz;
            tryp[v].teigSum += tryp[tryp[v].r].teigSum;
            tryp[v].neigSum += tryp[tryp[v].r].neigSum;
        }
    }
    int merge(int l, int r){ // viskas kaireje maziau uz viska desineje.
        if(l == -1 || r == -1){
            if(l == -1) return r;
            else return l; // r = -1
        }else if(tryp[l].prior > tryp[r].prior){
            int nd = merge(tryp[l].r, r);
            tryp[l].r = nd;
            updateTryp(l);
            return l;
        }else{
            int nd = merge(l, tryp[r].l);
            tryp[r].l = nd;
            updateTryp(r);
            return r;
        }
    }
    pair<int, int> splitByInd(int v, int x){ // paima visus elementus, kurie mazesni ar lygus x
        if(v == -1){
            return {-1, -1};
        }

        int lsz = 0; int rsz = 0;
        if(tryp[v].l != -1) lsz = tryp[tryp[v].l].sz;
        if(tryp[v].r != -1) rsz = tryp[tryp[v].r].sz;
        if(lsz <= x){ // jei as priklausau kairei
            auto kt = splitByInd(tryp[v].r, x - lsz - 1);
            tryp[v].r = kt.first; // mano desineje bus tas, kas ten priklauso kairei
            updateTryp(v);
            return {v, kt.second};
        }else{ // as priklausau desinei
            auto kt = splitByInd(tryp[v].l, x);
            tryp[v].l = kt.second;
            updateTryp(v);
            return {kt.first, v};
        }
    }
    int curRoot = -1;
    void push_back(int x){ // prideda i desine
        int st = newN(x);
//        cout << "pb " << x << "\n";
        if(curRoot == -1){
            curRoot = st;
        }else{
            curRoot = merge(curRoot, st);
        }
    }
    long long getEl(int x, int v = -2){ // gauna i-aji elementa
        if(v == -2) v = curRoot;
        int lsz = 0; int rsz = 0;
        if(tryp[v].l != -1) lsz = tryp[tryp[v].l].sz;
        if(tryp[v].r != -1) rsz = tryp[tryp[v].r].sz;
        if(x >= tryp[curRoot].sz) return -1;
        if(lsz == x) return v;
        if(tryp[v].l != -1){
            if(tryp[tryp[v].l].sz >= x+1) {
                return getEl(x, tryp[v].l);
            }
            else{
                return getEl(x-tryp[tryp[v].l].sz - 1, tryp[v].r);
            }
        }else{
            return getEl(x-1, tryp[v].r);
        }
    }
    long long getVal(int x, int v = -2){
        int ind = getEl(x, v);
        return tryp[ind].val;
    }
    void setVal(int x, long long vl){
        auto prm = splitByInd(curRoot, x); // first - visi kairiau-lygu, second - visi desinau
        auto ant = splitByInd(prm.first, x-1); // first - visi kairiau, second - x-as
        tryp[ant.second].val = vl; updateTryp(ant.second);
        curRoot = merge(ant.first, ant.second);
        curRoot = merge(curRoot, prm.second);
    }
    int findFirstPositive(int v){
        if(tryp[v].teigSum == 0) return -1;
        long long le = 0;
        long long ri = 0;
        int lsz = 0;
        if(tryp[v].l != -1){
            le = tryp[tryp[v].l].teigSum;
            lsz = tryp[tryp[v].l].sz;
        }
        if(tryp[v].r != -1){
            ri = tryp[tryp[v].r].teigSum;
        }

        if(le != 0){
            return findFirstPositive(tryp[v].l);
        }else if(tryp[v].val > 0){
            return lsz;
        }else{
            return 1 + lsz + findFirstPositive(tryp[v].r);
        }
    }
    int findFirstNegative(int v){
        if(tryp[v].neigSum == 0) return -1;
        long long le = 0;
        long long ri = 0;
        int lsz = 0;
        if(tryp[v].l != -1){
            le = tryp[tryp[v].l].neigSum;
            lsz = tryp[tryp[v].l].sz;
        }
        if(tryp[v].r != -1){
            ri = tryp[tryp[v].r].neigSum;
        }
        cout << "ieskau neg, esu " << v << ", le = " << le << ", lsz = " << lsz << ", mano val = " << tryp[v].val << endl;

        if(le != 0){
            return findFirstNegative(tryp[v].l);
        }else if(tryp[v].val < 0){
            return lsz;
        }else{
            return 1 + lsz + findFirstNegative(tryp[v].r);
        }
    }
    int findPosPref(int v, long long x){ // randa paskutini indeksa, kad pref[0; ind] <= x
        cout << "v = " << v << ", x = " << x << endl;
        if(v == -1) return -1;
        long long le = 0;
        long long ri = 0;
        int lsz = 0;
        if(tryp[v].l != -1){
            le = tryp[tryp[v].l].teigSum;
            lsz = tryp[tryp[v].l].sz;
        }
        if(tryp[v].r != -1){
            ri = tryp[tryp[v].r].teigSum;
        }
        long long st = 0;

        if(tryp[v].val >= 0) st += tryp[v].val;
        if(tryp[v].l == -1 && st > x){
            return -1;
        }
        if(le > x){
//            cout << "st " << endl;
            return findPosPref(tryp[v].l, x);
        }else if(le + st > x){
            return lsz-1;
        }else{
            return 1 + lsz + findPosPref(tryp[v].r, x - st - le);
        }
    }

    void print(){
        cout << "root: " << curRoot << endl;
        for(int v = 0; v < dbInd; v++){
            cout << v << " yra v, jo val = " << tryp[v].val << ", kaireje: " << tryp[v].l << ", desineje: " << tryp[v].r << ", teigSum = " << tryp[v].teigSum <<", neigSum = " << tryp[v].neigSum << ", hsh = "<< tryp[v].prior << endl;
        }
        cout << endl;
    }
    treap(){
        tryp.resize(dydis);
    }
};
treap vec;
int n;
long long prm = 0;
void add(int ind, long long x){
    if(ind == -1){
        prm += x;
        return;
    }
    long long bv = vec.getVal(ind);
    vec.setVal(ind, x + bv);
}
int firstPlus(int ind, int root = -2){ // randa pirma teigiama intervale [ind; n-1]
    if(root == -2) root = vec.curRoot;
    pair<int, int> splt = vec.splitByInd(root, ind-1);
//    vec.print();
    cout << "intervalas [" << ind << "; " << n-1 << " turi " << vec.tryp[splt.second].sz << " elementu" << endl;
    int rt = vec.findFirstPositive(splt.second);
    cout << "rt = " << rt << endl;
    if(rt == -1) {
        vec.curRoot = vec.merge(splt.first, splt.second);
        return n;
    }
    int ret = (splt.first == -1 ? 0 : vec.tryp[splt.first].sz) + rt;
    vec.curRoot = vec.merge(splt.first, splt.second);
    return ret;
}
int firstMinus(int ind, int root = -2){ // randa pirma neigiama intervale [ind; n-1]
    if(root == -2) root = vec.curRoot;
    pair<int, int> splt = vec.splitByInd(root, ind-1);
    vec.print();
//    vec.print();
    int rt = vec.findFirstNegative(splt.second);
    cout << "ind = " << ind << ", splt.first = " << splt.first << ", o rt = " << rt << endl;
    if(rt == -1) {
        vec.curRoot = vec.merge(splt.first, splt.second);
        return n;
    }
    int ret = (splt.first == -1 ? 0 : vec.tryp[splt.first].sz) + rt;
    vec.curRoot = vec.merge(splt.first, splt.second);
    return ret;
}
long long sum(int l, int r){
    auto prm = vec.splitByInd(vec.curRoot, r);
    auto ant = vec.splitByInd(prm.first, l-1);
    int L = ant.first;
    int M = ant.second;
    int R = prm.second;
    long long ret = vec.tryp[M].teigSum + vec.tryp[M].neigSum;
    vec.curRoot = vec.merge(L, M);
    vec.curRoot = vec.merge(vec.curRoot, R);
    return ret;
}
void shiftLeft(int l, int r){
//    if(l == r) return ;
    if(r < l) return;
    cout << endl << "__------shift " << l << "; " << r << endl << endl;
    // vec[i] := vec[i+1]
    auto prm = vec.splitByInd(vec.curRoot, r);
    auto ant = vec.splitByInd(prm.first, l-1);
    int L = ant.first;
    int M = ant.second; // intervalas [l; r]
    int R = prm.second;
    auto tre = vec.splitByInd(M, 0);
    M = vec.merge(tre.second, tre.first);
    vec.curRoot = vec.merge(L, M);
    vec.curRoot = vec.merge(vec.curRoot, R);
    if(r+1 < n-1) vec.setVal(r, vec.getVal(r+1));
}
void printVec(){
    for(int i = 0; i < n-1; i++){
        cout << vec.getVal(i) << " ";
    }
    cout << endl;
}
void printMas(){
    long long cur = prm;
    cout << prm << " ";
    for(int i = 0; i < n-1; i++){
        cur += vec.getVal(i);
        cout << cur << " ";
    }
}
vector<long long> getMas(){
    long long cur = prm;
    vector<long long> ret = {cur};
    for(int i = 0; i < n-1; i++){
        cur += vec.getVal(i);
        ret.push_back(cur);
    }
    return ret;
}
void desinen(int a, int b, long long k){
    if(a == b){
        add(a-1, k);
        add(a, -k);
        return;
    }
    while(true){
        cout << "pries viska a= " << a << ", b = " << b << endl;
        printVec();
        int L = firstPlus(a); // sito teigiamo intervalo ribos nuo a;
        int R;
        cout << ", tai L = " << L << endl;
        if(L == n){
            break;
        }
        R = firstMinus(L) - 1;
        if(L >= b) break;
        if(L < a) L = a;
        if(R > b-1) R = b-1;

        // gaunu, kad dabar teigiamas intervalas yra [L; R]

        auto s1 = vec.splitByInd(vec.curRoot, L-1);
        auto s2 = vec.splitByInd(s1.second, R-L);

        int lft = s1.first;
        int mid = s2.first; // cia yra visas intervalas
        int rht = s2.second;
        cout << lft << "; " << mid << "; " << rht << ", lft.sz = " << vec.tryp[lft].sz << ", mid = " << vec.tryp[mid].sz << ", rht = " << (rht == -1 ? 0 : vec.tryp[rht].sz )<< endl;

        int tl = vec.findPosPref(mid, k) ;
       // cout << "pirma tl = " << tl << ", o dydis = " << vec.tryp[mid].sz << end§l;
        tl += (lft == -1 ? 0 : vec.tryp[lft].sz);
        cout << "tl = " << tl << ", L = " << L << ", R = " << R << endl;
        vec.curRoot = vec.merge(lft, mid);
        vec.curRoot = vec.merge(vec.curRoot, rht);
        cout << "po mergo, dydis: " << vec.tryp[vec.curRoot].sz << endl;
        if(tl == R){
            int pr = vec.getVal(L);
            k -= sum(L, R);
            shiftLeft(L, R-1);
            add(R, -vec.getVal(R));
            add(L-1, pr);
        }else{
            if(tl != L-1){
                int pr = vec.getVal(L);
                k -= sum(L, tl);
                shiftLeft(L, tl-1);
                add(tl, -vec.getVal(tl));
                add(L-1, pr);
            }
            add(tl, k);
            add(tl+1, -k);
            k = 0;

        }
        if(k == 0) break;
        a = tl+1;
        cout << endl;
        cout << "po sito padarymo masyvas yra: "; printMas(); cout << endl;
    }
    cout << "k = " << k << endl;
    add(b-1, +k);
    add(b, -k);

    cout << "po visko vec: "; printVec();
    cout << "po visko mas: "; printMas(); cout << endl << endl << endl << endl;

}
vector<int> mas;
void test(){
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int a; cin >> a; vec.push_back(a);
    }
    vec.print();
    while(true){
        char a;
        int b; cin >> a >> b;
        if(a == 'c'){
            int c; cin >> c;
            vec.setVal(b, c);
        }else if(a == '?'){
            cout << vec.getVal(b) << endl;
        }else{
            cout << vec.findPosPref(vec.curRoot, b) << endl;
        }
    }
}
vector<long long> MAS;
void stumk(int esu, int goal, int kek) {
    if (kek == 0) {
        return;
    }

    if (esu == goal) {
        MAS[esu] += kek;
        return ;
    }

    int dir = (goal < esu ? -1 : 1);
    int kt = dir + esu;
    int dif = MAS[kt] - MAS[esu];

    if (dif <= 0) {
        stumk (kt, goal, kek);
    }
    else if (dif >= kek) {
        MAS[esu] += kek;
    }
    else {
        MAS[esu] += dif;
        stumk(kt, goal, kek - dif);
    }
}
int main(){
    srand(time(0));
//    test();
    int q; cin >> n >> q;
    mas.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> mas[i];
        MAS.push_back(mas[i]);
    }
    for(int i = 0; i < n-1; i++) {
        vec.push_back(mas[i+1]-mas[i]);
    }
    prm = mas[0];
    for(int i = 0; i < q; i++){
        int a, b, c; cin >> a >> b >> c;
        stumk (a, b, c);
        auto bv = getMas();
        if(a <= b){
            desinen(a, b, c);
        }else{

        }
        if(MAS != getMas()){
            cout << "bv: "; for(auto x : bv) cout << x << " "; cout << endl;
            cout << a << " " << b << " " << c << endl;
            cout << "turi but: "; for(auto x : MAS) cout <<  x<< " "; cout << endl;
            break;
        }
    }
    printMas();
    return 0;
}
