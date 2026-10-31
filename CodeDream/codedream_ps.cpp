#include <bits/stdc++.h>
#define int long long
#define MAXX 1000000002
using namespace std;

struct PS {
    int x, y;

    bool operator==(const PS& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const PS& other) const {
        if(x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator>(const PS& other) const {
        if(x != other.x) return x > other.y;
        return y > other.y;
    }
    
    bool operator!=(const PS& other) const {
        return x != other.x || y != other.y;
    }
};

int p, q;
bool found = false;
PS ppss = {p, q};
map<PS, pair<PS, char>> par;
stack<char> trace;

void dq(PS cur, char x, PS lst_left, PS lst_right, PS prv) {
    if(found)
        return;
    if(cur.x > p || cur.y > q)
        return;
    par[cur] = {prv, x};
    if(cur == ppss) {
        // cout << "found\n";
        found = true;
        return;
    }
    if(x == 'L') {
        // di xuong left
        PS nl = {cur.x + lst_right.x, cur.y + lst_right.y};
        dq(nl, 'L', cur, lst_right, cur);
        // di xuong right
        PS nr = {cur.x + lst_left.x, cur.y + lst_left.y};
        dq(nr, 'R', lst_left, cur, cur);
    } else {
        PS nl = {cur.x + lst_right.x, cur.y + lst_right.y};
        dq(nl, 'L', cur, lst_right, cur);
        PS nr = {cur.x + lst_left.x, cur.y + lst_left.y};
        dq(nr, 'R', lst_left, cur, cur);
    }
}

void solve() {
    ppss = {p, q};
    dq({1, 2}, 'L', {1, 1}, {0, 1}, {1, 1});
    dq({2, 1}, 'R', {1, 0}, {1, 1}, {1, 1});
    PS cur = {p, q};
    PS st = {1, 1};
    while(cur != st)
        trace.push(par[cur].second), cur = par[cur].first;
    // string res = "";
    while(trace.size())
        cout << trace.top(), trace.pop();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(cin >> p >> q) {
        if(p == 1 && q == 1)
            return 0;
        solve();
    }
}