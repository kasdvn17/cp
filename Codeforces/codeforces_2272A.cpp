#include <bits/stdc++.h>
#define MAXX 102
using namespace std;

int n, k, a[MAXX];
int init[MAXX], cnt[MAXX], f[MAXX], f2[MAXX];

void solve() {
    int l = 0;
    pair<int, pair<int, int>> res = {0, {0, 0}};
    for(int i = 0; i <= n; i++)
        cnt[i] = 0;
    for(int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        while(cnt[l] > 0) l++;
        f[i] = l;
    }
    k = n - k + 1;
    for(int op1 = 1; op1 <= n; op1++)
        for(int op2 = op1 + 1; op2 <= n; op2++) {
            swap(a[op1], a[op2]);
            for(int i = 0; i <= n; i++)
                cnt[i] = 0;
            int l = 0;
            for(int i = 1; i <= k; i++) {
                cnt[a[i]]++;
                while(cnt[l] > 0) l++;
                f2[i] = l;
            }
            res = max(res, {f2[k], {op1, op2}});
            swap(a[op1], a[op2]);
        }
    if(res.first <= f[k])
        cout << "-1\n";
    else
        cout << res.second.first << " " << res.second.second << "\n";
}

void read() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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