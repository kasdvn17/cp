#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, m, a[MAXX];

void solve() {
    int l = 1, cur = 0, res = 0;
    for(int r = 1; r <= n; r++) {
        cur += a[l];
        
    }
}

void read() {
    cin >> n >> m;
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