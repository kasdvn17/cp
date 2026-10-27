#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, a[MAXX];
int res, dp[MAXX];

void solve() {
    res = 0;
    for(int i = 1; i <= n; i++) {
        dp[i] = a[i];
        for(int j = i - 1; j >= 1; j--)
            if(abs(i - j) > max(a[i], a[j]))
                dp[i] = max(dp[i], dp[j] + a[i]);
        res = max(res, dp[i]);
    }
    cout << res << "\n";
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