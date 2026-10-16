#include <bits/stdc++.h>
#define int long long
#define MAXX 1000002
using namespace std;

int n, p, q, cntb, bbb[MAXX];
int a[MAXX], seg[4 * MAXX];

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = a[l] % p;
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    seg[idx] = (seg[2 * idx] * seg[2 * idx + 1]) % p;
}

int query(int idx, int l, int r, int s, int e) {
    if(l > e || r < s)
        return 1;
    if(l >= s && r <= e)
        return seg[idx];
    int mid = (l + r) >> 1;
    return (query(2 * idx, l, mid, s, e) * query(2 * idx + 1, mid + 1, r, s, e)) % p;
}

void solve() {
    build(1, 0, n - 1);
    int prvans = 0, prevvL = 0, prevvR = 0;
    for(int i = 0; i < q; i++) {
        int L, R;
        if(i % 64 == 0) {
            L = (bbb[i / 64] + prvans) % n;
            R = (bbb[i / 64 + 1] + prvans) % n;
        } else {
            L = (prevvL + prvans) % n;
            R = (prevvR + prvans) % n;
        }
        if(L > R) swap(L, R);
        prevvL = L, prevvR = R;
        prvans = (query(1, 0, n - 1, L, R) + 1) % p;
    }
    cout << prvans << "\n";
}

void read() {
    cin >> n >> p >> q;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    cntb = (int)(q / 64) + 2;
    for(int i = 0; i < cntb; i++)
        cin >> bbb[i];
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