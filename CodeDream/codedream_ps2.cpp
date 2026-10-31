#include <bits/stdc++.h>
#define MAXX 1002
#define int long long
using namespace std;

int n, M, d[MAXX];

int multiply(int x, int y) {
    if(y == 1) return x;
    if(y == 0) return 0;
    int T = multiply(x, y / 2);
    T = (T + T) % M;
    if(y & 1) T = (T + x) % M;
    return T;
}

struct PS {
    int x, y;

    bool operator<=(const PS& other) { return x * other.y <= y * other.x; }
};

void solve() {
    PS cur = {1, 1};
    PS lft = {0, 1}, rig = {1, 0};
    for(int i = 1; i <= n; i++) {
        char v;
        if(d[i] == 0)
            continue;
        if(i & 1) {
            // di sang phai
            PS nr = {(cur.x + multiply(d[i], rig.x)) % M, (cur.y + multiply(d[i], rig.y)) % M};
            PS lstnr = {(cur.x + multiply(d[i] - 1, rig.x)) % M, (cur.y + multiply(d[i] - 1, rig.y)) % M};
            cur = nr;
            lft = lstnr;
        } else {
            // di sang trai
            PS nl = {(cur.x + multiply(d[i], lft.x)) % M, (cur.y + multiply(d[i], lft.y)) % M};
            PS lstnl = {(cur.x + multiply(d[i] - 1, lft.x)) % M, (cur.y + multiply(d[i] - 1, lft.y)) % M};
            cur = nl;
            rig = lstnl;
        }
    }
    cout << cur.x << " " << cur.y;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> M;
    for(int i = 1; i <= n; i++)
        cin >> d[i];
    solve();
}