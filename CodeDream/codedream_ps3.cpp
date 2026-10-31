#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, M;
stack<char> trace;

struct PS {
  int x, y;

  bool operator<=(const PS& other) { return x * other.y <= y * other.x; }
};

int find(int x) {
  int hang = 1, cur = 1;
  while (x > cur) hang++, cur += 1LL << (hang - 1);
  return hang;
}

void solve() {
  while (t > 1) {
    int hang = find(t);
    int tot = (1LL << (hang - 1)) - 1;
    int zz = t - tot;  // pos tren hang hien tai
    if (zz & 1)
      trace.push('L');
    else
      trace.push('R');
    if (zz & 1) zz++;
    int sonhomsauday = ((1LL << (hang - 1)) - zz) / 2;
    int nw = ((1LL << (hang - 1)) - 1) - sonhomsauday;
    t = nw;
  }
  PS cur = {1, 1};
  // cout << x << " " << y << "\n";
  PS lft = {0, 1}, rig = {1, 0};
  while (trace.size()) {
    char v = trace.top();
    trace.pop();
    PS nl = {cur.x + lft.x, cur.y + lft.y};
    PS nr = {cur.x + rig.x, cur.y + rig.y};
    nl.x %= M;
    nl.y %= M;
    nr.x %= M;
    nr.y %= M;
    if (v == 'L') {
      rig = cur;
      cur = nl;
    } else {
      lft = cur;
      cur = nr;
    }
  }
  cout << cur.x << " " << cur.y;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> t >> M;
  solve();
}