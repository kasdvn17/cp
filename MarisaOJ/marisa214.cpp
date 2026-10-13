#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

struct ST {
    int x, y, k;

    bool operator==(const ST& other) const {
        return x == other.x && y == other.y && k == other.k;
    }
};

const ST noo = {0, 0, 0};
int n, q;
int a[MAXX], b[MAXX];
ST seg[4 * MAXX], lazy[4 * MAXX];

void fix(int idx, int l, int r) {
    if(lazy[idx] == noo)
        return;
    seg[idx] = lazy[idx];
    if(l != r) {
        lazy[2 * idx] = lazy[idx];
        lazy[2 * idx + 1] = lazy[idx];
    }
    lazy[idx] = {0, 0, 0};
}

void update(int idx, int l, int r, int s, int e, int x, int y, int k) {
    fix(idx, l, r);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e) {
        lazy[idx] = {x, y, k};
        fix(idx, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * idx, l, mid, s, e, x, y, k);
    update(2 * idx + 1, mid + 1, r, s, e, x, y, k);
}

ST query(int idx, int l, int r, int pos) {
    fix(idx, l, r);
    if(l > pos || r < pos)
        return noo;
    if(l == r)
        return seg[idx];
    int mid = (l + r) >> 1;
    if(pos >= l && pos <= mid)
        return query(2 * idx, l, mid, pos);
    else
        return query(2 * idx + 1, mid + 1, r, pos);
}

void solve1(int x, int y, int k) {
    update(1, 1, n, y, y + k - 1, x, y, k);
}

int solve2(int i) {
    ST v = query(1, 1, n, i);
    if(v == noo)
        return b[i];
    int def = i - v.y;
    return a[v.x + def];
}

void solve() {
    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            solve1(x, y, k);
        } else {
            int idx;
            cin >> idx;
            cout << solve2(idx) << "\n";
        }
    }
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];
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