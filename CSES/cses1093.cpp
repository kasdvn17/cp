#include <bits/stdc++.h>
#define int long long
#define MAXX 502
#define MAX2 200000 // offset
#define MOD 1000000007
using namespace std;

int n;
int pre[2 * MAX2], cur[2 * MAX2];
// map<int, int> pre, cur;
// dp[x]: so cach tao ra 2 tong sao cho tong a - b == x

void solve() {
    int smm = n * (n + 1) / 2;
    pre[MAX2] = 1; // x = 0
    for(int i = 1; i <= n; i++) {
        for(int diff = -smm; diff <= smm; diff++) {
            // cho i vao tap a
            if(diff + i <= smm)
                cur[diff + MAX2] += pre[diff + i + MAX2];
            // cho i vao tap b
            if(diff - i >= -smm)
                cur[diff + MAX2] += pre[diff - i + MAX2];
            cur[diff + MAX2] %= MOD;
            // cout << i << " " << diff << " " << dp[i][diff] << "\n";
        }
        for(int diff = -smm; diff <= smm; diff++)
            pre[diff + MAX2] = cur[diff + MAX2], cur[diff + MAX2] = 0;
    }
    cout << (pre[MAX2] * (int)(5e8 + 4) % MOD);
}

void read() {
    cin >> n;
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