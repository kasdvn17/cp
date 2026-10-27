#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int k, n, dp[MAXX][2], choosen[MAXX];
vector<int> path[MAXX];
vector<tuple<int, int, int, int>> res;

void dfs(int x, int p) {
    dp[x][1] = 1;
    for(int v : path[x]) {
        if(v == p)
            continue;
        dfs(v, x);
        dp[x][1] += dp[v][0];
        dp[x][0] += max(dp[v][0], dp[v][1]);
    }
}

void solve() {
    res.clear();
    cin >> k;
    int in2d = -1;
    for(int i = 1; i <= k; i++) {
        cin >> n;
        if(n >= 2 && in2d == -1) in2d = i;
        if(n == 1)
            continue;
        for(int i = 1; i <= n; i++)
            path[i].clear(), dp[i][0] = dp[i][1] = 0;
        for(int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            path[u].push_back(v);
            path[v].push_back(u);
        }
        dfs(1, 0);
        if(dp[1][0] >= dp[1][1]) {
            choosen[i] = 1;
        } else {
            choosen[i] = path[1][0];
        }
    }
    if(in2d == -1) {
        for(int i = 2; i <= k; i++)
            res.push_back({1, 1, i, 1});
    } else {
        for(int i = 1; i <= k; i++) {
            if(i == in2d)
                continue;
            res.push_back({in2d, choosen[in2d], i, 1});
        }
    }
    for(auto [t1, v1, t2, v2] : res)
        cout << t1 << " " << v1 << " " << t2 << " " << v2 << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--)
        solve();
}