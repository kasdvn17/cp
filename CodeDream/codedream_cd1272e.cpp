#include <bits/stdc++.h>
#define int long long
#define MAXX 200002
using namespace std;

int n, a[MAXX], res[MAXX], d[MAXX];
vector<int> path[MAXX];
queue<int> q;

void bfs(int p) {
    memset(d, -1, sizeof(d));
    for(int i = 1; i <= n; i++) {
        if(a[i] % 2 == p)
            d[i] = 0, q.push(i);
    }
    while(q.size()) {
        int z = q.front();
        q.pop();
        for(auto v : path[z])
            if(d[v] == -1)
                d[v] = d[z] + 1, q.push(v);
    }
    for(int i = 1; i <= n; i++)
        if(a[i] % 2 != p)
            res[i] = d[i];
}

void solve() {
    for(int i = 1; i <= n; i++) {
        int tar1 = i - a[i];
        if(tar1 >= 1 && tar1 <= n)
            path[tar1].push_back(i);
        tar1 = i + a[i];
        if(tar1 >= 1 && tar1 <= n)
            path[tar1].push_back(i);
    }
    bfs(0);
    bfs(1);
    for(int i = 1; i <= n; i++)
        cout << res[i] << " ";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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