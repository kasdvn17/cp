#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, m, par[MAXX], sz[MAXX];
set<pair<int, int>> s;

int find_set(int x) {
    if(x == par[x])
        return x;
    return par[x] = find_set(par[x]);
}

void join(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if(x == y)
        return;
    if(sz[x] > sz[y])
        swap(x, y);
    s.erase({sz[x], x});
    s.erase({sz[y], y});
    par[x] = y;
    sz[y] += sz[x];
    s.insert({sz[y], y});
}

void solve() {

}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1, s.insert({sz[i], i});
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        join(u, v);
        cout << s.size() << " " << s.rbegin()->first << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}