
#include <bits/stdc++.h>
using namespace std;
const int maxSz = 1e5 + 10;
const int maxSviesoforoIlgis = 4;
int I, D, S, V, F;  // I - sankryzos, V - masinos
unordered_map<string, int> keliuSkaiciai; // pavadinimas -> skaicius
int keliuPavadinimai[maxSz]; // kelio skaicius -> kelio pavadinimas
int streetA[maxSz], streetB[maxSz], streetL[maxSz];
vector<int> routes[maxSz]; // keliu eiliskumas i-ajai masinai

vector<pair<int, int> > DegimoTvarka[maxSz];  // i-osios virsunes eiliskumo sarasas
vector<pair<int, int> > DegimoTvarkaPr[maxSz];
// first - briaunos indeksas, priesdelio suma/trukme

int KurMasina[maxSz]; // kur yra dabar i-oji masina
int KadaPraleido[maxSz]; // Kuriuo metu i-oji sankryza praleido paskutine masina
deque<int> PradinisEiliskumas[maxSz], DabartinisEiliskumas[maxSz]; // paskutinis elementas yra tos masinos indeksas, kuri anksciausiai isvaziuos
int KelintojeStoteleje[maxSz];
int Liko[maxSz] = {0};
int SankryzosDydis[maxSz]; // kiek gatviu ieina i i-aja sankryza

int DegantisSviesaforas(int laikas, int sankryza) { // kas dega?
    laikas %= DegimoTvarkaPr[sankryza][DegimoTvarkaPr[sankryza].size()-1].second;
    int left = 0, right = DegimoTvarka[sankryza].size();
    while (right - left > 1) 
    {
        int middle = (left + right) / 2;  // middle - tikrinamasis sviesaforas (ar jis dega?)
        if (DegimoTvarkaPr[sankryza][middle-1].second <= laikas)  // Dega (tai bus kairiausias kol kas degantis sviesaforas)
            left = middle;
        else                                     // Nedega
            right = middle;
    }
    return DegimoTvarka[sankryza][left].first;
}

int simuliacija(){
    int Taskai = 0;
    for(int i = 0; i < V; i++){
        KurMasina[i] = routes[i][0];
        KelintojeStoteleje[i] = 0;
        Liko[i] = 0;
    }
    for (int i = 0; i < I; i++)
    {
        KadaPraleido[i] = -1;
    }
    for(int i = 0; i < I; i++){
        DegimoTvarkaPr[i].resize(DegimoTvarka[i].size()); // nustatau priesdeliu sumos masyvo dydi
        for(int j = 0; j < DegimoTvarkaPr[i].size(); i++) {
            DegimoTvarkaPr[i][j].first = DegimoTvarka[i][j].first; // indeksai bus kokie buvo.
            DegimoTvarkaPr[i][j].second = (j == 0 ? 0 : DegimoTvarkaPr[i][j-1].second) + DegimoTvarka[i][j].first;
        }
    }
    for(int i = 0; i < I; i++)
    {
        DabartinisEiliskumas[i] = PradinisEiliskumas[i];
    }

    for (int i = 0; i <= D; i++) { // per laiko momenta
        for (int j = 0; j < V; i++) { // per masinas
            if (Liko[j] > 0)
                Liko[j]--;
            else if (Liko[j] == 0) {
                DabartinisEiliskumas[KurMasina[j]].push_front(j);
                Liko[j] = -1; // Yra prie sviesoforo
            }
            if(Liko[j] == -1 && DabartinisEiliskumas[KurMasina[j]].back() == j 
            && KadaPraleido[KurMasina[j]] != i) {
                if(DegantisSviesaforas(i, streetB[KurMasina[j]]) == KurMasina[j]){ // KAI DEGA SVIESAFORAS
                    KadaPraleido[KurMasina[j]] = i;    
                    DabartinisEiliskumas[KurMasina[j]].pop_back();
                    if(KelintojeStoteleje[j] == routes[j].size()-1) { // jei stotele, kurioje ji buvo yra paskutine
                    
                        Taskai += F + (D - i);
                        Liko[j] = -2;  // Kad netikrintume isvaziavusios masinos antra karta
                        continue;
                    }
                    Liko[j] = streetL[KurMasina[j]];
                    KelintojeStoteleje[j]++;
                    KurMasina[j] = routes[j][KelintojeStoteleje[j]];
                }
            }
        }
    }
    
    return Taskai;
}
int rnd(int l, int r){ // atsitiktinis skaicius intervale [l; r]
    return l + rand() % (r - l + 1);
}
void generuokRandom(){
    for(int i = 0; i < maxSz; i++){
        DegimoTvarka[i].clear();
    }
    for(int i = 0; i < S; i++){
        DegimoTvarka[streetB[i]].push_back({i, rnd(0, maxSviesoforoIlgis)});
    }
}
int main(){
    freopen("a.txt", "r", stdin);
    //freopen("FailasRez.txt", "w", stdout);
    cin >> I >> D >> S >> V >> F;

    for (int i = 0; i < S; i++) { // gatviu nuskaitymas
        int B, E, L;
        string gatve;
        cin >> B >> E >> gatve >> L;
        int GNumeris = keliuSkaiciai[gatve];
        if (GNumeris == 0)
            keliuSkaiciai[gatve] = keliuSkaiciai.size();
        streetA[GNumeris] = B;
        streetB[GNumeris] = E;
        streetL[GNumeris] = L;
    }
    for(int i = 0; i < V; i++) {
        int kiek;  
        cin >> kiek;
        for(int j = 0; j < kiek; j++) {
            string gatve; cin >> gatve;
            int realIndex = keliuSkaiciai[gatve];
            routes[i].push_back(realIndex);
        }
        PradinisEiliskumas[routes[i][0]].push_front(i);
    }

    for (int kartas = 0; kartas < 1; kartas++) {  
        generuokRandom();
        int Taskai0 = simuliacija();
        for (int keitimuKartas = 0; keitimuKartas < 1; keitimuKartas++) { 
            // 1) Pakeiciamos vienos sankryzos vieno sviesaforo diegimo laikas
            int randSankryza = rand() * RAND_MAX + rand();
            randSankryza %= I;
            int randSviesaforas = rand() * RAND_MAX + rand();
            randSviesaforas %= 
        }
    }
    
    // Isitikinti, kam lygus RAND_MAX   
    return 0;
}
