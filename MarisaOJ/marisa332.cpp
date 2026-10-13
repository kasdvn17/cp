#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, a[MAXX], bit[MAXX];
int euler, tin[MAXX], tout[MAXX];
vector<int> path[MAXX];

void dfs(int u, int p) {
    tin[u] = ++euler;
    for(auto v : path[u])
        if(v != p)
            dfs(v, u);
    tout[u] = euler;
}

void update(int idx, int val) {
    while(idx <= n) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}

int query(int idx) {
    int res = 0;
    while(idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void solve() {
    dfs(1, 0);
    for(int i = 1; i <= n; i++) {
        cout << query(tin[a[i]]) << "\n";
        update(tin[a[i]], 1);
        update(tout[a[i]] + 1, -1);
    }
}

void read() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
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