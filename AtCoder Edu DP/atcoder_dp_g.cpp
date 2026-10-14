#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, m, res, dp[MAXX];
vector<int> path[MAXX];

int dfs(int x) {
    if(dp[x]) return dp[x];
    for(auto v : path[x]) {
        dp[v] = dfs(v);
        dp[x] = max(dp[x], dp[v] + 1);
    }
    res = max(res, dp[x]);
    return dp[x];
}

void solve() {
    for(int i = 1; i <= n; i++)
        if(!dp[i]) dfs(i);
    cout << res;
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
    }
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