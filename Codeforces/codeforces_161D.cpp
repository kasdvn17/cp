#include <bits/stdc++.h>
#define MAXX 50002
#define MAX2 502
#define int long long
using namespace std;

int n, k, res, dp[MAXX][MAX2];
vector<int> path[MAXX];

void dfs(int x, int p)
{
    for (auto u : path[x])
        if (u != p)
        {
            dfs(u, x);
            for (int j = 0; j < k; j++)
                res += dp[x][j] * dp[u][k - j - 1];
            for (int j = 1; j <= k; j++)
                dp[x][j] += dp[u][j - 1];
        }
}

void solve()
{
    for (int i = 1; i <= n; i++)
        dp[i][0] = 1;
    dfs(1, 0);
    cout << res;
}

void read()
{
    cin >> n >> k;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}