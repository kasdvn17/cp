#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, a[MAXX];
int mn = 1e12;
vector<int> has[32];

void dnc(int l, int r, int idx, int prv) {
    if(l > r)
        return;
    if(idx == -1) {
        int cur = a[l] ^ prv;
        mn = min(mn, cur);
        return;
    }
    if(l == r) {
        int cur = a[l];
        cur >>= (idx + 1);
        cur <<= (idx + 1);
        mn = min(mn, cur ^ prv);
        return;
    }
    auto v = lower_bound(has[idx].begin(), has[idx].end(), l);
    if(v == has[idx].end() || (*v) > r) {
        // ko co idx
        dnc(l, r, idx - 1, prv);
    } else if((*v) == l) {
        // ca doan la idx
        dnc(l, r, idx - 1, prv | (1ll << idx));
    } else {
        // l => v - 1 ko co bit idx, v => r co bit idx
        int mid = (*v) - 1;
        dnc(l, mid, idx - 1, prv | (1ll << idx));
        dnc(mid + 1, r, idx - 1, prv);
    }
}

void solve() {
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) {
        int tmp = a[i], cur = 0;
        while(tmp > 0) {
            if(tmp & 1) has[cur].push_back(i);
            tmp >>= 1;
            cur++;
        }
    }
    dnc(1, n, 30, 0);
    cout << mn;
}

void read() {
    cin >> n;
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