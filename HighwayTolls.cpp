




#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
//#include "highway.h"

namespace {

constexpr int MAX_NUM_CALLS = 100;
constexpr long long INF = 1LL << 61;

int N, M, A, B, S, T;
std::vector<int> U, V;
std::vector<std::vector<std::pair<int, int>>> graph;

bool answered, wrong_pair;
int num_calls;

int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  return x;
}

void wrong_answer(const char *MSG) {
  printf("Wrong Answer: %s\n", MSG);
  exit(0);
}

}  // namespace

long long ask(const std::vector<int> &w) {
  if (++num_calls > MAX_NUM_CALLS) {
    wrong_answer("more than 100 calls to ask");
  }
  if (w.size() != (size_t)M) {
    wrong_answer("w is invalid");
  }
  for (size_t i = 0; i < w.size(); ++i) {
    if (!(w[i] == 0 || w[i] == 1)) {
      wrong_answer("w is invalid");
    }
  }

  std::vector<bool> visited(N, false);
  std::vector<long long> current_dist(N, INF);
  std::queue<int> qa, qb;
  qa.push(S);
  current_dist[S] = 0;
  while (!qa.empty() || !qb.empty()) {
    int v;
    if (qb.empty() ||
        (!qa.empty() && current_dist[qa.front()] <= current_dist[qb.front()])) {
      v = qa.front();
      qa.pop();
    } else {
      v = qb.front();
      qb.pop();
    }
    if (visited[v]) {
      continue;
    }
    visited[v] = true;
    long long d = current_dist[v];
    if (v == T) {
      return d;
    }
    for (auto e : graph[v]) {
      int vv = e.first;
      int ei = e.second;
      if (!visited[vv]) {
        if (w[ei] == 0) {
          if (current_dist[vv] > d + A) {
            current_dist[vv] = d + A;
            qa.push(vv);
          }
        } else {
          if (current_dist[vv] > d + B) {
            current_dist[vv] = d + B;
            qb.push(vv);
          }
        }
      }
    }
  }
  return -1;
}

void answer(int s, int t) {
  if (answered) {
    wrong_answer("answered not exactly once");
  }

  if (!((s == S && t == T) || (s == T && t == S))) {
    wrong_pair = true;
  }

  answered = true;
}


















//#include "highway.h"
#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
vector<pair<int, int> > gr[dydis];
int n, m;
long long light, heavy;
int tevas[dydis];
int dist[dydis];
int virs[dydis];
vector<pair<int, int> > brn;
int getLen(){
	vector<int> st;
	for(int i = 0; i < m; i++) st.push_back(0);
	return 1ll * ask(st) / light;
}
void dfs(int v, int came = -1, int dst = 0){
	dist[v] = dst;
	if(came == -1) virs[v] = -1;
	for(auto x : gr[v]){
		if(x.first == came) continue;
		tevas[x.first] = v;
		virs[x.first] = x.second;
		dfs(x.first, v, dst+1);
	}
}
vector<pair<int, int> > getInds(int v, int len){ // first - brianos indeksas, sec - virsunes
	dfs(v, -1);
	vector<pair<int, int> > ret;
	for(int i = 0; i < n; i++){
		if(dist[i] != len) continue;
		ret.push_back({virs[i], i});
	}
	return ret;
}
pair<int, int> solveWhenHave(int v, int len){
	vector<pair<int, int> > inds = getInds(v, len); // cia turetu visi buti blogi, isskyrus viena!
	int l = 0; int r = inds.size()-1; int mid = -1; int kair = inds.size()-1;
	vector<int> askk(m, 0);
	long long turi = len * light;
	while(l <= r){
		mid = (l + r) / 2;
		for(int i = 0; i <= mid; i++) askk[inds[i].first] = 1;
		if(ask(askk) != turi){
			r = mid-1;
			kair = min(kair, mid);
		}else{
			l = mid+1;
		}
		for(int i = 0; i <= mid; i++) askk[inds[i].first] = 0;
	}
	return {v, inds[kair].second};
}
/*
int findOne(int len){ //randa viena node'a
	vector<pair<int, int> > inds;
	for(int i = 0; i < (int) brn.size(); i++) inds.push_back({i, brn[i].first});
	int l = 0; int r = inds.size()-1; int mid = -1; int kair = inds.size()-1;
	vector<int> askk(m, 0);
	long long turi = len * light;
	while(l <= r){
		mid = (l + r) / 2;
		for(int i = 0; i <= mid; i++) askk[inds[i].first] = 1;
		if(ask(askk) != turi){
			r = mid-1;
			kair = min(kair, mid);
		}else{
			l = mid+1;
		}
		for(int i = 0; i <= mid; i++) askk[inds[i].first] = 0;
	}
	return inds[kair].second;
}*/

