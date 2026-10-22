#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

struct G {
    int w, s;
};

struct Q {
    int type, m, k, t;
    int l, r, ans;
};

int n, q;
G a[MAXX];
Q queries[MAXX];
vector<pair<int, int>> processes;

bool cmpG(G x, G y) {
    return x.w < y.w;
}

void solve() {
    for(int i = 1; i <= q; i++)
        queries[i].l = 1, queries[i].r = 1000000000, queries[i].ans = 0;
    bool processing = true;
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
    }
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