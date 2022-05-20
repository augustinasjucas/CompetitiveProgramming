#include <cstdio>
#include <cstdlib>
#include <vector>
//#include "meetings.h"

namespace {

int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  return x;
}

}  // namespace





//#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 10;
struct seg_tree1{
	int l[dydis], r[dydis], val[dydis]; int dbInd = 0;
	int n;
	void build(int v = 1){
		if(v >= n){
			l[v] = r[v] = dbInd++;
		}else{
			build(v*2); build(v*2+1);
			l[v] = l[v*2]; r[v] = r[v*2+1];
		}
		val[v] = 0;
	}
	seg_tree1(int dd){
		n = dd;
		build();
	}
	void change(int v, int L, int R, int x){
		if(L <= l[v] && r[v] <= R){
			val[v] = x;
		}else if(R < l[v] || r[v] < L){
			
		}else{
			change(v*2, L, R, x);
			change(v*2+1, L, R, x);
			val[v] = max(val[v*2], val[v*2+1]);
		}
	}
	int getMax(int v, int L, int R){
		if(L <= l[v] && r[v] <= R){
			return val[v];
		}else if(R < l[v] || r[v] < L){
			return 0;
		}else{
			return max(getMax(v*2, L, R), getMax(v*2+1, L, R));
		}
	}
};
struct seg_tree{
	int l[dydis], r[dydis], val[dydis]; int dbInd = 0;
	int n;
	void build(int v = 1){
		if(v >= n){
			l[v] = r[v] = dbInd++;
		}else{
			build(v*2); build(v*2+1);
			l[v] = l[v*2]; r[v] = r[v*2+1];
		}
		val[v] = 0;
	}
	seg_tree(int dd){
		n = dd;
		build();
	}
	void change(int v, int L, int R, int x){
		if(L <= l[v] && r[v] <= R){
			val[v] = x;
		}else if(R < l[v] || r[v] < L){
			
		}else{
			change(v*2, L, R, x);
			change(v*2+1, L, R, x);
			val[v] = max(val[v*2], val[v*2+1]);
		}
	}
	int getMax(int v, int L, int R){
		if(L <= l[v] && r[v] <= R){
			return val[v];
		}else if(R < l[v] || r[v] < L){
			return 0;
		}else{
			return max(getMax(v*2, L, R), getMax(v*2+1, L, R));
		}
	}
};
vector<int> mas;
vector<pair<int, int> > vec;
vector<int> mxai;
int q;
int n;
vector<long long> mazas(){
	int pref[n][2], suf[n][2];
	for(auto &x : mas) x--;
	pref[0][0] = mas[0] == 0;
	pref[0][1] = mas[0] == 1;
	for(int i = 1; i < n; i++){
		pref[i][0] = pref[i-1][0] + (mas[i] == 0);
		pref[i][1] = pref[i-1][1] + (mas[i] == 1);
	}
	suf[n-1][0] = mas[n-1] == 0;
	suf[n-1][1] = mas[n-1] == 1;
	for(int i = n-2; i > -1; i--){
		suf[i][0] = suf[i+1][0] + (mas[i] == 0);
		suf[i][1] = suf[i+1][1] + (mas[i] == 1);
	}
	mxai.resize(n);
	for(int i = 0; i < n; i++){
		if(mas[i] == 1) continue;
		for(int j = i; j <= n; j++){
			if(j == n || mas[i] != mas[j]){
				for(int h = i; h < j; h++) mxai[h] = j - i;
				i = j - 1; break;
			}
		}
	}
	seg_tree medis(n);
	for(int i = 0; i < n; i++){
		medis.change(1, i, i, mxai[i]);
	}
	vector<long long> ret;
	for(auto x : vec){
		int L = x.first;
		int R = x.second;
		int mxas = 0;
		int LL = L, RR = R;
		//cout << "L = " << L << ", R = " << R << endl;
		if(mas[L] == 0){
			int l = L; int r = R; int mid;
			while(l <= r){
				mid = (l + r) / 2;
				//cout << "mid = " << mid << endl;
				if(pref[mid][1] == pref[L][1]){
					L = max(L, mid);
					l = mid+1;
				}else{
					r = mid-1;
				}
			}
			L++;
			if(L > R) {
				ret.push_back(RR - LL + 1);
				continue;
			}
		}
		if(mas[R] == 0){
			int l = L; int r = R; int mid;
			while(l <= r){
				mid = (l + r) / 2;
				if(suf[mid][1] == suf[R][1]){
					R = min(R, mid);
					r = mid-1;
				}else{
					l = mid+1;
				}
			}
			R--;
			if(L > R) {
				ret.push_back(RR - LL + 1);
				continue;
			}
		}
		mxas = max(RR-R, L-LL);
		//cout << "is [" << LL << "; "  << RR << "] i [" << L << "; " << R << "]\n";
		mxas = max(mxas, medis.getMax(1, L, R));
		ret.push_back((RR-LL + 1 - mxas) * 2 + mxas);
	}
	return ret;
	
}



vector<long long> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
	q = L.size();
	n = H.size();
	mas = H; q = L.size();
	for(int i = 0; i < q; i++){
		vec.push_back({L[i], R[i]});
	}
	bool viendu = 1;
	for(auto x : mas) if(x > 2) viendu = 0;
	if(viendu){
		return mazas();
	}
	
	
	
	
	return {};
}

/*
10 1
1 1 1 1 2 1 1 2 1 1
0 0
*/


int main() {
  int N = read_int();
  int Q = read_int();
  std::vector<int> H(N);
  for (int i = 0; i < N; ++i) {
    H[i] = read_int();
  }
  std::vector<int> L(Q), R(Q);
  for (int j = 0; j < Q; ++j) {
    L[j] = read_int();
    R[j] = read_int();
  }

  std::vector<long long> C = minimum_costs(H, L, R);
  for (size_t j = 0; j < C.size(); ++j) {
    printf("%lld\n", C[j]);
  }
  return 0;
}

