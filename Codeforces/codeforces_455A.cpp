#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, a[MAXX];

void solve() {
    sort(a + 1, a + n + 1, greater<int>());
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