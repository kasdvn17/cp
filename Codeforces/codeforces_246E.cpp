#include <bits/stdc++.h>
#define MAXX 300005
using namespace std;

int n, m, parr[MAXX], a[MAXX], h[MAXX], sz[MAXX], res[MAXX];
int tin[MAXX], tout[MAXX], eul[MAXX], euler;
map<int, int> cnt[MAXX];
vector<int> path[MAXX];
vector<pair<int, int>> queries[MAXX];
string tmp[MAXX];

void dfs(int u, int p) {
    h[u] = h[p] + 1;
    sz[u] = 1;
    tin[u] = ++euler;
    eul[euler] = u;
    for(auto v : path[u]) {
        if(v == p)
            continue;
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
    // add
    for(auto v : path[u])
        if(v != p && v != big)
            for(int z = tin[v]; z < tout[v]; z++)
                if(eul[z] != 0)
                    cnt[h[eul[z]]][a[eul[z]]]++;
    cnt[h[u]][a[u]]++;
    for(auto [k, idx] : queries[u]) {
        int tar = h[u] + k;
        if(tar > n)
            continue;
        res[idx] = cnt[tar].size();
    }
    if(!keep)
        for(int z = tin[u]; z < tout[u]; z++)
            if(eul[z] != 0) {
                int vv = eul[z];
                cnt[h[vv]][a[vv]]--;
                if(cnt[h[vv]][a[vv]] == 0)
                    cnt[h[vv]].erase(a[vv]);
            }
}

void solve() {
    for(int i = 1; i <= n; i++)
        if(parr[i])
            dfs(i, 0), dfs2(i, 0, 0);
    for(int i = 1; i <= m; i++)
        cout << res[i] << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> tmp[i] >> v;
        if(v == 0) {
            parr[i] = true;
            continue;
        }
        path[v].push_back(i);
        path[i].push_back(v);
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        int v, k;
        cin >> v >> k;
        queries[v].push_back({k, i});
    }
}

void normalize() {
    vector<string> vec;
    for(int i = 1; i <= n; i++)
        vec.push_back(tmp[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(vec.begin(), vec.end(), tmp[i]) - vec.begin() + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    normalize();
    solve();
}