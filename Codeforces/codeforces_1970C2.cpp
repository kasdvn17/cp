#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, pos;
vector<int> path[MAXX];

bool dfs(int x, int p) {
    // nguoi tai vi tri nay dfs xuong co thang duoc ko
    for(auto v : path[x]) {
        if(v == p)
            continue;
        bool z = dfs(v, x);
        if(!z)
            return true;
    }
    return false;
}

void solve() {
    if(dfs(pos, 0))
        cout << "Ron";
    else
        cout << "Hermione";
}

void read() {
    cin >> n >> pos;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
    cin >> pos;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}