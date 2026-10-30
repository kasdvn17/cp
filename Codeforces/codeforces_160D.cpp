#include <bits/stdc++.h>
#define MAXX 100005
using namespace std;

struct E {
	int u, v, w, idx;
};

int n, m, ans[MAXX];
int par[MAXX], sz[MAXX];
E edges[MAXX];

int find_set(int x) {
	if(par[x] == x)
		return x;
	return par[x] = find_set(par[x]);
}

void join(int x, int y) {
	x = find_set(x), y = find_set(y);
	if(x == y)
		return;
	if(sz[x] > sz[y])
		swap(x, y);
	sz[y] += sz[x];
	par[x] = y;
}

bool cmp(E x, E y) {
	return x.w < y.w;
}

void solve() {
	sort(edges + 1, edges + m + 1, cmp);
	for(int i = 1; i <= n; i++)
		par[i] = i, sz[i] = 1;
	int l = 1;
	while(l <= m) {
		int r = l;
		while(r <= m && edges[r].w == edges[l].w)
			r++;
		r--;
        int cnt = 0;
        stack<int> cc;
		for(int i = l; i <= r; i++)
			if(find_set(edges[i].u) != find_set(edges[i].v))
				ans[edges[i].idx] = 2, cnt++;
		for(int i = l; i <= r; i++) {
            if(find_set(edges[i].u) != find_set(edges[i].v))
                cnt--;
            join(edges[i].u, edges[i].v);
        }
        if(cnt > 0) {
            for(int i = l; i <= r; i++)
                ans[edges[i].idx] = 1;
        }
		l = r + 1;
	}
	for(int i = 1; i <= m; i++) {
        if(ans[i] == 1) cout << "at least one\n";
        else if(ans[i] == 2) cout << "any\n";
        else cout << "none\n";
    }
}

void read() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
		cin >> edges[i].u >> edges[i].v >> edges[i].w, edges[i].idx = i;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	read();
	solve();
}