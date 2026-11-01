#include <bits/stdc++.h>
#define int long long
#define MAXX 300005
using namespace std;

int n, m, par[MAXX], sz[MAXX];
int d[MAXX], h[MAXX], up[20][MAXX];
int step[25][MAXX];
vector<tuple<int, int, int>> rmn;
vector<pair<int, int>> path[MAXX];

int find_set(int x) {
    if(x == par[x])
        return x;
    return par[x] = find_set(par[x]);
}

void join(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if(u == v)
        return;
    if(sz[u] > sz[v])
        swap(u, v);
    par[u] = v;
    sz[v] += sz[u];
}

void dfs(int u, int p) {
    up[0][u] = p;
    for(auto [v, w] : path[u])
        if(v != p) {
            h[v] = h[u] + 1;
            d[v] = d[u] + w;
            dfs(v, u);
        }
}

void dijkstra(int x, int d[MAXX]) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for(int i = 1; i <= n; i++)
        d[i] = 1e18;
    d[x] = 0;
    pq.push({d[x], x});
    while(pq.size()) {
        auto [kc, dinh] = pq.top();
        pq.pop();
        if(kc > d[dinh])
            continue;
        for(auto [v, w] : path[dinh])
            if(kc + w < d[v])
                d[v] = kc + w, pq.push({d[v], v});
    }
}

int lca(int u, int v) {
    if(h[u] != h[v]) {
        if(h[u] > h[v])
            swap(u, v);
        int diff = h[v] - h[u];
        for(int k = 19; k >= 0; k--)
            if(diff >> k & 1)
                v = up[k][v];
    }
    if(u == v)
        return u;
    for(int k = 19; k >= 0; k--)
        if(up[k][u] != up[k][v])
            u = up[k][u], v = up[k][v];
    return up[0][u];
}

int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}

void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(find_set(u) == find_set(v))
            rmn.push_back({u, v, w});
        else
            path[u].push_back({v, w}), path[v].push_back({u, w}), join(u, v);
    }
    dfs(1, 0);
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i <= n; i++)
            up[lg][i] = up[lg - 1][up[lg - 1][i]];
    for(auto [u, v, w] : rmn)
        path[u].push_back({v, w}),
        path[v].push_back({u, w});
    for(int i = 0; i < rmn.size(); i++) {
        auto [u, v, w] = rmn[i];
        dijkstra(u, step[i]);
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        int res = dist(u, v);
        for(int i = 0; i < rmn.size(); i++)
            res = min(res, step[i][u] + step[i][v]);
        cout << res << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    solve();
}