#include <bits/stdc++.h>
#define int long long
#define MAXX 200002
using namespace std;

int n, k;
int a[MAXX], b[MAXX];

bool check(int m)
{
    for (int i = 1; i <= n; i++)
        if (a[i] >= m)
            b[i] = 1;
        else
            b[i] = -1;
    for (int i = 1; i <= n; i++)
        b[i] += b[i - 1];
    int mn = 0, mx = b[k];
    for (int i = k + 1; i <= n; i++)
        mn = min(mn, b[i - k]), mx = max(mx, b[i] - mn);
    return mx > 0;
}

void solve()
{
    int l = 1, r = n, ans = 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    cout << ans << "\n";
}

void read()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    read();
    solve();
}