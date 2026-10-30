#include <bits/stdc++.h>
#define MAXX 100005
#define int long long
using namespace std;

int n, col[MAXX], res[MAXX], par[MAXX];
int cnt[MAXX], sz[MAXX];
int mx = 0, sm = 0;
bool hev[MAXX];
vector<int> path[MAXX];

void update(int x, int p, int val) {
  cnt[col[x]] += val;
  if(val > 0) {
    if(cnt[col[x]] > mx)
      mx = cnt[col[x]], sm = col[x];
    else if(cnt[col[x]] == mx)
      sm += col[x];
  }
  for (auto v : path[x])
    if (v != p && !hev[v])
      update(v, x, val);
}

void dfs(int x, int p, bool k) {
  int big = -1, mx2 = -1;
  for(auto xx : path[x])
    if(xx != p && sz[xx] > mx2)
      mx2 = sz[xx], big = xx;
  for(auto xx : path[x])
    if(xx != big && xx != p)
      dfs(xx, x, false);
  if(big != -1) {
    dfs(big, x, true);
    hev[big] = true;
  }
  update(x, p, 1);
  res[x] = sm;
  if(big != -1)
    hev[big] = false;
  if(!k) {
    update(x, p, -1);
    mx = sm = 0;
  }
}

void size(int x, int p) {
  sz[x] = 1;
  for(auto xx : path[x]) {
    if(xx != p)
      size(xx, x), sz[x] += sz[xx];
  }
}

void solve() {
  size(1, 0);
  dfs(1, 0, true);
  for(int i = 1; i <= n; i++)
    cout << res[i] << " ";
}

void read() {
  cin >> n;
  for(int i = 1; i <= n; i++)
    cin >> col[i];
  for(int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    path[u].push_back(v);
    path[v].push_back(u);
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  read();
  solve();
}