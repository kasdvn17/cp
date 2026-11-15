#include <bits/stdc++.h>
#define ll long long
#define MAXX 100005
using namespace std;

int n;
ll res, cost[MAXX];
int h[MAXX], up[20][MAXX];
int sp[20][MAXX];
int timdfs, tin[MAXX];
vector<int> path[MAXX], oripath[MAXX], vheight[MAXX];
vector<pair<int, int>> vtv;

void dfsori(int x, int p) {
    tin[x] = ++timdfs;
    h[x] = h[p] + 1;
    up[0][x] = p;
    for(auto v : oripath[x])
        if(v != p)
            dfsori(v, x);
}

ll queryMin(int l, int r) {
    int lg = __lg(r - l + 1);
    return min(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
}

int lca(int u, int v) {
    if(h[u] != h[v]) {
        if(h[u] < h[v])
            swap(u, v);
        int diff = h[u] - h[v];
        for(int k = 19; k >= 0; k--)
            if(diff >> k & 1)
                u = up[k][u];
    }
    if(u == v)
        return u;
    int lg = __lg(h[u]);
    for(int k = lg; k >= 0; k--)
        if(up[k][u] != up[k][v])
            u = up[k][u], v = up[k][v];
    return up[0][u];
}

pair<int, int> dpp(int x, int p, int ch) {
    // cost nho nhat de to mau toan bo dinh ben trong subtree x - so luong dinh con co height == ch    
    ll tot1 = 0;
    int tot2 = 0;
    if(h[x] == ch)
        tot1 = 1e15, tot2 = 1;
    for(auto v : path[x])
        if(v != p) {
            pair<int, int> tmp = dpp(v, x, ch);
            tot1 += tmp.first;
            tot2 += tmp.second;
        }
    int tar = ch - h[x];
    // query min tu cost[tar + 1] => cost[ch]
    return {min(queryMin(tar + 1, ch), tot1), tot2};
}

void query(int height) {
    vtv.clear();
    for(auto idx : vheight[height])
        vtv.push_back({tin[idx], idx});
    sort(vtv.begin(), vtv.end());
    int z = vtv.size();
    for(int i = 1; i < z; i++) {
        int lcc = lca(vtv[i].second, vtv[i - 1].second);
        vtv.push_back({tin[lcc], lcc});
    }
    sort(vtv.begin(), vtv.end());
    vtv.erase(unique(vtv.begin(), vtv.end()), vtv.end());
    for(int i = 1; i < vtv.size(); i++) {
        int lcc = lca(vtv[i].second, vtv[i - 1].second);
        path[lcc].push_back(vtv[i].second);
        path[vtv[i].second].push_back(lcc);
    }
    // xay canh va dinh virtual tree
    // dp tren vt
    int v = dpp(vtv[0].second, 0, height).first;
    res += v;
    for(auto xx : vtv)
        path[xx.second].clear();
}

void solve() {
    res = 0;
    timdfs = 0;
    dfsori(1, 0);
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i <= n; i++)
            up[lg][i] = up[lg - 1][up[lg - 1][i]];
    for(int i = 1; i <= n; i++)
        sp[0][i] = cost[i];
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i + (1 << lg) - 1 <= n; i++)
            sp[lg][i] = min(sp[lg - 1][i], sp[lg - 1][i + (1 << (lg - 1))]);
    for(int i = 1; i <= n; i++)
        vheight[h[i]].push_back(i);
    for(int i = 1; i <= n; i++)
        if(vheight[i].size())
            query(i);
    cout << res << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> cost[i];
    for(int i = 0; i <= n; i++) {
        oripath[i].clear();
        vheight[i].clear();
        tin[i] = 0;
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        oripath[u].push_back(v);
        oripath[v].push_back(u);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}