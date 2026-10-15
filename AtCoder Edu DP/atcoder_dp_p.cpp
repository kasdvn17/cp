#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
#define MOD 1000000007
using namespace std;

int n, dp[MAXX][2];
vector<int> path[MAXX];

void dfs(int x, int p) {
    // cout << x << " " << path[x].size() << "\n";
    dp[x][0] = dp[x][1] = 1;
    for(auto v : path[x])
        if(v != p) {
            dfs(v, x);
            dp[x][0] = (dp[x][0] * (dp[v][0] + dp[v][1])) % MOD;
            dp[x][1] = (dp[x][1] * dp[v][0]) % MOD;
        }
}

void solve() {
    dfs(1, 0);
    cout << (dp[1][0] + dp[1][1]) % MOD;
}

void read() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}