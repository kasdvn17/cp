#include <bits/stdc++.h>
#define MAXX 1002
#define int long long
using namespace std;

int n, k, Mod;
char s[MAXX];

struct M {
  int arr[2][2] = {0};

  void init(int a, int b, int c, int d) {
    arr[0][0] = a;
    arr[0][1] = b;
    arr[1][0] = c;
    arr[1][1] = d;
  }
};

M A, base;

M mul(M x, M y) {
  M res;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) {
      // res[i][j] = x[i] * y[j]
      __int128 tot = 0;
      for (int k = 0; k < 2; k++) tot = (tot + (__int128)x.arr[i][k] * y.arr[k][j]) % Mod;
      tot %= Mod;
      int v2 = tot;
      res.arr[i][j] = v2;
    }
  return res;
}

M pow2(M x, int k) {
  if (k == 0) return base;
  if (k == 1) return x;
  M T = pow2(x, k / 2);
  T = mul(T, T);
  if (k & 1) return mul(T, x);
  return T;
}

void solve() {
  M L, R;
  base.init(1, 0, 0, 1);
  L.init(1, 0, 1, 1);
  R.init(1, 1, 0, 1);
  A= base;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'L')
      A = mul(A, L);
    else
      A = mul(A, R);
  }
  // cout << A.arr[0][0] << " " << A.arr[0][1] << " " << A.arr[1][0] << " "
  // << A.arr[1][1] << "\n";
  A = pow2(A, k);
  cout << ((A.arr[0][0] + A.arr[0][1]) % Mod) << " " << ((A.arr[1][0] + A.arr[1][1]) % Mod);
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  string str;
  cin >> n >> k >> Mod >> str;
  for (int i = 1; i <= n; i++) s[i] = str[i - 1];
  solve();
}