#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, m, k, cnt = 0, nmd[MAXX];
int d[MAXX];
vector<int> path[MAXX];
priority_queue<pair<int, int>> pq;

void solve() {
    for(int i = 1; i <= n; i++) {
        if(nmd[i]) d[i] = nmd[i], pq.push({d[i], i});
        else d[i] = -1e18;
    }
    while(pq.size()) {
        int kc = pq.top().first, dinh = pq.top().second;
        pq.pop();
        if(kc < d[dinh])
            continue;
        for(auto v : path[dinh])
            if(d[v] < d[dinh] - 1) {
                d[v] = d[dinh] - 1;
                if(d[v] >= 0)
                    pq.push({d[v], v});
            }
    }
    for(int i = 1; i <= n; i++)
        if(d[i] >= 0) cnt++;
    cout << cnt;
}

void read() {
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
    for(int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        nmd[u] = max(nmd[u], v);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}