#include <bits/stdc++.h>
#define MOD 998244353
#define MAXX 600005
using namespace std;

int n, a[MAXX], seen[MAXX];
int dp[8][3], ndp[8][3];

void solve() {
    memset(seen, 0, sizeof(seen));
    memset(dp, 0, sizeof(dp));
    memset(ndp, 0, sizeof(ndp));
    for(int i = 1; i <= n; i++)
        seen[a[i]] = true;
    int mxx = a[n];
    dp[0][0] = 1;
    for(int i = 1; i <= mxx + 3; i++) {
        for(int mask = 0; mask < 8; mask++)
            for(int bad = 0; bad < 3; bad++) {
                if(!dp[mask][bad])
                    continue;
                for(int lay = 0; lay < 2; lay++) {
                    if(lay == 1 && !seen[i])
                        continue;
                    int nbad = bad;
                    if(mask & 1) {
                        // co lay i
                        int cnt = (mask >> 1 & 1) + (mask >> 2 & 1) + lay;
                        if(cnt != 2) nbad++;
                    }
                    if(nbad > 2)
                        continue;
                    int nmask = ((mask >> 1) & 3) | (lay << 2);
                    ndp[nmask][nbad] = (ndp[nmask][nbad] + dp[mask][bad]) % MOD;
                }
            }
        for(int mask = 0; mask < 8; mask++)
            for(int bad = 0; bad < 3; bad++)
                dp[mask][bad] = ndp[mask][bad], ndp[mask][bad] = 0;
    }
    int res = 0;
    for(int mask = 0; mask < 8; mask++)
        for(int bad = 0; bad < 3; bad++)
            res = (res + dp[mask][bad]) % MOD;
    cout << (res - 1 + MOD) % MOD << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}