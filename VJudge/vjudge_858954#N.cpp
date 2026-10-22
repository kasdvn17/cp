#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

int n, sz[MAXX], del[MAXX], res[MAXX];
vector<int> path[MAXX];

void dfs(int x, int p) {
  sz[x] = 1;
  for (auto v : path[x])
    if (v != p && !del[v]) dfs(v, x), sz[x] += sz[v];
}

int centroid(int x, int p, int n) {
  for (int v : path[x])
    if (v != p && sz[v] > n / 2 && !del[v]) return centroid(v, x, n);
  return x;
}

void proc(int u, int cur) {
  dfs(u, 0);
  int n = sz[u];
  int root = centroid(u, 0, n);
  res[root] = cur;
  del[root] = 1;
  for (int v : path[root])
    if (!del[v]) proc(v, cur + 1);
}

void solve() {
  proc(1, 0);
  for (int i = 1; i <= n; i++) cout << (char)(res[i] + 'A') << " ";
}

void read() {
  cin >> n;
  for (int i = 1; i < n; i++) {
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