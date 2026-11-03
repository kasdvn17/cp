#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define ll long long
#define MAXX 500005
using namespace std;

int n, m, q, k, cursz[MAXX], deg[MAXX], vis[MAXX];
ll totto[MAXX], w[MAXX];
vector<int> path[MAXX];
int npath[MAXX][5];
int szo, ord[MAXX];
queue<int> qu;
unsigned int seed;
unsigned long long XOR_SUM = 0;

unsigned int next_rand() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

void solve() {
    for(int i = 1; i <= n; i++)
        if(deg[i] <= 5)
            qu.push(i);
    while(qu.size()) {
        int z = qu.front();
        qu.pop();
        ord[++szo] = z;
        for(auto v : path[z]) {
            deg[v]--;
            if(deg[v] == 5)
                qu.push(v);
        }
    }
    for(int _ = n; _ >= 1; _--) {
        int i = ord[_];
        vis[i] = true;
        for(auto z : path[i])
            if(vis[z])
                npath[i][cursz[i]++] = z, totto[z] += w[i];
    }
    while(q--) {
        int type = (next_rand() % 2) + 1;
        int u = (next_rand() % k) + 1;
        if (type == 1) {
            long long x = (next_rand() % 1000000000) + 1;
            // gan cong suat tram u thanh x
            ll diff = x - w[u];
            w[u] = x;
            for(int v = 0; v < 5; v++) {
                if(!npath[u][v])
                    break;
                totto[npath[u][v]] += diff;
            }
        } else {
            long long ans = totto[u];
            for(int v = 0; v < 5; v++) {
                if(!npath[u][v])
                    break;
                ans += w[npath[u][v]];
            }
            XOR_SUM ^= ans;
        }
    }
    cout << XOR_SUM;
}

void read() {
    cin >> n >> m >> q >> k >> seed;
    for(int i = 1; i <= n; i++)
        cin >> w[i];
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        path[u].push_back(v);
        path[v].push_back(u);
        deg[u]++, deg[v]++;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    read();
    solve();
}