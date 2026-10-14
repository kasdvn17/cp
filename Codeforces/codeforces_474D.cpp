#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
#define MOD 1000000007
using namespace std;

int t, k, a, b;
int dp[MAXX], pf[MAXX];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    dp[0] = pf[0] = 1;
    cin >> t >> k;
    for(int i = 1; i <= 100000; i++) {
        dp[i] = dp[i - 1];
        if(i >= k)
            dp[i] += dp[i - k];
        dp[i] %= MOD;
        pf[i] = (pf[i - 1] + dp[i]) % MOD;
    }
    while(t--) {
        cin >> a >> b;
        cout << ((pf[b] - pf[a - 1]) % MOD + MOD) % MOD << "\n";
    }
}