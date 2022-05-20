#include <bits/stdc++.h>
using namespace std;
//#include "molecules.h"

vector<int> find_subset(int l, int r, vector<int> w) {
    vector<pair<int, int> > deltas;
    vector<pair<int, int> > mas;
    for(int i = 0; i < w.size(); i++){
        mas.push_back({w[i], i});
    }
    sort(mas.begin(), mas.end());
    long long sm = 0;
    for(auto x : mas){
        deltas.push_back({x.first - mas[0].first, x.second});
        sm += x.first - mas[0].first;
    }
    sort(deltas.begin(), deltas.end());
    vector<long long> pref;
    for(auto x : deltas){
        pref.push_back((pref.size() ? pref.back() : 0ll) + x.first);
    }
//    cout << "skaiciai: "; for(auto x : deltas) cout << x.first << " "; 
//    cout <<endl;
    for(int i = 1; i <= (int) w.size(); i++){
        long long L = l - 1ll *  i * mas[0].first;
        long long R = r - 1ll * i * mas[0].first;

        // reikia i skaiciu, kad ju suma butu intervale [L; R];
        // pref[j] - pref[i-j]
//        cout << "reikia " << i << " skaiciu, kad ju suma butu intervale " << L << "; " << R << endl;
        if(pref[i-1] > R || pref[(int)pref.size() - 1] - ((int)pref.size()-1-i < 0 ? 0ll : pref[(int)pref.size()-1-i]) < L) continue;
  //      cout << "ce! " << endl;
        deque<int> ret1;
        vector<int> ret;
        long long cur = 0;
        for(int j = 0; j < i; j++){
            ret1.push_back(deltas[j].second);
            cur += deltas[j].first;
        }
//        cout << "CUR = " << cur << endl;
        if(L <= cur && cur <= R){
            for(auto x : ret1) ret.push_back(x);
            return ret;
        }
        for(int j = i; j < w.size(); j++){
            ret1.push_back(deltas[j].second);
            ret1.pop_front();
            cur -= deltas[j-i].first;
            cur += deltas[j].first;
            if(L <= cur && cur <= R){
                for(auto x : ret1) ret.push_back(x);
                return ret;
            }
            if(L <= cur && cur <= R){
                return ret;
            }
        }
        return {};
    }
    return {};
    
}

// X0
// 0   d1    d2    d3    d4    d5
// jei naudoju k situ, tai bus k*x0 + F(k),
// L <= k*x0 + F(k) <= r
// L - k*x0 <= F(k) <= R - k*x0
// l <= f(k) <= r
// CIA bus visi d <= uz r-l, tai uztenka paziureti i maziausia ir didziausia imanoma sumas;
// arciausias skaicius, didesnis uz u - k*x0

#include <cstdio>
#include <vector>
#include <cassert>

//#include "molecules.h"

int main() {
    int n, l, u;
    assert(3 == scanf("%d %d %d", &n, &l, &u));
    std::vector<int> w(n);
    for (int i = 0; i < n; i++)
        assert(1 == scanf("%d", &w[i]));
    std::vector<int> result = find_subset(l, u, w);
    
    
    printf("%d\n", (int)result.size());
    for (int i = 0; i < (int)result.size(); i++)
        printf("%d%c", result[i], " \n"[i == (int)result.size() - 1]);
}
/*
    Laba diena. Aš ir dar vienas akademikas, Aldas Lenkšas, girdėjome gandus, jog, galimai, kitais metais keisis NMA informatikos sekcijos dėstytojas. Todėl norėjom paklausti, ar, keitimosi atveju, įmanoma būtų mums su Aldu tapti informatikos sekcijos mokytojais? Šiuo metu esame aktyvūs olimpiadininkai (dalyvaujam ir esam parsivežę medalių iš Baltijos ir tarptautinių informatikos olimpiadų), turime daug noro ir entuziazmo šiam darbui!
*/
