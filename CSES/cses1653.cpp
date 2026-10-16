#include <bits/stdc++.h>
#define int long long
#define MAXX 22
#define MAX2 2000002
using namespace std;

int n, w, a[MAXX];
pair<int, int> dp[MAX2]; // so elevator da dung - da dung it nhat bao nhieu weight trog elev hien tai

void solve() {
    for(int i = 0; i < (1 << n); i++)
        dp[i] = {1e9, 1e9};
    dp[0] = {1, 0};
    for(int mask = 0; mask < (1 << n); mask++) {
        if(dp[mask].first >= 1e9)
                continue;
        for(int i = 1; i <= n; i++) {
            if(mask >> (i - 1) & 1)
                continue;
            if(dp[mask].first >= 1e9)
                continue;
            int nmask = mask | (1 << (i - 1)), n1, n2;
            if(dp[mask].second + a[i] > w)
                n1 = dp[mask].first + 1, n2 = a[i];
            else
                n1 = dp[mask].first, n2 = dp[mask].second + a[i];
            dp[nmask] = min(dp[nmask], {n1, n2});
        }
    }
    pair<int, int> v = dp[(1 << n) - 1];
    // cout << v.first << " " << v.second << "\n";
    cout << v.first;
}

void read() {
    cin >> n >> w;
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