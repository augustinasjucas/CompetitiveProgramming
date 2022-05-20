#include <bits/stdc++.h>
using namespace std;
vector<int> inv(vector<int> a){
    for(auto &x : a) x = !x;
    return a;
}
vector<int> proc(vector<int> a){
    vector<int> ret;
    for(int i = 0; i < a.size(); i++){
        if(a[i] == 0){
            ret.push_back(0);
            continue;
        }
        for(int j = i; j <= a.size(); j++){
            if(j == a.size() || a[i] != a[j]){
                if((j-i) & 1)ret.push_back(1);
                for(int h = 0; h < j-i-((j-i)&1); h++) ret.push_back(0);
                i = j-1;
                break;
            }
        }
    }
    return ret;
}
int main(){
    int n;
    cin >> n;
    int sm = 0;
    vector<int> vec;
    for(int i = 0; i < n; i++){
        int a; cin >> a; a = (a & 1);
        vec.push_back(a);
        sm += a;
    }
    if(n % 2 == 0){
        if(sm & 1){
            cout << "NO";
            return 0;
        }
    }else{ // (n & 1)
        if(sm & 1){ // vienetu nelyginis, tai ju visu nepasalinsiu
            vec = inv(vec);
        }
    }
    // ar galiu visus 1 paversti nuliais?
    vec = proc(vec);
    deque<int> index;
    int lg = 0, nlg = 0;
    for(int i = 0; i < n; i++){
        if(vec[i]){
            index.push_back(i);
            lg += !(i & 1);
            nlg += (i & 1);
        }
    }
    if(lg == nlg){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}
