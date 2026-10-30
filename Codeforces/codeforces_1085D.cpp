#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, s, deg[MAXX];
int cnt = 0;
long double ans = 0;

void solve() {
    for(int i = 1; i <= n; i++)
        if(deg[i] == 1) cnt++;
    ans = 2.0 * s / (1.0 * cnt);
    cout << fixed << setprecision(18) << ans;
}

void read() {
    cin >> n >> s;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
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