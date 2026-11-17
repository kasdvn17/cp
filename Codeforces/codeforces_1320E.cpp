#include <bits/stdc++.h>
#define MAXX 300005
using namespace std;

struct SPQ {
    int iturn, itime, ivirus, rmndis, dinh;

    bool operator>(const SPQ& other) const {
        // SPQ > other
        if(iturn != other.iturn) return iturn > other.iturn;
        if(ivirus != other.ivirus) return ivirus > other.ivirus;
        return rmndis < other.rmndis;
    }
};

struct DPQ {
    int iturn, itime, ivirus, rmndis;

    bool operator>(const DPQ& other) const {
        // DPQ > other
        if(iturn != other.iturn) return iturn > other.iturn;
        if(ivirus != other.ivirus) return ivirus > other.ivirus;
        return rmndis < other.rmndis;
    }
};

struct V {
    int speed, icity;
};

struct Compare {
    bool operator()(const SPQ& a, const SPQ& b) const {
        // return true neu b len pq.top() trc
        if(a.iturn != b.iturn) return a.iturn > b.iturn;
        if(a.ivirus != b.ivirus) return a.ivirus > b.ivirus;
        return a.rmndis < b.rmndis;
    }
};

int n, q, k, m;
int timdfs, tin[MAXX], tout[MAXX], h[MAXX], up[20][MAXX];
int ans = 0, timer, important[MAXX];
V virus[MAXX];
vector<int> path[MAXX], oripath[MAXX];
vector<int> impcities;
vector<pair<int, int>> vtv;
// dijkstra
// luu index turn - index virus - dis con lai - dinh
DPQ d[MAXX];
priority_queue<SPQ, vector<SPQ>, Compare> pq;

void dfs(int x, int p) {
    h[x] = h[p] + 1;
    up[0][x] = p;
    tin[x] = ++timdfs;
    for(auto v : oripath[x])
        if(v != p)
            dfs(v, x);
    tout[x] = ++timdfs;
}

inline bool isimp(int x) {
    return important[x] == timer;
}

int lca(int u, int v) {
    if(h[u] != h[v]) {
        if(h[u] > h[v])
            swap(u, v);
        int diff = h[v] - h[u];
        for(int k = 0; k < 20; k++)
            if(diff >> k & 1)
                v = up[k][v];
    }
    if(u == v)
        return u;
    int lg = __lg(h[u]);
    for(int k = 19; k >= 0; k--)
        if(up[k][u] != up[k][v])
            u = up[k][u], v = up[k][v];
    return up[0][u];
}

int dist(int u, int v) {
    return h[u] + h[v] - 2 * h[lca(u, v)];
}

// build virtual tree
void bvt() {
    sort(vtv.begin(), vtv.end());
    int z = vtv.size();
    for(int i = 1; i < z; i++) {
        int lcc = lca(vtv[i].second, vtv[i - 1].second);
        vtv.push_back({tin[lcc], lcc});
    }
    sort(vtv.begin(), vtv.end());
    vtv.erase(unique(vtv.begin(), vtv.end()), vtv.end());
    for(int i = 1; i < vtv.size(); i++) {
        int lcc = lca(vtv[i].second, vtv[i - 1].second);
        path[lcc].push_back(vtv[i].second);
        path[vtv[i].second].push_back(lcc);
    }
}

void query() {
    bvt();
    for(auto [_, x] : vtv)
        d[x] = {(int)1e6, (int)1e6, (int)0};
    for(int i = 1; i <= k; i++) {
        int ct = virus[i].icity;
        d[ct] = {0, 0, i, 0};
        pq.push({0, 0, i, 0, ct});
    }
    while(pq.size()) {
        auto [turn, itime, idv, rmndis, dinh] = pq.top();
        pq.pop();
        DPQ tmp = {turn, itime, idv, rmndis};
        if(tmp > d[dinh])
            continue;
        for(auto v : path[dinh]) {
            int distt = dist(v, dinh);
            int ntime = itime + distt;
            if(distt > rmndis) {
                int rmnn = distt - rmndis;
                int speed = virus[idv].speed;
                int nturn = turn + (rmnn + speed - 1) / speed;
                int z = speed * (nturn - turn) - rmnn;
                DPQ tmp2 = {nturn, ntime, idv, z};
                if(d[v] > tmp2) {
                    d[v] = tmp2;
                    pq.push({nturn, ntime, idv, z, v});
                }
            } else {
                int rmn2 = rmndis - distt;
                DPQ tmp2 = {turn, ntime, idv, rmn2};
                if(d[v] > tmp2) {
                    d[v] = tmp2;
                    pq.push({turn, ntime, idv, rmn2, v});
                }
            }
        }
    }
    // for(auto [_, x] : vtv)
    //     cout << x << " " << d[x].ivirus << "\n";
    for(auto x : impcities)
        cout << d[x].ivirus << " ";
    cout << "\n";
    for(auto [_, x] : vtv)
        path[x].clear();
}

void solve() {
    dfs(1, 0);
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i <= n; i++)
            up[lg][i] = up[lg - 1][up[lg - 1][i]];
    cin >> q;
    while(q--) {
        cin >> k >> m;
        ans = 0;
        timer++;
        vtv.clear();
        impcities.clear();
        for(int i = 1; i <= k; i++)
            cin >> virus[i].icity >> virus[i].speed, vtv.push_back({tin[virus[i].icity], virus[i].icity});
        for(int i = 1; i <= m; i++) {
            int t;
            cin >> t;
            important[t] = timer;
            vtv.push_back({tin[t], t});
            impcities.push_back(t);
        }
        query();
    }
}

void read() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        oripath[u].push_back(v);
        oripath[v].push_back(u);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}