#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

struct Q {
    int type, res, idx;
};

int n, vis[MAXX], indeg[MAXX], cnt;
int cntsf;
bool hasst, hasust;
vector<int> restrue;
Q queries[MAXX];
vector<int> path[MAXX], res;
queue<int> q;

void dfs(int v) {
    if(vis[v])
        return;
    vis[v] = true;
    for(auto z : path[v])
        dfs(z);
}

void solve() {
    for(int i = 1; i <= n; i++)
        if(queries[i].res) {
            restrue.push_back(i);
            if(queries[i].type == 1)
                dfs(i), hasst = true;
            else hasust = true;
        } else if(queries[i].type == 1)
            cntsf++;
    if(restrue.size() == 2 && queries[restrue[0]].type == queries[restrue[1]].type) {
        cout << -1;
        return;
    }
    if(restrue.empty() && cntsf) {
        cout << -1;
        return;
    }
    if(!hasst && hasust) {
        cout << -1;
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(vis[i] && !queries[i].res && queries[i].type == 2 && !hasust) {
            cout << -1;
            return;
        }
    }
    for(auto idx : restrue) {
        int tat; // trang thai after this
        if(queries[idx].type == 1) tat = 1;
        else tat = 0;
        for(int i = 1; i <= n; i++) {
            if(i == idx)
                continue;
            int v1 = queries[i].type, v2 = queries[i].res;
            if(v2 && v1 == 2) {
                path[idx].push_back(i);
                continue;
            }
            if(v1 == 2 && tat == 1 && !vis[i])
                path[i].push_back(idx);
            if(v1 == 1 && tat == 1)
                path[idx].push_back(i);
            if(v1 == 1 && tat == 0)
                path[i].push_back(idx);
            if(v1 == 2 && tat == 0 && vis[i]) {
                path[idx].push_back(i);
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        // cout << "list: " << i << " -> ";
        sort(path[i].begin(), path[i].end());
        path[i].erase(unique(path[i].begin(), path[i].end()), path[i].end());
        for(auto v : path[i])
            indeg[v]++;
        // cout << "\n";
    }
    for(int i = 1; i <= n; i++) {
        // cout << "deg: " << i << " " << indeg[i] << "\n";
        if(indeg[i] == 0)
            q.push(i);
    }
    while(q.size()) {
        int z = q.front();
        q.pop();
        cnt++;
        res.push_back(z);
        for(auto v : path[z])
            if(indeg[v]) {
                indeg[v]--;
                if(indeg[v] == 0)
                    q.push(v);
            }
    }
    if(cnt != n) {
        cout << -1;
        return;
    }
    for(auto v : res)
        cout << v << " ";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        string a, b;
        cin >> a >> b;
        if(a == "set") queries[i].type = 1;
        else queries[i].type = 2;
        if(b == "false") queries[i].res = 0;
        else queries[i].res = 1;
        queries[i].idx = i;
    }
    int m;
    cin >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}