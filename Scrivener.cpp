#include <bits/stdc++.h>
using namespace std;

const int dydis = 20000000;
char val[dydis];
bitset<dydis> hasmin;
int lft[dydis];
int rght[dydis];
const int dd = 1e6 + 1;
int dbIndd = 0, dbInd ;
vector<int> roots;
int curPlace = 0;
void build(int v){
	if(v >= dd){
		val[v] = -1;
		hasmin[v] = 1;
		lft[v] = rght[v] = -1;
	}else{
		build(v*2); build(v*2+1);
		hasmin[v] = 1;
		lft[v] = v*2;
		rght[v] = v*2+1;
	}
}
void Init() {
	build(1);
	dbInd = dd*2 + 2;
	roots.push_back(1);
}
int it = 0;
int mid;
void addLast(int v, int ka, int tl = 0, int tr = -2){
	if(tr == -2) tr = dd-1;
	mid = (tl + tr) / 2;
	//if(it++ > 20) exit(0);
	//cout << "v = " << v << ", ka = " << ka << ", mano int: [" <<tree[v].l << "; " << tree[v].r << "]\n";
	if(tl == tr){
		val[v] = ka;
		hasmin[v] = val[v] == -1;
		//cout << "padarau " << tree[v].l << " i " << ka << endl;
		//cout << "[" << tree[v].l << "; " << tree[v].r << "].hasmin = " << tree[v].hasmin << endl;
		return;
	}
	if(hasmin[lft[v]]){ 
		//cout << "eisim i kaire!" << ", ten siaip yra " << tree[v].lft << ", tai as ji nukopijuoju i " << dbInd << endl;
		lft[dbInd] = lft[lft[v]];
		rght[dbInd] = rght[lft[v]];
		hasmin[dbInd] = hasmin[lft[v]];
		val[dbInd] = val[lft[v]];
		
		lft[v] = dbInd;
		addLast(dbInd++, ka, tl, mid);
	}else{
		lft[dbInd] = lft[rght[v]];
		rght[dbInd] = rght[rght[v]];
		hasmin[dbInd] = hasmin[rght[v]];
		val[dbInd] = val[rght[v]];
		rght[v] = dbInd;
		addLast(dbInd++, ka, mid+1, tr);
	}
	hasmin[v] = hasmin[lft[v]] | hasmin[rght[v]];
	//cout << "[" << tree[v].l << "; " << tree[v].r << "].hasmin = " << tree[v].hasmin << endl;
}
int getVal(int v, int x, int tl = 0, int tr = -2){
	if(tr == -2) tr = dd-1;

	if(tr < x || x < tl) return 0;
	mid = (tl + tr) / 2;
//	cout << "esu " << tl << "; " << tr << ", mid = " << mid << ", kaimynai [" << tl << "; " << mid << "], [" << mid+1 << "; "  << tr << "]\n";

	if(tl == tr){
//		cout << "ret " << tl << endl << endl;
		return val[v];
	
	}

	if(tl <= x && x <= tr){
		return getVal(lft[v], x, tl, mid) + getVal(rght[v], x, mid+1, tr);
	}else{
		return 0;
	}
}
/*
void print(int v){
	if(tree[v].l == tree[v].r){
		if(tree[v].val == -1) return;
		cout << ((char)('a' + tree[v].val));
		return;
	}
	print(tree[v].lft);
	print(tree[v].rght);
}
	*/

void TypeLetter(char L) {
	//cout << "rasom " << L << " raide " << endl;
	lft[dbInd] = lft[roots.back()];
	rght[dbInd] = rght[roots.back()];
	hasmin[dbInd] = hasmin[roots.back()];
	val[dbInd] = val[roots.back()];
	//cout << "kol kas" << endl;
	int bv = dbInd;
	dbInd++;
	addLast(dbInd-1, L-'a');
	roots.push_back(bv);
	//cout << "po typinant: "; print(roots.back());
	//cout << endl;
}

void UndoCommands(int U) {
	lft[dbInd] = lft[roots[roots.size()-1-U]];
	rght[dbInd] = rght[roots[roots.size()-1-U]];
	hasmin[dbInd] = hasmin[roots[roots.size()-1-U]];
	val[dbInd] = val[roots[roots.size()-1-U]];
	roots.push_back(dbInd);
	//cout << "po udno: "; print(roots.back());
	//cout << endl;
	dbInd++;
}

char GetLetter(int P) {
	
	return ((char)('a' + getVal(roots.back(), P)));
}
/*
10
T a
T b
T c
T d
T e
T f
P 5
*/ 













#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define inbuf_len 1 << 16
#define outbuf_len 1 << 16

void Init();
void TypeLetter(char L);
void UndoCommands(int U);
char GetLetter(int P);

int main() {
  Init();

  int cmd_num;
  auto tmp = scanf("%d", &cmd_num);
  assert(tmp == 1);

  int i;
  for (i = 0; i < cmd_num; i++) {
    char cmd;
    tmp = scanf(" %c", &cmd);
    assert(tmp == 1);
    if (cmd == 'T') {
      char letter;
      tmp = scanf(" %c", &letter);
      assert(tmp == 1);
      TypeLetter(letter);
    }
    else if (cmd == 'U') {
      int number;
      tmp = scanf("%d", &number);
      assert(tmp == 1);
      UndoCommands(number);
    }
    else if (cmd == 'P') {
      int index;
      char letter;
      tmp = scanf("%d", &index);
      assert(tmp == 1);
      letter = GetLetter(index);
      printf("%c\n", letter);
    }
  }
  
  puts("Let's test for cheating!!");

  return 0;

}
