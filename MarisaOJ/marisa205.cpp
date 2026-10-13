#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

struct S {
    int l, r, c;
};

int n, q, dp[MAXX], st[4 * MAXX], lazy[4 * MAXX];
S segs[MAXX];

bool cmp(S x, S y) {
    return x.r < y.r;
}

void build(int idx, int l, int r) {
    st[idx] = 1e18;
    if(l == r)
        return;
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
}

void fix(int idx, int l, int r) {
    if(lazy[idx] == -1)
        return;
    st[idx] = lazy[idx];
    if(l != r) {
        lazy[2 * idx] = lazy[idx];
        lazy[2 * idx + 1] = lazy[idx];
    }
    lazy[idx] = -1;
}

void update(int idx, int l, int r, int s, int e, int val) {
    fix(idx, l, r);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e) {
        lazy[idx] = val;
        fix(idx, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * idx, l, mid, s, e, val);
    update(2 * idx + 1, mid + 1, r, s, e, val);
    st[idx] = min(st[2 * idx], st[2 * idx + 1]);
}

int query(int idx, int l, int r, int s, int e) {
    fix(idx, l, r);
    if(l > e || r < s)
        return 1e18;
    if(l >= s && r <= e)
        return st[idx];
    int mid = (l + r) >> 1;
    return min(query(2 * idx, l, mid, s, e), query(2 * idx + 1, mid + 1, r, s, e));
}

// walk tim thang lon nhat <= val
int walk(int idx, int l, int r, int s, int e, int val) {
    fix(idx, l, r);
    // cerr << "fixed: " << idx << " " << l << " " << r << " " << s << " " << e << "\n";
    if(l > e || r < s)
        return -1;
    if(st[idx] > val)
        return -1;
    if(l == r)
        return l;
    int mid = (l + r) >> 1;
    int se = walk(2 * idx + 1, mid + 1, r, s, e, val);
    if(se != -1)
        return se;
    int fr = walk(2 * idx, l, mid, s, e, val);
    // cerr << "walked: " << idx << " " << l << " " << r << "\n";
    return fr;
}

void solve() {
    build(1, 0, n);
    memset(lazy, -1, sizeof(lazy));
    sort(segs + 1, segs + q + 1, cmp);
    update(1, 0, n, 0, 0, 0);
    // cerr << query(1, 0, n, 0, n) << "\n";
    for(int i = 1; i <= q; i++) {
        int l = segs[i].l, r = segs[i].r;
    //     // for(int j = r - 1; j >= l - 1; j--)
    //     //     mnn = min(mnn, dp[j]);
        int mnn = query(1, 0, n, l - 1, r);
        if(mnn >= 1e18)
            continue;
        int co = mnn + segs[i].c;
        // cerr << l << " " << r << " " << co << "\n";
        int idx = walk(1, 0, n, l, r, co);
        // cerr << idx << "\n";
        int L;
        if(idx == -1)
            L = l;
        else
            L = idx + 1;
        // cerr << L << " " << r << " err\n";
        update(1, 0, n, L, r, co);
    }
    int v = query(1, 0, n, n, n);
    if(v >= 1e18)
        cout << -1;
    else
        cout << v;
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= q; i++)
        cin >> segs[i].l >> segs[i].r >> segs[i].c;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cerr.tie(0);

    read();
    solve();
}