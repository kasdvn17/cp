#include <bits/stdc++.h>
#define int long long
#define MAXX 102
using namespace std;

int n, k;
int a[MAXX], b[MAXX];
int cntle, cntchan;

void solve() {
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    int clea = 0 , cleb = 0, cchana = 0, cchanb = 0;
    for(int i = 1; i <= n; i++) {
        if(b[i] & 1) cleb++;
        else cchanb++;
        if(a[i] & 1) clea++;
        else cchana++;
    }
    if(cleb == clea) {
        cout << "YES\n";
        return;
    }
    if(k & 1) {
        // cout << "hello " << n << "\n";
        if(cchana >= cchanb) {
            cout << "YES\n";
            return;
        } else {
            cout << "NO\n";
            return;
        }
    } else {
        if(clea >= cleb) {
            cout << "YES\n";
            return;
        } else {
            cout << "NO\n";
        }
    }
}

void read() {
    cin >> n >> k;
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