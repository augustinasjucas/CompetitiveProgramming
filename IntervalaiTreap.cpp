#include <bits/stdc++.h>
#pragma GCC optimize("O2")
#pragma GCC targe("avx2")
#pragma GCC optimize("unroll-loops")
using namespace std;
const long long range_from  = -1e18;
const long long range_to    = 1e18;
std::random_device                  rand_dev;
std::mt19937                        generator(time(0));
std::uniform_int_distribution<long long>  distr(range_from, range_to);
int n, q;
const long long inf = 1e18;
const int dydis = 1e5 +1;
int l[dydis + 1], r[dydis + 1];
bool rot[dydis + 1] = {};
long long val[dydis + 1] = {};
long long min1[dydis + 1] = {};
long long min2[dydis + 1] = {};
int minCnt[dydis + 1] = {};
long long pl[dydis + 1] = {};
long long mx[dydis+ 1] = {}; // max(mx[i], x) + pl[i]
int dbInd = 0;
long long nodeVal[dydis + 1] = {};
int sz[dydis + 1];
int w[dydis + 1] = {};
int M = dydis;
void fastscan(int &result){
	cin >> result;
    return ;
    char ch;
	ch = getchar();
	if (ch >= '0' && ch <= '9') {

	}
	else
		ch = getchar();
	result = ch - '0';
	ch = getchar();
	if (ch < '0' || ch > '9')
		return ;
	result = result * 10 + (ch - '0');
	ch = getchar();
	if (ch < '0' || ch > '9')
		return ;
	result = result * 10 + (ch - '0');
	ch = getchar();
	if (ch < '0' || ch > '9')
		return ;
	result = result * 10 + (ch - '0');
	ch = getchar();
	if (ch < '0' || ch > '9')
		return ;
	result = result * 10 + (ch - '0');
	ch = getchar();
	if (ch < '0' || ch > '9')
		return ;
	result = result * 10 + (ch - '0');
	ch = getchar();
	if (ch < '0' || ch > '9')
		return ;
	result = result * 10 + (ch - '0');
	ch = getchar();
}
pair<long long, long long> conn(long long a, long long b, long long c, long long d) {  // virsuje yra max(x, A) + B, apacioje yra max(x, C) + D
    return {max(c, a - d), d + b};
}
int newN(int Val){
    l[dbInd] = M;
    r[dbInd] = M;
    sz[dbInd] = 1;
    nodeVal[dbInd] = Val;
    w[dbInd] = distr(generator);
    mx[dbInd] = -inf;
    min1[dbInd] = Val;
    min2[dbInd] = inf;
    minCnt[dbInd] = 1;
    val[dbInd] = Val;
    return dbInd++;
}
void apply(int v){
    if(v == M) return ;    
    if(rot[v]){
        swap(l[v], r[v]);
        rot[l[v]] = !rot[l[v]];
        rot[r[v]] = !rot[r[v]];
        rot[v] = 0;
    }
    if(mx[v] == -inf && pl[v] == 0)  return ;
    if(min1[v] >= mx[v]) {

    }else if(min1[v] < mx[v] && mx[v] < min2[v]) {
        val[v] += (mx[v] - min1[v]) * minCnt[v];
        min1[v] = mx[v];
    }
    val[v] += 1ll * sz[v] * pl[v];
    min1[v] += pl[v];
    min2[v] += pl[v];    
    if(l[v] != M){
        mx[l[v]] = max(mx[l[v]], mx[v] - pl[l[v]]);
        pl[l[v]] = pl[v] + pl[l[v]];
    }
    if(r[v] != M){
        mx[r[v]] = max(mx[r[v]], mx[v] - pl[r[v]]);
        pl[r[v]] = pl[v] + pl[r[v]];
    }

    nodeVal[v] = max(nodeVal[v], mx[v]) + pl[v];

    mx[v] = -inf;
    pl[v] = 0;

}

