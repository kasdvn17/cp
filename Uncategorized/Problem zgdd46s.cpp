#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int p50, p95, p99;
int n, a[MAXX];

void solve() {
    for(int i = 1; i <= 50; i++)
        a[i] = p50;
    for(int i = 51; i <= 95; i++)
        a[i] = p95;
    for(int i = 96; i <= 99; i++)
        a[i] = p99;
    a[100] = p99 + 5;
    cout << "100\n";
    for(int i = 1; i <= 100; i++)
        cout << a[i] << " ";
}

void read() {
    cin >> p50 >> p95 >> p99;
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