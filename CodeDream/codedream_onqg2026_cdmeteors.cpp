//author: hdmknkttp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define fi first
#define se second
#define pb push_back
typedef pair<int, int> pii;
typedef pair<ld, ld> pdd;
#define arr(T, i) array<T, i>
#define arr2d(T, i, j) array<array<T, j>,i>

const int N = 3e5 + 5;
const int INF = 1e18;
const int MOD = 1e9 + 7;

struct Q
{
	int l, r, a;
} queries[N];

int n, m, k;
int p[N], BIT[N], L[N], R[N], ans[N];
vector<int> pos[N], bucket[N];

void upd(int pp, int a)
{
	while(pp<=m)
	{
		BIT[pp] += a;
		pp += pp & -pp;
	}
}

int get(int pp)
{
	int cur = 0;
	while(pp > 0)
	{
		cur += BIT[pp];
		pp -= pp & -pp;
	}
	return cur;
}

int check(int i)
{
	int cur = 0;
	for (int t : pos[i])
	{
		cur += get(t);
	}
	return cur;
}

void solve()
{
	int ini = 1;
	memset(ans, -1, sizeof ans);
	while(ini)
	{
		ini = 0;
		for (int i = 1; i<=n; i++)
		{
			if (L[i] <= R[i])
			{
				ini = 1;
				bucket[(L[i] + R[i])>>1].pb(i);
			}
		}
		if (!ini) break;
		for (int i = 1; i<=k; i++)
		{
			auto [l, r, a] = queries[i];
			if (l <= r)
			{
				upd(l, a);
				upd(r+1, -a);
			}
			else
			{
				upd(l, a);
				upd(m+1, -a);
				upd(1, a);
				upd(r+1, -a);
			}
			for (int id : bucket[i])
			{
				if (check(id) >= p[id])
				{
					ans[id] = i;
					R[id] = i - 1;
				}
				else
				{
					L[id] = i + 1;
				}
			}
			bucket[i].clear();
		}
        // for (int i = 1; i<=m; i++)
        // {
        //     cout << BIT[i] << ' ';
        // }
        // cout << "\n";
		memset(BIT, 0, sizeof BIT);
	}
	for (int i = 1; i<=n; i++)
	{
		if (ans[i] == -1) cout << "NIE\n";
		else cout << ans[i] << "\n";
	}
}


void read()
{
	cin >> n >> m;
	for (int i = 1; i<=m; i++)
	{
		int x; cin >> x;
		pos[x].pb(i);
	}
	for (int i = 1; i<=n; i++)
	{
		cin >> p[i];
	}
	cin >> k;
	for (int i = 1; i<=k; i++)
	{
		cin >> queries[i].l >> queries[i].r >> queries[i].a;
	}
	for (int i = 1; i<=n; i++)
	{
		L[i] = 1; R[i] = k;
		ans[i] = N;
	}
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	//cin >> t;
	
	while(t--)
	{
		read();
		solve();
	}
}
