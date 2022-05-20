#include <bits/stdc++.h>
using namespace std;
int n, d;
vector<int> compress(vector<int> &a){
	set<int> st;
	for(auto x : a) st.insert(x);
	vector<int> un;
	for(auto x : st) un.push_back(x);
	vector<int> ret;
	for(auto x : a){
		ret.push_back(lower_bound(un.begin(), un.end(), x) - un.begin());
	}
	return ret;
}
vector<int> mas;
const int inf = 1e9;
const int dydis = 3e5 + 1;
int dp[dydis];
const int dd = 20;
pair<int, int> sparse[dd][dydis];

int lg2[dydis];
void calc(){
	lg2[1] = 0;
	for(int i = 2; i < dydis; i++) lg2[i] = lg2[i/2] + 1;
	for(int i = 0; i < n; i++) sparse[0][i] = {mas[i], i};
	for(int j = 1; j < dd; j++){
		for(int i = 0; i < n; i++){
			sparse[j][i] = min(sparse[j-1][i], sparse[j-1][i + (1 << (j-1))]);
		}
	}
}
auto getMin(int l, int r){
	int lg = lg2[r-l+1];
	return min(sparse[lg][l], sparse[lg][r-(1 << lg)+1]);
}
int nxt[dydis];
int main(){
	for(auto &x : dp) x = -inf;
	cin >> n >> d;
	mas.resize(n);
	for(auto &x : mas) cin >> x;
	mas = compress(mas);
	int mx = 0; for(auto x : mas) mx = max(mx, x);
	for(auto &x : mas) x = mx - x;
	reverse(mas.begin(), mas.end());
	calc();
	// DABAR REIKIA RASTI DIDZIAUSIA DIDEJANT POSEKI, KURIAM PRIKLAUSYTU 0-INIS ELEMENTAS IR D - SKIRTUMAS
	for(int i = 0; i < n; i++){
		if(i + d < n)
			nxt[i] = getMin(i+1, i+d).second;
		else 
			nxt[i] = n;
	}
	dp[0] = 1;
	int ans = 1;
	for(int i = 1; i < n; i++){
		for(int j = 0; j < i; j++){
			if(dp[j] < dp[i]){
				// ar galiu sujungti?
				// galesiu sujungti, jei galiu nukeliauti paliesdamas visus TIK mazesnius uz mas[i]
			}
		}
		ans = max(ans, dp[i]);
	}
	cout  << ans;
	return 0;
}
/*
7 1
100 600 600 200 300 500 500
*/
