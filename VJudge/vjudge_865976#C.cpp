#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

int n, mx, my;
int bitgex[MAXX], bitlex[MAXX];
vector<int> has[MAXX];
pair<int, int> choosen;
pair<int, int> cord[MAXX];
vector<int> norx, nory;

void update(int idx, int val, int bit[MAXX]) {
    while(idx <= n) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}

int query(int idx, int bit[MAXX]) {
    int res = 0;
    while(idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int walk(int tar, int bit[MAXX]) {
    int pos = 0, sum = 0;
    for(int i = 1 << 17; i > 0; i >>= 1) {
        if(pos + i <= my && sum + bit[pos + i] < tar) {
            pos += i;
            sum += bit[pos];
        }
    }
    return pos + 1;
}

bool check(int x) {
    int cnt = 0;
    for(int i = 1; i <= n; i++)
        bitgex[i] = bitlex[i] = 0;
    for(int i = 1; i <= n; i++)
        update(cord[i].second, 1, bitgex);
    for(int curx = 1; curx < mx; curx++) {
        for(auto v : has[curx]) {
            cnt++;
            update(cord[v].second, -1, bitgex);
            update(cord[v].second, 1, bitlex);
        }
        if(cnt < 2 * x || (n - cnt) < 2 * x) continue;
        int firstgex = walk(x, bitgex);
        int firstlex = walk(x, bitlex);
        int p = max(firstgex, firstlex);
        if(p < my && (n - cnt) - query(p, bitgex) >= x && cnt - query(p, bitlex) >= x) {
            choosen = {curx + 1, p + 1};
            return true;
        }
    }
    return false;
}

void solve() {
    for(int i = 1; i <= n; i++)
        has[cord[i].first].push_back(i);
    int l = 1, r = n / 4, ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    if(ans == 0)
        cout << "0\n0 0\n";
    else {
        check(ans);
        cout << ans << "\n";
        cout << norx[choosen.first - 1] << " " << nory[choosen.second - 1] << "\n";
    }
    // reset
    for(int i = 1; i <= n; i++)
        has[cord[i].first].clear();
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> cord[i].first >> cord[i].second;
}

void normalize() {
    for(int i = 1; i <= n; i++) {
        norx.push_back(cord[i].first);
        nory.push_back(cord[i].second);
    }
    sort(norx.begin(), norx.end());
    sort(nory.begin(), nory.end());
    norx.erase(unique(norx.begin(), norx.end()), norx.end());
    nory.erase(unique(nory.begin(), nory.end()), nory.end());
    for(int i = 1; i <= n; i++) {
        cord[i].first = lower_bound(norx.begin(), norx.end(), cord[i].first) - norx.begin() + 1;
        cord[i].second = lower_bound(nory.begin(), nory.end(), cord[i].second) - nory.begin() + 1;
        mx = max(mx, cord[i].first);
        my = max(my, cord[i].second);
    }
}

void reset() {
    choosen = {0, 0};
    norx.clear();
    nory.clear();
    mx = 0, my = 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        reset();
        read();
        normalize();
        solve();
    }
}