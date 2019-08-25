树上删边游戏
    给出一个N个点的有根树，游戏者轮流从树中删去一条边，删去一条边后，不与根节点相连的部
分将被移走，无边可删者输。

结论:
    把每棵树看成Nim游戏的一个石子堆，求出每棵树的sg值做为石子堆的石子个数，再全部异或
起来。每棵树的sg值：叶子节点的额sg值为0，中间节点的sg值为它所有孩子的sg值加1后的异或和。

树上有环的处理：
奇环：可以等效成一条边，即sg值为1；
偶环：可以等效成一个点，即sg值为0；

无向图删边游戏
    一个无相联通图，有一个点作为图的根，规则和树上山边游戏相同。

结论：
    把任意个一个偶环缩成一个新点，把任意一个奇环缩成一个新点加一条新边。所有连到原先环
上的边全部改为与新点相连，这样就变成了一棵树，再按之前的处理即可。注：这样的改动不会影
响图的sg值。

poj 3710 树上删边游戏
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define N 105

int T,n,m,x,y,top;
int tot, point[N], next[N*10], v[N*10];
int sg[N], stack[N], vis[N];

void clear() {
    n = m = top = 0;
    tot = 0;
    memset(point, 0, sizeof(point));
    memset(sg, 0, sizeof(sg));
    memset(vis,-1,sizeof(vis));
}
void add(int x,int y) {
    ++tot;
    next[tot] = point[x]; point[x] = tot; v[tot]=y;
}
void dfs(int x,int fa) {  //深搜找环
    stack[++top] = x;
    vis[x] = 1;
    bool flag = false;
    for (int i = point[x]; i; i = next[i]) {
        if (v[i] == fa && !flag) {
            flag=true;
            continue;
        }
        if (vis[v[i]] == 1) {   //判断奇环还是偶环
            int now = stack[top], cnt=1;
            while (now != v[i]) {
                cnt++;
                vis[now] = 0;
                now = stack[--top];
            }
            if (cnt % 2) sg[v[i]] ^= 1; //偶环处理
        }
        else if (vis[v[i]]==-1) {
            dfs(v[i], x);
            if (vis[v[i]]) sg[x] ^= (sg[v[i]]+1);
        }
    }
    if (vis[x]) --top;
}
int main() {
    while (~scanf("%d",&T)) {
        int sum = 0;
        while (T--)
        {
            clear();
            scanf("%d%d", &n, &m);
            for (int i=1;i<=m;++i) {
                scanf("%d%d", &x, &y);
                add(x, y);
                add(y, x);
            }
            dfs(1, 0);
            sum ^= sg[1];
        }
        if (sum) puts("Sally");
        else puts("Harry");
    }
    return 0;
}
