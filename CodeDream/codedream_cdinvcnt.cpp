#include <bits/stdc++.h>
#define int long long
#define MAXX 200002
using namespace std;

int n, res, a[MAXX], cnt[MAXX];
int bit[MAXX];

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

void dnc(int l, int r) {
    if(l >= r)
        return;
    int mid = (l + r) >> 1;
    for(int i = l; i <= mid; i++) {
        cnt[a[i]]++;
        update(a[i], 1);
    }
    for(int i = mid + 1; i <= r; i++)
        res += query(n) - query(a[i] - 1);
    for(int i = l; i <= mid; i++) {
        if(cnt[a[i]] == 0)
            continue;
        update(a[i], -cnt[a[i]]);
        cnt[a[i]] = 0;
    }
    dnc(l, mid);
    dnc(mid + 1, r);
}

void solve() {
    res = 0;
    dnc(1, n);
    cout << res << "\n";
}

void normalize() {
    vector<int> vec;
    for(int i = 1; i <= n; i++)
        vec.push_back(a[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
    }
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        read();
        normalize();
        solve();
    }
}