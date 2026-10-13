#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, res, a[MAXX], cur[MAXX];
int dp[MAXX], bit[MAXX];

void update(int idx, int val) {
    while(idx <= n) {
        bit[idx] = max(bit[idx], val);
        idx += idx & (-idx);
    }
}

int query(int idx) {
    int res = 0;
    while(idx > 0) {
        res = max(res, bit[idx]);
        idx -= idx & (-idx);
    }
    return res;
}

void solve() {
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = max(query(a[i] - 2), cur[a[i]]) + a[i];
        update(a[i], dp[i]);
        cur[a[i]] = max(cur[a[i]], dp[i]);
        res = max(res, dp[i]);
    }
    cout << res;
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