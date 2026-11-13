#include <bits/stdc++.h>
#define MAXX 100002
#define MOD 1000000007
using namespace std;

long long n, a[MAXX], ans;

int main() {
    int t;
    cin >> t;
    while(t--) {
        ans = 0;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            for(int j = i + 1; j <= n; j++)
                ans = (ans + a[i] * a[j]) % MOD;
        cout << ans << "\n";
    }
}
