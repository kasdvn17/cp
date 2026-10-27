#include <bits/stdc++.h>
#include "color3lib.h"
using namespace std;

namespace DFSA {
    int n, m;
    vector<vector<int>> path;
    vector<int> par, ord;

    void dfs(int x, int p) {
        par[x] = p;
        ord.push_back(x);
        for(auto v : path[x])
            if(!par[v])
                dfs(v, x);
    }

    void init(int v, const vector<pair<int, int>>& ed) {
        n = v;
        path.resize(n + 1, vector<int>(0));
        par.resize(n + 1, 0);
        for(auto [x, y] : ed) {
            path[x].push_back(y);
            path[y].push_back(x);
        }
        for(int i = 1; i <= n; i++)
            sort(path[i].begin(), path[i].end());
        for(int i = 1; i <= n; i++)
            if(!par[i])
                dfs(i, -1);
    }
}

namespace DFSB {
    int n, m;
    vector<vector<int>> path;
    vector<int> par, ord;

    void dfs(int x, int p) {
        par[x] = p;
        ord.push_back(x);
        for(auto v : path[x])
            if(!par[v])
                dfs(v, x);
    }

    void init(int v, const vector<pair<int, int>>& ed) {
        n = v;
        path.resize(n + 1, vector<int>(0));
        par.resize(n + 1, 0);
        for(auto [x, y] : ed) {
            path[x].push_back(y);
            path[y].push_back(x);
        }
        for(int i = 1; i <= n; i++)
            sort(path[i].begin(), path[i].end());
        for(int i = 1; i <= n; i++)
            if(!par[i])
                dfs(i, -1);
    }
}

namespace personA {
 // n: số đỉnh, m: số cạnh
 // edges: danh sách m cạnh
 // colors: mảng n phần tử, colors[i] (1, 2 hoặc 3) là màu của đỉnh
 string Alice (int n, int m, const vector<pair<int, int>>&
edges, const vector<int>& colors) {
 // Viết code xử lý của Alice tại đây
 // Trả về một xâu gồm đúng n ký tự '0' hoặc '1'
 string res(n, '#');
 DFSA::init(n, edges);
 for(int i = 1; i <= n; i++) {
    int par = DFSA::par[i];
    if(par == -1)
        res[i - 1] = '0';
    else {
        int diff = (colors[i - 1] - colors[par - 1] + 3) % 3;
        res[i - 1] = (char)('0' + diff - 1);
    }
 }
 return res;
 }
}
namespace personB {
 // n: số đỉnh, m: số cạnh
 // edges: danh sách m cạnh
 // bits: xâu nhị phân độ dài n do Alice truyền sang
 void Bob (int n, int m, const vector<pair<int, int>>& edges,
const string& bits) {
 // Viết code xử lý của Bob tại đây
 vector<int> col(n + 1, 0);
 DFSB::init(n, edges);
 for(auto x : DFSB::ord) {
    int par = DFSB::par[x];
    if(par == -1)
        paint(x, 1), col[x] = 0;
    else {
        int cp = col[par];
        int st = bits[x - 1] - '0' + 1;
        int tar = (cp + st) % 3;
        paint(x, tar + 1);
        col[x] = tar;
    }
 }
 }
}