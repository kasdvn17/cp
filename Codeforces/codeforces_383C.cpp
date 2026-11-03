#include <bits/stdc++.h>
#define int long long
#define MAXX 500005
using namespace std;

int n, m, a[MAXX], euler;
int tin[MAXX], tout[MAXX], h[MAXX], segle[MAXX], segchan[MAXX];
vector<int> path[MAXX];

void dfs(int u, int p) {
    tin[u] = ++euler;
    h[u] = h[p] + 1;
    for(auto v : path[u])
        if(v != p)
            dfs(v, u);
    tout[u] = ++euler;
}

void update(int idx, int val, int bit[MAXX]) {
    while(idx <= 2 * n) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}

int query(int idx, int bit[MAXX]) {
    int res = 0;
    while(idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void solve() {
    dfs(1, 0);
    while(m--) {
        int type, x, val;
        cin >> type;
        if(type == 1) {
            cin >> x >> val;
            if(h[x] & 1) {
                update(tin[x], val, segle);
                update(tout[x], -val, segle);
            } else {
                update(tin[x], val, segchan);
                update(tout[x], -val, segchan);
            }
        } else {
            cin >> x;
            int v1 = query(tin[x], segle);
            int v2 = query(tin[x], segchan);
            if(h[x] & 1) {
                cout << v1 - v2 + a[x] << "\n";
            } else {
                cout << v2 - v1 + a[x] << "\n";
            }
        }
    }
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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