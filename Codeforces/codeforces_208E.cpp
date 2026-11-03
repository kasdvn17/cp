#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, m, a[MAXX];
vector<int> path[MAXX];

void solve() {
    while(m--) {

    }
}

void read() {
    cin >> n;
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        p++;
        path[i].push_back(p);
        path[p].push_back(i);
    }
    cin >> m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}