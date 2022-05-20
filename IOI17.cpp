

#include <bits/stdc++.h>
//#include "wiring.h"
using namespace std;
vector<int> r, b;
const int inf = 1e9;
long long linf = 1e18;
long long dp[201][201] = {};
long long min_total_length(vector<int> r, vector<int> b) {
	int n  = r.size(); int m = b.size();
	for(int i = 0; i < 201; i++) for(int j = 0; j < 201; j++) dp[i][j] = linf;
	dp[0][0] = 0;
	if(r.back() < b[0]){
		long long ret = 0;
		for(int i = 0; i < min(r.size(), b.size()); i++){
			ret += b[i] - r[i];
		}
		for(int i = min(r.size(), b.size()); i < r.size(); i++){
			ret += b[0] - r[i];
		}
		for(int i = min(r.size(), b.size()); i < b.size(); i++){
			ret += b[i] - r.back();
		}
		return ret;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(i + j == 0) continue;
			dp[i][j] = min(dp[i][j], abs(r[i-1] - b[j-1]) + dp[i-1][j-1]);
			dp[i][j] = min(dp[i][j], abs(r[i-1] - b[j-1]) + dp[i-1][j]);
			dp[i][j] = min(dp[i][j], abs(r[i-1] - b[j-1]) + dp[i][j-1]);
		}
	}
	return dp[n][m];
}






//#include "wiring.h"

#include <cassert>
#include <cstdio>

using namespace std;

int main() {
	int n, m;
	assert(2 == scanf("%d %d", &n, &m));

	vector<int> r(n), b(m);
	for(int i = 0; i < n; i++)
		assert(1 == scanf("%d", &r[i]));
	for(int i = 0; i < m; i++)
		assert(1 == scanf("%d", &b[i]));

	long long res = min_total_length(r, b);
	printf("%lld\n", res);

	return 0;
}

