#include <bits/stdc++.h>
#define MAXX 1000002
#define MAX2 1000002
#define BSIZE 180
using namespace std;

struct Q {
  int l, r, k, idx;
};

int n, q, ans, a[MAXX], res[MAXX];
int cnt_num[MAXX];
Q queries[MAXX];

bool cmp(Q x, Q y) {
  return make_pair(x.l / BSIZE, x.r) < make_pair(y.l / BSIZE, y.r);
}

void add(int idx) {
  int val = a[idx];
  cnt_num[val]++;
  if(cnt_num[val] == 1) ans++;
}

void del(int idx) {
  // cout << "removed: " << idx << "\n";
  int val = a[idx];
  cnt_num[val]--;
  if(cnt_num[val] == 0) ans--;
}

void solve() {
  sort(queries + 1, queries + q + 1, cmp);
  int cl = 1, cr = 0;
  for (int _ = 1; _ <= q; _++) {
    int l = queries[_].l, r = queries[_].r, k = queries[_].k,
        idx = queries[_].idx;
    while (cl > l) add(--cl);
    while (cr < r) add(++cr);
    while (cl < l) del(cl++);
    while (cr > r) del(cr--);
    res[idx] = ans;
  }
  for (int i = 1; i <= q; i++) cout << res[i] << "\n";
}

void read() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  cin >> q;
  for (int i = 1; i <= q; i++)
    cin >> queries[i].l >> queries[i].r, queries[i].idx = i;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  read();
  solve();
}