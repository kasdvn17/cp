#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, k, a[MAXX];
int mnn[MAXX], mxx[MAXX];
deque<int> dq;

void solve() {
    for(int i = 1; i <= n; i++) {
        while(dq.size() && a[dq.back()] >= a[i])
            dq.pop_back();
        dq.push_back(i);
        if(i < k)
            continue;
        while(dq.size() && dq.front() < i - k + 1)
            dq.pop_front();
        cout << a[dq.front()] << " ";
    }
    while(dq.size())
        dq.pop_back();
    cout << "\n";
    for(int i = 1; i <= n; i++) {
        while(dq.size() && a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        if(i < k)
            continue;
        while(dq.size() && dq.front() < i - k + 1)
            dq.pop_front();
        cout << a[dq.front()] << " ";
    }
}

void read() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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