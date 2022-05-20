#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int dydis = 3e5+10;
const int lg = 19;
int lg2[dydis] = {0};
int n, k;
int st[dydis][lg];
int nk[dydis];
int mz[dydis];
int cnt[dydis];
int mx[dydis];
vector<int> kur[dydis];
vector<int> mas;
void build(){
    for(int i = 0; i < n; i++){
        st[i][0] = mas[i];
    }  
    for(int j = 1; j < lg; j++){
        for(int i = 0; i + (1 << (j-1)) < n; i++){
            st[i][j] = min(st[i][j-1], st[i+(1 << (j-1))][j-1]);
        }
    }
}
int mn(int l, int r){
    int ind = lg2[r-l+1];
//    cout << "ind = " << ind << endl;
    return min(st[l][ind], st[r-(1<<ind)+1][ind]);
}
int kai(int i){
    if(i == 0) return 0;
    int l = 0, r = i;
    int ret = inf;
    while(l <= r){
        int mid = (l+r)/2;
        if(mn(mid, i) == mas[i]){
            r = mid-1;
            ret = min(ret, mid);
        }else l = mid+1;
    }
    return ret;
}
int des(int i){
    int l = i, r= n-1;
    int ret = -1;
    while(l <= r){
        int mid = (l+r)/2;
        if(mn(i, mid) == mas[i]){
            l = mid+1;
            ret = max(ret, mid);
        }else r = mid-1;
    }   
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    int t; cin >> t;
    lg2[1] = 0;
    for(int i = 2; i < dydis; i++) lg2[i] = lg2[i/2]+1;
    while(t--){
        set<int> been, vs;
        cin >> n ;
        mas.resize(n);
        for(auto &x : mas){
            cin >> x; x--;
            been.insert(x);
        }
        vs = been;
        been.clear();
//        cout << "[";
//        for(auto x : been) cout << x << " "; cout << "]\n" << endl;
        for(int i = 0; i < n; i++){
            nk[i] = -1;
            kur[i].clear();
        }
        for(int i = 0; i < n; i++) kur[mas[i]].push_back(i);
        build();
        for(int i = 0; i < n; i++){
            nk[i] = -1;
            mz[i] = -1;
            for(auto x : kur[i]){
                int vt = x;
                int k = kai(vt);
                int d = des(vt);
                int nuoKada = 1;
                nuoKada = d-k+1;
                nk[i] = max(nk[i], nuoKada);
            }
       //     cout << i << ": " << endl;
            
            if(kur[i].size()){
         //       cout << "ce" << endl;
                int l = kur[i][0];
                int r = kur[i].back();
                if(mn(l, r) != i){
                    mz[i] = inf;
                    continue;
                }
                int k = kai(l);
                int d = des(r);
                if(k != 0 && d != n-1){
//                    cout  << "kai i = " << i+1 << ", " << k << " ir " << d << endl;
                    mz[i] = max(mz[i], d-k+1);
                }else{
                    if(d == n-1){
                        if(kur[i].back() != n-1) mz[i] = kur[i][0]-k+1;
                        else {
                        
                        }
                    }
                    if(k == 0){
                        if(kur[i][0] != 0) mz[i] = min(d-kur[i].back()+1, mz[i]);
                    }
                    if(k == 0 && d == n-1){
                        if(kur[i][0] == 0 || kur[i].back() == n-1){
                            
                        }else{
                       
                            mz[i] = n;
                        }
                    }
                    bool reik = 0;
                    for(auto x : kur[i]) if(x != 0 && x != n-1) reik = 1;
                    if(reik) mz[i] = n;
                    
     //                                   cout << i << ", elsas, " << k << ", " << d << ", tai " << kur[i][0]-k+1 << " ir " << d-kur[i].back()+1 << "-> " << mz[i] << endl;
                }
                mz[i] = max(mz[i], kur[i].back()-kur[i][0]+1);
            }  
            
        }
        vector<pair<int, pair<int, int> > > vec;
//        cout << "es " << endl;
        for(int i = 0; i < n; i++){


            cout << i +1<< " bus lygiai vienas tik [" <<  mz[i] << "; " << nk[i] << "]\n";
            if(nk[i] == -1 || mz[i] == -1) continue;
//            if(mz[i] != -1)
            if(mz[i] > nk[i]) continue;
            been.insert(i);
            vec.push_back({mz[i], {0, i}});
//            if(nk[i] != -1) 
                vec.push_back({nk[i]+1, {1, i}});
        }
        sort(vec.begin(), vec.end());
//        cout << "vec = "; for(auto x : vec) cout << "{" << x.first << "; " << x.second.second << "}   ";
//        cout << endl;
        int ind = 0;
        set<int> setas;
  //      cout << "esi " << endl;
        for(int i = 1; i <= n; i++){
            while(ind < vec.size() && vec[ind].first == i){
                been.erase(vec[ind].second.second);
                if(vec[ind].second.first){
                    setas.erase(vec[ind].second.second);
                }else{
                    setas.insert(vec[ind].second.second);
                }
                ind++;
            }
    //        cout <<been.empty() << ".  " <<  ind << "vs " << vec.size() << ".  " << "setas[" << i << "] = ["; for(auto x : setas) cout << x<< " "; cout << "]\n";
//            cout << "ans[" << i << "] = ";
            if(!setas.empty() && setas.size() == (*setas.rbegin()) + 1 && been.empty()){
                cout << 1;
            }else {
                if(i == 1 && vs.size() == n && (*vs.begin() == 0 && *setas.rbegin() == n-1)) cout << 1;
                else cout << 0;
            }
//            cout << endl;
        }
        cout << "\n";

    }
}
