#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

struct Q {
    int l, r, idx;
};

int n, q, seen[MAXX], res[MAXX];
int a[MAXX], bit[MAXX];
Q queries[MAXX];

bool cmp(Q x, Q y) {
    return x.r < y.r;
}

void update(int idx, int val) {
    while(idx <= n) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}

int query(int idx) {
    int res = 0;
    while(idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void solve() {
    sort(queries + 1, queries + q + 1, cmp);
    int idx = 1;
    for(int i = 1; i <= q; i++) {
        int l = queries[i].l, r = queries[i].r;
        while(idx <= r) {
            if(seen[a[idx]] != 0)
                update(seen[a[idx]], -1);
            seen[a[idx]] = idx;
            update(idx, 1);
            // cout << "seen: " << idx << " | " << query(idx) << "\n";
            idx++;
        }
        res[queries[i].idx] = query(r) - query(l - 1);
    }
    for(int i = 1; i <= q; i++)
        cout << res[i] << "\n";
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= q; i++)
        cin >> queries[i].l >> queries[i].r, queries[i].idx = i;
}

void file() {
    if(fopen("TASK.INP", "r")) {
        (void)freopen("TASK.INP", "r", stdin);
        (void)freopen("TASK.OUT", "w", stdout);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    file();
    read();
    solve();
}