#include <bits/stdc++.h>
#define int long long
#define MAXX 300005
using namespace std;

int n, x, a[MAXX], res;
int dp[MAXX][3];

void solve() {
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < 3; j++)
            dp[i][j] = -1e18;
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        dp[i][0] = max(0ll, dp[i - 1][0] + a[i]);
        dp[i][1] = max(dp[i][0], dp[i - 1][1] + a[i] * x);
        dp[i][2] = max(dp[i][1], dp[i - 1][2] + a[i]);
        res = max(res, dp[i][2]);
    }
    cout << res << "\n";
}

void read() {
    cin >> n >> x;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}