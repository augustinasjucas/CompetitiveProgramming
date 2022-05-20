#include <iostream>
#include <vector>
using namespace std;
vector<vector<long long> > mat;
const long long mod = 666013;
vector<vector<long long> > sud(vector<vector<long long> > a, vector<vector<long long> > b){
    long long aa = a.size();
    long long bb = b.size();
    vector<vector<long long> > ats;
    ats.resize(aa);
    for(long long i = 0; i < aa; i++){
        for(long long j = 0; j < bb; j++) ats[i].push_back(0);
    }
    for(long long i = 0; i < a.size(); i++){ /// Per eilutes
        for(long long j = 0; j < b[0].size(); j++){ /// Per stulpelius
            long long atss = 0;
            for(long long h = 0; h < a[0].size(); h++){
                atss += ((a[i][h]%mod) * (b[h][j]%mod))%mod;
                atss %= mod;
            }
            ats[i][j] = atss;
        }
    
    }
    return ats;
}
vector<vector<long long> > kelk(vector<vector<long long> > a, long long k){
    if(k == 1) return a;
    vector<vector<long long> > b = kelk(a, k/2);
    if(k & 1) return sud(sud(b, b), a);
    else return sud(b, b);
}

int main(int argc, const char * argv[]) {
    long long n, k; cin >> n >> k;
    vector<vector<long long> > A = {{n-2ll, 1}, {n-1, 0}};
    vector<vector<long long> > B = {{0}, {1}};
    vector<vector<long long> > C = sud(kelk(A, k), B);
    cout << C[1][0];
    return 0;
}
