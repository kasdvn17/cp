#include <bits/stdc++.h>
#define int long long
#define MAXX 100002
using namespace std;

int n, q, u, v;
int start[MAXX], en[MAXX], pf[MAXX], cnt = 0;
vector<int> path[MAXX];

void dfs(int u, int par) {
  cnt++, start[u] = cnt;
  for(auto v : path[u])
    if(v != par)
      dfs(v, u);
  en[u] = cnt;
}

void query() {
    if(start[u] <= start[v] && en[v] <= en[u])
        cout << "MA\n";
    else if(start[v] <= start[u] && en[u] <= en[v])
        cout << "RI\n";
    else
        cout << "SA\n";
}

void read() {
  cin >> n >> q;
  for(int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    path[u].push_back(v);
    path[v].push_back(u);
  }
  dfs(1, 0);
  while(q--) {
    cin >> u >> v;
    query();
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  read();
}