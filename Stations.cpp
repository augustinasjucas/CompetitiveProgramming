//#include "stations.h"
#include <bits/stdc++.h>
using namespace std;
const int dydis = 1000;
vector<int> gr[dydis];
int enter[dydis];
int leave[dydis];
vector<int> ret (dydis);
int dbInd = 0;
void dfs(int v, int came, int h = 0){
	enter[v] = dbInd++;
	for(auto x : gr[v]){
		if(x == came) continue;
		dfs(x, v, h+1);
	}
	leave[v] = dbInd++;
	//cout << "enter[" << v << "] = " << enter[v] << ", leave[" << v << "] = " << leave[v] << ", ";
	if(h & 1){
		cout << "dedu leave" << endl;
		ret[v] = leave[v];
	}else{
		ret[v] = enter[v];
		//cout << "dedu enter" << endl;
	}
}
vector<int> compress(vector<int> a){
	vector<int> ret;
	auto cp = a;
	sort(cp.begin(), cp.end());
	for(auto x : a){
		ret.push_back(lower_bound(cp.begin(), cp.end(), x) - cp.begin());
	}
	//cout << "{"; for(auto x : a) cout << x  << " "; cout << "} -> {"; for(auto x : ret) cout << x << " "; cout << "}\n\n";
	return ret;
}
vector<int> label(int n, int k, vector<int> u, vector<int> v) {
	for(int i = 0; i < n; i++){
		gr[i].clear();
	}
	dbInd = 0;
	ret.resize(n);
	for(int i = 0; i < n-1; i++){
		gr[u[i]].push_back(v[i]);
		gr[v[i]].push_back(u[i]);
	}
	dfs(0, -1);
	ret = compress(ret);
	return ret;
}

int find_next_station(int s, int t, vector<int> c) {
	
	bool yraMaz = 1;
	for(auto x : c){
		if(x < s) yraMaz = 0;
	}
	if(yraMaz){
		int dd = c.back();
		int last = s+1;
		//cout << s << " yra enter" << endl;
		for(auto x : c){
			if(x == dd && s != 0) continue;
			int enter = last;
			int leave = x;
			//cout << "gaunu [" << enter << "; " << leave << "]\n";
			if(enter <= t && t <= leave) return x;
			last = leave;
		}
		return c.back();
	}else{ 
		//cout << s << " yra leave" << endl;

		for(int i = 1; i < (int)c.size(); i++){
			int enter = c[i];
			int leave = (i == (int)c.size() - 1 ? s  : c[i+1] ) - 1;
			//cout << c[i] << ", enter: " << enter << ", leave: " << leave << endl;
			if(enter <= t && t <= leave){
				return c[i];
			}
		}
		return c[0];
	}
	
}




//#include "stations.h"
#include <cstdio>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>

static int max_label = 0;
static int r, n, k, q;
static std::vector<int> u, v, labels, answers;
static std::map<int, int> reverse_labels;
static std::vector<std::vector<int>> adjlist;
static int s, t, w;
static std::vector<int> c;

int main() {
	/*while(true){
		int a, b; cin >> a >> b;
		find_next_station(a, b, {});
		cout << endl << endl;
	}*/
	assert(scanf("%d", &r) == 1);
	for (int tc = 0; tc < r; tc++) {
		assert(scanf("%d%d", &n, &k) == 2);
		u.resize(n - 1);
		v.resize(n - 1);
		adjlist.clear();
		adjlist.resize(n);
		for (int i = 0; i < n - 1; i++) {
			assert(scanf("%d%d", &u[i], &v[i]) == 2);
			adjlist[u[i]].push_back(v[i]);
			adjlist[v[i]].push_back(u[i]);
		}
		labels = label(n, k, u, v);
		if ((int)labels.size() != n) {
			printf("Number of labels not equal to %d\n", n);
			exit(0);
		}
		reverse_labels.clear();
		for (int i = 0; i < n; i++) {
			if (labels[i] < 0 || labels[i] > k) {
				printf("Label not in range 0 to %d\n", k);
				exit(0);
			}
			if (reverse_labels.find(labels[i]) != reverse_labels.end()) {
				printf("Labels not unique\n");
				exit(0);
			}
			reverse_labels[labels[i]] = i;
			if (labels[i] > max_label) {
				max_label = labels[i];
			}
		}
		assert(scanf("%d", &q) == 1);
		for (int i = 0; i < q; i++) {
			assert(scanf("%d%d%d", &s, &t, &w) == 3);
			c.clear();
			for (int v : adjlist[s]) {
				c.push_back(labels[v]);
			}
			std::sort(c.begin(), c.end());
			int answer = find_next_station(labels[s], labels[t], c);
			if (!std::binary_search(c.begin(), c.end(), answer)) {
				printf("Label %d returned by find_next_station not found in c\n", answer);
				exit(0);
			}
			answers.push_back(reverse_labels[answer]);
		}
	}
	printf("%d\n", max_label);
	for (int index : answers) {
		printf("%d\n", index);
	}
	exit(0);
}
