#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

int n, BSIZE, cnt_times = 0, a[MAXX];
int res[MAXX];
int seen[MAXX];
vector<pair<int, pair<int, int>>> pres;

// max v mau => min doi ?
int f(int v) {
  cnt_times++;
  int res = 1, cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (seen[a[i]] == cnt_times) continue;
    if (cnt == v) {
      res++;
      cnt_times++;
      cnt = 1;
      seen[a[i]] = cnt_times;
    } else
      seen[a[i]] = cnt_times, cnt++;
  }
  return res;
}

void solve() {
  BSIZE = sqrt(n);
  for (int i = 1; i <= BSIZE; i++) res[i] = f(i);
  int nxt = BSIZE + 1;
  while (nxt <= n) {
    int cur = f(nxt);
    int l = nxt, r = n, ans = -1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (f(mid) == cur)
        ans = mid, l = mid + 1;
      else
        r = mid - 1;
    }
    pres.push_back({cur, {nxt, ans}});
    nxt = ans + 1;
  }
  for (int i = 1; i <= BSIZE; i++) cout << res[i] << " ";
  for (int i = 0; i < pres.size(); i++)
    for (int j = pres[i].second.first; j <= pres[i].second.second; j++)
      cout << pres[i].first << " ";
}

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