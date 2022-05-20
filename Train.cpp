
#pragma GCC optimize("O2")
#pragma GCC target("avx2")
//#include "train.h"
#include <bits/stdc++.h>
using namespace std;
vector<int> charg;
vector<int> priklauso;
int n;
vector<bool> isEnd(5001, 0);
const int dydis = 5e3 + 10;
int ind[dydis] = {};
int low[dydis] = {};
int onS[dydis] = {};
vector<int> gr[dydis];
int dbInd = 0;
vector<int> st;
int sz[dydis] = {0};
vector<pair<int, int> > br;
void dfs(int v){
 	if(ind[v] == -1){
		ind[v] = dbInd;
		low[v] = dbInd++;
		onS[v] = 1;
		st.push_back(v);
	}
	
	for(auto x : gr[v]){
		if(ind[x] == -1){
			dfs(x);
			low[v] = min(low[x], low[v]);
		}else if(onS[x]){
			low[v] = min(low[v], ind[x]);
		}
	}
	if(low[v] == ind[v]){
		sz[low[v]] = 0;
		while(true){
			int u = st.back(); st.pop_back();
			low[u] = min(low[u], low[v]);
			onS[u] = 0;
			sz[low[v]]++;
			if(u == v) break;
		}
	}
}
vector<int> g[dydis];
bool has[dydis];
set<pair<int, int> > setas;
int rem[dydis];
bool arYra(int v){
	if(sz[v] > 1 && has[v]) return true;
	if(isEnd[v]) if(has[v]) return true;
	if(rem[v] != -1) return rem[v];
	bool ret = 0;
//	cout << "esu " << v << endl;
	for(auto x : g[v]){
		ret = ret | arYra(x);
	} 
	return rem[v] = ret;
}
bool arYra1(int v){
	if(sz[v] > 1 && !has[v]) return true;
	if(isEnd[v]) if(!has[v]) return true;
	if(rem[v] != -1) return rem[v];
	bool ret = 0;
//	cout << "esu " << v << endl;
	for(auto x : g[v]){
		ret = ret | arYra1(x);
	} 
	return rem[v] = ret;
}
vector<int> viskasPirmo(){
	
//	cout << "pirmo! " << endl;
	for(int i = 0; i < 5001; i++) isEnd[i] = 0, rem[i] = -1;
	vector<int> ret(n, 0);
	for(int i = 0; i < n; i++){
		if(ind[i] == -1) dfs(i);
		has[low[i]] |= charg[i];
		//cout << i << " komp: " << low[i] << endl;
	}
	for(auto x : br){
		int a = low[x.first];
		int b = low[x.second];
		if(a == b) isEnd[a] = 1;
		if(setas.count({a, b})) continue;
		//cout << a << " -> " << b << "\n";
		setas.insert({a, b});
		if(a != b) g[a].push_back(b);
	}
	for(int i = 0; i < n; i++){
	//	cout << "nuo " << i << endl;
		ret[i] = arYra(low[i]);
	}
	
	return ret;
}
vector<int> viskasAntro(){
	
//	cout << "pirmo! " << endl;
	for(int i = 0; i < 5001; i++) isEnd[i] = 0, rem[i] = -1;
	vector<int> ret(n, 0);
	for(int i = 0; i < n; i++){
		if(ind[i] == -1) dfs(i);
		has[low[i]] |= charg[i];
		//cout << i << " komp: " << low[i] << endl;
	}
	for(auto x : br){
		int a = low[x.first];
		int b = low[x.second];
		if(a == b) isEnd[a] = 1;
		if(setas.count({a, b})) continue;
		//cout << a << " -> " << b << "\n";
		setas.insert({a, b});
		if(a != b) g[a].push_back(b);
	}
	for(int i = 0; i < n; i++){
	//	cout << "nuo " << i << endl;
		ret[i] = !arYra1(low[i]);
	}
	
	return ret;
}
vector<int> vienCharg(){
	vector<int> ret(n);
	return ret;
}

vector<int> prm(){
	vector<int> ret(n, 0);

	for(int i = 0; i < n; i++){
		int v = i;
	//	cout << "i  = " << i << endl;
		while(true){
		//	cout << "v = " << v << ", end = " << isEnd[v] << endl;
			if(isEnd[v] && priklauso[v] == charg[v]){
				ret[i] = priklauso[v];
				break;
			}else{
				if(gr[v].size() == 1 && gr[v][0] == v){
					ret[i] = charg[v];
					break;
				}else{
					v++;
				}
			}
		}
	}
	return ret;
}
vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
	vector<int> res(a.size());
	priklauso = a;
	charg = r;
	n = a.size();
	for(int i = 0; i < n; i++) ind[i] = -1;
	for(int i = 0; i < (int)u.size(); i++){
		br.push_back({u[i], v[i]});
		gr[u[i]].push_back(v[i]);
	//	gr[v[i]].push_back(u[i]);
	}
	int cnt[2] = {0}; for(auto x : a) cnt[x]++;
	int rc = 0; for(auto x : r) rc += x;
	bool pirmasSub = 1;
	for(int i = 0 ; i < u.size(); i++) {
		if(v[i] == u[i]) isEnd[v[i]] = 1;
		if(v[i] - u[i] == 0 || v[i]-u[i] == 1) continue;
		pirmasSub = 0;
	}
	if(pirmasSub){
		return prm();
	}
	if(cnt[0] == 0){
		return viskasPirmo();
	}else if(cnt[1] == 0){
		return viskasAntro();
	}else if(rc == 0){
		return vienCharg();
	}
	//for(int i = 0; i < n; i++)
	
	return res;
}








/*

8 9
1 1 1 1 1 1 1 1
0 0 0 1 0 0 0 0 
0 1
1 2
1 3
3 4
4 5
5 3
2 7
7 6
6 2 


6 7
0 0 1 1 0 1
0 1 0 0 0 1
0 1
1 2
2 3
3 4
4 5
2 2
5 5



*/










//#include "train.h"

#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

int main() {
	int n, m;
	assert(2 == scanf("%d %d", &n, &m));

	vector<int> a(n), r(n), u(m), v(m);

	for(int i = 0; i < n; i++)
		assert(1 == scanf("%d", &a[i]));

	for(int i = 0; i < n; i++)
		assert(1 == scanf("%d", &r[i]));

	for(int i = 0; i < m; i++)
		assert(2 == scanf("%d %d", &u[i], &v[i]));

	vector<int> res = who_wins(a, r, u, v);

	for(int i = 0; i < (int)res.size(); i++)
		printf(i ? " %d" : "%d", res[i]);
	printf("\n");

	return 0;
}
