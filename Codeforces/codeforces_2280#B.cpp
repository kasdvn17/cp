#include <bits/stdc++.h>
#define MAXX 20002
using namespace std;

int n, a[MAXX];
bool broken = false;

int ask(int l, int r) {
    cout << "? " << l << " " << r << "\n";
    cout.flush();
    int z;
    cin >> z;
    if(z == -1) {
        broken = true;
        return z;
    }
    return z;
}

void solve() {
    int slc1 = ask(1, n);
    if(slc1 == 0 || slc1 == n) {
        cout << "! NO\n";
        cout.flush();
        return;
    }
    int fs1 = ask(1, slc1);
    if(fs1 != slc1) {
        cout << "! YES\n";
        cout.flush();
    } else {
        cout << "! NO\n";
        cout.flush();
    }
}

void read() {
    cin >> n;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        if(broken)
            return 0;
        read();
        solve();
    }
}