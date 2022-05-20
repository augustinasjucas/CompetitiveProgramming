#include <bits/stdc++.h>
using namespace std;
const int maxSz = 1e5 + 10;
const int maxSviesoforoIlgis = 4;
int I, D, S, V, F;  // I - sankryzos, V - masinos
unordered_map<string, int> keliuSkaiciai; // pavadinimas -> skaicius
string keliuPavadinimai[maxSz]; // kelio skaicius -> kelio pavadinimas
int streetA[maxSz], streetB[maxSz], streetL[maxSz];
vector<int> routes[maxSz]; // keliu eiliskumas i-ajai masinai

vector<vector<pair<int, int> > > DegimoTvarka;  // i-osios virsunes eiliskumo sarasas
vector<pair<int, int> > DegimoTvarkaPr[maxSz];
vector<vector<pair<int, int> > > Atsakymas;
// first - briaunos indeksas, priesdelio suma/trukme

int KurMasina[maxSz]; // kur yra dabar i-oji masina
int KadaPraleido[maxSz]; // Kuriuo metu i-oji sankryza praleido paskutine masina
deque<int> PradinisEiliskumas[maxSz], DabartinisEiliskumas[maxSz]; // paskutinis elementas yra tos masinos indeksas, kuri anksciausiai isvaziuos
int KelintojeStoteleje[maxSz];
int Liko[maxSz] = {0};
int SankryzosDydis[maxSz] = {0}; // kiek gatviu ieina i i-aja sankryza

int DegantisSviesaforas(int laikas, int sankryza) { // kas dega?
    if (DegimoTvarkaPr[sankryza][DegimoTvarkaPr[sankryza].size()-1].second == 0)
    {
        return -2;
    }
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
    cout << "start" << endl;
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
        for(int j = 0; j < DegimoTvarkaPr[i].size(); j++) {
            DegimoTvarkaPr[i][j].first = DegimoTvarka[i][j].first; // indeksai bus kokie buvo.
            DegimoTvarkaPr[i][j].second = (j == 0 ? 0 : DegimoTvarkaPr[i][j-1].second) + DegimoTvarka[i][j].first;
        }
    }
    for(int i = 0; i < I; i++)
    {
        DabartinisEiliskumas[i] = {};
    }

    for (int i = 0; i <= D; i++) { // per laiko momenta
        for (int j = 0; j < V; j++) { // per masinas
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
    cout << "end" << endl;
    return Taskai;
}
int rnd(int l, int r){ // atsitiktinis skaicius intervale [l; r]
    return l + (rand()) % (r - l + 1);
}
void generuokRandom(){ // atsitiktinis sviesoforu sugeneravimas
    for(int i = 0; i < maxSz; i++){
        DegimoTvarka[i].clear();
    }
    vector<int> indeksai(S);

    for(int i = 0; i < S; i++) indeksai[i] = i;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (indeksai.begin(), indeksai.end(), std::default_random_engine(seed));

    for(int i = 0; i < S; i++){
        int ind = indeksai[i];
        DegimoTvarka[streetB[ind]].push_back({ind, rnd(0, maxSviesoforoIlgis)});
    }
}
int ne0Ieinancios(int v){
    int ret = 0;
    for(auto x : Atsakymas[v]){
        if(x.second != 0) ret++;
    }
    return ret;
}
int main(){
    DegimoTvarka.resize(maxSz);
    srand(time(NULL));
    freopen("a.txt", "r", stdin);
    //freopen("FailasRez.txt", "w", stdout);
    cin >> D >> I >> S >> V >> F;

    for (int i = 0; i < S; i++) { // gatviu nuskaitymas
        int B, E, L;
        string gatve;
        cin >> B >> E >> gatve >> L;
        int GNumeris = i;
        keliuSkaiciai[gatve] = i;
        streetA[GNumeris] = B;
        streetB[GNumeris] = E;
        streetL[GNumeris] = L;
        SankryzosDydis[E]++;
        keliuPavadinimai[i] = gatve;
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
    int Rezultatas = 0;
    for (int kartas = 0; kartas < 1; kartas++) {  
        generuokRandom();
        auto DegimoTvarkuKopija = DegimoTvarka;
        int Taskai0 = simuliacija(), Taskai1;
        for (int keitimuKartas = 0; keitimuKartas < 1; keitimuKartas++) { 
            // 1) Pakeiciamos vienos gatves sviesoforo degimo laikas
            for (int keiciamasLaikas = 0; keiciamasLaikas < 1; keiciamasLaikas++)
            {
                int randSankryza = rand();
                randSankryza %= I;
                int randSviesaforasA = rand();
                randSviesaforasA %= SankryzosDydis[randSankryza];
                DegimoTvarka[randSankryza][randSviesaforasA].second = rnd(0, maxSviesoforoIlgis);
            }
            Taskai1 = simuliacija();
            // AR GERIAU? Patikrinimas
            if(Taskai1 <= Taskai0) { // jei ne geriau
                DegimoTvarka = DegimoTvarkuKopija; // padarom kaip buvo
            }
            else
                Taskai0 = Taskai1;

            // 2 ) Pakeiciamos vienos sankryzos dvieju sviesaforu degimo tvarka
            for (int keiciamasLaikas = 0; keiciamasLaikas < 1; keiciamasLaikas++)
            {
                int randSankryza = rand();
                randSankryza %= I;
                int randSviesaforasA = rand();
                randSviesaforasA %= SankryzosDydis[randSankryza];
                int randSviesaforasB = rand();
                randSviesaforasB %= SankryzosDydis[randSankryza];
                swap(DegimoTvarka[randSankryza][randSviesaforasA], DegimoTvarka[randSankryza][randSviesaforasB]);
            }
            
            // AR GERIAU? Patikrinimas
            Taskai1 = simuliacija();
            if(Taskai1 <= Taskai0) { // jei ne geriau
                DegimoTvarka = DegimoTvarkuKopija; // padarom kaip buvo
            }
            else
                Taskai0 = Taskai1;

        }
        if(Taskai0 > Rezultatas){
            Rezultatas = Taskai0;
            Atsakymas = DegimoTvarka;
        }
    }
    
    for(int i = 0; i < I; i++){
        if(ne0Ieinancios(i) == 0) continue;
        cout << "i = " << i << endl;
        cout << i << " " << ne0Ieinancios(i) << "\n";
        for(int j = 0; j < Atsakymas[i].size(); j++){
            if(Atsakymas[i][j].second == 0) continue;
            cout << keliuPavadinimai[Atsakymas[i][j].first] << " " << Atsakymas[i][j].second << "\n";
        }
    }
    cout << "SURINKTA: " << Rezultatas;
    return 0;
}
