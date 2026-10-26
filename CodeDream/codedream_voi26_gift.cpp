#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define ll long
#define int long
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

int n, q, sms;
ll TOT, cnt[MAXX], finres[MAXX];
G a[MAXX];
Q queries[MAXX];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> processes;
ST seg[4 * MAXX], tmp[4 * MAXX];
vector<pair<int, ST>> builded;

bool cmpG(G x, G y) {
    return x.s < y.s;
}

ST merge(const ST& x, const ST& y) {
    return {x.sl + y.sl, x.x + y.x, x.sl2 + y.sl2, x.x2 + y.x2};
}

void build(int idx, int l, int r) {
    if(l == r) {
        tmp[idx] = {0, 0, cnt[l], l * cnt[l]};
        builded.push_back({idx, tmp[idx]});
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    tmp[idx] = merge(tmp[2 * idx], tmp[2 * idx + 1]);
    builded.push_back({idx, tmp[idx]});
}

void update(int idx, int l, int r, int pos, int typ1, int typ2) {
    if(l > pos || r < pos)
        return;
    if(l == r) {
        seg[idx].sl += typ1,
        seg[idx].x += l * typ1;
        seg[idx].sl2 += typ2,
        seg[idx].x2 += l * typ2;
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * idx, l, mid, pos, typ1, typ2);
    update(2 * idx + 1, mid + 1, r, pos, typ1, typ2);
    seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
}

// walk de tim rea
ll walk(int idx, int l, int r, const ll& T, const ll& M) {
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
    for(int i = 1; i <= q; i++) {
        queries[i].ans = 0, queries[i].idx = i;
        if(queries[i].type == 1)
            queries[i].l = queries[i].r = queries[i].t;
        else
            queries[i].l = 1, queries[i].r = min(queries[i].m / queries[i].k, sms / queries[i].k);
    }
    bool processing = true;
    sort(a + 1, a + n + 1, cmpG);
    build(1, 1, TOT);
    while(processing) {
        processing = false;
        for(int i = 1; i <= q; i++) {
            if(queries[i].l > queries[i].r)
                continue;
            processing = true;
            processes.push({(queries[i].l + queries[i].r) >> 1, i});
        }
        for(auto [idx, S] : builded)
            seg[idx] = S;
        int l = 1;
        while(processes.size()) {
            auto [T, idx] = processes.top();
            processes.pop();
            while(l <= n && a[l].s < T) {
                update(1, 1, TOT, a[l].w, a[l].s, -1);
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
            finres[queries[i].idx] = (int)(queries[i].ans >= queries[i].t);
        } else finres[queries[i].idx] = queries[i].ans;
    }
    for(int i = 1; i <= q; i++)
        cout << finres[i] << "\n";
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i].w, TOT = max(TOT, a[i].w), cnt[a[i].w]++;
    for(int i = 1; i <= n; i++)
        cin >> a[i].s, sms += a[i].s, a[i].idx = i;
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