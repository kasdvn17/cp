#include <bits/stdc++.h>
#define int long long
#define MAXX 300005
using namespace std;

int n, a[MAXX];
int pf[MAXX], sf[MAXX];

void solve() {
    pf[0] = 0, sf[n] = 0;
    int k = 1;
    for(int i = 1; i < n; i++)
        pf[i] = max(pf[i - 1], abs(a[i] - a[i + 1]));
    for(int i = n - 1; i >= 1; i--)
        sf[i] = max(sf[i + 1], abs(a[i] - a[i + 1]));
    for(int i = 1; i < n; i++)
        if(abs(a[i] - a[i + 1]) > abs(a[k] - a[k + 1]))
            k = i;
    int ans = abs(a[k] - a[k + 1]);
    // xoa abs(a[l] - a[l - 1]) va thay bang abs(a[l - 1] - 2 * a[r])
    // co dinh l
    int l = k + 1, mxx = 0;
    for(int r = l; r <= n; r++) {
        if(r > l)
            mxx = max(mxx, 2 * abs(a[r - 1] - a[r]));
        int tmp = mxx;
        if(l >= 2) {
            tmp = max(tmp, pf[l - 2]);
            tmp = max(tmp, abs(a[l - 1] - 2 * a[r]));
        }
        if(r < n) {
            tmp = max(tmp, sf[r + 1]);
            tmp = max(tmp, abs(2 * a[l] - a[r + 1]));
        }
        ans = min(ans, tmp);
    }
    // co dinh r
    int r = k;
    mxx = 0;
    for(int l = r; l >= 1; l--) {
        if(l < r)
            mxx = max(mxx, 2 * abs(a[l] - a[l + 1]));
        int tmp = mxx;
        if (l >= 2) {
            tmp = max(tmp, pf[l - 2]);
            tmp = max(tmp, abs(a[l - 1] - 2 * a[r]));
        }
        if (r < n) {
            tmp = max(tmp, sf[r + 1]);
            tmp = max(tmp, abs(2 * a[l] - a[r + 1]));
        }
        ans = min(ans, tmp);
    }
    cout << ans << "\n";
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
        solve();
    }
}