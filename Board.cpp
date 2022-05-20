#include <bits/stdc++.h>
using namespace std;
struct medis1 {
	const int inf = 1e9;
	vector<int> l, r, val, lazy;
	int n;
	int dbInd=  0;
	void build(int v = 1){
		if(v >= n) {
			l[v] =r[v] = dbInd++;
		}else {
			build(v*2);
			build(v*2+1);
			l[v] = l[v*2];
			r[v] = r[v*2+1];
		}
	}
	medis1(int dd) {
		n = dd;
		l.resize(2*n);
		r.resize(2*n);
		val.resize(2*n);
		lazy.resize(2*n);
		build();
	}
	void apply(int v) {
		if(v >= 2*n) return ;
		if(lazy[v] == -1) return;
		val[v] = (r[v] - l[v] + 1) * lazy[v];
		if(v < n) {
			lazy[v*2] = lazy[v];
			lazy[v*2+1] = lazy[v];
		}
		lazy[v] = -1;
	}
	void change(int v, int L, int R, int x) {
		apply(v);
		if(L <= l[v] && r[v] <= R) {
			lazy[v] = x;
			apply(v);
		}else if(L > r[v] || l[v] > R) {
			return ;
		}else {
			change(v*2, L, R, x);
			change(v*2+1, L, R, x);
			val[v] = val[v*2] + val[v*2+1];
		}
	}
	int getSum(int v, int L, int R) {
		apply(v);
		if(L <= l[v] && r[v] <= R) {
			return val[v];
		}else if(L > r[v] || l[v] > R) {
			return 0;
		}else {
			return getSum(v*2, L, R) + getSum(v*2+1, L, R);
		}
	}
	int getLeftmost0(int v, int L, int R){
		apply(v);
		apply(v*2);
		apply(v*2+1);
		if(L <= l[v] && r[v] <= R) {
			if(l[v] == r[v]) {
				if(val[v] == 0) return l[v];
				else return inf;
			}
			if(val[v*2+1] == 0) {
				return min(l[v*2+1], getLeftmost0(v*2, L, R));
			}else {
				return getLeftmost0(v*2+1, L, R);
			}
		}else if(L > r[v] || l[v] > R) {
			return inf;
		}else {
			
			int dsn = getLeftmost0(v*2+1, L, R);
			if(l[v*2+1] > R) {
				return getLeftmost0(v*2, L, R);
			}else {
				if(dsn == l[v*2+1]) {
					return min(l[v*2+1], getLeftmost0(v*2, L, R));
				}else {
					return dsn;
				}
			}
		}
	}
	int getLeftmost1(int v, int L, int R){
		apply(v);
		apply(v*2);
		apply(v*2+1);
		if(L <= l[v] && r[v] <= R) {
			if(l[v] == r[v]) {
				if(val[v] == 1) return l[v];
				else return inf;
			}
			if(val[v*2+1] == r[v*2+1]-l[v*2+1]+1) {
				return min(l[v*2+1], getLeftmost1(v*2, L, R));
			}else {
				return getLeftmost1(v*2+1, L, R);
			}
		}else if(L > r[v] || l[v] > R) {
			return inf;
		}else {
			
			int dsn = getLeftmost1(v*2+1, L, R);
			if(l[v*2+1] > R) {
				return getLeftmost1(v*2, L, R);
			}else {
				if(dsn == l[v*2+1]) {
					return min(l[v*2+1], getLeftmost1(v*2, L, R));
				}else {
					return dsn;
				}
			}
		}
	}
};
struct bigNum{
	deque<bool> mas = {1};	
	string st(){
		string ret = "";
		for(bool x : mas) {
			ret.push_back('0' + x);
		}
		return ret;
	}
	
	void dg2(){
		mas.push_back(0);
	}
	void dl2() {
		mas.pop_back();
		if(mas.size() == 0) mas.push_back(0);
	}
	void add1() {
		int carry = 1;
		for(int i = mas.size()-1; i > -1; i--) {
			if(carry == 0) break;
			if(mas[i] == 0) {
				mas[i] = 1;
				carry = 0;
			}else {
				mas[i] = 0;
				carry = 1;
			}
			if(carry == 0) break;
		}
		if(carry == 1) {
			mas.push_front(1);
		}
		
	}
	void sub1(){	// bitu kiekis po sios operacijos nepakis!
		int carry = 1;
		for(int i = mas.size()-1; i > -1; i--) {
			if(carry == 0) break;
			if(mas[i] == 0) {
				mas[i] = 1;
				carry = 1;
			}else {
				mas[i] = 0;
				carry = 0;
			}
		}
		if(mas[0] == 0) mas.pop_front();
	}
	long long toInt() {
		long long ret = 0;
		for(int i = 0; i < (int) mas.size(); i++) {
			if(mas[i]) ret += (1ll << ((int)mas.size()-i-1));
		}
		return ret;
	}
	const bool operator < (bigNum rhs) const {
		// ar as mazesnis uz rhs?
		if(mas.size() < rhs.mas.size()) return true;
		if(mas.size() > rhs.mas.size()) return false;
		for(int i = 0; i < (int) mas.size(); i++) {
			if(mas[i] == rhs.mas[i]) continue;
			if(mas[i] < rhs.mas[i]) return true;
			return false;
		}
		return false;
	}
	
};
 
