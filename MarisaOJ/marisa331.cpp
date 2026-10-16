// buon ngu nen luoi code
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;
const int maxn=1e5;
int n,q,u,v,st[maxn+5],en[maxn+5],cnt=0,type;
ll t[maxn<<2],lz[maxn<<2];
vector<int>adj[maxn+5],f;
void push(int id,int l,int r,int mid) {
    lz[id<<1]+=lz[id];
    lz[id<<1|1]+=lz[id];
    t[id<<1]+=lz[id]*(mid-l+1);
    t[id<<1|1]+=lz[id]*(r-mid);
    lz[id]=0;
}

void up(int id,int l,int r,int u,int v,int x){
    if(u>r||v<l)return;
    if(u<=l&&v>=r){
        lz[id]+=x;
        t[id]+=x*(r-l+1); 
        return;
    }
    int mid=l+r>>1;
    if(lz[id])push(id,l,r,mid);
    up(id<<1,l,mid,u,v,x);
    up(id<<1|1,mid+1,r,u,v,x);
    t[id]=t[id<<1]+t[id<<1|1];
}
ll get(int id,int l,int r,int u){
    if(l==r)return t[id];
    int mid=l+r>>1;
    if(lz[id])push(id,l,r,mid);
    return (u<=mid?get(id<<1,l,mid,u):get(id<<1|1,mid+1,r,u));
}
void dfs(int u,int p){
    st[u]=++cnt;
    f.push_back(u);
    for(int v:adj[u]){
        if(v!=p){
            dfs(v,u);
        }
    }
    en[u]=cnt;
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    if(fopen(".INP","r")){
        freopen(".INP","r",stdin);
        freopen(".OUT","w",stdout);
    }
    cin>>n>>q;
    n--;
    while(n--){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    f.push_back(0);
    dfs(1,-1);
    n=f.size();
    while(q--){
        cin>>type>>u;
        if(type==1){
            cin>>v;
            up(1,1,n,st[u],en[u],v);
        }else cout<<get(1,1,n,st[u])<<'\n';
    }
    return 0;
}
