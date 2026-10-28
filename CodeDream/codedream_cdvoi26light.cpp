#include <bits/stdc++.h>
#define MAXX 667
#define MAX2 100002
using namespace std;

int n, q, x, y, a[MAXX], res[MAXX];
int dp[MAXX][10][10];
pair<int, int> queries[MAX2];

int get(int x, int huong) {
    if(x == 0)
        return 0;
    if(huong == 0) return 3 - x;
    return x;
}

void solve() {
    int l, r;
    while(q--) {
        cin >> l >> r;
        cout << "check: " << l << " " << r << "\n";
        for(int i = l; i <= r; i++)
            for(int m = 0; m <= 5; m++)
                for(int n = 0; n <= 5; n++)
                    dp[i][m][n] = 1e9;
        if(get(a[l], 0) <= x)
            dp[l][get(a[l], 0)][0] = 1;
        if(get(a[l], 1) <= y)
            dp[l][0][get(a[l], 1)] = 1;
        for(int i = l; i < r; i++)
            for(int m = 0; m <= x; m++)
                for(int n = 0; n <= y; n++) {
                    if(dp[i][m][n] >= 1e9)
                        continue;
                    // dang tu dp[i][m][n] => dp[i + 1][..][..]
                    int cost1 = get(a[i + 1], 0), cost2 = get(a[i + 1], 1);
                    if(m + cost1 > x) {
                        dp[i + 1][m + cost1 - x][0] = min(dp[i + 1][m + cost1 - x][0], dp[i][m][n] + 1);
                    } else {
                        dp[i + 1][m + cost1][n] = min(dp[i + 1][m + cost1][n], dp[i][m][n]);
                    }
                    if(n + cost1 > y) {
                        dp[i + 1][0][n + cost1 - y] = min(dp[i + 1][0][n + cost1 - y], dp[i][m][n] + 1);
                    } else {
                        dp[i + 1][0][n + cost1] = min(dp[i + 1][0][n + cost1], dp[i][m][n]);
                    }
                }
        int res = dp[r][x][y];
        if(res >= 1e9)
            cout << "-1\n";
        else
            cout << res << "\n";
    }
}

void read() {
    cin >> n >> q >> x >> y;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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