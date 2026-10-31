#include <bits/stdc++.h>
#define int long long
using namespace std;

int x, y;

struct PS {
  int x, y;

  bool operator<=(const PS& other) { return x * other.y <= y * other.x; }
};

void solve() {
  PS cur = {1, 1};
  PS tar = {x, y};
  // cout << x << " " << y << "\n";
  PS lft = {0, 1}, rig = {1, 0};
  while (cur.x != x || cur.y != y) {
    PS nl = {cur.x + lft.x, cur.y + lft.y};
    PS nr = {cur.x + rig.x, cur.y + rig.y};
    // cout << cur.x << " " << cur.y << " | " << nl.x << " " << nl.y << " | "
    // << nr.x << " " << nr.y << "\n";
    if (tar <= cur) {
      cout << "L";
      rig = cur;
      cur = nl;
    } else {
      cout << "R";
      lft = cur;
      cur = nr;
    }
  }
  cout << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  while (cin >> x >> y) {
    if (x == 1 && y == 1) return 0;
    solve();
  }
}