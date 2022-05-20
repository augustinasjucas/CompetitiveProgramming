#include <bits/stdc++.h>
using namespace std;
const int dydis = 2e5 + 19;
__int128_t inf = 1e18;
int desn[dydis];
vector<long long> mas;
int n;
long long k;
int main(){
    cin >> n >> k;
    mas.resize(n);
    for(auto &x : mas) cin >> x;
    int last = n;
    for(int i = n-1; i > -1; i--){
        if(mas[i] == 1){
            if(last == n) last = i;
        }else{
            last = n;
        }
        desn[i] = last;
    }
    __int128_t sand = 1;
    long long sm = 0;
    int ind = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
         // daugiau 60 tikrai nereikes
        ind = i-1;
        sand = 1;
        sm = 0;
        for(int j = 0; j < 60; j++){ 
            // dabar turiu [i; ind] intervala, ji didinsiu i desine per 1
            ind++;
            if(ind == n) break;
            if(mas[ind] != 1){
                sand *= mas[ind];
                sm += mas[ind]*k;
                if(sand >= inf) break;
                ans += sand == sm;
                if(sand == sm){
            //        cout << i << "; " << ind << " tinka, sand = " <<(long long) sand << ", sm = " << sm << endl;;
                }
            }else{ 
                int vnt = desn[ind] - ind + 1;
                if(sm < sand && sand <= sm + vnt * k && sm%k == sand%k){ // s < sand cia, nes jei s == sand, tai reiskia, kad pries tai jau bvo, tai jau kaip ir priskaiciauvau
                    ans++;
                }
                sm += vnt * k;
                ind = desn[ind];
            }
        }
    }
    cout << ans;
    
    return 0;
}
