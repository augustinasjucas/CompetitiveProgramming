







//#include "prize.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
static int query_count = 0;

static const int max_q = 10000;

static vector<vector<int> > rank_count;
int n;
static vector<int> g;
vector<int> ask(int i) {
	query_count++;
	if(query_count > max_q) {
		cerr << "Query limit exceeded" << endl;
		exit(0);
	}

	if(i < 0 || i >= n) {
		cerr << "Bad index: " << i << endl;
		exit(0);
	}

	vector<int> res(2);
	res[0] = rank_count[g[i] - 1][i + 1];
	res[1] = rank_count[g[i] - 1][n] - res[0];
	return res;
}




























#include <bits/stdc++.h>
//#include "prize.h"
using namespace std;
int find_best(int n) {
	int l = 0; int r = n-1;
	
	while(l <= r){
		int mid = (l + r) / 2;
		auto f = ask(mid);
		if(f[0] == 0 && f[1] == 0) return mid;
		if(f[0] == 1){
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	return 0;
}






















int main() {

	cin >> n;

	g.resize(n);
	for(int i = 0; i < n; i++) {
		cin >> g[i];
		if(g[i] < 1) {
			cerr << "Invalid rank " << g[i] << " at index " << i << endl;
			exit(0);
		}
	}

	int max_rank = *max_element(g.begin(), g.end());

	rank_count.resize(max_rank + 1, vector<int>(n + 1, 0));
	for(int r = 0; r <= max_rank; r++) {
		for(int i = 1; i <= n; i++) {
			rank_count[r][i] = rank_count[r][i - 1];
			if(g[i - 1] == r)
			  rank_count[r][i]++;
		}
	}

	for(int i = 0; i <= n; i++)
		for(int r = 1; r <= max_rank; r++)
			rank_count[r][i] += rank_count[r - 1][i];

	int res = find_best(n);
	cout << res << endl << "Query count: " << query_count << endl;

	return 0;
}
