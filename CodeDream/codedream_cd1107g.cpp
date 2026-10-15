#include <bits/stdc++.h>
#define int long long
#define DEBUG false
#define MAXX 300005
using namespace std;

struct C {
    int c, d, diff;
};

int n, res, a, pf[MAXX];
int spDiff[20][MAXX], spPf[20][MAXX];
// L[i], R[i]: xa nhat ma cm[i].diff la max
C cm[MAXX];

int query(int l, int r, int sp[20][MAXX]) {
    int lg = __lg(r - l + 1);
    return max(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
}

void dnc(int l, int r) {
    if(l > r)
        return;
    if(l == r) {
        res = max(res, pf[r] - pf[l - 1]);
        return;
    }
    int mid = (l + r) >> 1;
    dnc(l, mid);
    dnc(mid + 1, r);
    if(DEBUG)
        cout << "check: " << l << " " << mid << " " << r << "\n";
    for(int i = mid; i >= l; i--) {
        int mxDiff = query(i, mid, spDiff);
        if(DEBUG)
            cout << i << " " << mxDiff << "\n";
        // tim r xa nhat ma query(mid, r) <= mxDiff
        int lo = mid, hi = r, ans = lo;
        while(lo <= hi) {
            int m2 = (lo + hi) >> 1;
            if(query(mid, m2, spDiff) <= mxDiff)
                ans = m2, lo = m2 + 1;
            else
                hi = m2 - 1;
        }
        int z = query(mid, min(ans + 1, n), spPf);
        if(DEBUG)
            cout << i << " " << mxDiff << " " << z << " " << pf[l - 1] << " " << ans << "\n";
        res = max(res, z - pf[i - 1] - mxDiff);
    }
}

void solve() {
    cm[n + 1].d = cm[n].d;
    for(int i = 1; i <= n; i++) {
        cm[i].c = a - cm[i].c;
        cm[i].diff = (cm[i + 1].d - cm[i].d) * (cm[i + 1].d - cm[i].d);
        pf[i] = pf[i - 1] + cm[i].c;
    }
    for(int i = 1; i <= n; i++) {
        spDiff[0][i] = cm[i].diff;
        spPf[0][i] = pf[i];
    }
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i + (1 << lg) - 1 <= n; i++) {
            spDiff[lg][i] = max(spDiff[lg - 1][i], spDiff[lg - 1][i + (1 << (lg - 1))]);
            spPf[lg][i] = max(spPf[lg - 1][i], spPf[lg - 1][i + (1 << (lg - 1))]);
        }
    dnc(1, n);
    cout << res;
}

void read() {
    cin >> n >> a;
    for(int i = 1; i <= n; i++)
        cin >> cm[i].d >> cm[i].c;
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