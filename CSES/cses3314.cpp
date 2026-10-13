#include <bits/stdc++.h>
#define int long long
#define MAXX 200005
using namespace std;

int n, res, h[MAXX];
int L[MAXX], R[MAXX];
int seg[4 * MAXX], dp[MAXX];
stack<int> st;
vector<pair<int, int>> vec;

void update(int idx, int l, int r, int pos, int val) {
    if(l > pos || r < pos)
        return;
    if(l == r) {
        seg[idx] = max(seg[idx], val);
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * idx, l, mid, pos, val);
    update(2 * idx + 1, mid + 1, r, pos, val);
    seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
}

int query(int idx, int l, int r, int s, int e) {
    if(l > e || r < s)
        return 0;
    if(l >= s && r <= e)
        return seg[idx];
    int mid = (l + r) >> 1;
    return max(query(2 * idx, l, mid, s, e), query(2 * idx + 1, mid + 1, r, s, e));
}

void solve() {
    for(int i = 1; i <= n; i++) {
        while(st.size() && h[st.top()] < h[i])
            st.pop();
        if(st.empty())
            L[i] = 1;
        else
            L[i] = st.top() + 1;
        st.push(i);
    }
    while(st.size())
        st.pop();
    for(int i = n; i >= 1; i--) {
        while(st.size() && h[st.top()] < h[i])
            st.pop();
        if(st.empty())
            R[i] = n;
        else
            R[i] = st.top() - 1;
        st.push(i);
    }
    for(int i = 1; i <= n; i++)
        vec.push_back({h[i], i});
    sort(vec.begin(), vec.end());
    for(auto [_, idx] : vec) {
        int v = query(1, 1, n, L[idx], R[idx]) + 1;
        // cout << _ << " " << idx << " " << L[idx] << " " << R[idx] << " " << v << "\n";
        res = max(res, v);
        update(1, 1, n, idx, v);
    }
    cout << res;
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> h[i];
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