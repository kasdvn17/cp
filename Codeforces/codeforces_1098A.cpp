#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, s[MAXX], a[MAXX], mn[MAXX];
bool wrong = false;
vector<int> path[MAXX];

void dfs(int x, int p) {
    if(s[x] != -1)
        mn[x] = s[x];
    else
        mn[x] = 1e18;
    for(auto v : path[x]) {
        if(v == p)
            continue;
        dfs(v, x);
        mn[x] = min(mn[x], mn[v]);
    }
}

void dfs2(int x, int p, int tot_top) {
    if(wrong)
        return;
    if(mn[x] < max(tot_top, s[x])) {
        wrong = true;
        return;
    }
    if(mn[x] >= 1e18)
        a[x] = 0;
    else
        a[x] = mn[x] - tot_top;
    for(auto v : path[x])
        if(v != p)
            dfs2(v, x, tot_top + a[x]);
}

void solve() {
    dfs(1, 0);
    dfs2(1, 0, 0);
    if(wrong)
        cout << -1;
    else {
        int res = 0;
        for(int i = 1; i <= n; i++)
            res += a[i];
        cout << res;
    }
}

void read() {
    cin >> n;
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        path[p].push_back(i);
        path[i].push_back(p);
    }
    for(int i = 1; i <= n; i++)
        cin >> s[i];
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