void update(int v){ // tarkim v jau yra pa'applyintas
    apply(l[v]);
    apply(r[v]);

    val[v] = val[l[v]] + val[r[v]] + nodeVal[v];
    
    min1[v] = min(min1[l[v]], min1[r[v]]);
    if(min1[r[v]] == min1[l[v]]) min2[v] = min(min2[l[v]], min2[r[v]]);
    else min2[v] = min(min1[l[v]], min1[r[v]]);
    
    minCnt[v] = (min1[l[v]] == min1[v] ? minCnt[l[v]] : 0) + (min1[r[v]] == min1[v] ? minCnt[r[v]] : 0);
    
    if(nodeVal[v] == min1[v]) {
        minCnt[v]++;
    }else if(nodeVal[v] < min1[v]){
        min2[v] = min1[v];
        min1[v] = nodeVal[v];
        minCnt[v] = 1;
    }else if(nodeVal[v] < min2[v]){
        min2[v] = nodeVal[v];
    }

    sz[v] = 1;
    sz[v] += sz[l[v]];
    sz[v] += sz[r[v]];
}

int merge (int L, int R){
    if(L == M) return R;
    if(R == M) return L;
    apply(L);
    apply(R);
    if(w[L] > w[R]){
        int rt = merge(r[L], R);
        r[L] = rt;
        update(L);
        return L;
    }else{
        int rt = merge(L, l[R]);
        l[R] = rt;
        update(R);
        return R;
    }
}

pair<int, int> split(int v, int kek){ 
    if(v == M) return {M, M};
    apply(v);
    if(sz[l[v]] + 1 <= kek) {
        auto bus = split(r[v], kek - sz[l[v]] - 1);
        r[v] = bus.first;
        update(v);
        return {v, bus.second};
    }else { 
        auto bus = split(l[v], kek);
        l[v] = bus.second;
        update(v);
        return {bus.first, v};
    }
}
int root = M;  
long long fSum(int v, int x){
    long long ret = 0;
    while(true){
        apply(v);
        if(sz[l[v]] + 1 <= x){
            apply(l[v]);
            ret += val[l[v]] + nodeVal[v];
            x -= sz[l[v]] + 1;
            v = r[v];
        }else{
            v = l[v];
        }
        if(v == M) break;
    }
    return ret;
}
long long quer(int l, int r){
    return fSum(root, r + 1) - fSum(root, l);
}
void add(int l, int r, int x){
    auto prm = split(root, l);
    auto ant = split(prm.second, r - l + 1);
    apply(ant.first);
    pl[ant.first] += x;
    root = merge(prm.first, ant.first);
    root = merge(root, ant.second);
}
void dfs(int v, int x){
    apply(v);    
    if(min1[v] < x && x < min2[v]){
        mx[v] = x;
    }else if(min1[v] >= x){
        return ;
    }else{
        if(l[v] != M) dfs(l[v], x);
        if(r[v] != M) dfs(r[v], x);
        nodeVal[v] = max(nodeVal[v], (long long)x);
        update(v);
    }
}
void maxi(int l, int r, int x){
    auto prm = split(root, l);
    auto ant = split(prm.second, r - l + 1);
    dfs(ant.first, x);
    root = merge(prm.first, ant.first);
    root = merge(root, ant.second);   
}
void rotat(int l, int r){
    auto prm = split(root, l);
    auto ant = split(prm.second, r - l + 1);
    rot[ant.first] = !rot[ant.first];
    root = merge(prm.first, ant.first);
    root = merge(root, ant.second);   
}
int main(){
    srand(time(0));
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    min1[M] = min2[M] = inf;
    val[M] = 0;
    mx[M] = -inf;
    minCnt[M] = 0;
    sz[M] = 0;
    nodeVal[M] = 0;
    fastscan(n);
    fastscan(q);
    for(int i = 0; i < n; i++){
        int a; fastscan(a);
        root = merge(root, newN(a));
    }
    for(int i = 0; i < q; i++){
        int t; fastscan(t);
        int l, r, x;
        if(t == 1){
            fastscan(l);
            fastscan(r);
            fastscan(x);
            l--; r--;
            add(l, r, x);
        }
        if(t == 2){
            fastscan(l);
            fastscan(r);
            fastscan(x);
            l--; r--;
            maxi(l, r, x);
        }
        if(t == 3){
            fastscan(l);
            fastscan(r);
            l--; r--;
            if(l == r) continue;
            rotat(l, r);
        }
        if(t == 4){
            fastscan(l);
            fastscan(r);
            l--; r--;
            cout << quer(l, r) << "\n";
        }
    }
    return 0;
}
