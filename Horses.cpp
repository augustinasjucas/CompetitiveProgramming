#include <bits/stdc++.h>
//#include "horses.h"
//#pragma GCC optimize("O2")
//#pragma GCC target("avx2")
 
using namespace std;
const long long mod = 1e9 + 7;
struct medis{
	struct node{
		int l, r;
		int sand = 1;
		int vntCnt = 0;
		int maxY = 0;
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
	medis(int dd){
		n = dd;
		tree.resize(2*n+1);
		build(1);
	}
	void changeX(int v, int l, int r, int x){
		if(l <= tree[v].l && tree[v].r <= r){
			tree[v].sand = x;
			tree[v].vntCnt = (x != 1);
		}else if(r < tree[v].l || tree[v].r < l){
			return;
		}else{
			changeX(v*2, l, r, x);
			changeX(v*2+1, l, r, x);
			tree[v].sand = 1ll * tree[v*2].sand * tree[v*2+1].sand % mod;
			tree[v].vntCnt = tree[v*2].vntCnt + tree[v*2+1].vntCnt;
		}
	}
	void changeY(int v, int l, int r, int x){
		if(l <= tree[v].l && tree[v].r <= r){
			tree[v].maxY = x;
		}else if(r < tree[v].l || tree[v].r < l){
			return;
		}else{
			changeY(v*2, l, r, x);
			changeY(v*2+1, l, r, x);
			tree[v].maxY = max(tree[v*2].maxY, tree[v*2+1].maxY);
		}
	}
	int getSand(int v, int l, int r){
		if(l <= tree[v].l && tree[v].r <= r){
			return tree[v].sand;
		}else if(r < tree[v].l || tree[v].r < l){
			return 1;
		}else{
			return 1ll * getSand(v*2, l, r) * getSand(v*2+1, l, r) % mod;
		}
	}
	long long getMax(int v, int l, int r){
		if(l <= tree[v].l && tree[v].r <= r){
			return tree[v].maxY;
		}else if(r < tree[v].l || tree[v].r < l){
			return 1;
		}else{
			return max(getMax(v*2, l, r), getMax(v*2+1, l, r));
		}
	}
	int get1(int v, int l, int r){
		if(l <= tree[v].l && tree[v].r <= r){
			return tree[v].vntCnt;
		}else if(r < tree[v].l || tree[v].r < l){
			return 0;
		}else{
			return get1(v*2, l, r) + get1(v*2+1, l, r);
		}
	}
	int fd(int v, int sm){ // rasti kairiausia x, kad suf[x; n] <= sm
		if(tree[v].l == tree[v].r){
			if(tree[v].vntCnt == 1 && sm == 0) return tree[v].l + 1;
			return tree[v].l;
		}
		if(tree[v*2+1].vntCnt < sm){
			return fd(v*2, sm-tree[v*2+1].vntCnt);
		}else if(tree[v*2+1].vntCnt == sm){
			return fd(v*2, sm-tree[v*2+1].vntCnt);
		}else{
			return fd(v*2+1, sm);
		}
		
	}
};
const int dydis = 5e5 + 1;
medis tree(dydis);
int n;
int rt, tr,st;
pair<int, vector<pair<int, int> > > last30(int n){
	int lastNotIn = n-1;
	vector<pair<int, int> > ret;
	int kk = 0;
	for(int i = 0; i < 32; i++){
		if(lastNotIn == -1) break;
		if(tree.getSand(1, lastNotIn, lastNotIn) == 1){
			tr = tree.get1(1, lastNotIn, dydis-1); 
			rt = tree.fd(1, tr); rt = max(rt-1, 0);
			st = tree.getSand(1, rt, rt);
			ret.push_back({st, tree.getMax(1, rt, lastNotIn)});
			lastNotIn = rt-1;
			kk++;
		}else{
			st = tree.getSand(1, lastNotIn, lastNotIn);
			ret.push_back({st, tree.getMax(1, lastNotIn, lastNotIn)});
			lastNotIn--;
			kk++;
		}
		if(kk > 30) break;
	}
	reverse(ret.begin(), ret.end());
	long long bv = 1;
	if(lastNotIn != -1) bv = tree.getSand(1, 0, lastNotIn);
	return {bv, ret};
}
 
long long h;
int curMax;
long long B;
bool did;
long long turiButi, ret;
long long get(){
	auto rk = last30(n);
	h = rk.first;
	auto mas = rk.second;
	curMax = 0;
	//for(auto x : mas) cout << x.first << "-" << x.second << "  "; cout << endl;
	for(int i = 0; i < (int)mas.size(); i++){
		B = 1;
		did = 0;
		for(int j = i+1; j < (int) mas.size(); j++){
			B *= mas[j].first;
			if(mas[j].second >= mas[i].second){
				curMax = j;
				did = 1;
				i = j-1; break;
			}
			turiButi = mas[i].second / mas[j].second + 1;
			if(B >= turiButi){
				i = j-1;
				did = 1;
				curMax = j;
				break;
			}
		}
		if(!did) break;
 
	}
	ret = h;
	for(int i = 0; i <= curMax; i++){
		ret = ret * mas[i].first % mod;
	}
	ret = ret * mas[curMax].second % mod;
	return ret;
}
 
 
int init(int N, int X[], int Y[]) {
	n = N;
	for(int i = 0; i < n; i++){
		tree.changeX(1, i, i, X[i]);
		tree.changeY(1, i, i, Y[i]);
	}
	
	return get();
}
 
int updateX(int pos, int val) {	
	tree.changeX(1, pos, pos, val);
	return get();
}
 
int updateY(int pos, int val) {
	tree.changeY(1, pos, pos, val);
	return get();
}



































//#include "horses.h"
#include <stdio.h>
#include <stdlib.h>

static char _buffer[1024];
static int _currentChar = 0;
static int _charsNumber = 0;
static FILE *_inputFile, *_outputFile;

static inline int _read() {
    if (_charsNumber < 0) {
        exit(1);
    }
    if (!_charsNumber || _currentChar == _charsNumber) {
        _charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), _inputFile);
        _currentChar = 0;
    }
    if (_charsNumber <= 0) {
        return -1;
    }
    return _buffer[_currentChar++];
}

static inline int _readInt() {
    int c, x, s;
    c = _read();
    while (c <= 32) c = _read();
    x = 0;
    s = 1;
    if (c == '-') {
        s = -1;
        c = _read();
    }
    while (c > 32) {
        x *= 10;
        x += c - '0';
        c = _read();
    }
    if (s < 0) x = -x;
    return x;
}


int main() {
	//_inputFile = fopen("horses.in", "rb");
	//_outputFile = fopen("horses.out", "w");
	
	int N; cin >> N;

	int *X = (int*)malloc(sizeof(int)*(unsigned int)N);
	int *Y = (int*)malloc(sizeof(int)*(unsigned int)N);

	for (int i = 0; i < N; i++) {
		cin >> X[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> Y[i];
	}	

	cout << init(N, X, Y) << endl;
	int M; cin >> M;

	for (int i = 0; i < M; i++) {
		int type; 
		int pos; 
		int val;
		cin >> type >> pos >> val;

		if (type == 1) {
			cout << updateX(pos, val) << endl;
		} else if (type == 2) {
			cout << updateY(pos, val);
		}
	}

	return 0;
}
/*
3
2 1 3
3 2 1
*/
