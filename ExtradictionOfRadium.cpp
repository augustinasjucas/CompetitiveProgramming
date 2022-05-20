#include <bits/stdc++.h>
using namespace std;

struct seg_tree{
	vector<vector<int> > l, r, val;
	int n, trees; int dbInd;
	void build(int k, int v){
		if(v >= n){
			l[k][v] = r[k][v] = dbInd++;
			val[k][v] = 0;
		}else{
			build(k, v*2); build(k, v*2+1);
			l[k][v] = l[k][v*2]; r[k][v] = r[k][v*2+1]; 
			val[k][v] = 0;
		}
	}
	seg_tree(int medzioDydis, int medziu){
		l.resize(medziu); r.resize(medziu); val.resize(medziu);
		for(auto &x : l) x.resize(medzioDydis * 2 + 1);
		for(auto &x : r) x.resize(medzioDydis * 2 + 1);
		for(auto &x : val) x.resize(medzioDydis * 2 + 1);
		n = medzioDydis;
		trees = medziu;
		for(int i = 0; i < medziu; i++) {
			dbInd = 0;
			build(i, 1);
		}
	}
	void change(int k, int v, int L, int R, int x){
		if(L <= l[k][v] && r[k][v] <= R){
			val[k][v] = x;
		}else if(R < l[k][v] || r[k][v] < L){
			return ;
		}else{
			change(k, v*2, L, R, x);
			change(k, v*2+1, L, R, x);
			val[k][v] = max(val[k][v*2], val[k][v*2+1]);
		}
	}
	int getMax(int k, int v, int L, int R){
		if(L <= l[k][v] && r[k][v] <= R){
			return val[k][v];
		}else if(R < l[k][v] || r[k][v] < L){
			return -1;
		}else{
			return max(getMax(k, v*2, L, R), getMax(k, v*2+1, L, R));
		}
	}
	int getMaxBe(int k, int ind){
		return max(getMax(k, 1, 0, ind-1), getMax(k, 1, ind+1, n-1));
	}
};

int n, m, q;
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> q;
	int mas[n][m];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> mas[i][j];
		}
	}
	//cout << "eilutes: " << n << " ir " << m << endl;
	seg_tree eilutes(m, n);
	seg_tree stulpeliai(n, m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			eilutes.change(i, 1, j, j, mas[i][j]);			
			stulpeliai.change(j, 1, i, i, mas[i][j]);
		}
	}

	set<pair<int, int> > mxe, mxs;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int mxE = eilutes.getMaxBe(i, j);
			int mxS = stulpeliai.getMaxBe(j, i);
			//cout << "[" << i << "; " << j << "], mxE = " << mxE << ", mxS = " << mxS << endl;
			if(max(mxE, mxS) < mas[i][j]){
				mxe.insert({i, j});
				mxs.insert({j, i});
			}
		}
		//cout << endl;
	}
	while(q--){
		int e, s, k; cin >> e >> s >> k; e--; s--;
		eilutes.change(e, 1, s, s, k);
		stulpeliai.change(s, 1, e, e, k);
		
		int eilutesE = -1, eilutesS = -1;
		auto low = mxe.lower_bound({e, -1});
		if(low != mxe.end() && low->first == e) eilutesE = low->first, eilutesS = low->second;
		
		int stulpelioE = -1, stulpelioS = -1;
		low = mxs.lower_bound({s, -1});
		if(low != mxs.end() && low->first == s) stulpelioE = low->second, stulpelioS = low->first;
		
		if(eilutesE != -1 && max(eilutes.getMaxBe(eilutesE, eilutesS), stulpeliai.getMaxBe(eilutesS, eilutesE)) > eilutes.getMax(eilutesE, 1, eilutesS, eilutesS)){
			mxe.erase({eilutesE, eilutesS});
			mxs.erase({eilutesS, eilutesE});
		}
		
		if(stulpelioE != -1 && max(eilutes.getMaxBe(stulpelioE, stulpelioS), stulpeliai.getMaxBe(stulpelioS, stulpelioE)) > eilutes.getMax(stulpelioE, 1, stulpelioS, stulpelioS)){
			mxe.erase({stulpelioE, stulpelioS});
			mxs.erase({stulpelioS, stulpelioE});
		}
		if(max(eilutes.getMaxBe(e, s), stulpeliai.getMaxBe(s, e)) < eilutes.getMax(e, 1, s, s)){
			mxe.insert({e, s});
			mxs.insert({s, e});
		}
		cout << mxe.size() << "\n";
	}
	return 0;
}
