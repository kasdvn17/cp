#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

int n, sz[MAXX];
vector<int> path[MAXX];

void dfs(int x, int p) {
    int cnt = 0;
    for(auto v : path[x]) {
        if(v == p)
            continue;
        cnt++;
        dfs(v, x);
        sz[x] += sz[v];
    }
    if(cnt == 0) sz[x] = 1;
}

void solve() {
    dfs(1, 0);
    sort(sz + 1, sz + n + 1);
    for(int i = 1; i <= n; i++)
        cout << sz[i] << " ";
}

void read() {
    cin >> n;
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        path[i].push_back(p);
        path[p].push_back(i);
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