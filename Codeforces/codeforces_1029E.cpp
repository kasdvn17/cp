#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, h[MAXX], dp[MAXX];
vector<int> path[MAXX];

void dfs(int x, int p) {
    for(auto v : path[x]) {
        if(v == p)
            continue;
        h[v] = h[x] + 1;
        dfs(v, x);
    }
}

void dfs2(int x, int p) {
    for(auto v : path[x]) {
        
    }
}

void solve() {
    dfs(1, 0);
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