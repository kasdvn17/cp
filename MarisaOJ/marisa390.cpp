#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, k, a[MAXX];
int pf[MAXX];

void solve() {
    for(int i = 1; i <= n; i++)
        pf[i] = pf[i - 1];
}

void read() {
    cin >> n >> k;
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