#include <bits/stdc++.h>
#define int long long
#define MAXX 202
#define MOD 1000000007
using namespace std;

int n, m, prevc[MAXX];
int pre[MAXX], suf[MAXX];
int dp[MAXX][MAXX][MAXX];
string mnn[MAXX], str[MAXX];

bool check(string x, string y) {
    // check x < y
    int r1 = 0, r2 = 0;
    reverse(x.begin(), x.end());
    for(int i = 0; i < m; i++)
        if(x[i] == '1')
            r1 |= 1ll << i;
    reverse(y.begin(), y.end());
    for(int i = 0; i < m; i++)
        if(y[i] == '1')
            r2 |= 1ll << i;
    return r1 < r2;
}

void solve() {
    // handle 1
    mnn[1] = str[1];
    for(int j = 0; j < m; j++) {
        if(mnn[1][j] == '.')
            mnn[1][j] = '0';
    }
    for(int i = 2; i <= n; i++) {
        // tim so nho nhat >= str[i - 1]
        mnn[i] = str[i];
        int prv0c = -1;
        bool found = false;
        for(int j = 0; j < m && !found; j++) {
            if(mnn[i][j] == '.' || mnn[i][j] == mnn[i - 1][j]) {
                if(mnn[i][j] == '.' && mnn[i - 1][j] == '0')
                    prv0c = j;
                mnn[i][j] = mnn[i - 1][j];
                continue;
            }
            if(mnn[i][j] == '1') {
                found = true;
                for(int j2 = j + 1; j2 < m; j2++)
                    mnn[i][j2] = (str[i][j2] == '.' ? '0' : str[i][j2]);
                continue;
            }
            if(mnn[i][j] == '0') {
                // phai doi 1 thang . o truoc tu 0 thanh 1
                if(prv0c == -1) {
                    cout << -1;
                    return;
                }
                mnn[i][prv0c] = '1';
                found = true;
                for(int j2 = prv0c + 1; j2 < m; j2++)
                    mnn[i][j2] = (str[i][j2] == '.' ? '0' : str[i][j2]);
                continue;
            }
        }
    }
    str[n] = mnn[n];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[m][i][j] = 1;
    for(int j = 0; j <= m; j++)
        for(int i = 1; i <= n + 1; i++)
            dp[j][i][i - 1] = 1;
    suf[n + 1] = n + 1;
    for(int j = m - 1; j >= 0; j--) {
        for(int i = 1; i <= n; i++)
            pre[i] = (str[i][j] == '0' ? i : pre[i - 1]);
        for(int i = n; i >= 1; i--)
            suf[i] = (str[i][j] == '1' ? i : suf[i + 1]);
        for(int l = 1; l <= n; l++)
            for(int r = l; r <= n; r++) {
                int lo = max(l - 1, pre[r]);
                int hi = min(r, suf[l] - 1);
                for(int k = lo; k <= hi; k++)
                    dp[j][l][r] = (dp[j][l][r] + dp[j + 1][l][k] * dp[j + 1][k + 1][r]) % MOD;
            }
    }
    cout << mnn[n] << " " << dp[0][1][n];
}

void read() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> str[i];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}