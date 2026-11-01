#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, cnt, res, indeg[MAXX], tim[MAXX];
vector<int> path[MAXX];
queue<int> q;

void solve() {
    for(int i = 1; i <= n; i++)
        if(indeg[i] == 0)
            q.push(i), tim[i] = 1;
    while(q.size()) {
        int v = q.front();
        q.pop();
        cnt++;
        for(auto u : path[v])
            if(indeg[u]) {
                indeg[u]--;
                if(u < v)
                    tim[u] = max(tim[u], tim[v] + 1);
                else
                    tim[u] = max(tim[u], tim[v]);
                res = max(res, tim[u]);
                if(indeg[u] == 0)
                    q.push(u);
            }
    }
    if(cnt < n) {
        cout << "-1\n";
        return;
    }
    cout << res << "\n";
}

void read() {
    cin >> n;
    cnt = 0, res = 1;
    for(int i = 1; i <= n; i++)
        path[i].clear(), indeg[i] = 0, tim[i] = 0;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        for(int j = 1; j <= v; j++) {
            int t;
            cin >> t;
            path[t].push_back(i);
            indeg[i]++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}