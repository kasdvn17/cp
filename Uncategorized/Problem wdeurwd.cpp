#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, a[MAXX];
set<int> s;

void solve() {
    s.insert(0);
    for(int i = 1; i <= n; i++)
        s.insert(a[i]);
    for(int i = 1; i < n; i++) {
        s.insert(a[i] & a[i + 1]);
        s.insert(a[i] | a[i + 1]);
        s.insert(a[i] ^ a[i + 1]);
        s.insert(a[i] & ~a[i + 1]);
        s.insert(a[i + 1] & ~a[i]);
    }
    cout << s.size();
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}