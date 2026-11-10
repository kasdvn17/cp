#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, m, s, e = 0;
int par[MAXX], cid[MAXX], par2;
vector<int> path[MAXX];
stack<int> trace1, trace2;

void dfs(int x, int p, int idd) {
    if(e) return;
    cid[x] = idd;
    par[x] = p;
    for(auto v : path[x]) {
        if(v == s)
            continue;
        if(par[v] && cid[v] != idd) {
            e = v;
            par2 = x;
            return;
        }
        if(par[v])
            continue;
        dfs(v, x, idd);
    }
}

void solve() {
    for(auto v : path[s]) {
        if(par[v]) {
            e = v;
            par2 = s;
            break;
        }
        dfs(v, s, v);
        if(e)
            break;
    }
    if(!e) {
        cout << "Impossible";
        return;
    }
    int cur = e;
    while(cur != 0) {
        trace1.push(cur);
        cur = par[cur];
    }
    trace2.push(e);
    cur = par2;
    while(cur != 0) {
        trace2.push(cur);
        cur = par[cur];
    }
    cout << "Possible\n";
    cout << trace1.size() << "\n";
    while(trace1.size())
        cout << trace1.top() << " ", trace1.pop();
    cout << "\n" << trace2.size() << "\n";
    while(trace2.size())
        cout << trace2.top() << " ", trace2.pop();
}

void read() {
    cin >> n >> m >> s;
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