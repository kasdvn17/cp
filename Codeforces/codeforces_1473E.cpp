#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
#define tiii tuple<int, int, int, int>
using namespace std;

int n, m;
int d[MAXX][2][2];
// d[i][x][y]: di den i, da dung 0/1 ve free, dung 0/1 ve x2 tien
vector<pair<int, int>> path[MAXX];
priority_queue<tiii, vector<tiii>, greater<tiii>> pq;

void solve() {
    for(int i = 1; i <= n; i++)
        for(int x = 0; x < 2; x++)
            for(int y = 0; y < 2; y++)
                d[i][x][y] = 1e18;
    d[1][0][0] = 0;
    pq.push({d[1][0][0], 1, 0, 0});
    while(pq.size()) {
        auto [kc, dinh, x, y] = pq.top();
        pq.pop();
        if(kc > d[dinh][x][y])
            continue;
        for(auto [v, w] : path[dinh]) {
            if(d[v][x][y] > kc + w) {
                d[v][x][y] = kc + w;
                pq.push({d[v][x][y], v, x, y});
            }
            if(x == 0 && d[v][1][y] > kc) {
                d[v][1][y] = kc;
                pq.push({d[v][1][y], v, 1, y});
            }
            if(y == 0 && d[v][x][1] > kc + 2 * w) {
                d[v][x][1] = kc + 2 * w;
                pq.push({d[v][x][1], v, x, 1});
            }
        }
    }
    for(int i = 2; i <= n; i++)
        cout << min({d[i][0][0], d[i][0][1], d[i][1][1]}) << " ";
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        path[u].push_back({v, w});
        path[v].push_back({u, w});
    }
}

void file() {
    if(fopen("TASK.INP", "r")) {
        freopen("TASK.INP", "r", stdin);
        freopen("TASK.OUT", "w", stdout);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    file();
    read();
    solve();
}