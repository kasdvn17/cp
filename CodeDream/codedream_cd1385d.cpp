#include <bits/stdc++.h>
#define int long long
#define MAXX 131075
using namespace std;

int n;
char s[MAXX];

int dnc(int l, int r, char tang) {
    if(l == r) {
        if(s[l] == tang) return 0;
        return 1;
    }
    int mid = (l + r) >> 1;
    // l -> mid & mid + 1 -> r
    // dong nhat la l -> mid
    int num = 0;
    for(int i = l; i <= mid; i++)
        if(s[i] != tang)
            num++;
    int v1 = num + dnc(mid + 1, r, (char)(tang + 1));
    num = 0;
    for(int i = mid + 1; i <= r; i++)
        if(s[i] != tang)
            num++;
    int v2 = num + dnc(l, mid, (char)(tang + 1));
    return min(v1, v2);
}

void solve() {
    cout << dnc(1, n, 'a') << "\n";
}

void read() {
    cin >> n;
    string str;
    cin >> str;
    for(int i = 1; i <= n; i++)
        s[i] = str[i - 1];
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

    int t;
    cin >> t;
    while(t--) {
        read();
        solve();
    }
}