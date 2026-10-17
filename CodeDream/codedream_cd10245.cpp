#include <bits/stdc++.h>
#define int long long
#define ld long double
#define MAXX 10002
using namespace std;

struct D {
    ld x, y;
};

int n;
D a[MAXX];

void solve() {
    for(int i = 1; i <= 4000000000; i++)
        cout << "hello\n";
}

void read() {
    for(int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
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

    while(cin >> n) {
        if(n == 0)
            return 0;
        read();
        solve();
    }
}