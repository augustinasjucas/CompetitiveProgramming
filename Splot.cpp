#include <bits/stdc++.h>
using namespace std;

string a;
string pa;
int dbInd = 0;
int realInd[200] = {};
bool taken[202] = {};
bool c[202] = {};
int n;
vector<int> gr[201];
int findEnd(int ind) {
	if(a[ind] == 'x' || a[ind] == 'o') {
		return ind;
	}
	if(a[ind] == 'S') {
		int bal = 1;
		for(int i = ind+1; i < (int) a.size(); i++) {
			if(a[i] == 'S' || a[i] == 'P') bal++;
			if(a[i] == '#') bal--;
			if(bal == 0) return i;
		}
		
	}else if(a[ind] == 'P'){
		int bal = 1;
		for(int i = ind+1; i < (int) a.size(); i++) {
			if(a[i] == 'S' || a[i] == 'P') bal++;
			if(a[i] == '#') bal--;
			if(bal == 0) return i;
		}
	}
	//cout << "NERADAU!!! ";
	return -1;
}

void conn(int a, int b) {
	gr[a].push_back(b);
	gr[b].push_back(a);
	//cout << a << " -- " << b << endl;
}
pair<int, int> gen(int l, int r) {
//	cout << "intervalas [" << l << "; " << r << "]\n";
	if(l == r) {
		realInd[dbInd] = l;
		dbInd++;
		return {dbInd-1, dbInd-1};
	}
	
	if(a[l] == 'S') {
		int ed = findEnd(l+1);
		
		auto k1 = gen(l+1, ed);
		auto k2 = gen(ed+1, r-1);
		
		conn(k1.second, k2.first);
		return {k1.first, k2.second};
	}else {
		int ed = findEnd(l);
		
		pair<int, int> stulpai = {l+2, ed - 2};
		
		
		int ed2 = findEnd(stulpai.first+1);
		
		auto k1 = gen(stulpai.first+1, ed2);
		auto k2 = gen(ed2+1, stulpai.second-1);
		
		realInd[dbInd++] = l+1;
		realInd[dbInd++] = r-1;
		
		conn(dbInd-2, k1.first);
		conn(dbInd-2, k2.first);
		
		conn(k1.second, dbInd-1);
		conn(k2.second, dbInd-1);
		return {dbInd-2, dbInd-1};
	}
}
bool vis[210] = {};
bool can[210] = {};
void dfs(int v){
	if(vis[v]) return ;
	vis[v] = 1;
	can[v] = 1;
	if(c[v] || taken[v]) return ;
	for(auto &x : gr[v]) {
		if(taken[x] || c[x]) {
			can[x] = 1;
			continue;
		}
		dfs(x);
	}
}
int main () {
	
	cin >> a;
	pa =a ;
	auto A = gen(0, a.size()-1);
	n = dbInd;
	for(int i = 0 ;i < n; i++) {
		if(a[realInd[i]] == 'x') taken[i] = 1;
	}
	int ans = 0;
	for(int i = 0; i < (1 << n); i++) {
		bool is = 1;
		for(int j = 0; j < n; j++) {
			if((1 << j) & i) {
			}else {
				if(taken[j]) {
					is = 0;
					break;
				}
			}
		}
		if(!is) continue;
		for(int j = 0; j < n; j++) c[j] = 0, vis[j] = 0, can[j] = 0;
		for(int j = 0; j < n; j++) {
			if((1 << j) & i) {
				c[j] = 1;
			}
		}
		dfs(A.first);
		for(int j = 0; j < n; j++) if(!can[j]) is = 0;
		if(!is) continue;
		int st = __builtin_popcount(i);
		if(st > ans) {
			pa = a;
		//	cout << "ans = " << st << ", jei nustatau i x: ";
			for(int j = 0; j < n; j++) {
				if((1 << j) & i) {
					pa[realInd[j]] = 'x';
			//		cout << j << " ";
				}
			}
		//	cout << endl;
			ans = st;
		}
	}
	cout << ans << "\n";
	cout << pa;
	return 0;
}
