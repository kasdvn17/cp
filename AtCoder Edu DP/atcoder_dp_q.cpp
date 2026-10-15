#include <bits/stdc++.h>
#define int long long
#define MAXX 200002
using namespace std;

int n, q;
int a[MAXX], b[MAXX], bit[MAXX];
int diff[MAXX];
int res = 1;

void update(int idx, int v) {
  while(idx <= n) {
    bit[idx] = max(bit[idx], v);
    idx += (idx & -idx);
  }
}

int mx(int idx) {
  int res = 0;
  while(idx > 0) {
    res = max(res, bit[idx]);
    idx -= (idx & -idx);
  }
  return res;
}

signed main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) cin >> b[i];
  for(int i = 1; i <= n; i++)
  {
    int xx = mx(a[i] - 1) + b[i];
    res = max(res, xx);
    update(a[i], xx);
  }
  cout << res;
}
