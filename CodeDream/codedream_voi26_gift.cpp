#include <bits/stdc++.h>
#define ll long long
#define int long long
#define MAXX 100001
using namespace std;

struct G {
    ll w, s, idx;
};

struct Q {
    ll type, m, k, t, idx;
    ll l, r, ans;
};

struct ST {
    ll sl, x;
    ll sl2, x2;
};

int n, q;
ll TOT, cnt[MAXX], finres[MAXX];
G a[MAXX];
Q queries[MAXX];
vector<pair<ll, int>> processes;
ST seg[4 * MAXX];

bool cmpG(G x, G y) {
    return x.s < y.s;
}

ST merge(ST x, ST y) {
    return {x.sl + y.sl, x.x + y.x, x.sl2 + y.sl2, x.x2 + y.x2};
}

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = {0, 0, cnt[l], l * cnt[l]};
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
}

void update(int idx, int l, int r, int pos, int val, int type) {
    if(l > pos || r < pos)
        return;
    if(l == r) {
        if(type == 1)
            seg[idx].sl += val,
            seg[idx].x = l * seg[idx].sl;
        else
            seg[idx].sl2 += val,
            seg[idx].x2 = l * seg[idx].sl2;
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * idx, l, mid, pos, val, type);
    update(2 * idx + 1, mid + 1, r, pos, val, type);
    seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
}

ST query(int idx, int l, int r, int s, int e) {
    if(l > e || r < s)
        return {0, 0, 0, 0};
    if(l >= s && r <= e)
        return seg[idx];
    int mid = (l + r) >> 1;
    return merge(query(2 * idx, l, mid, s, e), query(2 * idx + 1, mid + 1, r, s, e));
}

// walk de tim rea
ll walk(int idx, int l, int r, ll T, ll M) {
    ll tw = seg[idx].x + seg[idx].x2 * T;
    if (tw <= M)
        return seg[idx].sl + seg[idx].sl2 * T;
    if (l == r)
        return M / l;
    int mid = (l + r) >> 1;
    ll vleft = seg[2 * idx].x + seg[2 * idx].x2 * T;
    if (vleft <= M)
        return (seg[2 * idx].sl + seg[2 * idx].sl2 * T) + walk(2 * idx + 1, mid + 1, r, T, M - vleft);
    else
        return walk(2 * idx, l, mid, T, M);
}

void solve() {
    int sms = 0;
    for(int i = 1; i <= n; i++)
        a[i].idx = i, TOT = max(TOT, a[i].w), sms += a[i].s, cnt[a[i].w]++;
    for(int i = 1; i <= q; i++) {
        queries[i].ans = 0, queries[i].idx = i;
        if(queries[i].type == 1)
            queries[i].l = queries[i].r = queries[i].t;
        else
            queries[i].l = 1, queries[i].r = min(queries[i].m / queries[i].k, sms / queries[i].k);
    }
    bool processing = true;
    sort(a + 1, a + n + 1, cmpG);
    while(processing) {
        processing = false;
        processes.clear();
        for(int i = 1; i <= q; i++) {
            if(queries[i].l > queries[i].r)
                continue;
            processing = true;
            processes.push_back({(queries[i].l + queries[i].r) >> 1, i});
        }
        sort(processes.begin(), processes.end());
        build(1, 1, TOT);
        // tai T = 0
        // for(int i = 1; i <= n; i++)
        //     update(1, 1, TOT, a[i].w, 1, 2);
        int l = 1;
        for(auto [T, idx] : processes) {
            while(l <= n && a[l].s < T) {
                update(1, 1, TOT, a[l].w, -1, 2);
                update(1, 1, TOT, a[l].w, a[l].s, 1);
                l++;
            }
            ll M = queries[idx].m, K = queries[idx].k;
            // walk tim tong so luong mon qua lon nhat sao cho tong khoi luong cac mon qua <= M
            ll slg = walk(1, 1, TOT, T, M);
            if(slg / K >= T) {
                queries[idx].ans = T;
                queries[idx].l = T + 1;
            } else {
                queries[idx].r = T - 1;
            }
        }
    }
    for(int i = 1; i <= q; i++) {
        if(queries[i].type == 1) {
            if(queries[i].ans >= queries[i].t) finres[queries[i].idx] = 1;
            else finres[queries[i].idx] = 0;
        } else finres[queries[i].idx] = queries[i].ans;
    }
    for(int i = 1; i <= q; i++)
        cout << finres[i] << "\n";
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i].w;
    for(int i = 1; i <= n; i++)
        cin >> a[i].s;
    for(int i = 1; i <= q; i++) {
        cin >> queries[i].type;
        if(queries[i].type == 1)
            cin >> queries[i].m >> queries[i].k >> queries[i].t;
        else
            cin >> queries[i].m >> queries[i].k;
    }
}

void file() {
    if(fopen("GIFT.INP", "r")) {
        freopen("GIFT.INP", "r", stdin);
        freopen("GIFT.OUT", "w", stdout);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    file();
    read();
    solve();
}