#include <bits/stdc++.h>
#define int long long
#define MAXX 205
#define MAX2 5405
using namespace std;

int n, k, a[MAXX];
int dp[MAXX][MAX2];

void solve() {
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    int cnt2 = 0, cnt5 = 0;
    int temp = a[i];
    while (temp > 0 && temp % 2 == 0) cnt2++, temp /= 2;
    temp = a[i];
    while (temp > 0 && temp % 5 == 0) cnt5++, temp /= 5;
    for (int j = min(i, k); j >= 1; j--)
      for (int x = MAX2 - 1; x >= cnt5; x--)
        if (dp[j - 1][x - cnt5] != -1)
          dp[j][x] = max(dp[j][x], dp[j - 1][x - cnt5] + cnt2);
  }
  int res = 0;
  for (int x = 0; x < MAX2; x++)
    if (dp[k][x] != -1) res = max(res, min(x, dp[k][x]));
  cout << res;
}

void read() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  read();
  solve();
}