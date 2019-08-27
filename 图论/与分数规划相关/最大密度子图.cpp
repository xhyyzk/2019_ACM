UVA 1389
题意：有n个点， m条边，即求出一些点，使得这些点之间的点数/边数最大。

解法：
    设g = E / V, 源点到各个点连接一条有向边权值为U,各个点到汇点连接一条边权值为U+2*g-d，
原来有关系的点连接两条有向边（u,v），（v,u）权值为1（U可以取m，U的目的是用来使得2*g-d的
值始终为正），这样以后求最小割，那么h（g）= （U*n-mincut）/2;二分找到最优值即为mid ，
但是如果要求图中的点则需要用left来从新图求最大流之后然后从源点开始dfs遍历，最后得出结果。

代码：
#include <bits/stdc++.h>
using namespace std;
const int N=110;
const double inf=0x3fffffff;
const double eps=1e-8;
int gap[N],dis[N],start,end,ans,sum,head[N],num,dep[N],n,m;
bool vis[N];
struct edge
{
    int st,ed,next;
    double flow;
}e[80*N];
struct node
{
    int x,y;
}P[1100];
void addedge(int x,int y,double w)
{
    e[num].st=x;e[num].ed=y;e[num].flow=w;e[num].next=head[x];head[x]=num++;
    e[num].st=y;e[num].ed=x;e[num].flow=0;e[num].next=head[y];head[y]=num++;
}
void makemap(double g)
{
    int i;
    memset(head,-1,sizeof(head));
    num=0;
    for(i=1;i<=n;i++)
    {
        addedge(start,i,m*1.0);
        addedge(i,end,m+2*g-dep[i]);
    }
    for(i=0;i<m;i++)
    {
        addedge(P[i].x,P[i].y,1.0);
        addedge(P[i].y,P[i].x,1.0);
    }
}
double dfs(int u,double mincut)
{
    if(u==end)return mincut;
    int i,v;
    double f,flow=0.0;
    for(i=head[u];i!=-1;i=e[i].next)
    {
        v=e[i].ed;
        if(e[i].flow>0)
        {
            if(dis[v]+1==dis[u])
            {
                f=dfs(v,e[i].flow > mincut - flow ? mincut - flow : e[i].flow);
                flow += f;
                e[i].flow -= f;
                e[i^1].flow += f;
                if(mincut-flow <= 1e-8)return flow;
                if(dis[start] >= ans)return flow;
            }
        }
    }
    if(--gap[dis[u]]==0)
        dis[start]=ans;
    dis[u]++;
    gap[dis[u]]++;
    return flow;
}
double isap()
{
    double maxflow=0.0;
    memset(gap,0,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0]=ans;
    while(dis[start]<ans)
        maxflow+=dfs(start,inf);
    return maxflow;
}
void dfs1(int u)//遍历要选的点
{
    vis[u]=true;
    sum++;
    for(int i=head[u];i!=-1;i=e[i].next)
    {
        int v=e[i].ed;
        if(vis[v]==false&&e[i].flow>0)
          dfs1(v);
    }
}
int main()
{
    int i;
    double Left,Right,mid,hg;
    while(scanf("%d%d",&n,&m)!=-1)
    {
        if(m==0){printf("1\n1\n");continue;}
        start=0,end=n+1,ans=end+1;
        memset(dep,0,sizeof(dep));
        for(i=0;i<m;i++)
        {
            scanf("%d%d",&P[i].x,&P[i].y);
            dep[P[i].x]++;dep[P[i].y]++;
        }
        Left=0;Right=m;
        while(Right-Left>=1.0/n/n)//胡伯涛的论文给出了证明,不同解之间误差的精度不超过1/(n*n）
        {
            mid=(Left+Right)/2;
            makemap(mid);
            hg=isap();
            hg=(1.0*n*m-hg)/2;
            if(hg>eps)
                Left=mid;
            else Right=mid;
        }
        makemap(Left);//用mid值建图容易wa,因为你此时的mid不一定满足h(mid)>eps,但是Left一定是满足的
        isap();
        memset(vis,false,sizeof(vis));
        sum=0;
        dfs1(0);
        printf("%d\n",sum-1);
        for(i=1;i<=n;i++)
          if(vis[i]==true)
              printf("%d\n",i);
    }
    return 0;
}
