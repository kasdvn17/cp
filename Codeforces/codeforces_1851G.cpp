/*
khi đi đến u và đi qua v => thỏa mãn c - h[i2] + h[i1] - h[i3] + h[i2] - .. - h[u] + h[prv] - h[v] + h[u] >= 0
=> c + h[i1] >= h[v]
sort cạnh theo max(h[a], h[b]) và với các truy vấn ta lưu c + h[a], sort lại truy vấn và sort cạnh; 2 con trỏ để for dần truy vấn và add dần cạnh xem 2 thàng a, b có liên thông ko
*/
#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

struct Q {
    int tar, a, b, idx;
};

int n, m, q, h[MAXX], res[MAXX];
int par[MAXX], sz[MAXX];
Q queries[MAXX];
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

bool cmp(pair<int, int> x, pair<int, int> y) {
    return max(h[x.first], h[x.second]) < max(h[y.first], h[y.second]);
}

bool cmp2(Q x, Q y) {
    return x.tar < y.tar;
}

void solve() {
    sort(queries + 1, queries + q + 1, cmp2);
    sort(edges + 1, edges + m + 1, cmp);
    int idx = 1;
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1;
    for(int i = 1; i <= q; i++) {
        while(idx <= m && max(h[edges[idx].first], h[edges[idx].second]) <= queries[i].tar) {
            join(edges[idx].first, edges[idx].second);
            idx++;
        }
        res[queries[i].idx] = (find_set(queries[i].a) == find_set(queries[i].b));
    }
    for(int i = 1; i <= q; i++)
        cout << (res[i] ? "YES\n" : "NO\n");
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> h[i];
    for(int i = 1; i <= m; i++)
        cin >> edges[i].first >> edges[i].second;
    cin >> q;
    for(int i = 1; i <= q; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        int tar = c + h[u];
        queries[i] = {tar, u, v, i};
    }
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