#include <bits/stdc++.h>
using namespace std;
const int dydis = 3e5 + 10;
vector<int> gr[dydis];
int n, m;
vector<long long> hsh = {(long long)1e9 + 7, 123111211, 481128181, (long long)1e9 + 9, 1289312111ll, 1230192311111ll, 123712818111ll};
vector<long long> heshai[dydis];
int tevas[dydis];
vector<int> g[dydis];
bool vis[dydis] = {};
int dbInd = 0;
int sk[dydis];
bool galima = 1;
void dfs(int v, int came = -1){
	if(vis[v]) {
		galima = 0;
		return ;
	}
	vis[v] = 1;
	sk[v] = dbInd++;
	for(auto x : g[v]){
		if( x== came) continue;
		dfs(x, v);
	}
}
int fP(int v){
	if(v == tevas[v]) return v;
	return tevas[v] = fP(tevas[v]);
}
void conn(int a, int b){
	a = fP(a);
	b = fP(b);
	tevas[a] = b;
}
int main(){
	for(int i = 0; i < dydis; i++) tevas[i] = i;
	cin >> n >> m;
	vector<pair<int, int> > brn;
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b; a--; b--;
		gr[a].push_back(b);
		gr[b].push_back(a);
		brn.push_back({a, b});
	}
	for(int i = 0; i < n; i++){
		gr[i].push_back(i);
		sort(gr[i].begin(), gr[i].end());
		for(int j = 0; j < (int)hsh.size(); j++){
			long long st= 0;
			for(auto x : gr[i]) st = (1ll * st * n % hsh[j] + x)%hsh[j];
			heshai[i].push_back(st);
		}
	}
	for(auto x : brn){
		int a = x.first;
		int b = x.second;
		if(heshai[a] == heshai[b]) conn(a, b);
	}
	
	/*for(int i = 0; i < (int) vec.size(); i++){
		for(int j = i; j <= n; j++){
			if(j == n || vec[i].first != vec[j].first){
				i = j-1; break;
			}
			tevas[vec[j].second] = vec[i].second;
		//	cout << "tevas[" << vec[j].second+1 << "] = " <<  vec[i].second +1<< endl;
		}
	}*/
	set<pair<int, int> > bv;

	for(auto x : brn){
		int a = x.first;
		int b = x.second;
		
		a = fP(a);
		b = fP(b);
		if(a < b) swap(a, b);
		if(bv.count({a, b})) continue;
		if(a == b) continue;
		bv.insert({a, b});
		g[a].push_back(b);
		g[b].push_back(a);
		if(g[a].size() > 2 || g[b].size() > 2) galima = 0;
	}
	if(!galima) {
		cout << "NO";
		return 0;
	}
	int cur = 0;
	for(int i = 0; i < n; i++){
		if(fP(i) != i) continue;
		if(vis[i]) continue;
		if(g[i].size() > 1) continue;
		dfs(i); dbInd++; dbInd ++;
		break;
	}
	for(int i = 0; i < n; i++){	
		if(fP(i) == i && !vis[i]){
			 galima = 0;
		}
	 }
	if(!galima) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	for(int i = 0; i < n; i++){
		cout << sk[fP(i)] + 1 << " ";		
	}
	return 0;
}
