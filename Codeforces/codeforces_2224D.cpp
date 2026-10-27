#include <bits/stdc++.h>
#define int long long
#define MAXX 2002
#define MOD 998244353
using namespace std;

struct Num {
    int ts, ms;

    bool operator<(const Num& other) const {
        return ts * other.ms < ms * other.ts;
    }

    bool operator==(const Num& other) const {
        return ts * other.ms == ms * other.ts;
    }

    bool operator>(const Num& other) const {
        return ts * other.ms > ms * other.ts;
    }
};

int n, a[MAXX], b[MAXX], fact[MAXX];
int ts;
vector<Num> allb;

int pow2(int x, int y) {
    if(y == 0)
        return 1;
    if(y == 1)
        return x;
    int T = pow2(x, y / 2);
    T = (T * T) % MOD;
    if(y & 1)
        return (T * x) % MOD;
    else
        return T;
}

int inv(int x) {
    return pow2(x, MOD - 2);
}

void solve() {
    fact[0] = 1;
    for(int i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
    ts = 0;
    allb.clear();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            if(i == j)
                continue;
            allb.push_back({b[i], b[j]});
        }
    sort(allb.begin(), allb.end());
    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++) {
            // dem co bao nhieu b[x] va b[y] thoa man a[i] * b[x] > a[j] * b[y]
            // a[i] / a[j] > b[y] / b[x]
            Num cur = {a[i], a[j]};
            auto idx = lower_bound(allb.begin(), allb.end(), cur);
            int v = idx - allb.begin();
            v = (v * fact[n - 2]) % MOD;
            ts = (ts + v) % MOD;
            // int cnt = 0;
            // for(int x = 1; x <= n; x++)
            //     for(int y = 1; y <= n; y++) {
            //         if(x == y)
            //             continue;
            //         if(a[i] * b[x] > a[j] * b[y])
            //             cnt++;
            //     }
            // cout << v << " " << cnt << "\n";
            // cnt = (cnt * fact[n - 2]) % MOD;
            // ts = (ts + cnt) % MOD;
        }
    // cout << ts << " " << fact[n] << "\n";
    int ans = (ts * inv(fact[n])) % MOD;
    cout << ans << "\n";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];
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