bigNum diff(bigNum a, bigNum b) {
	if(b < a) swap(a, b);
	// nuo dabar a < b.
	while(a.mas.size() != b.mas.size()) {
		a.mas.push_front(0);
	}
	// skaiciuosiu b - a
	int carry = 0;
	for(int i = (int) a.mas.size() - 1; i > -1; i--) {
		if(carry + (int) a.mas[i] > (int) b.mas[i]) {
			b.mas[i] = ((carry + a.mas[i]) - ((int) b.mas[i])) % 2;
			carry = 1;
		}else {
			int bus = ((int) b.mas[i]) - ((int) a.mas[i] + carry);
			b.mas[i] = bus;
			carry = 0;
		}
	}
	while(b.mas.size() && b.mas.front() == 0) b.mas.pop_front();
	if(b.mas.size() == 0) b.mas.push_back(0);
	return b;
}
bigNum sum(bigNum a, bigNum b) {
	if(b < a) swap(a, b);
	// nuo dabar a < b.
	while(a.mas.size() != b.mas.size()) {
		a.mas.push_front(0);
	}
	int carry = 0;
	for(int i = (int) a.mas.size() - 1; i > -1; i--) {
		if((int)carry + ((int) a.mas[i]) + ((int)b.mas[i]) > 1) {
			b.mas[i] = ((carry + ((int)a.mas[i])) + ((int) b.mas[i])) % 2;
			carry = 1;
		}else {
			int bus = ((int) b.mas[i]) + ((int) a.mas[i]) + carry;
			b.mas[i] = bus;
			carry = 0;
		}
	}
	if(carry) b.mas.push_front(1);
	return b;
}
 
string a, b;
bigNum pos (string a) {
	bigNum cur;
	medis1 medis (100001);
	int sz = 1;
	medis.change(1, 0, 0, 1);
	for(auto &x : a) {
		if(x == '1') {
			medis.change(1, sz, sz, 0);
			sz++;
		}
		if(x == '2') {
			medis.change(1, sz, sz, 1);
			sz++;	
		}
		if(x == 'L') {
			if(medis.getSum(1, sz-1, sz-1) == 1) {
				medis.change(1, sz-1, sz-1, 0);
			}else {
				
				int kair = medis.getLeftmost0(1, 0, sz-1);
				// [kair; sz-1] visi 0-iai
				medis.change(1, kair, sz-1, 1);
				medis.change(1, kair-1, kair-1, 0);
			}
		}
		if(x == 'R') {
			if(medis.getSum(1, sz-1, sz-1) == 0) {
				medis.change(1, sz-1, sz-1, 1);
			}else {
				int kair = medis.getLeftmost1(1, 0, sz-1);
				medis.change(1, kair, sz-1, 0);
				medis.change(1, kair-1, kair-1, 1);
			}
		}
		if(x == 'U') {
			sz--;
		}
	}
	deque<bool> ret;
	for(int i = 0; i < sz; i++) {
		ret.push_back(medis.getSum(1, i, i));
	}
	bigNum rt;
	rt.mas = ret;
	return rt;
}
 
int main () {
 
	//bigNum A, B;
	//for(int i = 1; i < 11; i++) A.add1();
	//for(int i = 1; i < 11; i++) B.add1();
	//cout << "ar " << A.toInt() << " < " << B.toInt() << "? " << (A < B) << endl;
	
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> a >> b;
	auto p1 = pos(a);
	auto p2 = pos(b);
	
	if(p2.mas.size() > p1.mas.size()) {
		swap(p1, p2);
	}
	// nuo dabar p2 yra auksciau uz p1
	bigNum ans;
	for(int i = 0; i < 10000; i++) ans.dg2();
	
	long long auk = (int)p1.mas.size() - (int)p2.mas.size();
	
	while(p1.mas.size() != p2.mas.size()) {
		p1.dl2();
	}
	
	if(p2 < p1) {
		swap(p1, p2);
	}
	auto df = diff(p1, p2);
	
	bigNum aukk; aukk.sub1();
	for(int i = 0; i < auk; i++) aukk.add1();
	auto dif = diff(p1, p2);
	while(true) {
		
		//cout << "p1 = " << p1.toInt() << ", p2 = " << p2.toInt() << ", dif =" << df.toInt() << ", o aukk = " << aukk.toInt() << endl;
		if(dif.mas.size() < 19){
			df = diff(p1, p2);
			bigNum sitas;
			sitas = diff(p1, p2);
			sitas = sum(aukk, sitas);
			ans = min(ans, sitas);
			
			if(df.mas.size() == 1 && df.toInt() == 0) break;
			
		}
		p1.dl2();
		p2.dl2();	
		dif.dl2();
		aukk.add1();
		aukk.add1();
 
	}
	cout << ans.toInt();
	return 0;
}
/*
221LU
12L2
 
111111111111111111111111111111
222222222222222222222222222222
 
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
*/
