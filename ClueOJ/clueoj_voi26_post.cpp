#include <bits/stdc++.h>
#define MAXX 300005
#define BSIZE 550
#define int long long
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

struct Q {
    int l, r, id;
};

int n, q, ans, val[MAXX], nw[MAXX], res[MAXX], cnt[MAXX];
pair<int, int> a[MAXX];
Q queries[MAXX];

bool cmp(Q x, Q y) {
    return make_pair(x.l / BSIZE, x.r) < make_pair(y.l / BSIZE, y.r);
}

void add(int x) {
    ans += cnt[nw[x]];
    cnt[nw[x]]++;
}

void del(int x) {
    cnt[nw[x]]--;
    ans -= cnt[nw[x]];
}

void solve() {
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) {
        int j = i, xorr = 0;
        while(j <= n && a[j].first == a[i].first)
            j++;
        j--;
        for(int k = i; k < j; k++)
            val[a[k].second] = rand(1, 1e18), xorr = xorr ^ val[a[k].second];
        // val[a[i].second] ^ var[a[i + 1].second] ^ ... ^ val[a[j - 1].second] ^ val[a[j].second] = 0
        val[a[j].second] = xorr;
        i = j;
    }
    for(int i = 1; i <= n; i++)
        nw[i] = nw[i - 1] ^ val[i];
    // normalize
    vector<int> vec = {0};
    for(int i = 1; i <= n; i++)
        vec.push_back(nw[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++)
        nw[i] = lower_bound(vec.begin(), vec.end(), nw[i]) - vec.begin();
    sort(queries + 1, queries + q + 1, cmp);
    int cl = 0, cr = -1;
    for(int i = 1; i <= q; i++) {
        int l = queries[i].l - 1, r = queries[i].r;
        while (cl > l) add(--cl);
        while (cr < r) add(++cr);
        while (cl < l) del(cl++);
        while (cr > r) del(cr--);
        res[queries[i].id] = ans;
    }
    for(int i = 1; i <= q; i++)
        cout << res[i] << "\n";
}

void read() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i].first, a[i].second = i;
    for(int i = 1; i <= q; i++)
        cin >> queries[i].l >> queries[i].r, queries[i].id = i;
}

void file() {
    if (fopen("POST.INP", "r")) {
        freopen("POST.INP", "r", stdin);
        freopen("POST.OUT", "w", stdout);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    file();
    read();
    solve();
}