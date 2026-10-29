#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, m, a[MAXX];
int num3, totleft, totright, pending;
int lenum3, channum3;
multiset<int>::iterator l, r;
multiset<int> ms;

void print() {
    long double ans = 1.0 * (*l) + 1.0 * (*r);
    if(num3 % 2 == 0) ans = 2 * (channum3 - lenum3 - totright + pending) + ans;
    else ans = 2 * (lenum3 - channum3 + totright + pending) - ans;
    ans /= 2.0;
    cout << fixed << setprecision(1) << ans << "\n";
}

void insert(int x) {
    if(ms.size() & 1) {
        ms.insert(x);
        if(x >= *r) r = next(l);
        else l = prev(r);
    } else {
        auto it = ms.insert(x);
        if(x >= *r) l = r;
        else if(x < *l) r = l;
        else l = r = it;
    }
}

void solve() {
    sort(a + 1, a + n + 1);
    int cnt = 0;
    for(auto it = ms.begin(); it != ms.end(); it++) {
        cnt++;
        if(n & 1 && cnt == (int)(n / 2) + 1) {
            l = r = it;
            break;
        } else if(n % 2 == 0 && cnt == n / 2) {
            l = it;
            r = next(it);
            break;
        }
    }
    print();
    while(m--) {
        int type, k;
        cin >> type >> k;
        if(type == 1) {
            int tar;
            if(num3 % 2 == 0) tar = lenum3 - channum3 + totright + k - pending;
            else tar = lenum3 - channum3 + totright - k + pending;
            insert(tar);
        } else if(type == 2) {
            // cout << "hello " << pending << " " << k << "\n";
            pending += k;
        } else {
            num3++;
            if(num3 % 2 == 0) channum3 += 2 * k, totright += pending;
            else lenum3 += 2 * k, totright -= pending;
            pending = 0;
        }
        print();
    }
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i], ms.insert(a[i]);
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