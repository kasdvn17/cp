#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, a[MAXX];
int cnt[65];

void solve() {
    memset(cnt, 0, sizeof(cnt));
    bool ok = false;
    for(int i = 1; i <= n; i++)
        if(a[i] != a[1]) {
            ok = true;
            break;
        }
    if(!ok) {
        cout << a[1] << "\n";
        return;
    }
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        int cur = 0, tmp = a[i];
        while(a[i] > 0) {
            if(a[i] % 2 == 1)
                mx = max(mx, cur), cnt[cur]++;
            cur++;
            a[i] /= 2;
        }
        a[i] = tmp;
    }
    while(mx >= 0 && cnt[mx] == n)
        mx--;
    int res = 0;
    for(int i = 1; i <= n; i++)
        res |= a[i];
    res |= ((1ll << (mx + 1)) - 1);
    cout << res << "\n";
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

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}