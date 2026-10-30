#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, m, k, visited, indeg[MAXX], pos[MAXX];
vector<pair<int, int>> d2c, d1c;
vector<int> path[MAXX], topo;

void solve() {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
        q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        visited++;
        topo.push_back(v);
        for (int u : path[v]) {
        indeg[u]--;
        if (indeg[u] == 0)
            q.push(u);
        }
    }
    if (visited < n) {
        cout << "NO\n";
        return;
    }
    for (int i = 1; i <= n; i++)
        pos[topo[i - 1]] = i;
    cout << "YES\n";
    for (auto [u, v] : d2c) {
        if (pos[u] > pos[v])
        swap(u, v);
        cout << u << " " << v << "\n";
    }
    for(auto [u, v] : d1c)
        cout << u << " " << v << "\n";
}

void read() {
    cin >> n >> m;
    visited = 0;
    d2c.clear();
    d1c.clear();
    topo.clear();
    for(int i = 1; i <= n; i++)
        indeg[i] = 0, path[i].clear();
    for (int i = 1; i <= m; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
        path[u].push_back(v);
        d1c.push_back({u, v});
        indeg[v]++;
        } else {
        k++;
        d2c.push_back({u, v});
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}
