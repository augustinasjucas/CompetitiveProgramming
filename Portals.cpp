#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int dydis = 1001;
pair<int, int> tp[dydis][dydis][4];
bool mas[dydis+2][dydis+2] = {false};
int atstumas[dydis+2][dydis+2];
int n, m;
int ikiSienos[dydis+1][dydis+1];
void suraskAtstumus(int eil, int stul){

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ikiSienos[i][j] = 1000000001;
        }

    }

    deque<pair<int, int>> eilu;
    eilu.push_back({eil, stul});
    ikiSienos[eil][stul] = 500000;
    while(!eilu.empty()){

        int eil = eilu.front().first;
        int stul = eilu.front().second;
        eilu.pop_front();
        ////cout << "Ziurime i " << eil << ";" << stul << endl;
        bool cont = false;
        for(int i = -1; i < 2; i += 2){

            if((!mas[eil+i][stul] || !mas[eil][stul+i]) && (ikiSienos[eil][stul] != 0)){
                ikiSienos[eil][stul] = 0;
                eilu.push_front({eil, stul});
                cont = true;
                break;
            }

        }
        if(cont)continue;

        for(int i = -1; i < 2; i+=2){

            if(mas[eil+i][stul] && ikiSienos[eil+i][stul] > ikiSienos[eil][stul]+1){
                ikiSienos[eil+i][stul] = ikiSienos[eil][stul]+1;
                eilu.push_back({eil+i, stul});
            }
            if(mas[eil][stul+i] && ikiSienos[eil][stul+i] > ikiSienos[eil][stul]+1){
                ikiSienos[eil][stul+i] = ikiSienos[eil][stul]+1;
                eilu.push_back({eil, stul+i});
            }
        }

    }

   /* for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(ikiSienos[i][j] == 1000000001) //cout << "#";
            else //cout << ikiSienos[i][j];
        }
        //cout << endl;

    }*/

}

void generuok(){
    /// SIENA AUSKTYN
    for(int i = 1; i <= m; i++){
        int art = -1;
        for(int j = 1; j <= n; j++){
            if(mas[j][i] && art ==-1) art = j;
            if(!mas[j][i]) {art = -1; continue;}
            tp[j][i][0] = {art, i};
            //cout << "IS " << j << "; " << i << " siena is aukstyn yra " << art << "; " << i << endl;
        }
    }
    /// SIENA ZEMYN
    for(int i = 1; i <= m; i++){
        int art = -1;
        for(int j = n; j > 0; j--){
            if(mas[j][i] && art ==-1) art = j;
            if(!mas[j][i]){art = -1; continue;}
            tp[j][i][2] = {art, i};
            //cout << "IS " << j << "; " << i << " siena is Zemyn yra " << art << "; " << i << endl;
        }
    }
    /// SIENA KAIREJ
    for(int i = 1; i <= n; i++){
        int art = -1;
        for(int j = 1; j <= m; j++){
            if(mas[i][j] && art ==-1) art = j;
            if(!mas[i][j]) {art = -1; continue;}
            //cout << "IS " << i << "; " << j << " siena is kairen yra " << i << "; " << art << endl;
            tp[i][j][3] = {i, art};
        }
    }
    /// SIENA DESINEJ
    for(int i = 1; i <= n; i++){
        int art = -1;
        for(int j = m; j > 0; j--){
            if(mas[i][j] && art ==-1) art = j;
            if(!mas[i][j]) {art = -1; continue;}
            //cout << "IS " << i << "; " << j << " siena is desinen yra " << i << "; " << art << endl;
            tp[i][j][1] = {i, art};
        }
    }
}

void platyn(int eil, int stul){

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            atstumas[i][j] = 1000000001;
        }

    }

    queue<pair<int, int> > eilu;
    eilu.push({eil, stul});
    atstumas[eil][stul] = 0;

    while(!eilu.empty()){
        int eil = eilu.front().first;
        int stul = eilu.front().second;
        eilu.pop();
        for(int i = -1; i < 2; i+=2){
            if(mas[eil+i][stul] && atstumas[eil+i][stul] > atstumas[eil][stul]+1){
                atstumas[eil+i][stul] = atstumas[eil][stul]+1;
                eilu.push({eil+i, stul});
            }
            if(mas[eil][stul+i] && atstumas[eil][stul+i] > atstumas[eil][stul]+1){
                atstumas[eil][stul+i] = atstumas[eil][stul]+1;
                eilu.push({eil, stul+i});
            }
        }
        int AtIkiSien = ikiSienos[eil][stul];
        for(int i = 0; i < 4; i++){

            int eil1 = tp[eil][stul][i].first;
            int stul1 = tp[eil][stul][i].second;

            if(atstumas[eil1][stul1] > atstumas[eil][stul] + AtIkiSien + 1){
                atstumas[eil1][stul1] = atstumas[eil][stul] + AtIkiSien + 1;
                eilu.push({eil1, stul1});
            }
        }
    }
/*
   for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(atstumas[i][j] == 1000000001) //cout << "#";
            else //cout << atstumas[i][j];
        }
        //cout << endl;

    }*/


}
int main(int argc, const char * argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    pair<int, int> dest, start;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            char a;
            cin >> a;
            if(a == '#') continue;

            if(a == 'S') start = {i, j};
            if(a == 'C') dest = {i, j};

            mas[i][j] = true;
        }
    }
    suraskAtstumus(start.first, start.second);
    generuok();
    platyn(start.first, start.second);

    cout << atstumas[dest.first][dest.second];
    return 0;
}

