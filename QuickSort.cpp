#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> mas;
//int it = 0;
void dar(vector<int> &mas, int l, int r){
	//if(it++ > 100) exit(0);
	//cout << "mas: "; for(auto x : mas) cout << x << " "; cout << " | l = " << l << ", r = " << r<< endl;
	vector<int> a, b;
	for(int i = l; i <= r; i += 2){
		b.push_back(mas[i]);
	}
	for(int i = l+1; i <= r; i += 2){
		a.push_back(mas[i]);
	}
	int i1 = 0, i2 = 0;
	for(int i = l; i <= r; i++){
		if(i1 < (int)a.size()){
			mas[i] = a[i1++];
		}else{
			mas[i] = b[i2++];
		}
	}
	//cout << endl << "tada mas: "; for(auto x : mas) cout << x << " ";
	//cout << endl << endl;
}
vector<pair<int, int> > ans(vector<int> mas){	

	vector<pair<int, int> > ret;
	if(n > 1000){
		for(int i = 0; i < n; i += 3){
			int rnd = min(i + rand() % (n-i), n-1);
			ret.push_back({i, rnd});
			dar(mas, i, rnd);in
		}
	}
	for(int i = 0; i < n; i++){
		while(true){
			int kr = 0;
			for(int j = i; j < n; j++){
				if(mas[j] == i) {
					kr = j;
					break;
				}
			}
			if(kr == i) break;
			if((kr - i) % 2 == 0) {
				ret.push_back({kr-1, kr});
				dar(mas, kr-1, kr);
			}
			ret.push_back({i, kr});
			dar(mas, i, kr);
		}
	}
	return ret;
}
int main(){
	cin >> n;
	mas.resize(n);
	for(int i = 0; i < n; i++) {
		cin >> mas[i];
		mas[i]--;
	}
	
	auto aa = ans(mas);
	cout << aa.size() << "\n";
	for(auto x : aa){
		cout << x.first + 1 << " " << x.second + 1 << "\n";
	}
	return 0;
}
