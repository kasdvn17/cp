#include <bits/stdc++.h>
#define MAXX 200005
using namespace std;

int n, a[3][MAXX];

void solve() {
    int cntup = 0, cntdown = 0;
    for(int j = 1; j <= n; j++) {
        if(a[1][j]) cntup++;
        if(a[2][j]) cntdown++;
    }
    if(cntup == cntdown) {
        cout << "0\n";
        return;
    }
    for(int j = 1; j < n; j++) {
        if(a[1][j] && a[1][j + 1] && cntup > cntdown) cntup -= 2;
        if(a[2][j] && a[2][j + 1] && cntdown > cntup) cntdown -= 2;
    }
    // cout << cntup << " " << cntdown << "\n";
    cout << abs(cntup - cntdown) << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= 2; i++) {
        string str;
        cin >> str;
        for(int j = 1; j <= n; j++) {
            if(str[j - 1] == 'f')
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}