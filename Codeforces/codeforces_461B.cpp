#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
#define MOD 1000000007
using namespace std;

int n, a[MAXX];
int dp[MAXX][2];
vector<int> path[MAXX];

void dfs(int x, int p) {
    dp[x][0] = 1;
    dp[x][1] = 0;
    for(auto v : path[x]) {
        if(v == p)
            continue;
        dfs(v, x);
        dp[x][1] = (dp[x][1] * dp[v][0] + ((dp[v][1] * dp[x][0]) % MOD)) % MOD;
        dp[x][0] = (dp[x][0] * dp[v][0]) % MOD;
    }
    if(a[x] == 1)
        dp[x][1] = dp[x][0];
    else
        dp[x][0] += dp[x][1], dp[x][0] %= MOD;
}

void solve() {
    dfs(0, 0);
    cout << dp[0][1];
}

void read() {
    cin >> n;
    for(int i = 1; i <= n - 1; i++) {
        int u;
        cin >> u;
        path[u].push_back(i);
        path[i].push_back(u);        
    }
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}