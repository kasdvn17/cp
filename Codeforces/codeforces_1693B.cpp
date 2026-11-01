#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, res, mx[MAXX];
int l[MAXX], r[MAXX];
vector<int> path[MAXX];

int dfs(int x, int p) {
    int sm = 0;
    for(auto v : path[x])
        if(v != p)
            sm += dfs(v, x);
    if(sm < l[x]) {
        res++;
        return r[x];
    }
    return min(sm, r[x]);
}

void solve() {
    res = 0;
    dfs(1, 0);
    cout << res << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        path[i].clear();
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        path[p].push_back(i);
        path[i].push_back(p);
    }
    for(int i = 1; i <= n; i++)
        cin >> l[i] >> r[i];
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