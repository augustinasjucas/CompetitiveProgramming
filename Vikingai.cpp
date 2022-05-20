#include <iostream>
#include <queue>
using namespace std;

const short dydis = 710;
const int inf = 30000000;

short n, m;
int dist[dydis][dydis] = {0};
bool water[dydis][dydis] = {0};
int earliest[dydis][dydis] = {0};
void bfs2(short eil, short stul){
    for(short i = 0; i < dydis; i++) for(short j = 0; j < dydis; j++) dist[i][j] = inf;
    for(short i = 0; i < dydis; i++) for(short j = 0; j < dydis; j++) earliest[i][j] = inf;
    queue<pair<short, short> > q;
    q.push({eil, stul});
    dist[eil][stul] = 0;
    while(!q.empty()){
        eil = q.front().first;
         stul = q.front().second;
        q.pop();
        /*
        short lWall = -1, rWall = m, uWall = -1, dWall = n;
        
        for(short i = stul; i > -1; i--)
            if(!water[eil][i]) {lWall = i; break;}
        
        for(short i = stul; i < m; i++)
            if(!water[eil][i]) {rWall = i; break;}
        
        for(short i = eil; i > -1; i--)
            if(!water[i][stul]) {uWall = i; break;}
        
        for(short i = eil; i < n; i++)
            if(!water[i][stul]) {dWall = i; break;}
        
        
        for(short i = lWall+1; i < rWall; i++){
            earliest[eil][i] = min(dist[eil][stul], earliest[eil][i]);
        }
        for(short i = uWall+1; i < dWall; i++){
            earliest[i][stul] = min(dist[eil][stul], earliest[i][stul]);
        }*/
        
        for(short i = -1; i <= 1; i+=2){
            if(eil+i >= 0 && eil+i < n){
                if(water[eil+i][stul] && dist[eil+i][stul] > dist[eil][stul]+1){
                    dist[eil+i][stul] = dist[eil][stul]+1;
                    q.push({eil+i, stul});
                }
            }
            if(stul+i >= 0 && stul+i < m){
                if(water[eil][stul+i] && dist[eil][stul+i] > dist[eil][stul]+1){
                    dist[eil][stul+i] = dist[eil][stul]+1;
                    q.push({eil, stul+i});
                }
            }
        }
        
    }
    int ind, mn = inf;
    
    for(short i = 0; i < n; i++){
        
        for(short j = 0; j < m; j++){
            if(water[i][j]){
                 ind = j;
                 mn = dist[i][j];
                for(short h = j+1; h < m; h++){
                    if(!water[i][h]) break;
                    ind = h;
                    mn = min(dist[i][h], mn);
                }
                for(short h = j; h <= ind; h++){
                    earliest[i][h] = mn;
                }
                j = ind;
            }
        }
    }
    mn = inf;
    for(short j = 0; j < m; j++){
        
        for(short i = 0; i < n; i++){
            if(water[i][j]){
                ind = i;
                mn = dist[i][j];
                for(short h = i+1; h < n; h++){
                    if(!water[h][j]) break;
                    ind = h;
                    mn = min(dist[h][j], mn);
                }
                for(short h = i; h <= ind; h++){
                    earliest[h][j] = min(earliest[h][j], mn);
                }
                i = ind;
            }
        }
    }
}

void dfs1(short eil, short stul){
    for(short i = 0; i < dydis; i++) for(short j = 0; j < dydis; j++) dist[i][j] = inf;
    queue<pair<short, short> > q;
    q.push({eil, stul});
    dist[eil][stul] = 0;
    
    while(!q.empty()){
        
        eil = q.front().first;
        stul = q.front().second;
        //cout << "esame " << eil << " " << stul << ". " << endl;
        q.pop();
        //if(earliest[eil][stul] <= dist[eil][stul] && dist[eil][stul] != 0) continue;
        for(short i = -1; i <= 1; i+=2){
            if(eil+i >= 0 && eil+i < n){
                if(water[eil+i][stul] && dist[eil+i][stul] > dist[eil][stul]+1 && earliest[eil+i][stul] > dist[eil][stul]+1){
                    dist[eil+i][stul] = dist[eil][stul]+1;
                    q.push({eil+i, stul});
                }
            }
            if(stul+i >= 0 && stul+i < m){
                if(water[eil][stul+i] && dist[eil][stul+i] > dist[eil][stul]+1 && earliest[eil][stul+i] > dist[eil][stul]+1){
                    dist[eil][stul+i] = dist[eil][stul]+1;
                    q.push({eil, stul+i});
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    char a;
    short trE, trS, vE = -1, vS = -1, tE, tS;
    for(short i = 0; i < n; i++){
        for(short j = 0; j < m; j++){
            
            cin >> a;
            if(a != 'I') water[i][j] = true;
            if(a == 'T'){
                trE = i;
                trS = j;
            }
            if(a == 'V'){
                vE = i;
                vS = j;
            }
            if(a == 'Y'){
                tE = i;
                tS = j;
            }
        }
    }
    for(short i = 0; i < dydis; i++) for(short j = 0; j < dydis; j++) earliest[i][j] = inf;
    if(vE != -1){
        //while(true){}
        bfs2(vE, vS);
    }else{
        cout << "NO";
        return 0;
    }
    
    /*for(short i = 0; i < n; i++){
        for(short j = 0; j < m; j++)
            if(earliest[i][j] == inf) cout << "n ";
            else cout << earliest[i][j] << " ";
        
        cout<< endl;
    }*/
    dfs1(tE, tS);
    if(dist[trE][trS] < earliest[trE][trS]){
        cout << "YES";
    }else cout << "NO";

    return 0;
}
