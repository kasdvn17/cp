#include <bits/stdc++.h>
#define int long long
using namespace std;
long long dp[2][20][200][4];
int x[20];

long long f(int idx, bool smaller, int prv, bool started) {
	if(idx < 0)
		return started ? 1 : 0;
    long long &memo = dp[smaller][idx][prv][started];
    if(memo != -1) return memo;
    int lim = smaller ? 9 : x[idx];
    memo = 0;
    for(int digit = 0; digit <= lim; ++digit) {
    	if(started && digit == prv)
    		continue;
    	int nsmal = smaller || (digit < lim);
    	bool nstart = started || (digit > 0);
        memo += f(idx - 1, nsmal, digit, nstart);
    }
    return memo;
}

long long G(long long X){
	if(X == -1)
		return -1;
    int n = 0; x[n] = 0;
    while(X > 0){
        x[n++] = X % 10;
        X /= 10;
    }

    memset(dp, -1, sizeof(dp));
    return f(n - 1, 0, 0, false);
}

signed main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long a, b; cin >> a >> b;
    cout << G(b) - G(a - 1);

    return 0;
}