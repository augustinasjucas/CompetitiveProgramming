//#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> find_subset(int l, int r, vector<int> w) {
	vector<pair<int, int> > ms; 
	for(int i = 0; i < (int) w.size(); i++){
		if(l <= w[i] && w[i] <= r) {
			return {i};
		}
		if(w[i] > l) continue;
		ms.push_back({w[i], i});
	}
	sort(ms.begin(), ms.end());
	if(ms.size() == 0) return {};
	vector<int> deltas, pref;
	multiset<long long> setas;
	for(int i = 0; i < (int)ms.size(); i++){
		deltas.push_back(ms[i].first - ms[0].first);
		pref.push_back((pref.size() == 0 ? 0 : pref.back()) + deltas.back());
		setas.insert(pref.back());
	}
	for(int k = 1; k <= (int)ms.size(); k++){
		int L = l - k * ms[0].first;
		int R = L + (r-l);
		cout << "K = " << k << endl;
		if(pref[k-1] <= L && pref[pref.size()-1] - pref[pref.size()-k] >= R)
		if(L <= *sk && *sk <= R){

		}
	}
	return {};
}
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
