#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const long long inf = 1e18;
int n, k;
vector<pair<int, int> > virs, apac;
set<int> tsk;
vector<int> taskai;
set<pair<int, int> > akj, akr, akz, adz, adr, adj, vkj, vkm, vdm, vdj;
long long svkj[2] = {}, svkm[2] = {}, svdm[2] = {}, svdj[2] = {};
long long sakj[2] = {}, sakr[2] = {}, sakz[2] = {}, sadz[2] = {}, sadr[2] = {}, sadj[2] = {};
bool pakj(int x, int y, int X){ // priklauso apaciai kairej juodam
    if(x + y <= X && x < X-k) return true;
    return false;
}
bool pakr(int x, int y, int X){
    if(x < X && x + y < X && x >= X-k) return true;
    return false;
}
bool pakz(int x, int y, int X){
    if(x < X && x+y >= X) return true;
    return false;
}
bool padz(int x, int y, int X){
    if(x >= X && x-y < X) return true;
    return false;
}
bool padr(int x, int y, int X){
    if(x-y >= X && x <= X+k) return true;
    return false;
}
bool pvkj(int x, int y, int X){
    if(x+y < X) return true;
    return false;
}
bool pvkm(int x, int y, int X){
    if(x+y >= X && x < X) return true;
    return false;
}
bool pvdm(int x, int y, int X){
    if(x >= X && x-y < X) return true;
    return false;
}
void addvkj(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vkj.insert({x+y, ind});
    svkj[0] += x;
    svkj[1] += y;
}
void addvkm(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vkm.insert({x, ind});
    svkm[0] += x;
    svkm[1] += y;
}
void addvdm(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vdm.insert({x-y, ind});
    svdm[0] += x;
    svdm[1] += y;
}
void addvdj(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vdj.insert({x, ind});
    svdj[0] += x;
    svdj[1] += y;
}
void addakj(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    akj.insert({x, ind});
    sakj[0] += x;
    sakj[1] += y;
}
void addakr(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    akr.insert({x+y, ind});
    sakr[0] += x;
    sakr[1] += y;
}
void addakz(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    akz.insert({x, ind});
    sakz[0] += x;
    sakz[1] += y;
}
void addadz(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    adz.insert({x-y, ind});
    sadz[0] += x;
    sadz[1] += y;
}
void addadr(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    adr.insert({x, ind});
    sadr[0] += x;
    sadr[1] += y;
}
void addadj(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    adj.insert({x, ind});
    sadj[0] += x;
    sadj[1] += y;
}
void delvkj(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vkj.erase({x+y, ind});
    svkj[0] -= x;
    svkj[1] -= y;
}
void delvkm(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vkm.erase({x, ind});
    svkm[0] -= x;
    svkm[1] -= y;
}
void delvdm(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vdm.erase({x-y, ind});
    svdm[0] -= x;
    svdm[1] -= y;
}
void delvdj(int ind){
    int x = virs[ind].first;
    int y = virs[ind].second;
    vdj.erase({x, ind});
    svdj[0] -= x;
    svdj[1] -= y;
}
void delakj(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    akj.erase({x, ind});
    sakj[0] -= x;
    sakj[1] -= y;
}
void delakr(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    akr.erase({x+y, ind});
    sakr[0] -= x;
    sakr[1] -= y;
}
void delakz(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    akz.erase({x, ind});
    sakz[0] -= x;
    sakz[1] -= y;
}
void deladz(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    adz.erase({x-y, ind});
    sadz[0] -= x;
    sadz[1] -= y;
}
void deladr(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    adr.erase({x, ind});
    sadr[0] -= x;
    sadr[1] -= y;
}
void deladj(int ind){
    int x = apac[ind].first;
    int y = apac[ind].second;
    adj.erase({x, ind});
    sadj[0] -= x;
    sadj[1] -= y;
}
void sudek(int X){
    int ind = 0;
    for(auto x : virs){
//        cout << "virs taskas (" << x.first << ", " << x.second << "), ind = " << ind << endl;
        if(pvkj(x.first, x.second, X)){
            addvkj(ind);
        }else if(pvkm(x.first, x.second, X)){
            addvkm(ind);
        }else if(pvdm(x.first, x.second, X)){
            addvdm(ind);
        }else{ // pvdj
            addvdj(ind);
        }
        ind++;
    }
    ind = 0;
    for(auto x : apac){
//        cout << "apacios taskas (" << x.first << ", " << x.second << "), ind = " << ind << endl;
        if(pakj(x.first, x.second, X)){
            addakj(ind);
        }else if(pakr(x.first, x.second, X)){
            addakr(ind);
        }else if(pakz(x.first, x.second, X)){
            addakz(ind);
        }else if(padz(x.first, x.second, X)){
            addadz(ind);
        }else if(padr(x.first, x.second, X)){
            addadr(ind);
        }else{
            addadj(ind);
        }
        ind++;
    }
}
long long getCurVal(long long x){
    long long ret = 0;

    ret += svkj[1];
    ret += vkm.size() * x - svkm[0];
    ret += svdm[0] - vdm.size() * x;
    ret += svdj[1];
    ret += sakj[1];
    ret += sakr[1] + sakr[0] - akr.size() * (x-k);
    ret += akz.size() * x - sakz[0] + akz.size() * k - sakz[1];
    ret += sadz[0] - adz.size() * x + adz.size() * k - sadz[1];
    ret += sadr[1] + adr.size() * (x+k) - sadr[0];
    ret += sadj[1];

    return ret;
}
void clr(){
    akj.clear(); akr.clear(); akz.clear(); adz.clear(); adr.clear(); adj.clear(); vkj.clear(); vkm.clear(); vdm.clear(); vdj.clear();
    svkj[0] = 0; svkj[1] = 0;
    svkm[0] = svkm[1] = 0;
    svdm[0] = svdm[1] = 0;
    svdj[0] = svdj[1] = 0;
    sakj[0] = sakj[1] = 0;
    sakr[0] = sakr[1] = 0;
    sakz[0] = sakz[1] = 0;
    sadz[0] = sadz[1] = 0;
    sadr[0] = sadr[1] = 0;
    sadj[0] = sadj[1] = 0;
}
void moveTo(int x){
    while(vkj.size()){
        // reikia didziausio
        int ind = vkj.rbegin()->second;
        if(!pvkj(virs[ind].first, virs[ind].second, x)){
            delvkj(ind);
            addvkm(ind);
        }else{
            break;
        }
    }
    while(vkm.size()){
        int ind = vkm.rbegin()->second;
        if(!pvkm(virs[ind].first, virs[ind].second, x)){
            delvkm(ind);
            addvdm(ind);
        }else{
            break;
        }
    }
    while(vdm.size()){
        int ind = vdm.rbegin()->second;
        if(!pvdm(virs[ind].first, virs[ind].second, x)){
            delvdm(ind);
            addvdj(ind);
        }else{
            break;
        }
    }

    while(akj.size()){
        int ind = akj.rbegin()->second;
        if(!pakj(apac[ind].first, apac[ind].second, x)){
            delakj(ind);
            addakr(ind);
        }else{
            break;
        }
    }
    while(akr.size()){
        int ind = akr.rbegin()->second;
        if(!pakr(apac[ind].first, apac[ind].second, x)){
            delakr(ind);
            addakz(ind);
        }else{
            break;
        }
    }
    while(akz.size()){
        int ind = akz.rbegin()->second;
        if(!pakz(apac[ind].first, apac[ind].second, x)){
            delakz(ind);
            addadz(ind);
        }else{
            break;
        }
    }
    while(adz.size()){
        int ind = adz.rbegin()->second;
        if(!padz(apac[ind].first, apac[ind].second, x)){
            deladz(ind);
            addadr(ind);
        }else{
            break;
        }
    }
    while(adr.size()){
        int ind = adr.rbegin()->second;
        if(!padr(apac[ind].first, apac[ind].second, x)){
            deladr(ind);
            addadj(ind);
        }else{
            break;
        }
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int x, y; cin >> y >> x;
        y = abs(y);
//        cout << "taskas(" << x << ", " << y << ")\n";
        if(y <= k){
            apac.push_back({x, y});
        }else{
            virs.push_back({x, y});
        }
        tsk.insert(x);
        tsk.insert(x+k);
        tsk.insert(x-k);
    }
    for(auto x : tsk) taskai.push_back(x);
    reverse(taskai.begin(), taskai.end());
    long long ret = inf;
    sudek(taskai[0]);
    for(auto x : taskai){
        moveTo(x);
        ret = min(ret, getCurVal(x));
/*        cout << "tried " << x << ", ans = " << getCurVal(x) << endl;

        cout << "virsus kaires juodas: ["; for(auto x : vkj) cout << "(" << virs[x.second].first << " " << virs[x.second].second << "), "; cout << endl;
        cout << "virsus kaires melynas: ["; for(auto x : vkm) cout << "(" << virs[x.second].first << " " << virs[x.second].second << "), "; cout << endl;
        cout << "virsus desines melynas: ["; for(auto x : vdm) cout << "(" << virs[x.second].first << " " << virs[x.second].second << "), "; cout << endl;
        cout << "virsus desines juodas: ["; for(auto x : vdj) cout << "(" << virs[x.second].first << " " << virs[x.second].second << "), "; cout << endl;

        cout << "apacia kaires juodas: ["; for(auto x : akj) cout << "(" << apac[x.second].first << " " << apac[x.second].second << "), "; cout << endl;
        cout << "apacia kaires raudonas: ["; for(auto x : akr) cout << "(" << apac[x.second].first << " " << apac[x.second].second << "), "; cout << endl;
        cout << "apacia kaires zalias: ["; for(auto x : akz) cout << "(" << apac[x.second].first << " " << apac[x.second].second << "), "; cout << endl;

        cout << "apacia desines zalias: ["; for(auto x : adz) cout << "(" << apac[x.second].first << " " << apac[x.second].second << "), "; cout << endl;
        cout << "apacia desines raudonas: ["; for(auto x : adr) cout << "(" << apac[x.second].first << " " << apac[x.second].second << "), "; cout << endl;
        cout << "apacia desines juodas: ["; for(auto x : adj) cout << "(" << apac[x.second].first << " " << apac[x.second].second << "), "; cout << endl;
        cout << endl << endl;*/
//        clr();
    //    break;
    }
    cout << ret;
    return 0;
}
