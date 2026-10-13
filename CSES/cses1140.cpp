#include <bits/stdc++.h>
#define int long long
#define MAXX 500005
using namespace std;

struct S {
    int l, r, c;
};

int n, mx, res, bit[MAXX];
S segs[MAXX];

void update(int idx, int val) {
    while(idx <= mx) {
        bit[idx] = max(bit[idx], val);
        idx += idx & (-idx);
    }
}

int query(int idx) {
    int res = 0;
    while(idx > 0) {
        res = max(res, bit[idx]);
        idx -= idx & (-idx);
    }
    return res;
}

bool cmp(S x, S y) {
    return x.r < y.r;
}

void solve() {
    sort(segs + 1, segs + n + 1, cmp);
    for(int i = 1; i <= n; i++) {
        int v = query(segs[i].l - 1) + segs[i].c;
        res = max(res, v);
        update(segs[i].r, v);
    }
    cout << res;
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> segs[i].l >> segs[i].r >> segs[i].c;
}

void normalize() {
    vector<int> vec;
    for(int i = 1; i <= n; i++) {
        vec.push_back(segs[i].l);
        vec.push_back(segs[i].r);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++) {
        segs[i].l = lower_bound(vec.begin(), vec.end(), segs[i].l) - vec.begin() + 1;
        segs[i].r = lower_bound(vec.begin(), vec.end(), segs[i].r) - vec.begin() + 1;
    }
    mx = vec.size();
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
    normalize();
    solve();
}