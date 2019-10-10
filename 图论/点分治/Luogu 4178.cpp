给你一棵TREE,以及这棵树上边的距离.问有多少对点它们两者间的距离小于等于K

#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct edge{
    int to,next,w;
}e[80001];

int n,tot,root;
ll k;
int head[40001];


void addedge(int u, int v, int l){
    e[++tot].to = v;
    e[tot].next = head[u];
    e[tot].w = l;
    head[u] = tot;
}
int size_[40001],vis[40001],mx,sz;
ll dis[40001],q[40001],l,r;

void getroot(int u,int fa){
    size_[u] = 1;
    int num=0;
    for(int i = head[u]; i; i=e[i].next){
        int v = e[i].to;
        if(v == fa || vis[v])continue;
        getroot(v, u);
        size_[u] += size_[v];
        num = max(num, size_[v]);
    }
    num=max(num, sz-size_[u]);
    if(num < mx){
        mx = num;
        root = u;
    }
}
void getdis(int u,int fa){
    q[++r] = dis[u];
    for(int i=head[u]; i; i = e[i].next){
        int v = e[i].to;
        if(v == fa || vis[v])continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
}
ll calc(int x, int v){
    r = 0;
    dis[x] = v;
    getdis(x, 0);
    ll sum = 0;
    l = 1;
    sort(q+1, q+r+1);
    while(l < r){
        if(q[l] + q[r] <= k) {
            sum += r-l;
            l++;
        }
        else r--;
    }
    return sum;
}

ll ans;
void dfs(int u){
    ans += calc(u,0);
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next){
        int v = e[i].to;
        if(vis[v])continue;
        ans -= calc(v, e[i].w);
        sz = size_[v];
        mx = 0x3f3f3f3f;
        getroot(v, 0);
        dfs(root);
    }
}
int main(){
    scanf("%d", &n);
    int u, v, w;
    for(int i = 1; i < n; i++){
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    scanf("%d", &k);
    sz = n;
    mx = 0x3f3f3f3f;
    getroot(1, 0);
    dfs(root);
    printf("%lld",ans);
    return 0;
}
