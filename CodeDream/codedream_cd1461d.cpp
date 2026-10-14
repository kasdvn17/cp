#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, q;
int a[MAXX], pf[MAXX], qu[MAXX];
map<int, int> res;

void correct(int x) {
    if(res.find(x) != res.end())
        res[x] = true;
}

void dnc(int l, int r) {
    if(l > r)
        return;
    if(l == r) {
        correct(a[l]);
        return;
    }
    correct(pf[r] - pf[l - 1]);
    int mid = (a[l] + a[r]) >> 1;
    int lo = l, hi = r, ans = l;
    while(lo <= hi) {
        int mid2 = (lo + hi) >> 1;
        if(a[mid2] <= mid)
            ans = mid2, lo = mid2 + 1;
        else
            hi = mid2 - 1;
    }
    // cout << l << " " << r << " " << mid << " " << ans << '\n';
    if(ans == r) {
        correct(pf[r] - pf[l - 1]);
        return;
    }
    dnc(l, ans);
    dnc(ans + 1, r);
}

void solve() {
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++)
        pf[i] = pf[i - 1] + a[i];
    dnc(1, n);
    for(int i = 1; i <= q; i++)
        if(res.find(qu[i]) != res.end() && res[qu[i]])
            cout << "Yes\n";
        else
            cout << "No\n";
}

void read() {
    res.clear();
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= q; i++)
        cin >> qu[i], res[qu[i]] = 0;
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

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
} 