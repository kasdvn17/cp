#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

struct S {
    int first, second, idx;
};

int n, bit[MAXX], res[MAXX];
S segs[MAXX];

void update(int idx, int val) {
    while(idx <= 100000) {
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

bool cmp(S x, S y) {
    return x.second < y.second;
}

void solve() {
    sort(segs + 1, segs + n + 1, cmp);
    int i = 1;
    while(i <= n) {
        int j = i;
        while(j <= n && segs[i].second == segs[j].second)
            j++;
        j--;
        for(int k = i; k <= j; k++)
            update(segs[k].first, 1);
        for(int k = i; k <= j; k++)
            res[segs[k].idx] = query(segs[k].second) - query(segs[k].first - 1) - 1;
        i = j + 1;
    }
    for(int i = 1; i <= n; i++)
        cout << res[i] << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> segs[i].first >> segs[i].second, segs[i].idx = i;    
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