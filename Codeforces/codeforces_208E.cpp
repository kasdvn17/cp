#include <bits/stdc++.h>
#define MAXX 300005
using namespace std;

int n, m, a[MAXX], parr[MAXX], res[MAXX], sz[MAXX];
int tin[MAXX], tout[MAXX], eul[MAXX], euler;
int cnt[MAXX];
int up[20][MAXX], h[MAXX];
vector<pair<int, int>> queries[MAXX];
vector<int> path[MAXX];

void dfs(int u, int p) {
    sz[u] = 1;
    up[0][u] = p;
    tin[u] = ++euler;
    eul[euler] = u;
    for(auto v : path[u])
        if(v != p) {
            h[v] = h[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    tout[u] = ++euler;
}

void dfs2(int u, int p, int keep) {
    int mx = -1, big = -1;
    for(auto v : path[u])
        if(v != p && sz[v] > mx)
            mx = sz[v], big = v;
    for(auto v : path[u])
        if(v != p && v != big)
            dfs2(v, u, 0);
    if(big != -1)
        dfs2(big, u, 1);
    for(auto v : path[u])
        if(v != p && v != big)
            for(int zz = tin[v]; zz < tout[v]; zz++) {
                int ta = eul[zz];
                if(ta == 0)
                    continue;
                cnt[h[ta]]++;
            }
    cnt[h[u]]++;
    for(auto [dis, idx] : queries[u])
        res[idx] = cnt[h[u] + dis] - 1;
    if(!keep)
        for(int zz = tin[u]; zz < tout[u]; zz++) {
            int ta = eul[zz];
            if(ta == 0)
                continue;
            cnt[h[ta]]--;
        }
}

int jump(int u, int k) {
    for(int v = 19; v >= 0; v--)
        if(k >> v & 1)
            u = up[v][u];
    return u;
}

void solve() {
    for(int i = 1; i <= n; i++)
        if(parr[i])
            dfs(i, 0);
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i <= n; i++)
            up[lg][i] = up[lg - 1][up[lg - 1][i]];
    cin >> m;
    for(int i = 1; i <= m; i++) {
        int v, p;
        cin >> v >> p;
        if(p > h[v])
            continue;
        queries[jump(v, p)].push_back({p, i});
    }
    for(int i = 1; i <= n; i++)
        if(parr[i])
            dfs2(i, 0, 0);
    for(int i = 1; i <= m; i++)
        cout << res[i] << " ";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        if(p == 0) {
            parr[i] = true;
            continue;
        }
        path[i].push_back(p);
        path[p].push_back(i);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}