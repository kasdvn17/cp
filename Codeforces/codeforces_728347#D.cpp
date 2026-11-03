#include <bits/stdc++.h>
#define MAXX 300005
#define INF 1000000000
using namespace std;

struct Node {
    int mal, mar, curL, curR, res;
    int lazyL = 0, lazyR = 0;
};

int n, q;
set<int> msl, msr;
Node seg[4 * MAXX];

Node merge(Node x, Node y) {
    Node res;
    res.mal = max(x.mal, y.mal);
    res.mar = max(x.mar, y.mar);
    res.curL = x.curL == y.curL ? x.curL : -1;
    res.curR = x.curR == y.curR ? x.curR : -1;
    res.res = max(x.res, y.res);
    return res;
}

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = {INF, INF, -INF, INF, INF, 0, 0};
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
}

int calc(int idx, int l, int r) {
    int curL = seg[idx].curL, curR = seg[idx].curR;
    if(curL == -INF && curR == INF) return INF;
    if(curL == -INF) return curR - l;
    if(curR == INF) return r - curL;
    int m1 = (curL + curR) / 2, m2 = m1 + 1;
    int pos1 = max(l, min(m1, r)), pos2 = max(l, min(m2, r));
    return max(min(pos1 - curL, curR - pos1), min(pos2 - curL, curR - pos2));
}

void applyL(int idx, int l, int r, int X) {
    seg[idx].curL = X;
    seg[idx].mal = r - X;
    if(seg[idx].curR != -1)
        seg[idx].res = calc(idx, l, r);
    else
        seg[idx].res = seg[idx].mar;
}

void applyR(int idx, int l, int r, int X) {
    seg[idx].curR = X;
    seg[idx].mar = X - l;
    if(seg[idx].curL != -1)
        seg[idx].res = calc(idx, l, r);
    else
        seg[idx].res = seg[idx].mal;
}

void fix(int idx, int l, int r) {
    if(seg[idx].lazyL) {
        applyL(idx, l, r, seg[idx].lazyL);
        if(l != r) {
            seg[2 * idx].lazyL = seg[idx].lazyL;
            seg[2 * idx + 1].lazyL = seg[idx].lazyL;
        }
        seg[idx].lazyL = 0;
    }
    if(seg[idx].lazyR) {
        applyR(idx, l, r, seg[idx].lazyR);
        if(l != r) {
            seg[2 * idx].lazyR = seg[idx].lazyR;
            seg[2 * idx + 1].lazyR = seg[idx].lazyR;
        }
        seg[idx].lazyR = 0;
    }
}

int query(int idx, int l, int r, int s, int e) {
    fix(idx, l, r);
    if(l > e || r < s)
        return 0;
    if(l >= s && r <= e)
        return seg[idx].res;
    int mid = (l + r) >> 1;
    int res = 0;
    if(l <= mid) res = max(res, query(2 * idx, l, mid, s, e));
    if(mid < r) res = max(res, query(2 * idx + 1, mid + 1, r, s, e));
    return res;
}

void updateL(int idx, int l, int r, int s, int e, int pos) {
    fix(idx, l, r);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e && (seg[idx].curR != -1 || l - pos >= seg[idx].mar)) {
        seg[idx].lazyL = pos;
        fix(idx, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    updateL(2 * idx, l, mid, s, e, pos);
    updateL(2 * idx + 1, mid + 1, r, s, e, pos);
    seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
}

void updateR(int idx, int l, int r, int s, int e, int pos) {
    fix(idx, l, r);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e && (seg[idx].curL != -1 || pos - r >= seg[idx].mal)) {
        seg[idx].lazyR = pos;
        fix(idx, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    updateR(2 * idx, l, mid, s, e, pos);
    updateR(2 * idx + 1, mid + 1, r, s, e, pos);
    seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
}

void solve() {
    cin >> n >> q;
    build(1, 1, n);
    for(int i = 1; i <= q; i++) {
        int type, u, v, prvv;
        cin >> type >> u >> v;
        if(type == 1) {
            if(u == 0) {
                // L;
                if(msl.count(v))
                    continue;
                msl.insert(v);
                auto it = msl.lower_bound(v);
                if(it == msl.begin())
                    prvv = 1;
                else
                    prvv = (*prev(it)) + 1;
                updateR(1, 1, n, prvv, v, v);
            } else {
                // R;
                if(msr.count(v))
                    continue;
                msr.insert(v);
                auto it = msr.upper_bound(v);
                if(it == msr.end())
                    prvv = n;
                else
                    prvv = (*it) - 1;
                updateL(1, 1, n, v, prvv, v);
            }
        } else {
            int anss = query(1, 1, n, u, v);
            if(anss > n)
                cout << -1 << "\n";
            else
                cout << anss << "\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    solve();
}