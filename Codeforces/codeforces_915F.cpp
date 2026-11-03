#include <bits/stdc++.h>
#define int long long
#define MAXX 1000005
using namespace std;

int n, a[MAXX], par[MAXX], sz[MAXX];
int res = 0;

int find_set(int x) {
  if(x == par[x])
    return x;
  return par[x] = find_set(par[x]);
}

void join(int u, int v) {
  u = find_set(u), v = find_set(v);
  if(u == v)
    return;
  if(sz[u] > sz[v])
    swap(u, v);
  sz[v] += sz[u];
  par[u] = v;
}

struct E {
  int u, v;
};

bool cmp1(E x, E y) {
  return max(a[x.u], a[x.v]) < max(a[y.u], a[y.v]);
}

bool cmp2(E x, E y) {
  return min(a[x.u], a[x.v]) > min(a[y.u], a[y.v]);
}

vector<E> edges;

void solve() {
  sort(edges.begin(), edges.end(), cmp1);
  for(int i = 1; i <= n; i++)
    par[i] = i, sz[i] = 1;
  for(auto vv : edges) {
    res += max(a[vv.u], a[vv.v]) * sz[find_set(vv.u)] * sz[find_set(vv.v)];
    join(vv.u, vv.v);
  }
}

void solve2() {
  sort(edges.begin(), edges.end(), cmp2);
  for(int i = 1; i <= n; i++)
    par[i] = i, sz[i] = 1;
  for(auto vv : edges) {
    res -= min(a[vv.u], a[vv.v]) * sz[find_set(vv.u)] * sz[find_set(vv.v)];
    join(vv.u, vv.v);
  }
  cout << res;
}

void read() {
  cin >> n;
  for(int i = 1; i <= n; i++)
    cin >> a[i];
  for(int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    edges.push_back({u, v});
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  read();
  solve();
  solve2();
}