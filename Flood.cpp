#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 2e4+ 10;
int n, m;
int dist[dydis * 2] ={};
const int inf = 1e9;
vector<pair<int, int> > pts, mas;
vector<pair<pair<int, int>, int> > vec, ms;
int kaim[dydis][4];
int plotas[dydis][2];
vector<int> gr[dydis];
/*
     0
   3 X 1
     2
     
      0
    -----
      1
     
      |
    0 | 1
      |
*/
vector<int> isores;
int dbInd = 0;
int f(int ind){
	if(ind == 0 || ind == 1) return 0;
	return 1;
}
void pr(int i1, int i2){
	cout << "[(" << pts[i1].first << "; " << pts[i1].second <<") -> (" << pts[i2].first << "; " << pts[i2].second << ")]"; 
}
string pus(int a){
	if(a == 0) return  "virsus";
	if(a == 1) return "kaire";
	if(a == 2) return "apacia";
	return "desine";
}
void daryk(int i1, int i2, int dir, int yraSonas, int side){
	//cout << "i1 = " << i1 << ", i2 = " << i2 << endl;
	if(i1 == -1 || i2 == -1) return;
	int i3 = lower_bound(ms.begin(), ms.end(), make_pair(make_pair(i1, i2), -1))->second;
	if(plotas[i3][f(side)] != -1) return;
	int orgi1 = i1, orgi2 = i2;
	if(yraSonas) isores.push_back(dbInd);
	// esu: 0 - virsuje, 1 - kaireje, 2 - apacioje, 3 - desineje
	//cout << "pradedu nuo "; pr(i1, i2); cout << endl;
	int it = 0;
	vector<pair<pair<int, int>, int> > neliesta;
	while(true){
	//	if(it++ > 100) break;
		//cout << "esu "; pr(i1, i2); cout << ", puse yra " << pus(side) << endl; 
		int i3 = lower_bound(ms.begin(), ms.end(), make_pair(make_pair(i1, i2), -1))->second;
		plotas[i3][f(side)] = dbInd;
		int bv = 0;
		for(int i = 0; i < 4; i++) if(kaim[i2][i] == i1) bv = i;
		neliesta.push_back({{i1, i2}, (side+2)%4});
		for(int i = 1; i <= 4; i++){
			int bs = (i*dir + bv + 4) % 4;
			if(kaim[i2][bs] == -1) continue;
			int i4 = kaim[i2][bs];
			if(i != 2 && i != 4) side = (side+i*dir+8)%4;
			else if(i == 4) side = (side+2*dir+8)%4;
			i1 = i2;
			i2 = i4;
			break;
		}
		if(i1 == orgi1 && i2 == orgi2) break;
	}
	dbInd++;
	for(auto x : neliesta){
		int i1 = x.first.first;
		int i2 = x.first.second;
		int dirr = -dir;
		int side = x.second;
		daryk(i1, i2, dirr, 0, side);
	}
}

void darom(int i1, int i2){
	//daryk(i1, i2, +1, 0, (pts[i1].first == pts[i2].first ? 3 : 0));
	daryk(i1, i2, -1, 1, (pts[i1].first == pts[i2].first ? 1 : 2));
	
}
int main(){
	for(auto &x : dist) x = inf;
	for(int i = 0; i < dydis; i++){
		for(int j = 0; j < 4; j++){
			kaim[i][j] = -1;
			plotas[i][j/2] = -1;
		}
	}
	cin >> m;
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b;
		pts.push_back({a, b});
		vec.push_back({{a, b}, i});
	}
	sort(vec.begin(), vec.end());
	cin >> n;
	for(int i = 0; i < n; i++){
		int a, b; cin >> a >> b; a--; b--;
		int x1 = pts[a].first;
		int y1 = pts[a].second;
		int x2 = pts[b].first;
		int y2 = pts[b].second;
		if(x1 == x2){ // vertikalu
			if(y1 > y2){
				swap(y1, y2);
				swap(a, b);
			}
			// dabar a zemiau uz b
			kaim[a][0] = b;
			kaim[b][2] = a;
		}else{
			if(x1 > x2){
				swap(x1, x2);
				swap(a, b);
			}
			// dabar a yra kairiau uz b 
			kaim[a][1] = b;
			kaim[b][3] = a;
		}
		mas.push_back({a, b});
		ms.push_back({{a, b}, i});
		ms.push_back({{b, a}, i});
	}
	sort(ms.begin(), ms.end());
	for(auto x : vec){
		int ind = x.second;
		darom(ind, kaim[ind][1]); // briauna i desine
		darom(ind, kaim[ind][0]); // briauna i virsu
	}
	for(int i = 0; i < n; i++){
		gr[plotas[i][0]].push_back(plotas[i][1]);
		gr[plotas[i][1]].push_back(plotas[i][0]);
	}
	queue<int> q;
	for(auto x : isores) {dist[x] = 0; q.push(x);}
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(auto x : gr[v]){
			if(dist[x] > dist[v] + 1){
				dist[x] = dist[v] + 1;
				q.push(x);
			}
		}
	}
	vector<int> ans;
	for(int i = 0; i < n; i++){
		if(dist[plotas[i][0]] == dist[plotas[i][1]]) ans.push_back(i+1);
	}
	cout << ans.size() << "\n";
	for(auto x : ans) cout << x << " ";
	return 0;
}
