#include <bits/stdc++.h>
#define MAXX 300005
using namespace std;

int n, m, timdfs, mod[MAXX];
int par[MAXX], sz[MAXX];
int num[MAXX], low[MAXX];
bool bridge = false;
pair<int, int> edges[MAXX];
vector<pair<int, int>> path[MAXX];

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

void dfs(int u, int idxpar) {
    num[u] = low[u] = ++timdfs;
    for(auto [v, idx] : path[u]) {
        if(idx == idxpar)
            continue;
        if(!num[v]) {
            dfs(v, idx);
            if(!mod[idx]) {
                mod[idx] = true;
                if(edges[idx].first == v)
                    edges[idx] = {u, v};
            }
            low[u] = min(low[u], low[v]);
            if(low[v] == num[v])
                bridge = true;
        } else {
            if(!mod[idx]) {
                mod[idx] = true;
                if(edges[idx].first == v)
                    edges[idx] = {u, v};
            }
            low[u] = min(low[u], num[v]);
        }
    }
}

void solve() {
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1;
    for(int i = 1; i <= m; i++)
        join(edges[i].first, edges[i].second);
    for(int i = 1; i <= n; i++) {
        if(find_set(i) != find_set(1)) {
            cout << 0;
            return;
        }
    }
    for(int i = 1; i <= n; i++)
        if(!num[i])
            dfs(i, 0);
    if(bridge) {
        cout << 0;
        return;
    }
    for(int i = 1; i <= m; i++)
        cout << edges[i].first << " " << edges[i].second << "\n";
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