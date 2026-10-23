#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, l, r, res;

int get(int num, int idx) {
    int pid = 1, tmp = num;
    while(tmp > 1) {
        tmp >>= 1;
        pid <<= 1;
    }
    if(idx > pid) return get(num >> 1, idx - pid);
    else if(idx == pid) return num % 2;
    else return get(num >> 1, idx);
}

void solve() {
    for(int i = l; i <= r; i++)
        res += get(n, i);
    cout << res;
} 

void read() {
    cin >> n >> l >> r;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}