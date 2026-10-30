#include <bits/stdc++.h>
#define MAXX 1002
using namespace std;

int n, par[MAXX], sz[MAXX];
set<int> st;
vector<pair<int, int>> repls;

int find_set(int x) {
    if(x == par[x])
        return x;
    return par[x] = find_set(par[x]);
}

void join(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if(u == v)
        return;
    if(sz[u] > sz[v])
        swap(u, v);
    par[u] = v;
    sz[v] += sz[u];
}

void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        par[i] = i, sz[i] = 1;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        if(find_set(u) == find_set(v))
            repls.push_back({u, v});
        join(u, v);
    }
    for(int i = 1; i <= n; i++)
        st.insert(find_set(i));
    cout << repls.size() << "\n";
    for(auto [u, v] : repls) {
        int x1 = *st.begin(), x2 = *st.rbegin();
        cout << u << " " << v << " " << x1 << " " << x2 << "\n";
        st.erase(x1);
        st.erase(x2);
        join(x1, x2);
        st.insert(find_set(x1));
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    solve();
}