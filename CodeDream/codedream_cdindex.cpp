#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

struct Q {
    int x, y, z;
};

int n, q, L[MAXX], R[MAXX], ans[MAXX];
int a[MAXX], bit[MAXX];
Q queries[MAXX];
vector<int> processes[MAXX];
pair<int, int> nm[MAXX];

void update(int idx, int val) {
    while(idx <= n) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}

int query(int idx) {
    int res = 0;
    while(idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void solve() {
    bool processing = true;
    for(int i = 1; i <= q; i++)
        L[i] = 1, R[i] = n, ans[i] = -1;
    for(int i = 1; i <= n; i++)
        nm[i] = {a[i], i};
    sort(nm + 1, nm + n + 1, greater<pair<int, int>>());
    while(processing) {
        processing = false;
        for(int i = 1; i <= q; i++) {
            if(L[i] > R[i])
                continue;
            processing = true;
            processes[(L[i] + R[i]) >> 1].push_back(i);
        }
        for(int i = 1; i <= n; i++)
            bit[i] = 0;
        int idxx = 1;
        for(int i = 200000; i >= 1; i--) {
            while(idxx <= n && nm[idxx].first >= i) {
                update(nm[idxx].second, 1);
                idxx++;
            }
            for(auto id : processes[i]) {
                if(query(queries[id].y) - query(queries[id].x - 1) >= i) {
                    ans[id] = i;
                    L[id] = i + 1;
                } else {
                    R[id] = i - 1;
                }
            }
            processes[i].clear();
        }
    }
    for(int i = 1; i <= q; i++)
        cout << ans[i] << "\n";
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= q; i++)
        cin >> queries[i].x >> queries[i].y;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}