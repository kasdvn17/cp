#include <bits/stdc++.h>
#define int long long
#define MAXX 502
using namespace std;

int n, a[MAXX][MAXX], grp[MAXX];
int val[MAXX];
vector<pair<int, int>> edges;

int real(vector<int>& nodes) {
    if(nodes.size() == 1)
        return nodes[0];
    int mxx = 0;
    for(auto u : nodes)
        for(auto v : nodes)
            mxx = max(mxx, a[u][v]);
    int grp = ++n;
    val[grp] = mxx;
    vector<bool> vis(nodes.size() + 1, false);
    for(int i = 0; i < (int)nodes.size(); i++) {
        if(vis[i])
            continue;
        vector<int> list;
        for(int j = i; j < (int)nodes.size(); j++)
            if(!vis[j] && a[nodes[i]][nodes[j]] < mxx) {
                list.push_back(nodes[j]);
                vis[j] = true;
            }
        int vv = real(list);
        edges.push_back({vv, grp});
    }
    return grp;
}

void solve() {
    for(int i = 1; i <= n; i++)
        val[i] = a[i][i];
    vector<int> list;
    for(int i = 1; i <= n; i++)
        list.push_back(i);
    int root = real(list);
    cout << n << "\n";
    for(int i = 1; i <= n; i++)
        cout << val[i] << " ";
    cout << "\n";
    cout << root << "\n";
    for(int vv = 0; vv < edges.size(); vv++)
        cout << edges[vv].first << " " << edges[vv].second << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> a[i][j];
}

void file() {
    if(fopen("TASK.INP", "r")) {
        freopen("TASK.INP", "r", stdin);
        freopen("TASK.OUT", "w", stdout);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    file();
    read();
    solve();
}