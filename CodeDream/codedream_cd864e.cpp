#include <bits/stdc++.h>
#define int long long
#define MAXX 102
#define MAX2 4002
using namespace std;

struct D {
    int t, p, d, idx;
};

int n, mx1, mx2;
int dp[MAXX][MAX2]; // mx gia tri
pair<int, pair<int, int>> res = {0, {0, 0}};
bool trace[MAXX][MAX2];
// xet den vat nao - time => max value
D a[MAXX];
stack<int> ans;

bool cmp(D x, D y) {
    if(x.d != y.d) return x.d < y.d;
    return x.t < y.t;
}

void solve() {
    sort(a + 1, a + n + 1, cmp);
    int mxt = mx1 + mx2;
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= mxt; j++)
            dp[i][j] = -1e18;
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = mxt; j >= 0; j--) {
            dp[i][j] = dp[i - 1][j];
            if(j < a[i].d && j - a[i].t >= 0) {
                int v = dp[i - 1][j - a[i].t] + a[i].p;
                if(dp[i][j] < v) {
                    dp[i][j] = v;
                    trace[i][j] = true;
                    if(res.first < dp[i][j])
                        res = {dp[i][j], {i, j}};
                }
            }
        }
    cout << res.first << "\n";
    while(res.second.first > 0) {
        if(trace[res.second.first][res.second.second])
            ans.push(a[res.second.first].idx), res.second.second -= a[res.second.first].t;
        res.second.first--;
    }
    // cout << ans.size() << "\n";
    // while(ans.size())
        // cout << ans.top() << " ", ans.pop();
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].t >> a[i].d >> a[i].p;
        a[i].idx = i;
        mx1 = max(mx1, a[i].d);
        mx2 += a[i].t;
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