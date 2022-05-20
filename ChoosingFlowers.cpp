#include <bits/stdc++.h>
using namespace std;
using ll = long double;
using ld =  long double;

ll inf = 5000000000000000000;

bool pagalka = true;

struct atk {
    long long a, k;
    ld fr;
    atk(ld a, ld k, ld fr) : a(a), k(k), fr(fr) {}
    bool operator<(const atk &o)const {
        if (pagalka) {
            return k > o.k;
        }
        else {
            return fr < o.fr;
        }
    }
    ld inter(const atk &o)const {
        return (long double)1.0 * (a - o.a) / (o.k - k);
    }
};
struct atkarpos {
    set<atk> v;
    void add(ld a, ld k) {
        pagalka = true;

        if (v.empty()) {
            v.insert(atk(a, k, 0));
        }
        else {
            pagalka = true;
            atk up(a, k, 0);
            auto vieta = v.lower_bound(up);

            for (; vieta != v.end();) {
                if (v.empty()) {
                    break;
                }

                if (vieta->k == k) {
                    if (vieta->a <= a) {
                        break;
                    }

                    v.erase(vieta++);
                    continue;
                }

                /// vieta 'k' kofas >= low 'k' kogas
                auto pvz = vieta;
                pvz++;
                ld to = inf;

                if (pvz != v.end()) {
                    to = pvz->fr;
                }

                ld intersection = up.inter(*vieta); /// tai reiskia, kad up < vieta, kai x yra [0; intersection]

                /// vieta x priklauso [fr; to]
                /// tada up < vieta, kai x bus [fr, min(to, intersection)]
                if (min(to, intersection) <= vieta->fr) { /// up > vieta
                    break;
                }
                else if (intersection >= to) {
                    v.erase(vieta++);
                }
                else {
                    auto past = *vieta;
                    past.fr = intersection;
                    v.erase(vieta++);
                    v.insert(past);
                    break;
                }
            }

            ld manoFr = inf;
            vieta = v.lower_bound(up);

            if (vieta != v.begin()) {
                vieta--;

                for (; vieta != v.end();) {
                    if (v.empty()) {
                        break;
                    }

                    if (vieta->k == k) {
                        if (vieta->a <= a) {
                            break;
                        }

                        v.erase(vieta--);
                        continue;
                    }

                    /// vieta 'k' kofas >= low 'k' kogas
                    auto pvz = vieta;
                    pvz++;
                    ld to = inf;

                    if (pvz != v.end()) {
                        to = pvz->fr;
                    }

                    ld intersection = up.inter(*vieta); /// tai reiskia, kad up < vieta, kai x yra [intersection; inf]

                    /// vieta x priklauso [fr; to]
                    /// tada up < vieta, kai x bus [max(fr, intersection), to]
                    if (max(vieta->fr, intersection) >= to) { /// up > vieta
                        break;
                    }
                    else if (intersection <= vieta->fr) {
//                        cout << "pilnai\n";
                        manoFr = vieta->fr;

                        if (vieta == v.begin()) {
                            v.erase(vieta);
                            break;
                        }

                        v.erase(vieta--);

                    }
                    else {
                        manoFr = intersection;
                        break;
                    }
                }
            }
            else {
                if (v.begin()->fr != 0) {
                    manoFr = 0;
                }
            }

            if (manoFr != inf)v.insert({a, k, manoFr});
        }
    }
    long long getmin(long long x) {
        pagalka = false;
        auto vieta = v.lower_bound({0, 0, (ld)x});

        if (vieta->fr != x) {
            vieta--;
        }

        return vieta->k * x + vieta->a;
    }

    void print() {
        for (auto x : v) {
            cout << x.k << "x + " << x.a << ". Prasideda " << x.fr << endl;
        }
    }
};

int n, m;
vector<pair<long long, long long> > mas;
int main(){
    int t; cin >> t;
    while(t--){
        mas.clear();
        cin >> n >> m;
        vector<pair<long long, long long> > vec(m);
        for(auto &x : vec){
            cin >> x.first >> x.second;
        }
        sort(vec.begin(), vec.end());
        mas = vec;
        int k = mas.size();
        atkarpos str;
        long long pref[k];
        for(int i = 0; i < k; i++){
            str.add(-(mas[i].first-mas[i].second), -mas[i].second);
            int imsiu = n-(k-i-1);
            pref[i] = -str.getmin(imsiu);
        }
        long long ans = 0;
        long long curMaxB = 0;
        long long s = 0;
        ans = pref[k-1];
        for(int i = k-1; i > -1; i--){
            s += mas[i].first;
            long long taken = k-i;
            long long left = n-taken;
            ans = max(ans, s);
            if(left == 0) break;
            curMaxB = max(curMaxB, mas[i].second);
            long long p1 = s + left * curMaxB;
            long long p2 = s + (i == 0 ? 0ll : pref[i-1]);
            ans = max(ans, max(p1, p2));
        }
        cout << ans << "\n";
    }
    return 0;
}
