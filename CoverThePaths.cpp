#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
vector<int> gr[dydis];
int n;

set<int> keliai[dydis];
int tevas[dydis];
int fP(int v){
	if(tevas[v] == v) return v;
	return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
	a = fP(a);
	b = fP(b);
	if(keliai[a].size() > keliai[b].size()){
		for(auto x : keliai[b]) keliai[a].insert(x);
		tevas[b] = a;
	}else{
		for(auto x : keliai[a]) keliai[b].insert(x);	
		tevas[a] = b;
	}
}
int ans = 0;
vector<int> reik;
bool privalau[dydis] = {};
void dfs(int v, int came = -1){
	int turetu = keliai[v].size();
	for(auto x : gr[v]){
		if(x == came) continue;
		dfs(x, v);
		turetu += keliai[fP(x)].size();
	}
	for(auto x : gr[v]){
		if(x == came) continue;
		conn(x, v);
	}
	if(turetu != keliai[fP(v)].size() || privalau[v]){
		keliai[fP(v)].clear();
		ans++;
		reik.push_back(v);
	}else{
	}
}
int main(){
	for(int i = 0; i < dydis; i++) tevas[i] = i;
	cin >> n;
	for(int i = 0; i < n-1; i++){
		int a, b; cin >> a >> b; a--; b--;
		gr[a].push_back(b);
		gr[b].push_back(a);
	}
	int m; cin >> m;
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b; a--; b--;
		if(a == b) privalau[a] = 1;
		keliai[a].insert(i);
		keliai[b].insert(i);
	}
	
	dfs(0);
	cout << ans << endl;
	for(auto x : reik) cout << x+ 1 << " ";
	
	return 0;
}
