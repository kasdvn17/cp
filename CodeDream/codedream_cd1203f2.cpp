#include <bits/stdc++.h>
#define int long long
#define MAXX 102
#define MAX2 60002
using namespace std;

struct DA {
    int a, b;
};

int n, r, res, cnt;
int dp[MAXX][MAX2]; // xet den thang i, dang co r diem uy tin thi cnt lon nhat la bao nhieu
DA d[MAXX];
vector<DA> am, duong;

bool cmpduong(DA x, DA y) {
    return x.a < y.a;
}

bool cmpam(DA x, DA y) {
    return x.a + x.b > y.a + y.b;
}

void solve() {
    for(int i = 1; i <= n; i++) {
        if(d[i].b >= 0) duong.push_back(d[i]);
        else am.push_back(d[i]);
    }
    sort(duong.begin(), duong.end(), cmpduong);
    for(auto [a, b] : duong) {
        if(r >= a) cnt++, r += b;
        else break;
    }
    sort(am.begin(), am.end(), cmpam);
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= r; j++)
            dp[i][j] = -1e18;
    dp[0][r] = 0;
    for(int i = 1; i <= am.size(); i++)
        for(int j = r; j >= 0; j--) {
            dp[i][j] = dp[i - 1][j];
            if(j - am[i - 1].b >= am[i - 1].a && j - am[i - 1].b <= r) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - am[i - 1].b] + 1);
                res = max(res, dp[i][j]);
            }
            // cout << i << " " << j << " " << dp[i][j] << " " << am[i - 1].a << " " << am[i - 1].b << '\n';
        }
    cout << res + cnt;
}

void read() {
    cin >> n >> r;
    for(int i = 1; i <= n; i++)
        cin >> d[i].a >> d[i].b;
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

    file();
    read();
    solve();
}