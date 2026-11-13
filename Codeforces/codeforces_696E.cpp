#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

const int INF = 1e18;

int n, m, q;
int par[MAXX], d[MAXX], sz[MAXX];
int idgirl[MAXX];
int chains, poschains, head[MAXX], cid[MAXX], cpos[MAXX], hlid[MAXX];
pair<int, int> st[4 * MAXX];
int lazy[4 * MAXX];
vector<int> path[MAXX];
deque<int> girls[MAXX];

void fix(int id, int l, int r) {
    if(!lazy[id]) return;
    st[id].first += lazy[id];
    if(l != r) {
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
    }
    lazy[id] = 0;
}

void build(int id, int l, int r) {
    if (l == r) {
        int _l = hlid[l];
        if(girls[_l].size()) {
            int g = girls[_l].front();
            st[id] = {g, g};
        } else {
            st[id] = {INF, 0};
        }
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

void update_point(int id, int l, int r, int pos, pair<int, int> val) {
    fix(id, l, r);
    if(l > pos || r < pos) return;
    if(l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    update_point(2 * id, l, mid, pos, val);
    update_point(2 * id + 1, mid + 1, r, pos, val);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

void update_seg(int id, int l, int r, int s, int e, int v) {
    fix(id, l, r);
    if(l > e || r < s) return;
    if (l >= s && r <= e) {
        lazy[id] += v;
        fix(id, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update_seg(id * 2, l, mid, s, e, v);
    update_seg(id * 2 + 1, mid + 1, r, s, e, v);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

pair<int, int> query_seg(int id, int l, int r, int u, int v) {
    fix(id, l, r);
    if (v < l || u > r) return {INF, 0};
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) / 2;
    return min(query_seg(id * 2, l, mid, u, v),
               query_seg(id * 2 + 1, mid + 1, r, u, v));
}

void dfs(int s, int p) {
    sz[s] = 1;
    par[s] = p;
    for(int v : path[s]) {
        if(v == p) continue;
        d[v] = d[s] + 1;
        dfs(v, s);
        sz[s] += sz[v];
    }
}

void hld(int s, int p) {
    if(!head[chains]) head[chains] = s;
    cid[s] = chains;
    cpos[s] = poschains;
    hlid[poschains] = s;
    poschains++;
    int nxt = 0;
    for(auto xx : path[s])
        if(xx != p && sz[xx] > sz[nxt])
            nxt = xx;
    if(nxt) hld(nxt, s);
    for(auto xx : path[s])
        if(xx != p && xx != nxt)
            chains++, hld(xx, s);
}

int lca(int u, int v) {
    while(cid[u] != cid[v]) {
        if(cid[u] > cid[v])
            u = par[head[cid[u]]];
        else
            v = par[head[cid[v]]];
    }
    if(d[u] < d[v]) return u;
    else return v;
}

void query(int u, int v, int k) {
    int lc = lca(u, v);
    vector<int> res;
    int _u = u, _v = v;
    while(k--) {
        u = _u, v = _v;
        pair<int, int> ans = {INF, 0};
        while(cid[u] != cid[lc])
            ans = min(ans, query_seg(1, 1, n, cpos[head[cid[u]]], cpos[u])),
            u = par[head[cid[u]]];
        while(cid[v] != cid[lc])
            ans = min(ans, query_seg(1, 1, n, cpos[head[cid[v]]], cpos[v])),
            v = par[head[cid[v]]];
        if(d[u] > d[v]) swap(u, v);
        ans = min(ans, query_seg(1, 1, n, cpos[u], cpos[v]));
        if(ans.second == 0 || ans.first >= INF) break;
        int idg = idgirl[ans.second];
        res.push_back(ans.second);
        girls[idg].pop_front();
        if(girls[idg].empty()) {
            update_point(1, 1, n, cpos[idg], {INF, 0});
        } else {
            int nxt = girls[idg].front();
            int new_val = ans.first - ans.second + nxt;
            update_point(1, 1, n, cpos[idg], {new_val, nxt});
        }
    }
    cout << res.size() << " ";
    for(auto x : res) cout << x << " ";
    cout << "\n";
}

void solve() {
    poschains = chains = 1;
    dfs(1, 0);
    hld(1, 0);
    build(1, 1, n);
    while(q--) {
        int type, u, v, k;
        cin >> type;
        if(type == 1) {
            cin >> u >> v >> k;
            query(u, v, k);
        } else {
            cin >> v >> k;
            update_seg(1, 1, n, cpos[v], cpos[v] + sz[v] - 1, k);
        }
    }
}

void read() {
    cin >> n >> m >> q;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
    }
    for(int i = 1; i <= m; i++) {
        int idx;
        cin >> idx;
        girls[idx].push_back(i);
        idgirl[i] = idx;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}