#include <bits/stdc++.h>
#define MAXX 300005
#define TOT 100000
using namespace std;

int n, q, timeu, sz[MAXX], cnt[MAXX];
int a[MAXX], bit[MAXX], res[MAXX];
int eul[MAXX], tin[MAXX], tout[MAXX];
vector<pair<int, int>> queries[MAXX];
vector<int> path[MAXX];

void update(int idx, int val) {
    // cout << "updated: " << idx << " " << val << "\n";
    while(idx <= TOT) {
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

void dfs1(int u, int p) {
    tin[u] = ++timeu;
    eul[timeu] = u;
    sz[u] = 1;
    for(auto v : path[u])
        if(v != p)
            dfs1(v, u), sz[u] += sz[v];
    tout[u] = ++timeu;
}

void insert(int x) {
    if(x == 0)
        return;
    cnt[x]++;
    if(cnt[x] > 1)
        update(cnt[x] - 1, -1);
    update(cnt[x], 1);
}

void erase(int x) {
    if(cnt[x] == 0 || x == 0)
        return;
    cnt[x]--;
    update(cnt[x] + 1, -1);
    if(cnt[x] > 0)
        update(cnt[x], 1);
}

void dfs(int u, int p, int keep) {
    int mx = -1, big = -1;
    for(auto v : path[u])
        if(v != p && sz[v] > mx)
            mx = sz[v], big = v;
    for(auto v : path[u])
        if(v != p && v != big)
            dfs(v, u, 0);
    if(big != -1)
        dfs(big, u, 1);
    for(auto v : path[u])
        if(v != p && v != big)
            for(int zz = tin[v]; zz < tout[v]; zz++) {
                insert(a[eul[zz]]);
            }
    insert(a[u]);
    for(auto [cc, idx] : queries[u]) {
        res[idx] = query(TOT) - query(cc - 1);
    }
    if(!keep)
        for(int zz = tin[u]; zz < tout[u]; zz++) {
            erase(a[eul[zz]]);
        }
}

void solve() {
    dfs1(1, 0);
    dfs(1, 0, 1);
    for(int i = 1; i <= q; i++)
        cout << res[i] << "\n";
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
    for(int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        queries[x].push_back({y, i});
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}