#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, m, k, special[MAXX];
int d1[MAXX], dn[MAXX];
vector<int> path[MAXX];
vector<pair<int, int>> vec;
queue<int> q;

void bfs(int x, int d[MAXX]) {
    d[x] = 0;
    q.push(x);
    while(!q.empty()) {
        int dinh = q.front();
        q.pop();
        for(auto v : path[dinh]) {
            if(d[v] == -1) {
                d[v] = d[dinh] + 1;
                q.push(v);
            }
        }
    }
}

bool cmp(pair<int, int> x, pair<int, int> y) {
    return x.first - x.second < y.first - y.second;
}

void solve() {
    memset(d1, -1, sizeof(d1));
    memset(dn, -1, sizeof(dn));
    bfs(1, d1);
    bfs(n, dn);
    for(int i = 1; i <= n; i++)
        if(special[i])
            vec.push_back({d1[i], dn[i]});
    sort(vec.begin(), vec.end(), cmp);
    int res = 0;
    int mxx = -1e18;
    for(auto p : vec) {
        int du = p.first;
        int dv = p.second;
        if(mxx != -1e18)
            res = max(res, mxx + dv + 1);
        mxx = max(mxx, du);
    }
    res = min(res, d1[n]);
    cout << res << "\n";
}

void read() {
    cin >> n >> m >> k;
    for(int i = 1; i <= k; i++) {
        int u;
        cin >> u;
        special[u] = true;
    }
    for(int i = 1; i <= m; i++) {
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