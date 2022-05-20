#include <bits/stdc++.h>
using namespace std;
const int dd = 1e3 + 10;
struct seg_tree{
	int l[dd];
	int r[dd];
	long long val[dd];
	
	long long lazy[dd];
	int n;
	int dbInd = 0;
	void build(int v = 1){
		//cout << "v = " << v << endl;
		if(v >= n){
			l[v] = r[v] = dbInd++;
			lazy[v] = 0;
			val[v] = 0;
		}else{
			build(v*2); build(v*2+1);
			l[v] = l[v*2];
			r[v] = r[v*2+1];
			lazy[v] = 0;
			val[v] = 0;
		}
	}
	seg_tree(){
		n = dd / 2;
		build();
	}
	void apply(int v){
		if(lazy[v] == 0) return ;
		//cout << "lazy [" << l[v] << "; " << r[v] << "] = " << lazy[v] << endl;
		val[v] += lazy[v];
		if(v < n) lazy[v*2] += lazy[v], lazy[v*2+1] += lazy[v];
		lazy[v] = 0;
	}
	long long getMax(int v, int L, int R){
		apply(v);
		if(L <= l[v] && r[v] <= R){
			return val[v];
		}else if(r[v] < L || R < l[v]){
			return 0;
		}else{
			return max(getMax(v*2, L, R), getMax(v*2+1, L, R));
		}
	}
	void change(int v, int L, int R, int x){
		apply(v);
		if(L <= l[v] && r[v] <= R){
			lazy[v] += x;
			apply(v);
		}else if(r[v] < L || R < l[v]){
			return ;
		}else{
			change(v*2, L, R, x); change(v*2 + 1, L, R, x);
			
			val[v] = max(val[v*2], val[v*2+1]);
		}
		//cout << "pachanginnau [" << l[v] << "; " << r[v] << "], tai as = " << val[v] << endl;
		
	}
	
};
int hsh(string a){
	if(a == "Amelia") return 0;
	if(a == "Calliope") return 1;
	if(a == "Gura") return 2;
	if(a == "Ina") return 3;
	if(a == "Kiara") return 4;
	return -1;
}
vector<int> mas;
int getReal(int a){
	
	return lower_bound(mas.begin(), mas.end(), a) - mas.begin();
}
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	seg_tree medziai[5];
	vector<pair<int, pair<int, int> > > vec; 
	int q; cin >> q;
	while(q--){
		string a; int b, c; cin >> a >> b >> c;
		int d = hsh(a);
		vec.push_back({d, {b, c}});
		mas.push_back(c);
	}
	sort(mas.begin(), mas.end());
	for(auto x : vec){
		int kas = x.first;
		int kada = getReal(x.second.second);
		int kiek = x.second.first;
		if(kas == 0){
			for(int i = 0; i < 5; i++){
				//cout << i << "-ajame pridedu [" << kada << "; " << dd-1 << "], -" << kiek << endl; 
				medziai[i].change(1, kada, dd-1, -kiek);
			}
		}else{
			//cout << "pridedu " <<x.first << "-e, [" << kada << "; " << dd-1 << "], " << kiek << endl;
			medziai[x.first].change(1, kada, dd-1, kiek);
		}
		long long ret = 0;
		for(int i = 0; i < 5; i++){
			//cout << "ieskosiu " << i << " maxo, kuris yra " <<  medziai[i].getMax(1, 0, dd-1) << endl;
			ret = max(ret, medziai[i].getMax(1, 0, dd-1));
		}
		cout << ret << "\n";
	}
}
