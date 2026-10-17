#include <bits/stdc++.h>
#define MAXX 1000002
using namespace std;

int n, a[MAXX];
int spMin[20][MAXX], spMax[20][MAXX];
long long res = 0;

int queryMax(int l, int r) {
    int lg = __lg(r - l + 1);
    return max(spMax[lg][l], spMax[lg][r - (1 << lg) + 1]);
}

int queryMin(int l, int r) {
    int lg = __lg(r - l + 1);
    return min(spMin[lg][l], spMin[lg][r - (1 << lg) + 1]);
}

void dnc(int l, int r) {
    if(l >= r)
        return;
    int mid = (l + r) >> 1;
    // cout << "checking: " << l << " " << mid << " " << r << "\n";
    int point = mid;
    for(int i = mid; i >= l; i--) {
        int mxx = queryMax(i, mid);
        while(point <= r && queryMax(mid, point) <= mxx)
            point++;
        point--;
        if(point == mid)
            continue;
        // cout << "with1: " << i << " " << ans << " " << mid << " " << mxx << " " << (ans - mid) * mxx << "\n";
        res += 1ll * mxx * 1ll * (point - mid);
    }
    point = mid;
    for(int i = mid; i >= l; i--) {
        int mnn = queryMin(i, mid);
        while(point <= r && queryMin(mid, point) >= mnn)
            point++;
        point--;
        if(point == mid)
            continue;
        res -= 1ll * mnn * (point - mid);
        // cout << "with2: " << i << " " << ans << " " << mid << " " << mnn << " " << (ans - mid) * mnn << "\n";
    }
    bool found = false;
    point = mid;
    for(int i = mid + 1; i <= r; i++) {
        int mxx = queryMax(mid + 1, i);
        while(point >= l && queryMax(point, mid) < mxx) {
            point--;
            found = true;
        }
        if(found)
            point++;
        if(!found)
            continue;
        res += 1ll * mxx * (mid - point + 1);
        // cout << "with3: " << i << " " << ans << " " << mid << " " << mxx << "\n";
    }
    found = false;
    point = mid;
    for(int i = mid + 1; i <= r; i++) {
        int mnn = queryMin(mid + 1, i);
        while(point >= l && queryMin(point, mid) > mnn)
            point--, found = true;
        if(found)
            point++;
        if(!found)
            continue;
        res -= 1ll * mnn * (mid - point + 1);
        // cout << "with4: " << i << " " << ans << " " << mid << " " << mnn << "\n";
    }
    // cout << "after: " << res << "\n";
    dnc(l, mid);
    dnc(mid + 1, r);
}

void solve() {
    for(int i = 1; i <= n; i++)
        spMin[0][i] = spMax[0][i] = a[i];
    for(int lg = 1; lg < 20; lg++)
        for(int i = 1; i + (1 << lg) - 1 <= n; i++) {
            spMin[lg][i] = min(spMin[lg - 1][i], spMin[lg - 1][i + (1 << (lg - 1))]);
            spMax[lg][i] = max(spMax[lg - 1][i], spMax[lg - 1][i + (1 << (lg - 1))]);
        }
    dnc(1, n);
    cout << res;
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