#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int dydis = 2e6 + 10;
int nxt[dydis];
int desn[dydis];
int n, k;
vector<pair<int, int> > mas;
vector<pair<int, int> > vec;
bool vis[dydis] = {};
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> n >> k;
	for(int i = 0; i < n; i++){
		int a, b; cin >> a >> b;
		vec.push_back({a, i*2});
		vec.push_back({b, i*2+1});
	}
	sort(vec.begin(), vec.end());
	for(int i = 0; i < (int)vec.size()-1; i++){
		//cout << ((char)('a'+(vec[i].second/2))) << " ";
		desn[vec[i].second] = vec[i+1].second;
	}
	//cout << endl;
	desn[vec.back().second] = 2*n;
	
	for(int i = 0; i < 2*n; i++){
		nxt[i] = desn[(i ^ 1)];
	//	cout << "nxt[" << i << "] = " << nxt[i] << endl;
	}
	
	int start = vec[0].second;
	int cur = start;
	int curAns = 0;
	int jauYra = 0;
	while(cur != 2*n){
		vis[cur] = 1;
		cur = nxt[cur];
		curAns++;
		jauYra++;
	}
	vector<int> ciklai;
	for(int i = 0; i < 2*n; i++){
		if(vis[i]) continue;
		int cur = i;
		int kek = 0;
		while(true){
			kek++;
			vis[cur] = 1;
			cur = nxt[cur];
			if(cur == i) break;
		}
		ciklai.push_back(kek);
		//cout << "dedu " << kek << endl;
	}
	
	sort(ciklai.begin(), ciklai.end()); reverse(ciklai.begin(), ciklai.end());
	
	for(int i = 0; i < min((int)ciklai.size(), k); i++){
		curAns += ciklai[i] + 2;
		jauYra += ciklai[i];
	}
	
	k -= min((int)ciklai.size(), k);
	if(k != 0){
		//cout << "k != 0" << endl;
		curAns += ((k/2) * 2) * 2;
		curAns += (k & 1);
	}
	
	cout << curAns;
	
	return 0;
}
