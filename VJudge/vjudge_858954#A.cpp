#include <bits/stdc++.h>
#define int long long
#define MAXX 5002
using namespace std;

int n, a[MAXX];
pair<int, int> sp[20][MAXX];

pair<int, int> query(int l, int r) {
    int lg = __lg(r - l + 1);
    return min(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
}

int dnc(int l, int r, int rmv) {
    if(l > r)
        return 0;
    int mid = query(l, r).second;
    cerr << l << " " << mid << " " << r << "\n";
    int v1 = dnc(l, mid - 1, a[mid]);
    int v2 = dnc(mid + 1, r, a[mid]);
    cerr << l << " " << r << " " << v1 << " " << v2 << " " << mid << " " << rmv << "\n";
    return min(r - l + 1, v1 + v2 + a[mid] - rmv);
    // return 0;
}

void solve() {
    for(int i = 1; i <= n; i++)
        sp[0][i] = {a[i], i};
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i + (1 << lg) - 1 <= n; i++)
            sp[lg][i] = min(sp[lg - 1][i], sp[lg - 1][i + (1 << (lg - 1))]);
    cout << dnc(1, n, 0);
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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