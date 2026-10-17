#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, a[MAXX], rev[MAXX];
int spMin[20][MAXX], spMax[20][MAXX];
long long res = 0;

int queryMax(int l, int r) {
    int lg = __lg(r - l + 1);
    return max(spMax[lg][l], spMax[lg][r - (1 << lg) + 1]);
}

int queryMin(int l, int r) {
    int lg = __lg(r - l + 1);
    return min(spMin[lg][l], spMin[lg][r - (1 << lg) + 1]);
}

void dnc(int l, int r) {
    if(l >= r)
        return;
    int mid = (l + r) >> 1;
    // cout << "checking: " << l << " " << mid << " " << r << "\n";
    for(int i = mid; i >= l; i--) {
        int mxx = queryMax(i, mid);
        int tar = mxx - a[i];
        int nww = rev[tar];
        if(nww <= mid || nww > r)
            continue;
        if(queryMax(mid, nww) > mxx)
            continue;
        res++;
    }
    for(int i = mid + 1; i <= r; i++) {
        int mxx = queryMax(mid + 1, i);
        int tar = mxx - a[i];
        int nww = rev[tar];
        if(nww < l || nww > mid)
            continue;
        if(queryMax(nww, mid) >= mxx)
            continue;
        res++;
    }
    dnc(l, mid);
    dnc(mid + 1, r);
}

void solve() {
    for(int i = 1; i <= n; i++)
        spMin[0][i] = spMax[0][i] = a[i];
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i + (1 << lg) - 1 <= n; i++) {
            spMin[lg][i] = min(spMin[lg - 1][i], spMin[lg - 1][i + (1 << (lg - 1))]);
            spMax[lg][i] = max(spMax[lg - 1][i], spMax[lg - 1][i + (1 << (lg - 1))]);
        }
    dnc(1, n);
    cout << res;
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i], rev[a[i]] = i;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}
