#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, q, a[MAXX];
set<pair<int, pair<int, int>>> mins;
set<pair<int, int>> segs;

int ans() {

}

pair<int, int> find(int x) {
    auto v = segs.upper_bound(x + 1);
    v--;
    return (*v);
}

void erase(int l, int r) {
    segs.erase({l, r});
    mins.erase({r - l + 1, {l, r}});
}

void add(int l, int r) {
    segs.insert({l, r});
    mins.insert({r - l + 1, {l, r}});
}

void solve() {
    segs.clear();
    mins.clear();
    for(int i = 1; i <= n; i++) {
        segs.insert({i, i});
        mins.insert({1, {i, i}});
    }
    for(int i = 1; i < n; i++) {
        if(a[i] > a[i + 1])
            continue;
        int lftt = find(i).first;
        erase(i + 1, i + 1);
        add(lftt, i + 1);
    }
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= q; i++)
        cin >> queries[i].first >> queries[i].second;
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

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}