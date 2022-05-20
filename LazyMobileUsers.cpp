#include <bits/stdc++.h>
using namespace std;
int n, k;
const int dydis = 1e5 + 19;
vector<int> gr[dydis];
int dp[dydis][2];
int dfs(int v, bool reikGrizti){
	if(dp[v][reikGrizti] != -1) return dp[v][reikGrizti];
	if(reikGrizti){
		int ret = 1;
		vector<int> ms;
		for(auto x : gr[v]){
			ms.push_back(dfs(x, 1));
		}
		sort(ms.begin(), ms.end()); reverse(ms.begin(), ms.end());
		for(int i = 0; i < min((int)ms.size(), k-1); i++){
			ret += ms[i];
		} 	
		return dp[v][reikGrizti] = ret;

	}else{
		if(gr[v].size() == 0) return 1;
		int ret = 1;
		vector<pair<int, int> > ms;
		for(auto x : gr[v]){
			ms.push_back({dfs(x, 1), dfs(x, 0)});
		}
		sort(ms.begin(), ms.end()); sort(ms.begin(), ms.end());
		int pref[ms.size()];
		pref[0] = ms[0].first; for(int i = 1; i < (int)ms.size(); i++) pref[i] = pref[i-1] + ms[i].first;
		for(int i = 0; i < (int)ms.size(); i++){
			int pr = (k == 1 ? 0 : pref[min((int)ms.size()-1, k-2)]);
			if(i <= min((int)ms.size()-1, k-2)){
				pr -= ms[i].first;
				if(k-1 <= (int)ms.size()-1) pr += ms[k-1].first; 
			}
			int st = ms[i].second + pr + 1;
			ret = max(ret, st);
		} 
		
		return dp[v][reikGrizti] = ret;
	}
}
int main(){
	cin >> n >> k;
	for(int i = 0; i < n; i++){
		dp[i][0] = dp[i][1] = -1;
		int kk; cin >> kk;
		for(int j = 0; j < kk; j++){
			int a; cin >> a; a--;
			gr[i].push_back(a);
			//gr[a].push_back(i);
		}
	}
	cout << dfs(0, 0);
	return 0;
}
