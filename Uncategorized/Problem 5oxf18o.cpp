#include <bits/stdc++.h>
#define ll long long
#define MAXX 302
#define MOD 1000000007
using namespace std;

int n, q;
int dp[MAXX][MAXX][MAXX][3], pfs[MAXX][MAXX][MAXX];
char s[MAXX];
vector<int> chc;

void solve() {
    bool valid_init = true;
    for (int i = 1; i < n; i++) {
        if (s[i] != '?' && s[i] == s[i + 1]) {
            valid_init = false;
        }
    }

    for (int i = 1; i <= n; i++)
        if (s[i] == '?')
            chc.push_back(i);

    int k = chc.size();

    if (!valid_init) {
        while (q--) {
            int a, b, c;
            cin >> a >> b >> c;
            cout << 0 << "\n";
        }
        return;
    }
    if (k == 0) {
        while (q--) {
            int a, b, c;
            cin >> a >> b >> c;
            cout << 1 << "\n";
        }
        return;
    }

    dp[1][0][0][0] = dp[0][1][0][1] = dp[0][0][1][2] = 1;
    int p = chc[0];
    if (p > 1) {
        if (s[p - 1] == 'a') dp[1][0][0][0] = 0;
        else if (s[p - 1] == 'b') dp[0][1][0][1] = 0;
        else if (s[p - 1] == 'c') dp[0][0][1][2] = 0;
    }
    if (p < n) {
        if (s[p + 1] == 'a') dp[1][0][0][0] = 0;
        else if (s[p + 1] == 'b') dp[0][1][0][1] = 0;
        else if (s[p + 1] == 'c') dp[0][0][1][2] = 0;
    }

    for (int vj = 2; vj <= k; vj++) {
        int p = chc[vj - 1];
        bool chka = 1, chkb = 1, chkc = 1, chkpre = 0;

        if (s[p - 1] == '?') chkpre = 1;
        else {
            if (s[p - 1] == 'a') chka = 0;
            else if (s[p - 1] == 'b') chkb = 0;
            else if (s[p - 1] == 'c') chkc = 0;
        }

        if (p < n && s[p + 1] != '?') {
            if (s[p + 1] == 'a') chka = 0;
            else if (s[p + 1] == 'b') chkb = 0;
            else if (s[p + 1] == 'c') chkc = 0;
        }

        for (int a = 0; a <= vj; a++) {
            for (int b = 0; b <= vj - a; b++) {
                int c = vj - a - b;
                if (a && chka) {
                    ll ways = 0LL + dp[a - 1][b][c][1] + dp[a - 1][b][c][2];
                    if (!chkpre) ways += dp[a - 1][b][c][0];
                    dp[a][b][c][0] = ways % MOD;
                }
                if (b && chkb) {
                    ll ways = 0LL + dp[a][b - 1][c][0] + dp[a][b - 1][c][2];
                    if (!chkpre) ways += dp[a][b - 1][c][1];
                    dp[a][b][c][1] = ways % MOD;
                }
                if (c && chkc) {
                    ll ways = 0LL + dp[a][b][c - 1][0] + dp[a][b][c - 1][1];
                    if (!chkpre) ways += dp[a][b][c - 1][2];
                    dp[a][b][c][2] = ways % MOD;
                }
            }
        }
    }

    for (int a = 0; a <= k; a++) {
        for (int b = 0; b <= k - a; b++) {
            int c = k - a - b;
            pfs[a][b][c] = (0LL + dp[a][b][c][0] + dp[a][b][c][1] + dp[a][b][c][2]) % MOD;
        }
    }

    for (int a = 1; a <= n; a++)
        for (int b = 0; b <= n; b++)
            for (int c = 0; c <= n; c++) {
                pfs[a][b][c] += pfs[a - 1][b][c];
                if (pfs[a][b][c] >= MOD) pfs[a][b][c] -= MOD;
            }

    for (int a = 0; a <= n; a++)
        for (int b = 1; b <= n; b++)
            for (int c = 0; c <= n; c++) {
                pfs[a][b][c] += pfs[a][b - 1][c];
                if (pfs[a][b][c] >= MOD) pfs[a][b][c] -= MOD;
            }

    for (int a = 0; a <= n; a++)
        for (int b = 0; b <= n; b++)
            for (int c = 1; c <= n; c++) {
                pfs[a][b][c] += pfs[a][b][c - 1];
                if (pfs[a][b][c] >= MOD) pfs[a][b][c] -= MOD;
            }

    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << pfs[a][b][c] << "\n";
    }
}

void read() {
    cin >> n >> q;
    string str;
    cin >> str;
    for (int i = 1; i <= n; i++)
        s[i] = str[i - 1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}