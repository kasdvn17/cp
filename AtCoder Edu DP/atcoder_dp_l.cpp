#include <bits/stdc++.h>
#define int long long
#define MAXX 3002
using namespace std;

int n, a[MAXX];
int memo[MAXX][MAXX][3];

int dp(int l, int r, int per) {
  // per 1 => maximize x - y
  // per 2 => minimize x - y
  if (memo[l][r][per]) return memo[l][r][per];
  if (l == r) {
    if (per == 1) return memo[l][r][per] = a[l];
    return memo[l][r][per] = -a[l];
  }
  if (l == r - 1) {
    if (per == 1) return memo[l][r][per] = abs(a[l] - a[r]);
    return memo[l][r][per] = -abs(a[l] - a[r]);
  }
  if (per == 1) {
    int x = dp(l, r - 1, 2), y = dp(l + 1, r, 2);
    int v1 = x + a[r], v2 = y + a[l];
    return memo[l][r][per] = max(v1, v2);
  } else {
    int x = dp(l, r - 1, 1), y = dp(l + 1, r, 1);
    int v1 = x - a[r], v2 = y - a[l];
    return memo[l][r][per] = min(v1, v2);
  }
}

void solve() { cout << dp(1, n, 1); }

void read() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  read();
  solve();
}
