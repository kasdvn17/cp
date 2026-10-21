#include <bits/stdc++.h>
#define int long long
#define MAXX 300005
using namespace std;

int n, q, a[MAXX];
vector<int> pos[MAXX];

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int cnt(int x, int l, int r) {
    auto lo = lower_bound(pos[x].begin(), pos[x].end(), l);
    auto hi = upper_bound(pos[x].begin(), pos[x].end(), r);
    return hi - lo;
}

void solve() {
    for(int i = 1; i <= q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int num = (r - l + 1) / k;
        int ans = 1e9;
        for(int z = 1; z <= 49; z++) {
            int xx = a[rand(l, r)];
            if(cnt(xx, l, r) * k > (r - l + 1))
                ans = min(ans, xx);
        }
        if(ans >= 1e9)
            cout << "-1\n";
        else
            cout << ans << "\n";
    }
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i], pos[a[i]].push_back(i);
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