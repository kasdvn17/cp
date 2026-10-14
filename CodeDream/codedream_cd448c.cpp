#include <bits/stdc++.h>
#define int long long
#define MAXX 5002
using namespace std;

int n, a[MAXX];
int res = 0;

int dnc(int l, int r, int x) {
    if (l > r)
        return 0;
    int mid = l;
    for (int i = l; i <= r; i++)
        if (a[mid] > a[i])
            mid = i;
    return min(r - l + 1, a[mid] - x + dnc(l, mid - 1, a[mid]) + dnc(mid + 1, r, a[mid]));
}

void solve() {
    cout << dnc(1, n, 0);
}

void read() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}

void file() {
    if (fopen("TASK.INP", "r")) {
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