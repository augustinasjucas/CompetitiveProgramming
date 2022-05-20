#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 3e5 + 10;
vector<int> gr[dydis];
int tevas[dydis];
int state[dydis];
int findP(int v){
    if(tevas[v] == v) return v;
    return tevas[v] = findP(tevas[v]);
}
void conn(int a, int b){
    a = findP(a);
    b = findP(b);
    tevas[a] = b;
}

bool turi[dydis] = {0};

void bfs(int v){
    queue<int> q;
    q.push(v);
    state[v] = 1;
    for(auto x : gr[v]){
        turi[x] = 1;
    }

    while(!q.empty()){
        v = q.front(); q.pop();
        for(auto x : gr[v]){
            if(state[x] != 0) continue;
            if(turi[x]){
                state[x] = -1;
                q.push(x);
            }else{
                state[x] = 1;
                q.push(x);
                for(auto y : gr[x]){
                    turi[y] = 1;
                }
            }
        }
    }
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        for(int i = 0; i < n; i++){
            gr[i].clear();
            state[i] = 0;
            turi[i] = 0;
        }
        for(int i = 0; i < n; i++) tevas[i] = i;
        vector<pair<int, int> > br;
        for(int i = 0; i < m; i++){
            int a, b; cin >> a >> b; a--; b--;
            gr[a].push_back(b);
            gr[b].push_back(a);
        } 
        bfs(0);
        int kek =0;
        for(int i = 0; i < n; i++) if(state[i] == 0) kek++;
        if(kek != 0){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        vector<int> vec;
        for(int i = 0; i < n; i++) if(state[i] == 1)  vec.push_back(i);
        cout << vec.size() << "\n";
        for(auto x : vec) {
            cout <<  x+1 << " ";
        }
        cout  << "\n";
    }
    return 0;
}
/*

To allow sb/sth to tell you what to do - bow down to
In a way that causes or shows sadness - dismally
to encourage sb to do sth or to encourage them to try harder to achieve sth - spur (sb) into action
not long ago - recently
quickly; after a very short time - ?
To resist or oppose the general direction in which a situation is changing or developing - 
To try harder in order to benefit from an opportunity or deal with a situation- step up the mark
To keep sb in an offiacial place, such as a police station, a prison or a hospital, and prevent them from leaving - detain
To officially charge of a crime - indict
To be relaxed - go with the flow
pareiskimas - Indictment 

to be or to do not natural - go against the grain

Unable to think clearly, especially because of a shock or because you have been hit on the head - dazed
IMPLICATE - to show or tu suggest that somebody is involved in illegal activity

bow down to.
dismally
spur into action
recently
swiftly
buck the trend
step up the mark
remand, - palikti po teismo 
detain - suimt
indict - paduoti i teisma
prosectute - teisti
go with the flow
indictment - pareiskimas
distraught

Beffudled - unable to think
Bewildered - confused
Baffled - kazkas labai keisto tave sutrikde, negali suprast
flustered - uzsiknises
dazed - gaves i galva


*/   
