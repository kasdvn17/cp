#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, m, res;
int par[MAXX], sz[MAXX], mn[MAXX];
pair<int, pair<int, int>> edges[MAXX];

int find_set(int u) {
    if(u == par[u])
        return u;
    return par[u] = find_set(par[u]);
}

void join(int u, int v, int w) {
    u = find_set(u);
    v = find_set(v);
    if(u == v) {
        mn[u] = min(mn[u], w);
        return;
    }
    if(sz[u] > sz[v])
        swap(u, v);
    par[u] = v;
    sz[v] += sz[u];
    mn[v] = min({mn[v], mn[u], w});
}

void solve() {
    res = 1e18;
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1, mn[i] = 1e18;
    sort(edges + 1, edges + m + 1);
    for(int i = 1; i <= m; i++) {
        join(edges[i].second.first, edges[i].second.second, edges[i].first);
        if(find_set(1) == find_set(n)) {
            res = min(res, edges[i].first + mn[find_set(1)]);
        }
    }
    cout << res << "\n";
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}