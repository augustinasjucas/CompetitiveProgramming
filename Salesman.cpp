#include <bits/stdc++.h>
using namespace std;
const long long inf = 2e9;
struct medis{
	struct node{
		int val[4] = {-inf, -inf, -inf, -inf};
		int l, r;
	};
	vector<node> mas;
	int n;
	int dbInd = 0;
	void build(int v){
		if(v >= n){
			mas[v].l = mas[v].r = dbInd++;
		}else{
			build(v*2); build(v*2+1);
			mas[v].l = mas[v*2].l;
			mas[v].r = mas[v*2+1].r;
		}
	}
	medis(int dd){
		n = dd;
		mas.resize(2 * n + 1);
		build(1);
	}
	void change(int v, int l, int r, long long x, int ii){
		if(l <= mas[v].l && mas[v].r <= r){
			mas[v].val[ii] = x;
		}else if(r < mas[v].l || mas[v].r < l){
			return;
		}else{
			change(v*2, l, r, x, ii);
			change(v*2+1, l, r, x, ii);
			mas[v].val[ii] = max(mas[v*2].val[ii], mas[v*2+1].val[ii]);
		}
	}
	long long get(int v, int l, int r, int ii){
		if(l <= mas[v].l && mas[v].r <= r){
			return mas[v].val[ii];
		}else if(r < mas[v].l || mas[v].r < l){
			return -inf;
		}else{
			return max(get(v*2, l, r, ii), get(v*2+1, l, r, ii));
		}
	}
};
 
int n, U, D, s;
const int dydis = 5e5 + 10;
vector<pair<int, int> > fairs[dydis];
long long curAns[dydis];
long long pref[dydis] = {};
medis v(dydis);
void updateCur(int ind, long long x){
	curAns[ind] = x;
	v.change(1, ind, ind, curAns[ind] + 1ll * D * ind, 0);
	v.change(1, ind, ind, curAns[ind] - 1ll * U * ind, 1);
}	
long long fMx1(int l, int r){
	return v.get(1, l, r, 0);
}
long long fMx2(int l, int r){
	return v.get(1, l, r, 1);
}
long long fMx3(int l, int r){
	return v.get(1, l, r, 2);
}
void upd1(int d){
	if(fairs[d].size() == 0) return;
	vector<pair<int, long long> > chang;
	for(auto x : fairs[d]){
		long long galiBut = fMx1(0, x.first-1) - 1ll * x.first * D; 
		chang.push_back({x.first,  galiBut + x.second});
	}
	for(int i = (int)fairs[d].size()-1; i > -1; i--){
		auto x = fairs[d][i];
		long long galiBut = fMx2(x.first+1, dydis-1) + 1ll * x.first * U;
		chang.push_back({x.first, galiBut + x.second});
	}
	for(auto x : chang){
		int ind = x.first;
		long long val = x.second;
		if(val < curAns[ind]){
			continue;
		}
		updateCur(ind, val);
	}
}
void upd2(int d){
	if(fairs[d].size() <= 1) return ;
	long long sm = 0;
	//UX + [DA - pref[A] + curVal[A]] + [pref[B]-B(D+U)]
	for(auto x : fairs[d]){
		sm += x.second;
		pref[x.first] = sm;
		v.change(1, x.first, x.first, 1ll * D * x.first - pref[x.first] + curAns[x.first], 2); // Kaip A
		v.change(1, x.first, x.first, 1ll * pref[x.first] - x.first * (D+U), 3); // kaip B
	}
	vector<pair<int, long long> > chang;
	for(int i = 1; i < (int)fairs[d].size(); i++){
		auto x = fairs[d][i];
		long long kair = v.get(1, 0, x.first-1, 2);
		long long desn = v.get(1, x.first, dydis-1, 3);
		chang.push_back({x.first, kair+desn + U * x.first});
	}
	pair<int, int> last = {-1, -1};
	//-XD + [curVal[A] + pref[A-1] - AU] + [B(D+U)-pref[B]]
	for(auto x : fairs[d]){
		if(last.first != -1)
			v.change(1, x.first, x.first, curAns[x.first] + (last.first == -1 ? 0 : pref[last.first]) -1ll * U * x.first, 2); // Kaip A
		v.change(1, x.first, x.first, x.first*(D+U) - (last.first == -1 ? 0 : pref[last.first]), 3); // kaip B
		last = x;
	}
	for(int i = 0; i < (int)fairs[d].size()-1; i++){
		auto x = fairs[d][i];
		long long kair = v.get(1, 0, x.first, 3);
		long long desn = v.get(1, x.first+1, dydis-1, 2);
		chang.push_back({x.first, kair+desn - D * x.first});
	}
	for(auto x : chang){
		int ind = x.first;
		long long val = x.second;
		if(val < curAns[ind]){
			continue;
		}
		updateCur(ind, val);
	}
	for(auto x : fairs[d]){
		v.change(1, x.first, x.first, -inf, 2); // kaip B
		v.change(1, x.first, x.first, -inf, 3);
	}
	//cout << v.get(1, 0, dydis-1, 2) << " " << v.get(1, 0, dydis-1, 3) << endl;
/*


X       X      X X   X    X    X
A              ^          B
 
-(X-A)*D - (B-X)*(D+U) + pref[B] - pref[A] + curVal[A]
DA - BD - BU + UX + pref[B] - pref[A] + curVal[A]
UX + [DA - pref[A] + curVal[A]] + [pref[B]-B(D+U)]



X       X      X X   X    X    X
B                ^        A
 
-(A-X)*U - (X-B)*(D+U) + pref[A-1] - pref[B] + curVal[A]
-AU - XD + BD + BU + pref[A-1] - pref[B] + curVal[A]
-XD + [curVal[A] + pref[A-1] - AU] + [B(D+U)-pref[B]]
 
 
*/
 
}
 
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	for(int i = 0; i < dydis; i++) curAns[i] = -inf;
	cin >> n >> U >> D >> s;
	
	updateCur(s, 0);
	for(int i = 0; i < n; i++){
		int t, l, p; cin >> t >> l >> p;
		fairs[t].push_back({l, p});
	}
	for(int i = 0; i < dydis; i++){
		sort(fairs[i].begin(), fairs[i].end());
	}
	for(int i = 0; i < dydis; i++){
		if(fairs[i].size() == 0) continue;
 
//        cout << i << " diena: \n";
		upd1(i);
//        cout << "po paprasto: ";
//		for(int i = 0; i <= 5; i++) cout << (curAns[i] == -inf ? -69 : curAns[i]) << " ";
//        cout << endl;
		upd2(i);
//        cout << "po antrojo: "; for(int i = 0; i <= 5; i++) cout << (curAns[i] == -inf ? -69 : curAns[i]) << " ";
//        cout << endl;
//        cout << endl;
 
	}
	long long ans = 0;
	for(int i = 0; i < dydis; i++){
		ans = max(ans, curAns[i] - 1ll * (i < s ? D : U) * abs(s-i));
	}
	cout << ans;
	return 0;
}
