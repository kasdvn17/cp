#include <bits/stdc++.h>
#define OFFSET 1000000
#define MAXX 5000002
#define MAX2 1002
using namespace std;

int n, k, a[MAXX];
int d[MAXX];
queue<int> q;
vector<int> vals;

void solve() {
    for(int i = 1; i <= k; i++)
        a[i] -= n, vals.push_back(a[i]);
    // -1000 <= a[i] <= 1000
    // co 2000 gia tri khac nhau, 
    // res <= 1000
    // sigma(x[i] * a[i]) = 0 (sigma(x[i]) <= 1000)
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    if(!vals.size() || vals.front() > 0 || vals.back() < 0) {
        cout << -1;
        return;
    }
    memset(d, -1, sizeof(d));
    for(int i = 1; i <= 1000; i++)
        for(auto v : vals) {
            int zz = i * v;
            if(d[zz + OFFSET] == -1)
                d[zz + OFFSET] = i, q.push(zz);
        }
    while(q.size()) {
        int cur = q.front();
        if(cur == 0) {
            cout << d[cur + OFFSET];
            return;
        }
        q.pop();
        for(auto v : vals) {
            int nw = cur + v, cost = d[cur + OFFSET] + 1;
            if(cost > 1000)
                break;
            if(d[nw + OFFSET] == -1 || d[nw + OFFSET] > cost)
                d[nw + OFFSET] = cost, q.push(nw);
        }
    }
    cout << d[OFFSET];
}

void read() {
    cin >> n >> k;
    for(int i = 1; i <= k; i++)
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