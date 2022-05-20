#include <bits/stdc++.h>
using namespace std;
vector<int> x, r;
int n;
vector<pair<long double, long double> > yra; 
long double inf = 1e18;
struct parab {
	long double A, B, C;
	void setVal (long double a, long double b, long double c) {
		A = a; B = b; C = c;
	}
	
	long double ev(long double x) {
		return A * x * x + B * x + C;
	}
	void print() {
		cout << "(" << setprecision(2) << A << "x^2 + " <<  setprecision(2) << B << "x + " << setprecision(2) << C << ")";
	}
};

parab getParab(long double x, long double r){
	parab ret;
	//long double a = 1.0 / (4.0 * r);
	//long double b = -0.5 * x / r;
	//long double c = x*x / 4.0 / r;
	long double a = 0;
	long double b = 1 / sqrtl(((long double)4.0)*r);
	long double c = -x / sqrtl(((long double)4.0)*r);
	ret.setVal(a, b, c);
	return ret;
}
const int dydis = 2e5 + 10;
vector<int> all[dydis * 2];
int dbInd = 0;
int le[dydis];
int ri[dydis];
parab val[dydis];
int midInd[dydis] = {};
void build(int v = 1) {
	if(v >= n) {
		all[v] = {x[dbInd++]};
		le[v] = ri[v] = all[v][0];
	}else {
		build(v*2);
		build(v*2+1);
		le[v] = le[v*2];
		ri[v] = ri[v*2+1];
		midInd[v] = all[v*2].size()-1;
		for(auto &x : all[v*2]) all[v].push_back(x);
		for(auto &x : all[v*2+1]) all[v].push_back(x);
	}
	val[v].setVal(0, 0, inf);
	//cout << "virsune [" << le[v] << "; " << ri[v] << "]: "; for(auto x : all[v]) cout << x << " "; cout << endl;
}
void add(int v, parab x){
	int mid = all[v][midInd[v]];
	int L = all[v][0];
	int R = all[v].back();
	if(x.ev(mid) < val[v].ev(mid)) {
		swap(x, val[v]);
		//cout << "nustatau [" << le[v] << "; " << ri[v] << "] reiksme i "; val[v].print(); cout << "\n";
	}
	if(le[v] == ri[v]) return ;
	if(x.ev(L) < val[v].ev(L)) {
		add(v*2, x);
	}else if(x.ev(R) < val[v].ev(R)) {
		add(v*2+1, x);
	}
}
long double getVal(int v, int x) {
	long double ret = val[v].ev(x);
	int mid =  all[v][midInd[v]];
	//cout << "ieskodamas min f(" << x << "), atsizvelgiu i [" << le[v] << "; " << ri[v] << "] = f(" << x << ") = " << ret << endl;
	if(le[v] == ri[v]) return ret;
	if(x <= mid) {
		return min(ret, getVal(v*2, x));
	}else {
		return min(ret, getVal(v*2+1, x));
	}
}
vector<long double> ans;
vector<parab> dumb;
void idek(long double x, long double r) {
	ans.push_back(r);
	add(1, getParab(x, r));
	dumb.push_back(getParab(x, r));
}
long double getDumb(long double X) {
	long double ret = inf;
	for(auto &x : dumb) {
		ret = min(ret, x.ev(X));
	}
	return ret;
}
void pridek(int ind) {
	long double X = x[ind];
	long double maxR = r[ind];
	
	long double mvl = getVal(1, X);
	mvl *= mvl;
	long double R = min(maxR, getDumb(X)*getDumb(X));
	//cout << "X = " << X << ", tai minval = " << mvl << ", vs " <<  << endl;
	idek(X, R);
	
}
int main () {
	cin >> n;
	for(int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		x.push_back(a);
		r.push_back(b);
	}
	build(1);
	
	idek(x[0], r[0]);
	for(int i = 1; i < n; i++) {
		pridek(i);
	}
	for(auto &x : ans) {
		cout << fixed << setprecision(3) << x << "\n";
	}
	return 0;
}

/*
10
0 9
8 1
13 7
16 100
17 100
20 3
50 40
100 100
101 10
110
*/
