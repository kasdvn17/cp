#include <bits/stdc++.h>
#define ll long long
#define MAXX 100005
using namespace std;

int n, q, s;
int lid[MAXX], seg2[4 * MAXX], seg3[4 * MAXX];
ll d[8 * MAXX + 5];
vector<pair<int, int>> path[8 * MAXX + 5];

void add(int u, int v, int w) {
    path[u].push_back({v, w});
}

void build2(int idx, int l, int r) {
    if(l == r) {
        lid[l] = idx;
        return;
    }
    int mid = (l + r) >> 1;
    build2(2 * idx, l, mid);
    build2(2 * idx + 1, mid + 1, r);
    add(idx, 2 * idx, 0);
    add(idx, 2 * idx + 1, 0);
}

void build3(int idx, int l, int r) {
    int nw = idx + 4 * n;
    if(l == r) {
        add(lid[l], nw, 0);
        add(nw, lid[l], 0);
        return;
    }
    int mid = (l + r) >> 1;
    build3(2 * idx, l, mid);
    build3(2 * idx + 1, mid + 1, r);
    add(2 * idx + 4 * n, nw, 0);
    add(2 * idx + 1 + 4 * n, nw, 0);
}

void update2(int idx, int l, int r, int s, int e, int from, int w) {
    if(l > e || r < s)
        return;
    if(l >= s && r <= e) {
        add(lid[from], idx, w);
        return;
    }
    int mid = (l + r) >> 1;
    update2(2 * idx, l, mid, s, e, from, w);
    update2(2 * idx + 1, mid + 1, r, s, e, from, w);
}

void update3(int idx, int l, int r, int s, int e, int to, int w) {
    if(l > e || r < s)
        return;
    if(l >= s && r <= e) {
        add(idx + 4 * n, lid[to], w);
        return;
    }
    int mid = (l + r) >> 1;
    update3(2 * idx, l, mid, s, e, to, w);
    update3(2 * idx + 1, mid + 1, r, s, e, to, w);
}

void dijkstra(int x) {
    for(int i = 1; i <= 8 * n; i++)
        d[i] = 1e18;
    d[x] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({d[x], x});
    while(pq.size()) {
        auto [kc, dinh] = pq.top();
        pq.pop();
        if(kc > d[dinh])
            continue;
        for(auto [v, w] : path[dinh])
            if(kc + w < d[v]) {
                d[v] = kc + w;
                pq.push({d[v], v});
            }
    }
}

void solve() {
    build2(1, 1, n);
    build3(1, 1, n);
    while(q--) {
        int type, u, v, l, r, w;
        cin >> type;
        if(type == 1) {
            cin >> v >> u >> w;
            add(lid[v], lid[u], w);
        } else if(type == 2) {
            cin >> v >> l >> r >> w;
            update2(1, 1, n, l, r, v, w);
        } else if(type == 3) {
            cin >> v >> l >> r >> w;
            update3(1, 1, n, l, r, v, w);
        }
    }
    dijkstra(lid[s]);
    for(int i = 1; i <= n; i++)
        if(d[lid[i]] >= 1e18) cout << "-1 ";
        else cout << d[lid[i]] << " ";
}

void read() {
    cin >> n >> q >> s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}