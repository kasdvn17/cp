#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

struct Q {
    int x, y, z;
};

int n, m, q, L[MAXX], R[MAXX], ans[MAXX];
int par[MAXX], sz[MAXX];
pair<int, int> edges[MAXX];
Q queries[MAXX];
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

bool check(int x, int y, int z) {
    x = find_set(x), y = find_set(y);
    if(x == y)
        return sz[x] >= z;
    else
        return sz[x] + sz[y] >= z;
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
                if(check(queries[id].x, queries[id].y, queries[id].z)) {
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
        cout << ans[i] << "\n";
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> edges[i].first >> edges[i].second;
    cin >> q;
    for(int i = 1; i <= q; i++)
        cin >> queries[i].x >> queries[i].y >> queries[i].z;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}