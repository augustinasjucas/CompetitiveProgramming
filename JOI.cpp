#include <bits/stdc++.h>
using namespace std;
const int kek = 3;
const int dydis = 2e5 + 10;
long long mod[kek] = {1000000007, 1000000009, 97657711};
long long vienetai[kek][dydis];
long long pw3[kek][dydis];
long long pw(long long x, long long y, long long mod){
	if(y == 0) return 1;
	long long sk = pw(x, y/2, mod);
	sk = sk * sk % mod;
	if(y & 1) sk = sk * x % mod;
	return sk;
}
long long inv(long long x, long long mod){
	return pw(x, mod-2, mod);
}
struct seg_tree{
	struct node {
		int l, r;
		long long val[kek] = {};
		int lazy = -1;
	};
	
	int n;
	int dbInd = 0;
	vector<node> tree;
	void build(int v){
		if(v >= n){
			tree[v].l = tree[v].r = dbInd++;
		}else{
			build(v*2); build(v*2+1);
			tree[v].l = tree[v*2].l;
			tree[v].r = tree[v*2+1].r;
		}
	}
	seg_tree(int dd){
		n = dd;
		tree.resize(dd * 2 + 1);
		build(1);
	}
	void apply(int v){
		if(tree[v].lazy == -1) return;
		for(int i = 0; i < kek; i++){
			tree[v].val[i] = vienetai[i][tree[v].r - tree[v].l + 1] * tree[v].lazy;
		}
		if(v < n) tree[v*2+1].lazy = tree[v*2].lazy = tree[v].lazy;
		tree[v].lazy = -1;
	}
	void change(int v, int l, int r, int x){
		apply(v);
		if(l <= tree[v].l && tree[v].r <= r){
			//cout << "nustatau " << tree[v].l << ";" << tree[v].r << " i " << x << endl;
			tree[v].lazy = x;
			apply(v);
			//cout << "cia reiksme tampa " << tree[v].val[0] << endl;
		}else if(r < tree[v].l || tree[v].r < l){
			return;
		}else{
			change(v*2, l, r, x);
			change(v*2+1, l, r, x);
			for(int i = 0; i < kek; i++){
				tree[v].val[i] = (tree[v*2].val[i] * pw3[i][tree[v*2+1].r-tree[v*2+1].l+1] % mod[i] + tree[v*2+1].val[i]) % mod[i];
			}
		}
		//cout << "[" << tree[v].l << "; " << tree[v].r << "] reiksme yra " << tree[v].val[0] << endl;
		
	}
	
};
char kt(char a, char b){
	if(a > b) swap(a, b);
	if(a == 'J' && b == 'O') return 'I';
	if(a == 'I' && b == 'J') return 'O';
	return 'J';
}
string naujas(string &a, string &b){
	string ret = "";
	for(int i = 0; i < (int)a.size(); i++){
		if(a[i] == b[i])ret.push_back(a[i]);
		else ret.push_back(kt(a[i], b[i]));
	}
	return ret;
}

int ind(char a){
	if(a == 'J') return 0;
	if(a == 'O') return 1;
	return 2;
}

long long hsh(string a, int i){
	long long ret = 0;
	for(auto x : a){
		ret = (ret * 3ll % mod[i] + ind(x)) % mod[i];
	}
	return ret;
}
vector<long long> hashai[kek];
int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	for(int i = 0; i < kek; i++){
		for(int j = 1; j < dydis; j++){
			vienetai[i][j] = (pw(3, j, mod[i]) - 1 + mod[i]) % mod[i] * inv(2, mod[i]) % mod[i];
			pw3[i][j] = pw(3, j, mod[i]);
		//	if(j < 5) cout << j << " vienetu moduliu " << mod[i] << " yra " << vienetai[i][j] << endl;
		}
	}
	int n; cin >> n;
	seg_tree medis(n);
	string a, b, c; cin >> a >> b >> c;
	set<string> vs = {a, b, c};
	for(int i = 0; i < 10; i++){
		vector<string> prd;
		for(auto x : vs){
			for(auto y: vs){
				prd.push_back(naujas(x, y));
			}
		}
		for(auto x : prd) vs.insert(x);
	}
	//cout << endl << endl;
	for(auto x : vs){
		for(int i = 0; i < kek; i++){
			hashai[i].push_back(hsh(x, i));
		}
		//cout << x << " galimas, " << hsh(x, 0) << endl;
	}
	int q; cin >> q;
	string prm; cin >> prm;
	for(int j = 0; j < n; j++){
		medis.change(1, j, j, ind(prm[j]));
	}
	/*cout << "dabar hashai: ";
	for(int i = 0; i < kek; i++){
		cout << medis.tree[1].val[i] << "  |  ";
	}
	cout << ", o turi buti: " << hsh(prm, 0) << endl;
	cout << endl;*/
	bool ans = 0;
	for(int j = 0; j < (int)hashai[0].size(); j++){
		bool sitas = 1;
		for(int i = 0; i < kek; i++){
			if(medis.tree[1].val[i] != hashai[i][j]) sitas = 0;
		}
		ans = ans | sitas;
	}
	if(ans) cout << "Yes\n";
	else cout << "No\n";
	while(q--){
		int l, r; cin >> l >> r;
		char a; cin >> a;
		medis.change(1, l-1, r-1, ind(a));
		bool ans = 0;
		
		for(int j = 0; j < (int)hashai[0].size(); j++){
			bool sitas = 1;
			for(int i = 0; i < kek; i++){
				if(medis.tree[1].val[i] != hashai[i][j]) sitas = 0;
			}
			ans = ans | sitas;
		}
		
	/*	cout << "\ndabar hashai: ";
		for(int i = 0; i < kek; i++){
			cout << medis.tree[1].val[i] << "  |  ";
		}
		cout <<"\ntai ans: ";*/
		
		if(ans) cout << "Yes\n";
		else cout << "No\n";
		
		//long long beGalo = 
	}
	return 0;
}
/*
4
JOJO
JJOI
OJOO
3
IJOJ
1 4 O
2 2 J
2 4 I



3
JOI
JOI
JOI
2
OJI
1 2 O
1 1 J
*/
