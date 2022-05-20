#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 1e5 + 10;
const int ktD = 301;
const long long inf = 1e18;
long long dist[dydis];
int k, n, m, q, visoGrp;
int kuriSakn[dydis]; // zymi, kuriai sakninei grupei priklauso sita grupe
vector<pair<int, int> > gr[dydis];
vector<long long> pradedantNuoI[ktD][6];
vector<int> pirmi[ktD];
vector<int> paskut[ktD];
int prmG[ktD];
int paskG[ktD];
vector<long long> mn(vector<long long> &a, vector<long long> &b){
    vector<long long> ret(a.size(), inf);
    for(int i = 0; i < a.size(); i++){
        ret[i] = min(a[i], b[i]);
    }
    return ret;
}
int grp(int a){
    return a/k;
}
vector<int> kasPriklauso(int grupe){
    vector<int> ret;
    for(int i = 0; i < k; i++){
        if(grupe * k + i  >= n) break;
        ret.push_back(grupe * k + i);
    }
    return ret;
}
void bfs(int v, int riba){
    queue<int> q;
    q.push(v);
    while(!q.empty()){
        v = q.front(); q.pop();
        for(auto x : gr[v]){
            if(kuriSakn[grp(x.first)] != riba) continue;
            if(dist[x.first] > dist[v] + x.second){
                dist[x.first] = dist[v] + x.second;
                q.push(x.first);
            }
        }
    }
}
void padfs(int v, int riba){ // v - VIRSUNES nr. riba - saknines grupes nr
//    cout << "is " <<v <<  ", tampa " << (v/k ) * k << endl;
    for(int i = (v / k) * k; i < n; i++){
        if(kuriSakn[grp(i)] != riba) break;
        dist[i] = inf;
    }
    dist[v] = 0;
    bfs(v, riba);
}
void prmC(int ind, int paskInd){ // darysiu kalkuliacija nuo sitos grupes. t.y. gausiu visus k galimu atsakymu, jei pradedu nuo i-osios grupes nares
//    cout << "precalc nuo " << kuriSakn[ind] << endl;
    vector<int> prm = kasPriklauso(ind);
    vector<int> gl = kasPriklauso(paskInd);
    pirmi[kuriSakn[ind]] = prm;
    paskut[kuriSakn[ind]] = gl;
    prmG[kuriSakn[ind]] = ind;
    paskG[kuriSakn[ind]] = paskInd;
    for(int i = 0; i < prm.size(); i++){
        padfs(prm[i], kuriSakn[ind]);
        vector<long long> zinomiNuoI;
//        cout << "pradejus dfsa tik nuo " << prm[i] << ", atstumai bus:\n";
        for(auto x : gl){
            zinomiNuoI.push_back(dist[x]);
//            cout << x << ": " << dist[x] << "\n";
        }
//        cout << endl;
        pradedantNuoI[kuriSakn[ind]][i] = zinomiNuoI;
    }
//    cout << endl << endl;
}
void precalc(){
    visoGrp = n/k + (n % k != 0);
//    cout << "viso Grp = " << visoGrp << endl;
    int sz = sqrt(visoGrp);
    int dbGrp = 0;  
//    sz = n;
//    cout << "sz = " << sz << endl;  
    for(int i = 0; i < visoGrp;){
       // i grupe yra saknines grupes pradzioje
//        cout << dbGrp << " - ajai saknu grupei priklauso grupes: ["; for(int j = i; j < min(i+sz, n); j++) cout << j << " "; cout << "]\n";
        for(int j = i; j < min(i + sz, n); j++) kuriSakn[j] = dbGrp;
        prmC(i, min(i + sz-1, n-1));
        i += sz;
        dbGrp++;
    }
}
vector<long long> per1(vector<long long> a, int lev){
    vector<int> nodes = kasPriklauso(lev);
    vector<int> nxt = kasPriklauso(lev+1);
    for(auto x : nxt) dist[x]  = inf;
    for(int i = 0; i < k; i++){
        dist[nodes[i]] = a[i];
    }
    for(int i = 0; i < k; i++){
        for(auto x : gr[nodes[i]]){
            dist[x.first] = min(dist[x.first], dist[nodes[i]] + x.second);
        }
    }
    vector<long long> ret;
    for(int i = 0; i < k; i++){
        ret.push_back(dist[nodes.back()+1+i]);
    }
    return ret;
 
}
void darDfs(vector<long long> pradz, int grupe){
    vector<int> nodes = kasPriklauso(grupe);
    for(int i = nodes[0]; i < n; i++){
        if(kuriSakn[grp(i)] != kuriSakn[grp(nodes[0])]) break;
        dist[i] = inf;
    }
    for(int i = 0; i < k; i++){
        dist[nodes[i]] = pradz[i];
        bfs(nodes[i], kuriSakn[grupe]);
    }
}
long long process(int a, int b){
    if(kuriSakn[grp(a)] == kuriSakn[grp(b)]){
        padfs(a, kuriSakn[grp(a)]);
        if(dist[b] == inf) return -1;
        return dist[b];
    }else{
//        cout << "padfsinsiu nuo " << a << ", ";
        padfs(a, kuriSakn[grp(a)]);
        vector<long long> pradz;
        for(auto x : paskut[kuriSakn[grp(a)]]){
  //          cout << "dst[" << x << "] = " << dist[x] << ",  ";
            pradz.push_back(dist[x]);
        }
//        cout << endl;
        int lastGr = paskG[kuriSakn[grp(a)]];
//        cout << "visu pirma pradz = ["; for(auto x : pradz) cout << x<< " "; cout << "]\n";
        for(int i = kuriSakn[grp(a)]+1; i < n; i++){
            pradz = per1(pradz, lastGr); lastGr++;
 
            if(i == kuriSakn[grp(b)]){
  //              cout << "pradedu nuo " << i << " saknines grupes, o joje jau yra mano ieskoma virsune!\n";
    //            cout << "pradz = ["; for(auto x : pradz) cout << x<< " "; cout << "]\n";
                darDfs(pradz, lastGr);
                if(dist[b] == inf) return -1;
                return dist[b];
            }else{
                vector<long long> taps(k, inf);
                for(int j = 0; j < k; j++){
                    vector<long long> pls = pradedantNuoI[i][j];
                    for(auto &x : pls) x += pradz[j];
                    taps = mn(taps, pls);
                }
//                cout << "jei atejau i " << i << " su ["; for(auto x : pradz) cout << x<< " ";
//                cout << "], tai gale bus ["; for(auto x : taps) cout << x << " "; cout << "]\n";
//                cout << endl;
                lastGr = paskG[i];
                pradz = taps;
            }
        }
    }
    while(true){
        for(int i = 0; i > 1; i--){
        
        }
    }
    return -10;
}
int main(){
//    cin.tie(NULL);
//    ios_base::sync_with_stdio(false);
    for(int i = 0; i < dydis; i++){
        kuriSakn[i] = -1;
    }
    cin >> k >> n >> m >> q;
    for(int i = 0 ; i < m; i++){
        int a, b, c; cin >> a >> b >> c;
        gr[a].push_back({b, c});
    }
    precalc();
//    cout << "padariau!" << endl;
    for(int i = 0; i < q; i++){
        int a, b; cin >> a >> b;
        if(a == b){
            cout << "0\n";
        }else if(grp(a) >= grp(b)){
            cout << "-1\n";
        }else{
            cout << process(a, b) << "\n";
        }
    }
    return 0;
}
/*
 
3 27 24 1000
0 3 10
0 4 3
2 5 2
3 6 1
3 7 1
4 7 1
5 8 2
6 10 1
8 11 2
9 13 3
11 13 3
13 15 4
13 16 4
14 17 2
16 18 3
17 20 1
18 21 1
18 22 7
19 22 2
20 23 9
22 25 1
4 8 1
8 9 1
10 14 2
*/

