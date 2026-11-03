#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, d[MAXX], ld[MAXX], par[MAXX], vis[MAXX], fur[MAXX];
int d1, d2;
vector<int> path[MAXX];

void dfs(int u, int p) {
    for(auto v : path[u])
        if(v != p)
            d[v] = d[u] + 1, dfs(v, u);
}

void dfs2(int u, int p) {
    ld[u] = 0;
    fur[u] = u;
    par[u] = p;
    for(auto v : path[u])
        if(v != p) {
            dfs2(v, u);
            if(ld[u] <= ld[v]) {
                ld[u] = ld[v] + 1;
                fur[u] = fur[v];
            }
        }
}

void solve() {
    dfs(1, 0);
    int cmx = -1;
    for(int i = 1; i <= n; i++)
        if(d[i] > cmx)
            cmx = d[i], d1 = i;
    d[d1] = 0;
    dfs(d1, 0);
    cmx = -1;
    for(int i = 1; i <= n; i++)
        if(d[i] > cmx)
            cmx = d[i], d2 = i;
    dfs2(d1, 0);
    pair<int, int> res2 = {-1, d1};
    int _d2 = d2;
    while(d2 != 0)
        vis[d2] = true, d2 = par[d2];
    d2 = _d2;
    while(d2 != 0) {
        if(d2 != d1 && d2 != _d2)
            res2 = max(res2, {0, d2});
        for(auto v : path[d2])
            if(!vis[v])
                res2 = max(res2, {ld[v] + 1, fur[v]});
        d2 = par[d2];
    }
    cout << cmx + res2.first << "\n" << d1 << " " << _d2 << " " << res2.second;
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