#include <bits/stdc++.h>
#define int long long
#define MAXX 200002
#define MOD 1000000007
using namespace std;

int n, q;
int a[MAXX], bit[MAXX];
int diff[MAXX];
int res;

void update(int idx, int v) {
    while(idx <= n) {
        bit[idx] += v;
        idx += (idx & -idx);
    }
}

int sum(int idx) {
    int res = 0;
    while(idx > 0) {
        res += bit[idx];
        idx -= (idx & -idx);
    }
    return res;
}

void normalize() {
    vector<int> vec;
    for(int i = 1; i <= n; i++) vec.push_back(a[i]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    normalize();
    for(int i = 1; i <= n; i++)
    {
        int xx = (sum(a[i] - 1) + 1) % MOD;
        res = (res + xx) % MOD;
        update(a[i], xx);
        // cout << i << " " << xx << "\n";
    }
    cout << res;
}
