#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

struct E {
    int u, v, col;
};

int n, res;
int par[MAXX], sz[MAXX];
int par2[MAXX], sz2[MAXX];
E edges[MAXX];

int find_set(int u) {
    if(u == par[u])
        return u;
    return par[u] = find_set(par[u]);
}

int find_set2(int u) {
    if(u == par2[u])
        return u;
    return par2[u] = find_set2(par2[u]);
}

void join2(int u, int v) {
    u = find_set2(u);
    v = find_set2(v);
    if(u == v)
        return;
    if(sz2[u] > sz2[v])
        swap(u, v);
    par2[u] = v;
    sz2[v] += sz2[u];
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
    for(int i = 1; i <= n; i++)
        par[i] = par2[i] = i, sz[i] = sz2[i] = 1;
    for(int i = 1; i < n; i++)
        if(edges[i].col == 1)
            join(edges[i].u, edges[i].v);
        else
            join2(edges[i].u, edges[i].v);
    for(int i = 1; i <= n; i++) {
        int white = find_set2(i), black = find_set(i);
        res += sz2[white] * sz[black];
    }
    cout << res - n;
}

void read() {
    cin >> n;
    for(int i = 1; i < n; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].col;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}