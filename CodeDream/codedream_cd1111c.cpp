#include <bits/stdc++.h>
#define int long long
#define MAXX 32
#define MAX2 100005
using namespace std;

int n, K, A, B;
int a[MAX2], pf[MAX2];

int count(int l, int r) {
    int f = lower_bound(a + 1, a + K + 1, l) - a;
    int s = upper_bound(a + 1, a + K + 1, r) - a;
    return s - f;
}

int dnc(int l, int r) {
    int cnt = count(l, r);
    if(cnt == 0)
        return A;
    if(l == r)
        return B * cnt; 
    int mid = (l + r) >> 1;
    return min(B * cnt * (r - l + 1), dnc(l, mid) + dnc(mid + 1, r));
}

void solve() {
    sort(a + 1, a + K + 1);
    cout << dnc(1, (1ll << n));
}

void read() {
    cin >> n >> K >> A >> B;
    for(int i = 1; i <= K; i++)
        cin >> a[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}