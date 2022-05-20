//#include "simurgh.h"

#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

static int MAXQ = 30000;

static int n, m, q = 0;
static vector<int> u, v;
static vector<bool> goal;

static void wrong_answer() {
	printf("NO\n");
	exit(0);
}

static bool is_valid(const vector<int>& r) {
	if(int(r.size()) != n - 1)
		return false;

	for(int i = 0; i < n - 1; i++)
		if (r[i] < 0 || r[i] >= m)
			return false;

	return true;
}

static int _count_common_roads_internal(const vector<int>& r) {
	if(!is_valid(r))
		wrong_answer();

	int common = 0;
	for(int i = 0; i < n - 1; i++) {
		bool is_common = goal[r[i]];
		if (is_common)
			common++;
	}

	return common;	
}

int count_common_roads(const vector<int>& r) {
	q++;
	if(q > MAXQ)
		wrong_answer();

	return _count_common_roads_internal(r);
}















#include <bits/stdc++.h>
//#include "simurgh.h"
using namespace std;
int N;
const int dydis = 501;
vector<pair<int, int> > brn;
vector<int> zn(dydis * dydis, -1);
vector<pair<int, int> > gr[dydis];
vector<int> tikrai;
int tevas[dydis];
int fP(int v){
	if(tevas[v] == v) return v;
	return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
	a = fP(a);
	b = fP(b);
	if(a == b) return;
	tevas[a] = b;
}
set<int> virs;
bool vis[dydis] = {0};
int deg[dydis] = {0};
void form(){
	for(int i = 0; i < N; i++) {
		gr[i].clear();
		vis[i] = 0;
		deg[i] = 0;
	}
	virs.clear();
//	cout << "grafas:\n";
	for(int i = 0; i < (int) brn.size(); i++){
		if(zn[i] != -1) continue;
		int a = fP(brn[i].first);
		int b = fP(brn[i].second);
		if(a == b) continue;
		gr[a].push_back({b, i});
		gr[b].push_back({a, i});
//		cout << a << " -- " << b << endl;
		virs.insert(a); virs.insert(b);
	}
	//cout << endl;
}
vector<int> pl;
void dfs(int v){
	vis[v] = 1;
	for(auto x : gr[v]){
		if(vis[x.first]) continue;
		pl.push_back(x.second);
		deg[v]++;
		deg[x.first]++;
		dfs(x.first);
	}
}
vector<int> find_roads(int n, vector<int> u, vector<int> v) {
	//count_common_roads
	N = n;
	vector<int> ret;
	for(int i = 0; i < N; i++) tevas[i] = i;
	for(int i = 0; i < (int)u.size(); i++) {
		brn.push_back({u[i], v[i]});
	}
	int it = 0;
	while((int) tikrai.size() != n-1){
		pl.clear();
		form();
		int v = *virs.begin();
		dfs(v);
		int u = -1;
		for(int i = 0; i < n; i++) if(deg[i] == 1) u = i;
	//	cout << "komponentai: \n"; for(int i = 0; i < n; i++) cout << i << ": " << fP(i) << endl; cout << endl;
	//	cout << "suformuoju medi: \n"; for(int i = 0; i < pl.size(); i++) cout << brn[pl[i]].first << " - > " << brn[pl[i]].second << endl;
	//	cout << "\nmedzio lapas: " << u << endl;
	//	cout << endl;
		vector<int> rest;
		for(int i = 0; i < (int)pl.size(); i++){
			int a = fP(brn[pl[i]].first);
			int b = fP(brn[pl[i]].second);
			if(a == u || b == u){
				continue;
			}
			rest.push_back(pl[i]);
		}
		for(auto x : tikrai) rest.push_back(x);
		vector<pair<int, int> > aa;
		int mx = 0;
		for(auto x : gr[u]){ 
			rest.push_back(x.second);
			int cm = count_common_roads(rest);
			aa.push_back({cm, x.second});
			mx = max(mx, cm);
			rest.pop_back();
		}
		for(auto x : aa){
			if(x.first == mx) {
				tikrai.push_back(x.second);
				zn[x.second] = 1;
				conn(brn[x.second].first, brn[x.second].second);
		//		cout << brn[x.second].first << " -> " << brn[x.second].second << " tikrai geras" << endl;
			}else{
				zn[x.second] = 0;
		//		cout << brn[x.second].first << " -> " << brn[x.second].second << " tikrai blogas" << endl;
			}
		}
	}

	return tikrai;
}
/*
6 9
0 1
1 2
2 3
3 4
4 5
5 0
4 0
4 1
1 3
0 1 5 4 3


4 3
0 2
0 1
1 3
0 2 1




*/



int main() {
	assert(2 == scanf("%d %d", &n, &m));

	u.resize(m);
	v.resize(m);

	for(int i = 0; i < m; i++)
		assert(2 == scanf("%d %d", &u[i], &v[i]));

	goal.resize(m, false);

	for(int i = 0; i < n - 1; i++) {
		int id;
		assert(1 == scanf("%d", &id));
		goal[id] = true;
	}

	vector<int> res = find_roads(n, u, v);

	if(_count_common_roads_internal(res) != n - 1)
		wrong_answer();

	printf("YES\n");

	return 0;
}
