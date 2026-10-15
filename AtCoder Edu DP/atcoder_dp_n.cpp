#include <bits/stdc++.h>
#define int long long
#define MAXX 1002
using namespace std;

int n, a[MAXX], dp[MAXX][MAXX];
int pf[MAXX];

void solve() {
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = 1e18;
    for(int i = 1; i <= n; i++) {
        pf[i] = pf[i - 1] + a[i];
        dp[i][i] = 0;
        if(i < n) dp[i][i + 1] = a[i] + a[i + 1];
    }
    for(int r = 3; r <= n; r++)
        for(int l = r - 2; l >= 1; l--) {
            for(int k = l; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + pf[r] - pf[l - 1]);
            // cout << l << " " << r << " " << dp[l][r] << "\n";
        }
    cout << dp[1][n];
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
}

void file() {
    if(fopen("TASK.INP", "r")) {
        freopen("TASK.INP", "r", stdin);
        freopen("TASK.OUT", "w", stdout);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    file();
    read();
    solve();
}