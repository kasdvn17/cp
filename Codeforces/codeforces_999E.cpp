#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, m, s, res, rc1[MAXX], scc[MAXX], indeg[MAXX], vis[MAXX];
int cntscc = 0, timdfs = 0, num[MAXX], low[MAXX];
vector<int> path[MAXX], scc_path[MAXX];
pair<int, int> edges[MAXX];
stack<int> st;

void dfs_first(int x) {
    rc1[x] = true;
    for(auto v : path[x])
        if(!rc1[v])
            dfs_first(v);
}

void tarjan(int x) {
    num[x] = low[x] = ++timdfs;
    st.push(x);
    for(auto v : path[x]) {
        if(rc1[v])
            continue;
        if(vis[v])
            continue;
        if(!num[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
        } else
            low[x] = min(low[x], num[v]);
    }
    if(num[x] == low[x]) {
        cntscc++;
        int z;
        do {
            z = st.top();
            st.pop();
            scc[z] = cntscc;
            vis[z] = true;
        } while(z != x);
    }
}

void solve() {
    dfs_first(s);
    for(int i = 1; i <= n; i++)
        if(!rc1[i] && !vis[i])
            tarjan(i);
    for(int i = 1; i <= m; i++) {
        int u = edges[i].first, v = edges[i].second;
        if(!scc[u] || !scc[v] || scc[u] == scc[v])
            continue;
        indeg[scc[v]]++;
    }
    for(int i = 1; i <= cntscc; i++)
        if(indeg[i] == 0)
            res++;
    cout << res;
}

void read() {
    cin >> n >> m >> s;
    for(int i = 1; i <= m; i++) {
        cin >> edges[i].first >> edges[i].second;
        path[edges[i].first].push_back(edges[i].second);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}