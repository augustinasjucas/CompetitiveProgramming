
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
using namespace std;

set<pair<int, int> > curPts;
vector<pair<int, int> > pts;
vector<pair<int, int> > eil;
int n;
int ret;
int kekPo(int &x, int &y){
	if(x == -1 && y == -1) return 0;
	ret = 0;
	for(auto x : curPts){
		ret += x.second < y;
	}
	return ret;
}
int kekVirs(int &x, int &y){
	if(x == -1 && y == -1) return 0;
	ret = 0;
	for(auto x : curPts){
		ret += x.second > y;
	}
	return ret;
}
int kekKair(int &X, int &y){
	if(X == -1 && y == -1) return 0;
	ret = 0;
	for(auto x : curPts){
		ret += x.first < X;
	}
	return ret;
}
int kekDesn(int &X, int &y){
	if(X == -1 && y == -1) return 0;
	ret = 0;
	for(auto x : curPts){
		ret += x.first > X;
	}
	return ret;
}
pair<int, int> kair, des, auk, zem;
int kv, kp, kk, kd;
int it = 0;
void donext(int X, int Y, int camedir, int lastX, int lastY){
	if(curPts.size() % 1000 == 0){
		cout << n-curPts.size() << " / " << n << "\n";
	}
	it = 0;
	curPts.erase({X, Y});
	//cout << "es u " << X << " " << Y << ", sz = " << curPts.size() << "prm " << curPts.begin()->first << ", " << curPts.begin()->second<< endl;
	if(curPts.size() == 0){ 
		//cout << "dedu " << X << " " << Y << endl;
		eil.push_back({X, Y});
		return;
	}
	if(X == -1 && Y == -1){
		X = curPts.begin() -> first;
		Y = curPts.begin() -> second;
		eil.push_back({lastX, Y});
		if(lastX > X) camedir = 2;
		else camedir = 0;
	//	cout << "priejau -1 -1, tai X = " << X << ", Y = " << Y << ", lastX = " << lastX << ", lastY = " << lastY << endl;
		curPts.erase({X, Y});
		if(curPts.size() == 0) {
			eil.push_back({X, Y});
			return;
		}
		lastY = Y;
		//cout << "pratesus, X = " << X << ", Y = " << Y << ", lastX = "  << lastX << ", LastY = " << lastY << endl;
	}
//	cout << "pries darant X = " << X << ", Y = " << Y << endl;
	
	if(camedir == 0){ // atejo is kaires
		auk = {-1, -1}, zem = {-1, -1};
	//	cout << "atejau is kaires i " << X << "; " << Y << endl;
		for(auto &x : curPts){
			
			if(x.first < X) continue;
			if(it++ > 100 && curPts.size() > 100) break;
			if(x.second > Y){ // sitas yra auksciau
				if(auk == make_pair(-1, -1)) auk = x;
				if(x.second < auk.second) auk = x;
			}else{ // sitas yra zemiau
				if(zem == make_pair(-1, -1)) zem = x;
				if(x.second > zem.second) zem = x;
			}
		}
		//cout << "pirmas zemiau yra " << zem.first << " " << zem.second << endl;
		kv = kekVirs(auk.first, auk.second);
		kp = kekPo(zem.first, zem.second);
		if(auk.first == -1 && zem.first == -1){
			eil.push_back({X, Y});
		//	cout << "donext, " << X << " " << Y << endl
			donext(-1, -1, 0, X, Y);
			return ;
		}
		if((auk.first != -1 && kv > kp) || zem.first == -1){
			curPts.erase(auk);
			eil.push_back({auk.first, lastY});
			donext(auk.first, auk.second, 3, auk.first, lastY);
		}else{
			curPts.erase(zem);
			eil.push_back({zem.first, lastY});
			donext(zem.first, zem.second, 1, zem.first, lastY);
		}
	}else if(camedir == 1){ // atejo is virsaus
		//cout << "atejau is virsaus i " << X << "; " << Y << endl;
		kair = {-1, -1}, des = {-1, -1};
		for(auto &x : curPts){
			
			if(x.second > Y) continue;
			if(it++ > 100 && curPts.size() > 100) break;
			if(x.first > X){ // sitas yra desiniau
				if(des == make_pair(-1, -1)) des = x;
				if(x.first < des.first) des = x;
			}else{ // sitas yra zemiau
				if(kair == make_pair(-1, -1)) kair = x;
				if(x.first > kair.first) kair = x;
			}
		}
		//cout << "kaireje yra " << kair.first << " " << kair.second << endl;
		kk = kekKair(kair.first, kair.second);
		kd = kekDesn(des.first, des.second);
		if(kair.first == -1 && des.first == -1){
			eil.push_back({X, Y});
		//	cout << "donext, " << X << " " << Y << endl;
			donext(-1, -1, 0, X, Y);
			return ;
		}
		if((kair.first != -1 && kk > kd) || des.first == -1){
			curPts.erase(kair);
			eil.push_back({lastX, kair.second});
			donext(kair.first, kair.second, 2, lastX, kair.second);
		}else{
			curPts.erase(des);
			eil.push_back({lastX, des.second});
			donext(des.first, des.second, 0, lastX, des.second);
		}	
	}else if(camedir == 2){ // atejo is desines
	//	cout << "atejau is desines i " << X << "; " << Y << endl;
		auk = {-1, -1}, zem = {-1, -1};
		for(auto &x : curPts){
			if(x.first > X) continue;
			if(it++ > 100 && curPts.size() > 100) break;
			if(x.second > Y){ // sitas yra auksciau
				if(auk == make_pair(-1, -1)) auk = x;
				if(x.second < auk.second) auk = x;
			}else{ // sitas yra zemiau
				if(zem == make_pair(-1, -1)) zem = x;
				if(x.second > zem.second) zem = x;
			}
		}
		kv = kekVirs(auk.first, auk.second);
		kp = kekPo(zem.first, zem.second);
		if(auk.first == -1 && zem.first == -1){
			eil.push_back({X, Y});
		//	cout << "donext, " << X << " " << Y << endl;
			donext(-1, -1, 0, X, Y);
			return ;
		}
		if((auk.first != -1 && kv > kp) || zem.first == -1){
			curPts.erase(auk);
			eil.push_back({auk.first, lastY});
			donext(auk.first, auk.second, 3, auk.first, lastY);
		}else{
			curPts.erase(zem);
			eil.push_back({zem.first, lastY});
			donext(zem.first, zem.second, 1, zem.first, lastY);
		}
	}else{ // is apacios
	//	cout << "atejau is apacios i " << X << "; " << Y << endl;
		kair = {-1, -1}, des = {-1, -1};
		for(auto & x : curPts){
			if(x.second < Y) continue;
			if(it++ > 100 && curPts.size() > 100) break;
			if(x.first > X){ // sitas yra desiniau
				if(des == make_pair(-1, -1)) des = x;
				if(x.first < des.first) des = x;
			}else{ // sitas yra zemiau
				if(kair == make_pair(-1, -1)) kair = x;
				if(x.first > kair.first) kair = x;
			}
		}
		kk = kekKair(kair.first, kair.second);
		kd = kekDesn(des.first, des.second);
		if(kair.first == -1 && des.first == -1){
			eil.push_back({X, Y});
		//	cout << "donext, " << X << " " << Y << endl;

			donext(-1, -1, 0, X, Y);
			return ;
		}
		if((kair.first != -1 && kk > kd) || des.first == -1){
			curPts.erase(kair);
			eil.push_back({lastX, kair.second});
			donext(kair.first, kair.second, 2, lastX, kair.second);
		}else{
			curPts.erase(des);
			eil.push_back({lastX, des.second});
			donext(des.first, des.second, 0, lastX, des.second);
		}	
	}
}
int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		int a, b; cin >> a >> b;
		curPts.insert({a, b});
	}
	string inp = "out-06-11.txt";

	cout << inp << endl;
	donext(0, 0, 3, 0, 0);
	ofstream out(inp);
	out << eil.size() << endl;
	for(auto x : eil){
		out << x.first << " " << x.second << endl;
	}
	return 0;
}
