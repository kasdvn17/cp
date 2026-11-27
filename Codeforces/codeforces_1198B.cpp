#include <bits/stdc++.h>
#define int long long
#define MAXX 200002
using namespace std;

int n, q;
int a[MAXX], mx2[MAXX];
pair<int, int> last[MAXX];
vector<pair<int, int>> q2; // index - number

void solve() {
  for(int i = q; i >= 0; i--)
    mx2[i] = max(mx2[i + 1], mx2[i]);
  for(int i = 1; i <= n; i++) {
    a[i] = max(last[i].second, mx2[last[i].first + 1]);
    cout << a[i] << " ";
  }
}

void read() {
  cin >> n;
  for(int i = 1; i <= n; i++)
    cin >> a[i], last[i] = {0, a[i]};
  cin >> q;
  for(int _ = 1; _ <= q; _++) {
    int type, i, j;
    cin >> type >> i;
    if(type == 1)
      cin >> j, last[i] = {_, j};
    else
      mx2[_] = max(mx2[_], i);
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  read();
  solve();
}