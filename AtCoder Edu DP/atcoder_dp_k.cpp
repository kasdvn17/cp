#include <bits/stdc++.h>
#define int long long
#define MAX1 102
#define MAX2 100002
using namespace std;

int n, k, a[MAX1];
int memo[MAX2];

int dp(int k) {
    if(memo[k] != -1) return memo[k];
    if(k < a[1]) return memo[k] = 0;
    for(int i = 1; i <= n; i++) {
        if(k >= a[i] && dp(k - a[i]) == 0)
            return memo[k] = 1;
    }
    return memo[k] = 0;
}

void solve() {
    memset(memo, -1, sizeof(memo));
    if(dp(k) == 1)
        cout << "First";
    else
        cout << "Second";
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