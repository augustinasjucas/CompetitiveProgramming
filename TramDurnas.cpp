
#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
int n, q;
set<pair<int, int> > is;

long long getDist(int e1, int e2, int e, int col, int yra[][2]) {
	if(e1 == e) {
		if(yra[0][col]) return -inf;
	}
	if(e2 == e) {
		if(yra[1][col]) return -inf;
	}
	long long ret = 1e18;
	if(yra[0][0]) {
		ret = min(ret, 1ll * (e-e1)*(e-e1) + abs(col-0));
	}
	if(yra[0][1]) {
		ret = min(ret, 1ll * (e-e1)*(e-e1) + abs(col-1));
	}
	if(yra[1][0]) {
		ret = min(ret, 1ll * (e-e2)*(e-e2) + abs(col-0));
	}
	if(yra[1][1]) {
		ret = min(ret, 1ll * (e-e2)*(e-e2) + abs(col-1));
	}
	return ret;
}
pair<long long, pair<int, int> > best(int e1, int e2) {
	int yra[2][2] = {{is.count({e1, 0}), is.count({e1, 1})}, {is.count({e2, 0}), is.count({e2, 1})}};
	int l = e1, r = e2, m1, m2;
	long long f1, f2;
	
	int col = 0;
	//cout << "IESKAU BEST(" << e1 << ", " << e2 << "), kai is: ";
	//for(auto x : is) cout << "(" << x.first << ", " << x.second << "), ";
	//cout << endl;
	pair<long long, pair<int, int> > ret = {-inf, {-1, -1}};
	
	while(l <= r) {
		m1 = l + (r - l) / 3;
		m2 = r - (r - l) / 3;
		
		f1 = getDist(e1, e2, m1, col, yra);
		f2 = getDist(e1, e2, m2, col, yra);
		
		//cout << "[" << l << "; " << r << "], f(" << m1 << ") = " << f1 << ", f(" << m2 << ") = " << f2 << endl;
		
		ret = max(ret, make_pair(f1, make_pair(-m1, -col)));
		ret = max(ret, make_pair(f2, make_pair(-m2, -col)));
		
		if(f1 >= f2) {
			r = m2-1;
		}else {
			l = m1+1;
		}
		
	}
	col = 1;
	l = e1, r = e2, m1, m2;
	//cout << "darau col = 1" << endl;
	while(l <= r) {
		m1 = l + (r - l) / 3;
		m2 = r - (r - l) / 3;
		
		f1 = getDist(e1, e2, m1, col, yra);
		f2 = getDist(e1, e2, m2, col, yra);
		
		//cout << "[" << l << "; " << r << "], f(" << m1 << ") = " << f1 << ", f(" << m2 << ") = " << f2 << endl;
		
		ret = max(ret, make_pair(f1, make_pair(-m1, -col)));
		ret = max(ret, make_pair(f2, make_pair(-m2, -col)));
		
		if(f1 >= f2) {
			r = m2-1;
		}else {
			l = m1+1;
		}
		
	}
	return ret;
}
bool arYraIsKaires(int e) {
	if(is.size() ==  0) return false;
	int mn = is.begin()->first;
	if(e <= mn) return false;
	return true;
}
bool arYraIsDesines(int e) {
	if(is.size() ==  0) return false;
	int mx = is.rbegin()->first;
	if(mx <= e) return false;
	return true;
}
int pirmasIsKaires(int e) {
	auto kur = is.lower_bound({e, 0});
	kur--;
	return kur->first;
}
int pirmasIsDesines(int e) {
	auto kur = is.upper_bound({e, 1});
	return kur->first;
}
set<pair<long long, pair<int, int> > > setas;
void idek(int e, int s) {
	is.insert({e, s});
}
void isimk(int e, int s) {
	is.erase({e, s});
}
pair<int, int> getMax() {
	pair<long long, pair<int, int> > ret;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 2;j++) {
			if(is.count({i, j})) continue;
			
			long long mn = 1e18;
			for(auto &x : is) {
				mn = min(mn, 1ll*(i-x.first)*(i-x.first) + 1ll * (j - x.second) * (j - x.second) );
			}
			ret = max(ret, make_pair(mn, make_pair(-i, -j)));
			
		}
	}
	return ret.second;
} 

void printState() {
	cout << "ideti: ";
	for(auto &x : is) {
		cout << "(" << x.first << ", " << x.second << ") ";
	}
	cout << endl;
	cout << "geriausios vietos: ";
	for(auto &x : setas) cout << "[" << x.first << ", (" << -x.second.first << ", " << -x.second.second << ")] ";
	cout << endl << endl;
}
pair<int, int> plac[30001];
int main () { 
	
	cin >> n >> q;
	
	for(int i = 0 ; i  < q; i++){
		char s;
		cin >> s;
		if(s == 'E') {
			if(is.size() == 0) {
				plac[i] = {0, 0};
				cout << "1 1" << endl;
				idek(0, 0);
			}else {
				auto bst = getMax();
				cout << -bst.first + 1 << " " << -bst.second+1 << endl;
				idek(-bst.first, -bst.second);
				plac[i] = {-bst.first, -bst.second};
			}
		}else {
			int ind; cin >> ind; ind--;
			isimk(plac[ind].first, plac[ind].second);
		}
	//	cout << "ivykdziau. Dabar state:\n";
	//	printState();
	}
	return 0;
}
/*
10 9
E
E
E
E
L 3
E
E
L 6
E



13 26
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
E 
E
*/
