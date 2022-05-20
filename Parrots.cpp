#include <bits/stdc++.h>
using namespace std;
int f(int n){
	int sm = 0; int rez = -1;
	for(int j = 1; j <= 100; j++) {
		sm += j;
		if(sm > n){
			return j;
			break;
		}
	}
	return -1;
}
int f(int n, int bt){
	vector<int> vec;
	for(int i = 0; i < n; i++){
		vec.push_back(rand() % (1 << bt));
	}
	
	for(int i = 1; i < (1 << bt); i++){
		bool st = 1;
		for(auto x : vec) if((x & i) == i) st = 0;
		if(st) return i;
	}
	return -1;
	
}
int main(){
	srand(time(0));
	
	long double sm = 0;
	for(int i = 0; i < 50000; i++){
		sm += f(64, 8);
	}
	
	cout << sm / 50000.0 << endl << endl;
	
	long double k = 5;
	for(int i = 1; i <= 64; i++){
		cout << "n = " << i << ", tai reiks siusti blogiausiu atveju po ";
		int sm = 0; int rez = -1;
		for(int j = 1; j <= 100; j++) {
			sm += j;
			if(sm > i){
				rez = j;
				break;
			}
		}
		long double reik = 0;
		for(int j = 1; j <= i; j++) reik += log2(i);
		//cout << rez << ", kad paduotum viena dali informacijos!" << ", tai per n cia butu " << 1.0 * i / (1.0 * rez) << " padavimu!" << endl;
		int galiuIssiusti = (k-2) * i / (1.0 * rez); // kiek pilnu bloku galiu issiust
		int reiksPanaudotiBitu = ceil(log2(galiuIssiusti)); // kiek bitu reiks panaudoti pradzioje, kad isliktu eiliskumas?
		long double kiekBitu = (8-reiksPanaudotiBitu) * galiuIssiusti;
		cout << "tai vieno skaiciaus pozicijai nustatyti reiks " << ceil(ceil(log2(i)) / (8.0-1.0*reiksPanaudotiBitu)) << " zinuciu!" << ", tai viso zinuciu reiks " << i *  ceil(ceil(log2(i)) / (8.0-1.0*reiksPanaudotiBitu))  << ", o as ju turiu " << (k-2) * i << endl;
	}
	long double K = k;
	for(long double N = 1; N <= 64; N++){
		long double kek = f(N);
		long double reiks =  kek * N * (ceil((ceil(log2(N))) / (8 - ceil(log2(floor((N * (K-2) - 1) / (kek)))))));
		cout << "viso zinuciu reiks " << reiks << ", o as ju turiu " << N * (K-2) - 1 << endl;
	}
	return 0;
}
/*
 *  1) Issiunciu visus N skaiciu
 * 	2) Surandu kek = MEX(skaiciu_pasikartojimu_kiekiai)
 *  3) Issiunciu N+1 kartu skaiciu kek.
 *  4) po kek kartu siunciu skaicius tokia forma: [skaiciausNR][skaicius]
 *  5) susidarau tu skaiciu masyva. 
 *  6) is to masyvo isimu indeksus. Kiekvienas skaicius ten bus sudarytas is X is eiles einanciu skaiciu
 * 	   bitu konkatenacijos
 * 
 *
 * 	Isnaudosiu siuntimu:
 * 		N;
 * 		kek = f(N);
 *      po pirmu 3, galesiu siusti lygiai N*k - N - N - 1 = N * (K-2) - 1
 * 		taigi, pilnu bloku galesiu issiust floor((N * (K-2) - 1) / (kek))
 * 		taigi, ant [skaiciausNr] panaudosiu ceil(log2(floor((N * (K-2) - 1) / (kek)))) bitu
 * 		taigi, vienam skaiciui liks 8 - ceil(log2(floor((N * (K-2) - 1) / (kek)))) bitu
 * 		taigi, vieno skaiciaus pozicijai nustatyti reiks ceil((ceil(log2(N))) / (8 - ceil(log2(floor((N * (K-2) - 1) / (kek)))))) bitu
 * 		taigi, viso zinuciu teks siusti kek*N * (ceil((ceil(log2(N))) / (8 - ceil(log2(floor((N * (K-2) - 1) / (kek)))))))
 *		O as zinuciu siuntimu turiu N * (K-2) - 1
 * 
 * 	
 * 	1) Nusiunciu visus N skaiciu
 * 	2) Surandu min(ceil(log2(N)), 5.0) dydzio priesdeli, kuris nesikartoja
 *  3) 
 * 
 * */ 
