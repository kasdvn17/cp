#include <bits/stdc++.h>
#define MAXX 400005
using namespace std;

int n, ans[MAXX], slkn, c[MAXX], cnt[MAXX];
int timdfs, euler[MAXX], tin[MAXX], tout[MAXX], sz[MAXX];
vector<int> path[MAXX];

void dfs(int u, int p) {
    tin[u] = ++timdfs;
    sz[u] = 1;
    euler[timdfs] = u;
    for(auto v : path[u])
        if(v != p)
            dfs(v, u), sz[u] += sz[v];
    tout[u] = ++timdfs;
}

void add(int x) {
    cnt[c[x]]++;
    if(cnt[c[x]] == 1)
        slkn++;
}

void del(int x) {
    cnt[c[x]]--;
    if(cnt[c[x]] == 0)
        slkn--;
}

void sack(int u, int p, int keep) {
    int mx = -1, big = -1;
    for(auto v : path[u])
        if(v != p && sz[v] > mx)
            mx = sz[v], big = v;
    for(auto v : path[u])
        if(v != p && v != big)
            sack(v, u, 0);
    if(big != -1)
        sack(big, u, 1);
    for(auto v : path[u])
        if(v != p && v != big)
            for(int zz = tin[v]; zz < tout[v]; zz++)
                if(euler[zz])
                    add(euler[zz]);
    add(u);
    ans[u] = slkn;
    if(!keep)
        for(int zz = tin[u]; zz < tout[u]; zz++)
            if(euler[zz])
                del(euler[zz]);
    
}

void solve() {
    dfs(1, 0);
    sack(1, 0, 0);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> c[i];
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
}

void normalize() {
    vector<int> vec;
    for(int i = 1; i <= n; i++)
        vec.push_back(c[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++)
        c[i] = lower_bound(vec.begin(), vec.end(), c[i]) - vec.begin() + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    normalize();
    solve();
}