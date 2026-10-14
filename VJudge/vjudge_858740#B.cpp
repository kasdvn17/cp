#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, k, sm, a[MAXX];
int dp[MAXX];
deque<int> dq;

void solve() {
    for(int i = 1; i <= n + 1; i++)
        dp[i] = 1e18;
    dq.push_back(0);
    for(int i = 1; i <= n + 1; i++) {
        // for(int j = i - 1; j >= max(0ll, i - k - 1); j--)
            // dp[i] = min(dp[i], dp[j] + a[i]);
        sm += a[i];
        while(dq.size() && dq.front() < max(0ll, i - k - 1))
            dq.pop_front();
        dp[i] = dp[dq.front()] + a[i];
        while(dq.size() && dp[dq.back()] >= dp[i])
            dq.pop_back();
        dq.push_back(i);
        // cout << i << " " << dp[i] << "\n";
    }
    cout << sm - dp[n + 1];
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