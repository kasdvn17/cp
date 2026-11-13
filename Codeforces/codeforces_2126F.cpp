#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

struct E {
    int u, v, w;
};

int n, q, res, a[MAXX];
E edges[MAXX];
pair<int, int> par[MAXX];
vector<pair<int, int>> path[MAXX];
map<int, int> cnt[MAXX];
// doi mau dinh x => y

void dfs(int x, int p, int idx) {
    par[x] = {p, idx};
    for(auto [v, canh] : path[x])
        if(v != p)
            dfs(v, x, canh);
}

void solve() {
    dfs(1, 0, 0);
    res = 0;
    for(int i = 1; i <= n; i++)
        for(auto [v, canhidx] : path[i])
            if(v != par[i].first) {
                cnt[i][a[v]] += edges[canhidx].w;
                if(a[i] != a[v])
                    res += edges[canhidx].w;
            }
    for(int _ = 1; _ <= q; _++) {
        int i, newcol;
        cin >> i >> newcol;
        if(newcol == a[i]) {
            cout << res << "\n";
            continue;
        }
        if(cnt[i].find(a[i]) != cnt[i].end())
            res += cnt[i][a[i]];
        if(cnt[i].find(newcol) != cnt[i].end())
            res -= cnt[i][newcol];
        // xu ly cha
        int cha = par[i].first, canhcha = par[i].second;
        cnt[cha][a[i]] -= edges[canhcha].w;
        if(cnt[cha][a[i]] == 0)
            cnt[cha].erase(a[i]);
        cnt[cha][newcol] += edges[canhcha].w;
        if(a[i] == a[cha])
            res += edges[canhcha].w;
        else if(a[cha] == newcol)
            res -= edges[canhcha].w;
        a[i] = newcol;
        cout << res << "\n";
    }
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        path[i].clear();
        cnt[i].clear();
        cin >> a[i];
    }
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        path[u].push_back({v, i});
        path[v].push_back({u, i});
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