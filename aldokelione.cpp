#include <bits/stdc++.h>
using namespace std;
const int dydis = 3e5;
const long long inf = 1e18;
int n;
long long b[dydis];
long long a[dydis];
long long dp[dydis];
vector<int> gr[dydis];
multiset<pair<long long, long long> > vec;
struct lichao{               // li chao
    vector<pair<long long, long long> > lines;
    vector<int> left, right;
    int n;
    int dbInd = 0;
    lichao(int dd){
        n = dd;
        int kek = 5e6;
        
        lines.resize(kek);
        left.resize(kek);
        right.resize(kek);

        for(int i = 0; i < lines.size(); i++){
            lines[i].first = 0;
            lines[i].second = inf;
            left[i] = 2*i;
            right[i] = 2 * i + 1; 
        }
        dbInd = 4 * dd + 1;
    }
    long long f(pair<long long, long> a, long long x){
        return a.first * x + a.second;
    }
    
    int newN(int l, int r, pair<long long, long long> val){
        lines[dbInd] = val;
        left[dbInd] = l;
        right[dbInd] = r;
        return dbInd++;
    }
    
    void add(int v, int l, int r, pair<long long, long long> line){
        long long mid = (l + r) / 2;
        
        long long f1 = f(lines[v], mid);
        long long f2 = f(line, mid);
        if(f2 < f1){
            swap(f1, f2);
            swap(line, lines[v]);
        }
        bool goLeft = f(lines[v], l) > f(line, l);

        if(l == r) return ;
        
        if(goLeft){
            left[v] = newN(left[left[v]], right[left[v]], lines[left[v]]);
            add(left[v], l, mid, line);
        }else {
            right[v] = newN(left[right[v]], right[right[v]], lines[right[v]]);
            add(right[v], mid+1, r, line);
        }
    }
    long long get(int v, int l, int r, long long x){
        long long mid = (l + r) / 2;
        if(l == r){
            return f(lines[v], x);
        }
        if(x < mid){
            return min(f(lines[v], x), get(left[v], l, mid, x));
        }else{
            return min(f(lines[v], x), get(right[v], mid+1, r, x));
        }
    }
};
lichao hull(dydis);
vector<int> roots = {1};
void putIn(long long k, long long b){
    int r = roots.back();
    roots.push_back(hull.newN(hull.left[r], hull.right[r], hull.lines[r]));
    hull.add(roots.back(), 0, dydis-1, {k, b});
}
void takeOut(long long k, long long b){
    roots.pop_back();
}
long long findMin(long long x){
    return hull.get(roots.back(), 0, dydis-1, x);
}
void dfs(int v, int came, int h){
    if(v == 0){
        dp[v] = a[v];
    }else{
        dp[v] = findMin(h) + a[v];
    }
    
    putIn(b[v], dp[v] - 1ll * b[v] * h);

    for(auto x : gr[v]){
        if(x == came) continue;
        dfs(x, v, h + 1);
    }
    takeOut(b[v], dp[v] - 1ll * b[v] * h);

}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 1; i < n; i++){
        int a; cin >> a;
        gr[i].push_back(a);
        gr[a].push_back(i);
    }
    dfs(0, -1, 0);
    for(int i = 0; i < n; i++){
        cout << dp[i] << " ";
    }
    return 0;
}
