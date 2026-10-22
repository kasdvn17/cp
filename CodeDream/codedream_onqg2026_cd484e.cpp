#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

struct Q {
    int l, r, w;
};

int n, q, a[MAXX];
int L[MAXX], R[MAXX], ans[MAXX], seg[4 * MAXX], lazy[4 * MAXX];
bool active[MAXX];
int len[MAXX];
pair<int, int> nm[MAXX];
Q queries[MAXX];
priority_queue<pair<int, int>> processes;
vector<int> vec;

void fix(int idx, int l, int r) {
    if(!lazy[idx])
        return;
    seg[idx] = lazy[idx] - l;
    if(l != r) {
        lazy[2 * idx] = lazy[idx];
        lazy[2 * idx + 1] = lazy[idx];
    }
    lazy[idx] = 0;
}

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = lazy[idx] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    seg[idx] = lazy[idx] = 0;
}

void update(int idx, int l, int r, int s, int e, int initR) {
    fix(idx, l, r);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e) {
        lazy[idx] = initR;
        fix(idx, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * idx, l, mid, s, e, initR);
    update(2 * idx + 1, mid + 1, r, s, e, initR);
    seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
}

void upset(int l, int r, int initR) {
    update(1, 1, n, l, r, initR + l);
}

int walk(int idx, int l, int r, int s, int e, int w) {
    fix(idx, l, r);
    if(l > e || r < s || seg[idx] < w)
        return -1;
    if(l == r)
        return l;
    int mid = (l + r) >> 1;
    int res = walk(2 * idx, l, mid, s, e, w);
    if(res != -1)
        return res;
    return walk(2 * idx + 1, mid + 1, r, s, e, w);
}

void activate(int p) {
    int l = p, r = p;
    if(p > 1 && active[p - 1])
        l = p - len[p - 1];
    if(p < n && active[p + 1])
        r = p + len[p + 1];
    active[p] = true;
    len[l] = len[r] = r - l + 1;
    upset(l, p, r - l + 1);
}

void solve() {
    int mxx = 1;
    for(int i = 1; i <= n; i++)
        nm[i] = {a[i], i}, mxx = max(mxx, a[i]);
    for(int i = 1; i <= q; i++)
        L[i] = 1, R[i] = n, ans[i] = 1;
    sort(nm + 1, nm + n + 1, greater<pair<int, int>>());
    bool processing = true;
    while(processing) {
        processing = false;
        for(int i = 1; i <= q; i++) {
            if(L[i] > R[i])
                continue;
            processes.push({(L[i] + R[i]) >> 1, i});
            processing = true;
        }
        build(1, 1, n);
        for(int i = 1; i <= n; i++)
            active[i] = false, len[i] = 1;
        int point = 1;
        while(processes.size()) {
            auto [midd, qid] = processes.top();
            processes.pop();
            while(point <= n && nm[point].first >= midd) {
                activate(nm[point].second);
                join(nm[point].second, nm[point].second - 1);
                join(nm[point].second, nm[point].second + 1);
                point++;
            }
            int idd = walk(1, 1, n, queries[qid].l, queries[qid].r, queries[qid].w);
            if(idd != -1 && idd + queries[qid].w - 1 <= queries[qid].r) {
                ans[qid] = midd;
                L[qid] = midd + 1;
            } else
                R[qid] = midd - 1;
        }
    }
    for(int i = 1; i <= q; i++)
        cout << vec[ans[i] - 1] << "\n";
}

void normalize() {
    for(int i = 1; i <= n; i++)
        vec.push_back(a[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> q;
    for(int i = 1; i <= q; i++)
        cin >> queries[i].l >> queries[i].r >> queries[i].w;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    normalize();
    solve();
}
