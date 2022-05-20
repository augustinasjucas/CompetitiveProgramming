#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e6 + 3;
struct seg_tree{
	int l[dydis*2 + 2], r[dydis*2 + 2];
	long long val[dydis*2+ 2];
	int n;
	int dbInd = 0;
	void build(int v){
		if(v >= n){
			l[v] = r[v] = dbInd++;
		}else{
			build(v * 2);
			build(v * 2 + 1);
			l[v] = l[v*2];
			r[v] = r[v*2+1];
		}
	}
	seg_tree (int dd){
		n = dd;
		build(1);
	}
	void change(int v, int L, int R, int x){
		if(L <= l[v] && r[v] <= R){
			val[v] = x;
		}else if(R < l[v] || r[v] < L){
			
		}else{
			change(v*2, L, R, x); change(v*2+1, L, R, x);
			val[v] = val[2*v] + val[2*v+1];
		}
	}
	long long getSum(int v, int L, int R){
		if(L <= l[v] && r[v] <= R){
			return val[v];
		}else if(R < l[v] || r[v] < L){
			return 0;
		}else{
			return getSum(v*2, L, R) + getSum(v*2+1, L, R);
		}
	}
};

int n;
vector<int> mas;

seg_tree medis(dydis);
int cnt[dydis] = {};

int kek = 0;

void rem(int ind){
	if(ind == n) return;
	cnt[mas[ind]]--;
	if(cnt[mas[ind]] == 1) kek--;
}
void add(int ind){
	if(ind == n) return;
	cnt[mas[ind]]++;
	if(cnt[mas[ind]] == 2) kek++;
}
int tol[dydis];
vector<int> vienetai;
int sparse[dydis][21];
int lg2[dydis];
long long ans = 0;
void calc(){
	lg2[1] = 0;
	for(int i = 2; i < dydis; i++) lg2[i] = lg2[i/2] + 1;
	for(int i = 0; i < n; i++) sparse[i][0] = mas[i];
	for(int i = 1; i < 21; i++){
		for(int j = 0; j + (1 << (i-1)) < n; j++){
			sparse[j][i] = max(sparse[j][i-1], sparse[j + (1 << (i-1))][i-1]);
		}
	}

}
int lg;
int get(int l, int r){
	if(l < 0 || r < l || r >= n) return 1000000000;
	lg = lg2[r - l + 1];
	return max(sparse[l][lg], sparse[r - (1 << lg)+1][lg]);
}


int main(){
	cin >> n;
	mas.resize(n);

	for(auto &x : mas) {
		cin >> x;
		x--;
	}
	int br = 0;
	calc();
	
	int ind = 0;
	add(0);
	for(int i = 0; i < n; i++){
		
		if(i != 0){
			rem(i-1);
		}
		
		while(ind < n && kek == 0){
			add(++ind);
		}
		rem(ind--);
		tol[i] = ind;
		if(mas[i] == 0) vienetai.push_back(i);
	}
	int sz, jau, reikia, ll, mid, rr, ret, ret1;
	vector<pair<int, pair<int, int> > > quers;
	for(int i = 0; i < n; i++){
		if(mas[i] == 0) {ans++; continue;}
		int l = -1, r = -1, li, ri;
		ri = lower_bound(vienetai.begin(), vienetai.end(), i) - vienetai.begin();
		li = ri - 1;
		if(0 <= li && li < (int) vienetai.size()) l = vienetai[li];
		if(0 <= ri && ri < (int) vienetai.size()) r = vienetai[ri];
		if(l != -1){
			if(tol[l] >= i && get(l, i) <= mas[i]){
				sz = mas[i] + 1;
				jau = i - l + 1;
				reikia = sz - jau;
				if(reikia == 0){
					ans++;
				}else{
					ll = max(0, l - reikia); rr = l;
					ret = l;
					while(ll <= rr){
						mid = (ll + rr) / 2;
						if(get(mid, i) <= mas[i]){
							ret = min(ret, mid);
							rr = mid-1;
						}else{
							ll = mid+1;
						}
					}
					ll = i; rr = min(n-1, i + reikia);
					ret1 = i;
					while(ll <= rr){
						mid = (ll + rr) / 2;
						if(get(i, mid) <= mas[i]){
							ll = mid+1;
							ret1 = max(ret1, mid);
						}else{
							rr = mid-1;
						}
					}
					ret1 = ret1 - sz + 1;
					if(ret <= ret1) quers.push_back({sz, {ret, ret1}}); 
					// reikia surasti kiek [L; R] intervale esanciu skaiciu turi tol[x] >= x + sz
				}
			}
		}
		
		if(r != -1){
 			if(tol[i] >= r && get(i, r) <= mas[i]){
				sz = mas[i] + 1;
				jau = r - i + 1;
				reikia = sz - jau;
				if(reikia == 0){
					ans++;
					continue;
				}

				ll = max(0, i - reikia); rr = i;
				ret = i;
				while(ll <= rr){
					mid = (ll + rr) / 2;
					//cout << "bandau " << mid << ", getas: " << get(mid, i) << " vs " << mas[i] << endl;
					if(get(mid, i) <= mas[i]){
						ret = min(ret, mid);
						rr = mid-1;
					}else{
						ll = mid+1;
					}
				}
				ll = r; rr = min(n-1, r + reikia);
				ret1 = r;
				while(ll <= rr){
					mid = (ll + rr) / 2;
					if(get(i, mid) <= mas[i]){
						ll = mid+1;
						ret1 = max(ret1, mid);
					}else{
						rr = mid-1;
					}
				}
				ret1 = ret1 - sz + 1;
				if(ret > ret1) continue;
				quers.push_back({sz, {ret, ret1}}); 
				// reikia surasti kiek [L; R] intervale esanciu skaiciu turi tol[x] >= x + sz-1
			}
		}
		//cout << endl;
	}

	for(int i = 0; i < n; i++){
		quers.push_back({tol[i] - i+1, {1000000000, i}});
	}
	sort(quers.begin(), quers.end()); reverse(quers.begin(), quers.end());
	for(auto x : quers){
		if(x.second.first == 1000000000){
			medis.change(1, x.second.second, x.second.second, 1);
		}else{
			ans += medis.getSum(1, x.second.first, x.second.second);
		}
	}
	cout << ans;
	//cout << " vs " << br << endl;
	return 0;
}
/*
10
1 2 3 5 4 1 2 5 5 1 


4
1 2 3 1

5
5 1 3 4 2


3
1 2 1

*/
