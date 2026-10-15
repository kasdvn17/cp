#include <bits/stdc++.h>
#define int long long
#define MAX1 102
#define MAX2 100002
#define MOD 1000000007
using namespace std;

int n, k, a[MAX1];
int dp[MAX1][MAX2], pf[MAX2];

void solve() {
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        pf[0] = 1;
        for(int j = 1; j <= k; j++)
            pf[j] = (pf[j - 1] + dp[i - 1][j]) % MOD;
        for(int j = 0; j <= k; j++) {
            dp[i][j] = pf[j];
            if(j > a[i]) dp[i][j] -= pf[j - a[i] - 1];
            dp[i][j] %= MOD;
        }
    }
    cout << (dp[n][k] + MOD) % MOD;
}

void read() {
    cin >> n >> k;
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