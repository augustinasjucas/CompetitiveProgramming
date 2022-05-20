#include <bits/stdc++.h>
#pragma GCC optimize("O2")
using namespace std;
const int dydis = 2e5 + 10;
int n, r, q;
vector<int> dideli; // regionai
vector<int> regs[dydis];
int tevas[dydis];
vector<int> gr[dydis];
unordered_map<long long, long long > rem;
int sm[dydis];
int val[dydis];
int kam[dydis];
int sq;
int dbInd = 0;
int kelint[dydis];
int enter[dydis], leave[dydis];
vector<long long> dideliuMem1[dydis], dideliuMem2[dydis];

void dfs1(int v, int came){
	enter[v] = dbInd++;
	for(auto x : gr[v]){
		if(x == came) continue;
		dfs1(x, v);
	}
	leave[v] = dbInd;
}
bool isAnc(int a, int b){
	return enter[a] <= enter[b] && leave[b] <= leave[a];
}
void dfs(int v, int came, int kek, int prm){
//		cout << "v = " << v << endl;
	sm[v] = val[v];
	for(auto x : gr[v]){
		if(x == came) continue;
		dfs(x, v, kek + val[v], prm);
		sm[v] += sm[x];
	}

	if(!val[v]){
//		cout << "rem[" << prm+1 << "][" << v+1 << "(" << kam[v]+1 << ")] += " << kek << "\n";
//		cout << "rem[" << v+1 << "(" << kam[v]+1 << ")][" << prm+1 << "] += " << sm[v] << "\n"
		dideliuMem1[prm][kam[v]] += kek;
		dideliuMem2[prm][kam[v]] += sm[v];
	}
}
int kell = 0;
void calc(int ind){
	kelint[ind] = kell++;
	dideliuMem1[kelint[ind]].resize(r);
	dideliuMem2[kelint[ind]].resize(r);
//	cout << "nuo " << ind+1 << endl;
	for(int i = 0; i < n; i++) sm[i] = val[i] = 0;
	for(auto x : regs[ind]){
		val[x] = 1;
	}
	dfs(0, -1, 0, kelint[ind]);
}
long long f(int a, int b){
	if((int)regs[a].size() >= sq){
		int sk = kelint[a];
		return dideliuMem1[sk][b];
	}
	if((int)regs[b].size() >= sq){
		int sk = kelint[b];
		return dideliuMem2[sk][a];
	}
	if(rem.count(a * dydis + b)) {
		return rem[a * dydis + b] ;
	}
	long long ret = 0;
	for(auto x : regs[a]){
		for(auto y : regs[b]){
			ret += isAnc(x, y);
		}
	}
	return rem[a * dydis + b] = ret;
}
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> n >> r >> q;
	for(int i = 0; i < n; i++){
		int par = -1, reg;
		if(i == 0) cin >> reg;
		else cin >> par >> reg;
		par--; reg--;
		regs[reg].push_back(i);
		if(par != -2){
			gr[i].push_back(par);
			gr[par].push_back(i);
		}
		tevas[i] = par;
		kam[i] = reg;
	}
	dfs1(0, -1);
	sq = sqrt(n);
	for(int i = 0; i < r; i++){
		if((int)regs[i].size() >= sq){
			calc(i);
			dideli.push_back(i);
		}
	}
	while(q--){
		int a, b; cin >> a >> b; a--; b--;
		cout << f(a, b) << endl;
	}
	return 0;
}
