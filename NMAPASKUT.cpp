#include <stdio.h>
#pragma GCC optimize("O3")
#pragma GCC target ("avx2")
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}
vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
vector<long long> daug(vector<long long> &a, vector<long long> &b){
    return multiply(a, b);
    //    cout << "{"; for(auto x : a) cout << x << ", "; cout << "} * " ;cout << "{"; for(auto x : b) cout << x << ", "; cout << "} = "; 
    vector<long long> ret(a.size() + b.size() - 1, 0);
    for(int i = 0; i < a.size(); i++) for(int j = 0; j < b.size(); j++) ret[i+j] += a[i] * b[j];
//    cout << "{"; for(auto x : ret) cout << x << ", "; cout << "}\n\n";
    return ret;
}
const int inf = 1e9;
//#include "race.h"
const int dydis = 2e5 + 10;
vector<int> gr[dydis];
int n, k;
bool vis[dydis] = {};
int tevas[dydis];
int gylis[dydis];
vector<int> visi;
int sz[dydis];
void dfs(int v, int came){
	tevas[v] = came;
	visi.push_back(v);
	sz[v] = 1;
	for(auto x : gr[v]){
		if(x == came) continue;
		dfs(x, v);
		sz[v] += sz[x];
	}
}
int findCentroid(int v){
//    cout << "ieskom nuo " << v << endl;
	visi.clear();
	dfs(v, v);
	for(auto x : visi){
		int mx = 0;
		int sm = 0;
		for(int i = 0; i < (int)gr[x].size(); i++){
			if(gr[x][i] == tevas[x]) continue;
			mx = max(mx, sz[gr[x][i]]);
			sm += sz[gr[x][i]];
		}
		mx = max(mx, (int)visi.size()-sm-1);
		if(mx <= (int)visi.size()/2+1) return x;
	}
    
    exit(0);
	return -1;
}
long long ans[dydis];
int known[dydis];
vector<long long> st;
void dfs1(int v, int came, int h, int prm){

    gylis[v] = h;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs1(x, v, h+1, prm);
        gylis[v] = max(gylis[v], gylis[x]);
    }
    gylis[prm] = max(h, gylis[prm]);
}
void dfs2(int v, int came, int h){
    while(st.size() <= h) st.push_back(0);
    st[h]++;
    for(auto x : gr[v]){
        if(x == came) continue;
        dfs2(x, v, h+1);
    }
}
void jeiPrik(int v){ // suskaiciuojam, koks ats, jei v priklauso atsakymui
    
    vector<pair<int, int> > gl;
    for(auto x : gr[v]){
        dfs1(x, v, 1, x);
        gl.push_back({gylis[x], x});
    }
    sort(gl.begin(), gl.end()); reverse(gl.begin(), gl.end());
    vector<vector<long long> > vecs;
    int V = v;
    for(auto x : gl){
        int v = x.second;
        st.clear();
        dfs2(v, V, 1);
        vecs.push_back(st);
    }
    ans[1]++;
    if(vecs.empty()){
        return ;
    }
    
/*    cout << "vecsai gaunasi: \n";
    for(auto x : vecs){
        cout << "{"; for(auto y : x) cout << y << " "; cout << "}\n";
    }
    cout << endl;*/
    vector<long long> sm(vecs[0].size());
    for(auto x : vecs){
        for(int i = 0; i < x.size(); i++){
            sm[i] += x[i];
        }
    }
//    cout << "sm: "; for(auto x : sm) cout << x<< " "; cout << endl;
    for(int i = 0; i < sm.size(); i++) ans[i+1] += sm[i];
    
    for(auto x : vecs){
        for(int i = 0; i < x.size(); i++) sm[i] -= x[i];
        while(sm.back() == 0 && sm.size()) sm.pop_back();
        if(sm.size() == 0) break;
        auto sand = daug(x, sm);
        for(int i = 0; i < sand.size(); i++) ans[i+1] += sand[i];
    }
//    cout << "po jo ans: "; for(int i = 0; i <= n; i++) cout << ans[i] << " "; cout << endl;
}
void calc(int v){
	v = findCentroid(v);
//	cout << "centroidas " << v+1 << endl;
    jeiPrik(v);
	vector<int> kaims;
	for(auto x : gr[v]) kaims.push_back(x);
	for(auto x : visi){
		vector<int> naujas;
		for(auto y : gr[x]){
			if(y == v) continue;
			naujas.push_back(y);
		}
		gr[x] = naujas;
	}
	for(auto x : kaims) calc(x);
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
	}
	calc(0);
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    return 0;
}
