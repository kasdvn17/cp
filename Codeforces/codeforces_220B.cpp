#include <bits/stdc++.h>
#define MAXX 100005
#define MAX2 100005
#define BSIZE 320
using namespace std;

struct Q {
  int l, r, k, idx;
};

int n, q, ans, a[MAXX], res[MAXX];
int cnt_num[MAXX];
bool tmp[MAX2];
Q queries[MAXX];

bool cmp(Q x, Q y) {
  return make_pair(x.l / BSIZE, x.r) < make_pair(y.l / BSIZE, y.r);
}

void add(int idx) {
  // cout << "added: " << idx << "\n";
  int val = a[idx];
  if(val > n)
    return;
  cnt_num[val]++;
  if(cnt_num[val] == val) ans++;
  else if(cnt_num[val] == val + 1) ans--;
}

void del(int idx) {
  // cout << "removed: " << idx << "\n";
  int val = a[idx];
  if(val > n)
    return;
  cnt_num[val]--;
  if(cnt_num[val] == val) ans++;
  else if(cnt_num[val] == val - 1) ans--;
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
    // cout << "\n";
  }
  for (int i = 1; i <= q; i++) cout << res[i] << "\n";
}

void read() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= q; i++)
    cin >> queries[i].l >> queries[i].r, queries[i].idx = i;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  read();
  solve();
}