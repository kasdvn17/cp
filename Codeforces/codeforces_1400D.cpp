// y tuong don gian nen thoi luoi code ah
#include <bits/stdc++.h>
using namespace std;
int n;
void solve()
{
    cin>>n;
    vector<int>cnt(n + 5);
    vector<int>v(n + 5);
    for(int i = 1;i<=n;i ++)
    {
        cin>>v[i];
        cnt[v[i]] ++;
    }
    long long ans = 0;
    for(int i = 1;i<=n - 3;i ++)
    {
        cnt[v[i]] --;
        vector<int>ncnt = cnt;
        vector<int>mp(n + 5);
        long long sum = 0;
        for(int k = i + 1;k <= n - 1;k++)
        {
            ncnt[v[k]] --;
            mp[v[k]] ++;
            sum -= 1LL*(ncnt[v[k]] + 1) * (mp[v[k]] - 1);
            sum += 1LL *ncnt[v[k]] * mp[v[k]];
            if(v[i] == v[k] && k - i >= 2)
            {
                ans += sum - ncnt[v[k]];
            }
        }
       // cout<<sum<<endl;
    }
    cout<<ans<<endl;
    return ;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}