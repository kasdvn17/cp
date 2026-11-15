#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

int n, q;
int timdfs, tin[MAXX], tout[MAXX], h[MAXX], up[20][MAXX];
int ans = 0, timer, important[MAXX];
bool cant = false;
vector<int> path[MAXX], oripath[MAXX];
vector<pair<int, int>> vtv;
// dp[i][0/1]: xet subtree v, so thang can xoa it nhat de 0: ko con ket noi voi important city nao,
// 1: con ket noi voi 1 city important
// tai dp[v] thi giu v

void dfs(int x, int p) {
    h[x] = h[p] + 1;
    up[0][x] = p;
    tin[x] = ++timdfs;
    for(auto v : oripath[x])
        if(v != p)
            dfs(v, x);
    tout[x] = ++timdfs;
}

inline bool isimp(int x) {
    return important[x] == timer;
}

int dpp(int x, int p) {
    if(cant)
        return 0;
    int hasimp = 0;
    for(auto v : path[x]) {
        if(v == p)
            continue;
        if(isimp(x) && isimp(v) && up[0][v] == x) {
            cant = true;
            return 0;
        }
        int cc = dpp(v, x);
        // cout << v << " " << cc << " ANS\n";
        if(cc) hasimp++;
        if(isimp(x) && cc)
            ans++; // xoa chinh thang v nay
    }
    if(isimp(x))
        return 1;
    if(hasimp >= 2) {
        ans++; // xoa dinh x di
        return 0;
    }
    if(hasimp == 0)
        return 0;
    return 1;
}

int lca(int u, int v) {
    if(h[u] != h[v]) {
        if(h[u] > h[v])
            swap(u, v);
        int diff = h[v] - h[u];
        for(int k = 0; k < 20; k++)
            if(diff >> k & 1)
                v = up[k][v];
    }
    if(u == v)
        return u;
    int lg = __lg(h[u]);
    for(int k = 19; k >= 0; k--)
        if(up[k][u] != up[k][v])
            u = up[k][u], v = up[k][v];
    return up[0][u];
}

void query() {
    sort(vtv.begin(), vtv.end());
    int z = vtv.size();
    for(int i = 1; i < z; i++) {
        int lcc = lca(vtv[i].second, vtv[i - 1].second);
        vtv.push_back({tin[lcc], lcc});
    }
    sort(vtv.begin(), vtv.end());
    vtv.erase(unique(vtv.begin(), vtv.end()), vtv.end());
    for(int i = 1; i < vtv.size(); i++) {
        int lcc = lca(vtv[i].second, vtv[i - 1].second);
        path[lcc].push_back(vtv[i].second);
        path[vtv[i].second].push_back(lcc);
    }
    dpp(vtv[0].second, 0);
    for(auto [_, x] : vtv)
        path[x].clear();
    if(cant) {
        cout << "-1\n";
        return;
    }
    cout << ans << "\n";
}

void solve() {
    dfs(1, 0);
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i <= n; i++)
            up[lg][i] = up[lg - 1][up[lg - 1][i]];
    cin >> q;
    while(q--) {
        int v;
        cin >> v;
        cant = false;
        ans = 0;
        timer++;
        vtv.clear();
        for(int i = 1; i <= v; i++) {
            int t;
            cin >> t;
            important[t] = timer;
            vtv.push_back({tin[t], t});
        }
        query();
    }
}

void read() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        oripath[u].push_back(v);
        oripath[v].push_back(u);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}