#include <bits/stdc++.h>
#define int long long
#define MAXX 500005
using namespace std;

int n, a[MAXX];
int res = 1e9;
int cnt[2], mx[2];

void solve() {
    res = 2 * n;
    cnt[0] = cnt[1] = mx[0] = mx[1] = 0;
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        if(i > 1 && a[i] == a[i - 1])
            cur++;
        else
            cur = 1;
        mx[a[i]] = max(mx[a[i]], cur);
    }
    for(int i = 0; i < 2; i++) {
        int other = 1 - i;
        res = min(res, 2 * (cnt[i] - mx[i]) + cnt[other]);
    }
    cout << res << "\n";
}

void read() {
    string str;
    cin >> n >> str;
    for(int i = 1; i <= n; i++)
        a[i] = str[i - 1] - '0';
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