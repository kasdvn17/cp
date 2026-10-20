#include <bits/stdc++.h>
#define int long long
#define MAXX 100005
using namespace std;

int n, res, a[MAXX], cnt[MAXX];

// vector 5
vector<int> process(vector<int> avail, int prv) {
    int times = 1e9;
    vector<int> res = {-1, -1, -1, -1, -1};
    if(avail.size() <= 1) {
        res[avail[0] - 1] = 0;
        return res;
    }
    for(int i = 1; i <= 5; i++)
        if(cnt[i] > 0) times = min(times, cnt[i]);
    do {
        int lst = (avail.front() - avail.back() + 5) % 5, ck = 0, tot = 0;
        if(prv != 0) tot = (avail.front() - prv + 5) % 5;
        for(int i = 1; i < avail.size(); i++)
            ck += (avail[i] - avail[i - 1] + 5) % 5;
        tot = tot + ck * times + lst * (times - 1);
        res[avail.back() - 1] = max(res[avail.back() - 1], tot);
    } while(next_permutation(avail.begin(), avail.end()));
    return res;
}

bool check() {
    for(int i = 1; i <= 5; i++)
        if(cnt[i] > 0)
            return true;
    return false;
}

void solve() {
    vector<int> prv = {-2, -2, -2, -2, -2};
    while(check()) {
        vector<int> avail;
        for(int i = 1; i <= 5; i++)
            if(cnt[i])
                avail.push_back(i);
        vector<int> tmp, nwprv = {-1, -1, -1, -1, -1};
        for(int prvv = 1; prvv <= 5; prvv++) {
            if(prv[prvv - 1] == -1) continue;
            if(prv[prvv - 1] == -2) tmp = process(avail, 0);
            else tmp = process(avail, prvv);
            for(int i = 1; i <= 5; i++) {
                int v2 = 0;
                if(prv[prvv - 1] < 0) v2 = tmp[i - 1];
                else v2 = tmp[i - 1] + prv[prvv - 1];
                nwprv[i - 1] = max(nwprv[i - 1], v2);
            }
        }
        prv = nwprv;
    }
    for(int i = 1; i <= 5; i++)
        cout << prv[i - 1] << " ";
}

void read() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i], cnt[a[i]]++;
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