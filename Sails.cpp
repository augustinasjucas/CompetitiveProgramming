#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct treap{
    struct node{
        int l= -1, r = -1, val;
        int sz = 0;
        long long w = 0;
        int pl = 0;
    };
    int curRoot = -1;
    vector<node> tree;
    int dbInd = 0;
    int newN(int x){
		tree[dbInd].sz = 1;
        tree[dbInd].w = rand();
        tree[dbInd].val = x;
        return dbInd++;
    }
    void upd(int v){
		if(v == -1) return ;
		tree[v].sz = 1;
		if(tree[v].l != -1){
			tree[v].sz += tree[tree[v].l].sz;
			tree[tree[v].l].pl += tree[v].pl;
		}
		if(tree[v].r != -1){
			tree[v].sz += tree[tree[v].r].sz;
			tree[tree[v].r].pl += tree[v].pl;
		}
		tree[v].val += tree[v].pl;
		tree[v].pl = 0;
    }
    int merge(int l, int r){
		upd(l);
		upd(r);
        if(l == -1) return r;
        if(r == -1) return l;
        if(tree[l].w > tree[r].w){ // l auksciau
            int R = merge(tree[l].r, r);
            tree[l].r = R;
            upd(l);
            return l;
        }else{
            int R = merge(l, tree[r].l);
            tree[r].l = R;
            upd(r);
            return r;
        }
    }
    pair<int, int> split(int v, int x){ // [0; x] bus kairej
		upd(v);
		if(v == -1) return {-1, -1};
        int lsz = 0;
        if(tree[v].l != -1){
			lsz += tree[tree[v].l].sz;
		}
		if(x >= lsz){ // as priklausau kairei
			auto sp = split(tree[v].r, x-lsz-1);
			tree[v].r = sp.first;
			upd(v);
			return {v, sp.second};
		}else{ // as desinei
			auto sp = split(tree[v].l, x);
			tree[v].l = sp.second;
			upd(v);
			return {sp.first, v};
		}
    }
    void push_back(int x){
		int st = newN(x);
		if(curRoot == -1){
			curRoot = st;
			return;
		}
		curRoot = merge(curRoot, st);
	}
	void push_front(int x){
		int st = newN(x);
		if(curRoot == -1){
			curRoot = st;
			return;
		}
		curRoot = merge(st, curRoot);
	}
	void add(int v, int L, int R, int x, int sl, int sr){
		if(v == -1) return ;
		upd(v);
		if(L <= sl && sr <= R){
			tree[v].pl += x;
			upd(v);
		}else if(R < sl || sr < L){
			return ;
		}else{
			int lft = 0; if(tree[v].l != -1) lft = tree[tree[v].l].sz;
			add(tree[v].l, L, R, x, sl, sl + lft-1);
			add(tree[v].r, L, R, x, sl + lft + 1, sr);
			if(L <= sl + lft && sl+lft <= R){
				tree[v].val += x;
			}
		}
	}
	void add(int l, int r, int x){
		add(curRoot, l, r, x, 0, tree[curRoot].sz-1);
	}
	int get(int v, int x){
		if(v == -1) return v;
		upd(v);
		int lsz = 0;
        if(tree[v].l != -1){
			lsz += tree[tree[v].l].sz;
		}
		if(x == lsz){
			return tree[v].val;
		}
		if(lsz < x){
			return get(tree[v].r, x-lsz-1);
		}else{
			return get(tree[v].l, x);
		}
	}
	int get(int x){ // gauna x-aji elementa
		return get(curRoot, x);
	}
	int desn(int v, int x, int curInd){ // desiniausias <= x indeksas
		if(v == -1) {
			return -1000000;
		}
		upd(v);
		if(tree[v].val <= x){
			if(tree[v].r == -1) return curInd;
			int lsz = 0; 
			int u = tree[v].r;
			if(tree[u].l != -1) lsz += tree[tree[u].l].sz;
			return max(curInd, desn(tree[v].r, x, lsz + curInd+1));
		}else{
			if(tree[v].l == -1) return -1;
			int rsz = 0; 
			int u = tree[v].l;
			if(tree[u].r != -1) rsz += tree[tree[u].r].sz;
			return desn(tree[v].l, x, curInd - rsz -1);
		}
	}
	int kair(int v, int x, int curInd){ // desiniausias <= x indeksas
		if(v == -1) {
			return 1000000;
		}
		upd(v);
		if(tree[v].val < x){
			if(tree[v].r == -1) return 1000000;
			int lsz = 0; 
			int u = tree[v].r;
			if(tree[u].l != -1) lsz += tree[tree[u].l].sz;
			return kair(tree[v].r, x, lsz + curInd+1);
		}else if(tree[v].val > x){
			if(tree[v].l == -1) return 1000000;
			int rsz = 0; 
			int u = tree[v].l;
			if(tree[u].r != -1) rsz += tree[tree[u].r].sz;
			return kair(tree[v].l, x, curInd - rsz -1);
		}else{
			if(tree[v].l == -1) return curInd;
			int rsz = 0; 
			int u = tree[v].l;
			if(tree[u].r != -1) rsz += tree[tree[u].r].sz;
			return min(curInd, kair(tree[v].l, x, curInd - rsz -1));
		}
	}
	int desn(int x){
		int lsz = 0;
		if(tree[curRoot].l != -1){
			lsz += tree[tree[curRoot].l].sz;
		}
		return desn(curRoot, x, lsz);
	}
	int kair(int x){ // randa kairiausia x elementa, kai x egzistuoja
		int lsz = 0;
		if(tree[curRoot].l != -1){
			lsz += tree[tree[curRoot].l].sz;
		}
		return kair(curRoot, x, lsz);
	}
	void print(int v = -2){
		if(v == -2) v = curRoot;
		if(v == -1) return;
		upd(v);
		print(tree[v].l);
		cout << tree[v].val << " ";
		print(tree[v].r);
	} 
	void del(int l, int r){
		cout << "del " << l << "; " << r << endl;
		auto prm = split(curRoot, r);
		cout << "prm: " << prm.first << "; " << prm.second << endl;
		auto ant = split(prm.first, l-1);
		curRoot = merge(ant.first, prm.second);
	}
	void pr(int v = -2){
		if(v == -2) v = curRoot;
		if(v == -1) return;
		pr(tree[v].l);
		int lsz = 0;
        if(tree[v].l != -1){
			lsz += tree[tree[v].l].sz;
		}
		cout << "esu ant " << v << ", jo val = " << tree[v].val << ", o lft = " << lsz  <<  ", kaireje yra " << tree[v].l << ", desineje - " << tree[v].r << endl;
		pr(tree[v].r);
	} 

    treap(){
		tree.resize(2e5);
    }
};
const int dydis = 1e5 + 10;
vector<pair<int, int> > vec;
int n;
int kek[dydis] = {};
treap ms;
void test(){
	
	for(int i = 0; i < 10; i++){
		int a; cin >> a;
		ms.push_back(a);
		cout << "db masyvas: "; ms.print();
		cout << endl; 
	}
	for(int i = 0; i < 10; i++){
		int x; cin >> x; 
		cout << ms.kair(x) << endl;
	}
	for(int i = 0; i < 4; i++){
		int l, r, a; cin >> l >> r >> a;
		ms.add(l, r, a);
		//cout << "db masyvas: "; ms.print();
		//cout << endl; 
	}
	//cout << "db masyvas: "; ms.print();
	//cout << endl; 
	/*
0 0 0 0 0 0 0 0 0 0
0 9 8
2 3 3
0 0 5
4 9 10
13 8 11 11 18 18 18 18 18 18
*/
	while(true){
		int l, r; cin >> l >> r; l--; r--;
		ms.del(l, r);
		cout << "db masyvas: "; ms.print();
		cout << endl; 
	}
	exit(0);
}
int main(){
	//test();
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        vec.push_back({a, b});
    }
    sort(vec.begin(), vec.end());
    int curHe = 0;
    for(auto x : vec){
        while(x.first != curHe){
			curHe++;
			ms.push_front(0);
		}
		int kek = x.second;
		int kas = ms.get(kek-1);
		
		int r = ms.desn(kas);
		int l = ms.kair(kas);
		
		int reiks = (kek-1)-l + 1;
		
		// intervalas [r-reiks + 1; r] ++;
		// intervalas [0; l-1]++
		ms.add(0, l-1, 1);
		ms.add(r-reiks+1, r, 1);
		// [0; pln]
		
    }
    long long ans = 0;
    for(int i = 0; i < ms.tree[ms.curRoot].sz; i++){
		long long sk = ms.get(i);
        ans += 1ll * sk *( sk-1) / 2ll;
    }
    cout << ans;
    return 0;
}
