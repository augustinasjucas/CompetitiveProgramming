#include <bits/stdc++.h>
using namespace std;
const int dydis = 1e5 + 10;
int n, k;
int playerCount[dydis] = {};
int cardCount[dydis] = {};
int reward[20] = {};
int dp[5010][5011];
const int inf = 1e9;
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 0; i < n*k; i++) {
        int a; cin >> a;
        cardCount[a]++;
    }
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        playerCount[a]++;
    }
    for(int i = 1; i <= k; i++) {
        cin >> reward[i];
    }
    int ans = 0;
    for(int i = 0; i < dydis; i++) {
        if(playerCount[i] == 0 || cardCount[i] == 0) continue;
        int players = playerCount[i];
        int cards = cardCount[i];
        // dp[i][j] - viso turiu j korteliu ir zaideju turiu i. Kokia max h suma?
        for(int i = 0; i <= players; i++) {
            for(int j = 0; j <= cards; j++) {
                dp[i][j] = -inf;
            }
        }
        dp[players][cards] = 0;
        for(int i = players; i > 0; i--) {
            for(int j = 0; j <= cards; j++) {
                if(dp[i][j] == -inf) continue;
                for(int h = 0; h <= min(10, j); h++) {
                    dp[i-1][j-h] = max(dp[i-1][j-h], dp[i][j] + reward[h]);
                }
            }
        }
        int st = 0;
        for(int i = 0; i <= players; i++) {
            for(int j = 0; j <= cards; j++) {
                st = max(st, dp[i][j]);
            }
        }
        ans =ans + st;
    }
    cout << ans;

    return 0;
}
