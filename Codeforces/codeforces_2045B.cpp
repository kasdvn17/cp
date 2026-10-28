#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, d, s;

void solve() {

}

void read() {
    cin >> n >> d >> s;
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