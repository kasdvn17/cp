#include <bits/stdc++.h>
#define MAX1 10002
using namespace std;

int n;
pair<int, int> a[MAX1];

void solve() {

}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}