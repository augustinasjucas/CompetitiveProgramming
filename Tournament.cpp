#include <bits/stdc++.h>
using namespace std;
struct treap{
	const int dydis = 1e5 * 3;
	struct node{
		int l = -1, r = -1;
		int w, val1, val2;
		int sz = 1;
		int leftmost = 1e9;
		int rightmost = 1e9;
	};
	vector<node> tree;
	int dbInd = 0;
	int root = -1;
	int newN(int x, int y){
		tree[dbInd].val1 = tree[dbInd].leftmost = x; tree[dbInd].val2 = tree[dbInd].rightmost = y;
		tree[dbInd].w = rand();
		return dbInd++;
	}
	void update(int v){
		tree[v].sz = 1;
		tree[v].leftmost = tree[v].val1;
		tree[v].rightmost = tree[v].val2;

		if(tree[v].l != -1){
			tree[v].sz += tree[tree[v].l].sz;
			tree[v].leftmost = tree[tree[v].l].leftmost;
		}
		if(tree[v].r != -1) {
			tree[v].sz += tree[tree[v].r].sz;
			tree[v].rightmost = tree[tree[v].r].rightmost;
		}
	}
	int merge(int l, int r){
		if(l == -1) return r;
		if(r == -1) return l;
		if(tree[l].w > tree[r].w){
			int bs = merge(tree[l].r, r);
			tree[l].r = bs;
			update(l);
			return l;
		}else{
			int bs = merge(l, tree[r].l);
			tree[r].l = bs;
			update(r);
			return r;
		}
	}
	pair<int, int> split(int v, int x){
		if(v == -1) return {-1, -1};
		int lsz = 0;
		if(tree[v].l != -1) lsz = tree[tree[v].l].sz;
		//cout << "split nuo " << v << ". jo val1 = " << tree[v].val1 << ", o lsz = " << lsz << endl;
		if(lsz <= x){ // as kairej
			auto bus = split(tree[v].r, x-lsz-1);
			tree[v].r = bus.first;
			update(v);
			return {v, bus.second};
		}else{
			auto bus = split(tree[v].l, x);
			tree[v].l = bus.second;
			update(v);
			return {bus.first, v};
		}
	}
	void print(int v = -2){
		if(v == -2) v = root;
		if(v == -1) return;
		print(tree[v].l);
		cout <<v << ": " << tree[v].val1 << "; " << tree[v].val2 << ", leftmost: " << tree[v].leftmost << ", raitmost: " << tree[v].rightmost << " | l = " << tree[v].l << ", r = " << tree[v].r << endl;
		print(tree[v].r);
	}
	treap(){
		tree.resize(dydis);
	}
};
const int dydis = 1e5 + 10;
vector<int> fins[dydis + 1];
struct seg_tree{
	struct node{
		int l, r;
		vector<int> val;
	};
	int dbInd = 0;
	int n;
	vector <node> tree;
	void build(int v){
		if(v >= n){
			tree[v].l = tree[v].r = dbInd;
			tree[v].val = fins[dbInd];
			dbInd++;
		}else{

			build(v*2);
			build(v*2+1);
			tree[v].l = tree[v*2].l;
			tree[v].r = tree[v*2+1].r;
			for(auto x : tree[v*2].val) tree[v].val.push_back(x);
			for(auto x : tree[v*2+1].val) tree[v].val.push_back(x);
			
		}
		sort(tree[v].val.begin(), tree[v].val.end());
		//if(tree[v].val.size()) {cout << "fins[" << tree[v].l << "; " << tree[v].r << "]: "; for(auto x : tree[v].val) cout << x<< " "; cout << endl;}
	}	
	seg_tree(int dd){
		n = dd;
		tree.resize(2 * n + 1);
		build(1);
	}
	int getVal(int v, int l, int r, int l1, int r1){
		if(l <= tree[v].l && tree[v].r <= r){
			//cout << endl;
			//for(auto x : tree[v].val) cout << x  << " "; cout << "   "; 
			//cout <<l1 << " ir " << r1 <<  " pridedu [" << tree[v].l << "; " << tree[v].r << "] = " << ((int)(upper_bound(tree[v].val.begin(), tree[v].val.end(), r1) - lower_bound(tree[v].val.begin(), tree[v].val.end(), l1))) << endl;
			return upper_bound(tree[v].val.begin(), tree[v].val.end(), r1) - lower_bound(tree[v].val.begin(), tree[v].val.end(), l1);
		}else if(r < tree[v].l || tree[v].r < l){
			return 0;
		}else{
			return getVal(v*2, l, r, l1, r1) + getVal(v*2+1, l, r, l1, r1);
		}
	}
};
int n, m, as;
vector<pair<int, int> > vec, rl;
vector<int> mas;
int tevas[dydis];
int le[dydis], ri[dydis];
treap medis;
int l, r, a1, a2, a3, nj;
pair<int, int> prm, ant;
int GetBestPosition(int N, int C, int RR, int *K, int *S, int *E) {
	n = N; m = C; as = RR;
	for(int i = 0; i < n; i++) tevas[i] = le[i] = ri[i];
	for(int i = 0; i < m; i++) vec.push_back({S[i], E[i]});
	for(int i = 0; i < n-1; i++) mas.push_back(K[i]);
	for(int i = 0; i < n; i++) medis.root = medis.merge(medis.root, medis.newN(i, i));
	//medis.print();
	//cout << endl;
	for(auto x : vec){
		l = x.first;
		r = x.second;
		
		//cout << "medis dabar: \n"; medis.print();
		//cout << "\nimsiu " << l << "; " << r  << ", t.y. pirma splitinsiu " << l-1 << endl; 
		//cout << endl;
		prm = medis.split(medis.root, l-1);
		ant = medis.split(prm.second, r-l);
		a1 = prm.first;
		a2 = ant.first;
		a3 = ant.second;
		//cout << "isskaidau taip: \n";
		//cout << "a1:\n";medis.print(a1); cout << endl << "a2:\n"; medis.print(a2); cout << endl << "a3:\n"; medis.print(a3); cout << endl;
		nj = medis.newN(medis.tree[a2].leftmost, medis.tree[a2].rightmost);
		rl.push_back({medis.tree[a2].leftmost, medis.tree[a2].rightmost});
		//cout << ", tai pridesiu " << medis.tree[a2].leftmost << " - " << medis.tree[a2].rightmost << endl;
		//cout << endl;
		medis.root = medis.merge(medis.merge(a1, nj), a3);
		// man reik a3;
	}
	for(auto x : rl){
		//cout << "[" << x.first << "; " << x.second << "]\n";
		fins[x.first].push_back(x.second);
	}
	for(int i = 0; i <= n; i++){
			//cout <<i << ": "; for(auto x : fins[i]) cout << x << " "; cout << endl;
	}
	seg_tree medis(dydis);
	mas.push_back(as);
	
	int L = -1, R = n;
	for(int i = mas.size()-1; i > -1; i--) if(mas[i] > mas.back()) L = max(L, i);
	pair<int, int> ans = {-1, -1};
	for(int i = mas.size()-1; i > -1; i--){
		if(i != (int)mas.size()-1) swap(mas[i+1], mas[i]);
		if(L == i){
			while(L != -1 && mas[L] <= mas[i]) L--;
		}
		if(i != (int)mas.size()-1 && mas[i+1] > mas[i]) R = i+1;
		//cout << "intervale [" << L+1 << "; " << i << "] - [" << i << "; " << R-1 << "], yra " << medis.getVal(1, L+1, i, i, R-1) << endl;
		//cout << "i = " << i << ", L = " << L << ", R = " << R << endl;
		ans = max(ans, make_pair(medis.getVal(1, L+1, i, i, R-1), -i));
	}
//	cout << ans.first  << " yra ats" << endl;
	return -ans.second;
}