int findAukste(vector<pair<int, int> > briaunos, int len){
	int l = 0; int r = briaunos.size()-1; int mid;
	vector<int> st(m, 0);
	long long turi = 1ll * len * light;
	int desn = r;
	//cout << "briaunos: \n"; for(auto x : briaunos) cout << "briauna " << x.first << ", jos galas " << x.second << endl; cout << endl;
	 
	while(l <= r){
		mid = (l + r) / 2;
		for(int i = 0; i <= mid; i++) st[briaunos[i].first] = 1;
		if(ask(st) != turi){
			r = mid-1;
			desn = min(desn, mid);
		}else{
			l = mid+1;
		}
		for(auto & x : st) x = 0;
	}
	return briaunos[desn].second;
}

vector<pair<int, int> > aukstai[dydis];
int findFarthest(int v, int len){
	
	dfs(v, -1);
	int mx = 0;
	for(int i = 0; i < n; i++){
		aukstai[dist[i]].push_back({virs[i], i});
		mx = max(mx, dist[i]);
	}
	int l = 1, r = mx, mid;
	long long turi = 1ll * len  * heavy;
	vector<int> st(m, 0);
	int ans = 0;
	while(l <= r){
		mid = (l + r) / 2;
		for(int i = 1; i <= mid; i++){
			for(auto x : aukstai[i]) st[x.first] = 1;
		}
		if(ask(st) == turi){
			r = mid-1;
		}else{
			ans = max(ans, mid);
			l = mid+1;
		}
		for(auto &x : st) x = 0;
	}
	// galas yra ans aukste
	ans++;
	//cout << "galas yra " << ans << " aukste nuo " << v << endl;
	return findAukste(aukstai[ans], len);
}
pair<int, int> solveEil(int len){
	long long turi = light * len;
	int leftmost = -1;
	int l = 0; int r = n-1; int mid;
	vector<int> st(m, 0);
 	while(l <= r){
		mid = (l + r) / 2;
		for(int i = 0; i <= mid; i++) st[i] = 1;
		if(ask(st) == turi){
			leftmost = max(leftmost, mid);
			l = mid+1;
		}else{
			r = mid-1;
		}
		for(int i = 0; i <= mid; i++) st[i] = 0;
	}
	//cout << "leftmost = " << leftmost << endl;
	int raitmost = n-1;
	l = 0; r = n-1;
	while(l <= r){
		mid = (l + r) /2;
		for(int i = mid; i <= n-1; i++) st[i] = 1;
		if(ask(st) == turi){
			raitmost = min(raitmost, mid);
			r = mid-1;
		}else{
			l = mid+1;
		}
		for(int i = mid; i <= n-1; i++) st[i] = 0;
	}
	return {leftmost+1, raitmost};
	
}
/*
 6 5
5 7
1 3
0 1    
1 2
2 3
3 4
4 5

*/
void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
	n = N;
	m = V.size();
	light = A; heavy = B;
	bool eile = 1;
	for(int i = 0; i < m; i++){
		gr[U[i]].push_back({V[i], i});
		gr[V[i]].push_back({U[i], i});
		brn.push_back({V[i], U[i]});
		if(!(U[i] == i && V[i] == i+1)) eile = 0;
	}
	int len = getLen();
	if(eile){
		auto ret = solveEil(len);
		answer(ret.first, ret.second);
		return ;
	}
	
	int uu = findFarthest(0, len);
	//cout << "galas yra " << uu << endl;
	auto ans = solveWhenHave(uu, len);
	answer(ans.first, ans.second);
	return ;
	
}
/*

12 11 5 7 6 10
0 2
0 3
2 4
2 5
3 6
3 7
4 8
5 9
8 10
8 11
9 1

*/

















int main() {
  N = read_int();
  M = read_int();
  A = read_int();
  B = read_int();
  S = read_int();
  T = read_int();
  U.resize(M);
  V.resize(M);
  graph.assign(N, std::vector<std::pair<int, int>>());
  for (int i = 0; i < M; ++i) {
    U[i] = read_int();
    V[i] = read_int();
    graph[U[i]].push_back({V[i], i});
    graph[V[i]].push_back({U[i], i});
  }

  answered = false;
  wrong_pair = false;
  num_calls = 0;
  find_pair(N, U, V, A, B);
  if (!answered) {
    wrong_answer("answered not exactly once");
  }
  if (wrong_pair) {
    wrong_answer("{s, t} is wrong");
  }
  printf("Accepted: %d\n", num_calls);
  return 0;
}
