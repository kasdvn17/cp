#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, x, a[MAXX];

bool check(int k) {
    int cnt = 0, prv = -3e18;
    for(int i = 1; i <= n; i++) {
        if (a[i] <= prv + k) {
            prv = a[i];
            continue;
        }
        if(i < n && a[i + 1] - a[i] <= k) {
            prv = a[i + 1];
            i++;
        } else if(i < n && a[i + 1] - a[i] <= 2 * k) {
            cnt++;
            prv = a[i + 1];
            i++;
        } else {
            cnt++;
            prv = a[i] + k;
        }
    }
    return cnt <= x;
}

void solve() {
    sort(a + 1, a + n + 1);
    int l = 1, r = 1e9, ans = 1e9;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    cout << ans << "\n";
}

void read() {
    cin >> n >> x;
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