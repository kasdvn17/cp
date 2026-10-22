#include <bits/stdc++.h>
#define int long long
#define MAXX 1000002
using namespace std;

int n, res, a[MAXX];
vector<int> seen[MAXX];

void dnc(int l, int r) {
    if(l >= r)
        return;
    int mid = (l + r) >> 1;
    dnc(l, mid);
    dnc(mid + 1, r);
    vector<int> cnt;
    for(int i = mid + 1; i <= r; i++) {
        int idui = lower_bound(seen[a[i]].begin(), seen[a[i]].end(), i) - seen[a[i]].begin() + 1;
        int rmn = seen[a[i]].size() - idui;
        cnt.push_back(rmn);
    }
    sort(cnt.begin(), cnt.end());
    for(int i = l; i <= mid; i++) {
        int idui = lower_bound(seen[a[i]].begin(), seen[a[i]].end(), i) - seen[a[i]].begin();
        // dem co bao nhieu dua < idui
        auto v = lower_bound(cnt.begin(), cnt.end(), idui);
        if(v == cnt.begin())
            continue;
        int id = v - cnt.begin();
        res += id;
    }
}

void solve() {
    for(int i = 1; i <= n; i++)
        seen[a[i]].push_back(i);
    dnc(1, n);
    cout << res;
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
}

void normalize() {
    vector<int> vec;
    for(int i = 1; i <= n; i++)
        vec.push_back(a[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
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

    read();
    normalize();
    solve();
}