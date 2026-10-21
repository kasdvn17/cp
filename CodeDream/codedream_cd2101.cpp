#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, m, q, L[MAXX], R[MAXX], ans[MAXX];
int par[MAXX], sz[MAXX];
pair<int, int> edges[MAXX], queries[MAXX];
vector<int> processes[MAXX];

int find_set(int idx) {
    if(idx == par[idx])
        return idx;
    return par[idx] = find_set(par[idx]);
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

void solve() {
    bool processing = true;
    for(int i = 1; i <= q; i++)
        L[i] = 1, R[i] = m, ans[i] = -1;
    while(processing) {
        processing = false;
        for(int i = 1; i <= q; i++) {
            if(L[i] > R[i])
                continue;
            processing = true;
            processes[(L[i] + R[i]) >> 1].push_back(i);
        }
        for(int i = 1; i <= n; i++)
            par[i] = i, sz[i] = 1;
        for(int i = 1; i <= m; i++) {
            join(edges[i].first, edges[i].second);
            for(auto id : processes[i]) {
                if(find_set(queries[id].first) == find_set(queries[id].second)) {
                    ans[id] = i;
                    R[id] = i - 1;
                } else {
                    L[id] = i + 1;
                }
            }
            processes[i].clear();
        }
    }
    for(int i = 1; i <= q; i++)
        if(queries[i].first != queries[i].second) cout << ans[i] << "\n";
        else cout << "0\n";
}

void read() {
    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++)
        cin >> edges[i].first >> edges[i].second;
    for(int i = 1; i <= q; i++)
        cin >> queries[i].first >> queries[i].second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}