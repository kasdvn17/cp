#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

struct E {
    int u, v, w, idx;
};

int n, m, timdfs, ans[MAXX];
int par[MAXX], sz[MAXX];
int num[MAXX], low[MAXX];
vector<pair<int, int>> path[MAXX];
E edges[MAXX];

int find_set(int x) {
    if(par[x] == x)
        return x;
    return par[x] = find_set(par[x]);
}

void join(int x, int y) {
    x = find_set(x), y = find_set(y);
    if(x == y)
        return;
    if(sz[x] > sz[y])
        swap(x, y);
    sz[y] += sz[x];
    par[x] = y;
}

bool cmp(E x, E y) {
    return x.w < y.w;
}

void dfs(int u, int p_idx) {
    low[u] = num[u] = ++timdfs;
    for(auto [v, idx] : path[u]) {
        if(idx == p_idx)
            continue;
        if(!num[v]) {
            dfs(v, idx);
            low[u] = min(low[u], low[v]);
            if(low[v] > num[u])
                ans[idx] = 2;
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

void solve() {
    sort(edges + 1, edges + m + 1, cmp);
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1;
    int l = 1;
    while(l <= m) {
        int r = l;
        while(r <= m && edges[r].w == edges[l].w)
            r++;
        r--;
        vector<int> vec;
        for(int i = l; i <= r; i++) {
            int u = find_set(edges[i].u);
            int v = find_set(edges[i].v);
            if(u != v) {
                ans[edges[i].idx] = 1;
                path[u].push_back({v, edges[i].idx});
                path[v].push_back({u, edges[i].idx});
                vec.push_back(u);
                vec.push_back(v);
            } else {
                ans[edges[i].idx] = 0;
            }
        }
        for(auto u : vec)
            if(!num[u])
                dfs(u, 0);
        timdfs = 0;
        for(auto u : vec) {
            num[u] = low[u] = 0;
            path[u].clear();
        }
        for(int i = l; i <= r; i++)
            join(edges[i].u, edges[i].v);
        l = r + 1;
    }
    for(int i = 1; i <= m; i++) {
        if(ans[i] == 1) cout << "at least one\n";
        else if(ans[i] == 2) cout << "any\n";
        else cout << "none\n";
    }
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w, edges[i].idx = i;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    read();
    solve();
}