#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define inbuf_len 1 << 16
#define outbuf_len 1 << 16

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E);

int main() {
  int tmp;

  /* Set input and output buffering */
  char *inbuf, *outbuf;
  inbuf = (char*) malloc(inbuf_len * sizeof(char));
  outbuf = (char*) malloc(outbuf_len * sizeof(char));
  tmp = setvbuf(stdin, inbuf, _IOFBF, inbuf_len);
  assert(tmp == 0);
  tmp = setvbuf(stdout, outbuf, _IOFBF, outbuf_len);
  assert(tmp == 0);

  int N, C, R;
  int *K, *S, *E;
  tmp = scanf("%d %d %d", &N, &C, &R);
  assert(tmp == 3);
  K = (int*) malloc((N-1) * sizeof(int));
  S = (int*) malloc(C * sizeof(int));
  E = (int*) malloc(C * sizeof(int));
  int i;
  for (i = 0; i < N-1; i++) {
    tmp = scanf("%d", &K[i]);
    assert(tmp == 1);
  }
  for (i = 0; i < C; i++) {
    tmp = scanf("%d %d", &S[i], &E[i]);
    assert(tmp == 2);
  }

  printf("%d\n", GetBestPosition(N, C, R, K, S, E));

  return 0;

}
/*
10 5 5
0 1 2 3 4 6 7 8 9
0 1
0 5
1 2
0 1
0 1
*/
