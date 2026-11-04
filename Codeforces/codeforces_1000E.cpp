// cầu, khớp
#include <bits/stdc++.h>
#define MAXX 300005
using namespace std;

int n, m, timdfs, cau[MAXX];
int par[MAXX], sz[MAXX], d[MAXX];
int num[MAXX], low[MAXX];
vector<pair<int, int>> path[MAXX];
vector<int> npath[MAXX];
pair<int, int> edges[MAXX];

int find_set(int u) {
    if(u == par[u])
        return u;
    return par[u] = find_set(par[u]);
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

void dfs(int x, int p) {
    low[x] = num[x] = ++timdfs;
    for(auto [v, idx] : path[x]) {
        if(v == p)
            continue;
        if(!num[v]) {
            dfs(v, x);
            low[x] = min(low[x], low[v]);
            if(low[v] == num[v])
                cau[idx] = true;
        } else
            low[x] = min(low[x], num[v]);
    }
}

void dfs2(int x, int p) {
    d[x] = d[p] + 1;
    for(auto v : npath[x])
        if(v != p)
            dfs2(v, x);
}

void solve() {
    for(int i = 1; i <= n; i++) {
        par[i] = i, sz[i] = 1;
        if(!low[i])
            dfs(i, 0);
    }
    for(int i = 1; i <= m; i++)
        if(!cau[i])
            join(edges[i].first, edges[i].second);
    int fr = find_set(1);
    for(int i = 1; i <= m; i++)
        if(cau[i]) {
            int u = find_set(edges[i].first);
            int v = find_set(edges[i].second);
            npath[u].push_back(v);
            npath[v].push_back(u);
        }
    dfs2(fr, 0);
    int mx = -1, logest = -1;
    for(int i = 1; i <= n; i++) {
        int u = find_set(i);
        if(d[u] > mx)
            mx = d[u], logest = u;
    }
    dfs2(logest, 0);
    mx = -1, logest = -1;
    for(int i = 1; i <= n; i++) {
        int u = find_set(i);
        if(d[u] > mx)
            mx = d[u], logest = u;
    }
    cout << mx - 1;
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back({v, i});
        path[v].push_back({u, i});
        edges[i] = {u, v};
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}