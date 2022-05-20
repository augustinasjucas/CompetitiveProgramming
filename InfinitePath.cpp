#include <bits/stdc++.h>
using namespace std;
vector<int> mas, col, vis;
int n;
int explore(int ind){
 //   cout << "bandau " << ind << endl;
    vector<int> vec;
    vector<int> cl;
    int db = ind;
    while(true){
        cl.push_back(col[db]);
        vec.push_back(db);
        db = mas[db];
        vis[db] = 1;
        if(db == ind) break;
    }
    // vienas pakelimas yra shiftas i kaire
//    cout << "gaunu spalvas = ["; for(auto x : cl) cout << x << " "; cout << "]\n";
    if(cl.size() == 1) return 1;
    for(int i = 1; i <= cl.size(); i++){
        if(vec.size() % i != 0) continue;
//        cout << "jei shiftinsiu per " << i-1 << " i kaire, susidarys " << i << " grupiu\n"; 
        for(int j = 0; j < i; j++){
            bool tinka = 1; int spalva = cl[j];
            for(int h = (j + i) % vec.size(); h != j; h = (h + i)%vec.size()){
                if(spalva != cl[h]) tinka = 0;
            }
            if(tinka) return i;
        }
    }
    return -1;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        cin >> n;
        mas.resize(n);
        col.resize(n);
        vis.resize(n);
        for(int i = 0; i < n; i++) vis[i] = 0;
        for(int i = 0; i < n; i++) cin >> mas[i];
        for(int i = 0; i < n; i++) cin >> col[i];
        for(int i = 0; i < n; i++) mas[i]--;
        int ans = n;
        for(int i = 0; i < n; i++){
            if(vis[i]) continue;
            ans = min(ans, explore(i));
        }
        cout << ans << "\n";
    }
    return 0;
}
