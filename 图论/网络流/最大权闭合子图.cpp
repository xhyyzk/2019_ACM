最大权闭合子图
定义：
    有一个有向图，每一个点都有一个权值（可以为正或负或0），选择一个权值和最大的子图，
使得每个点的后继都在子图里面，这个子图就叫最大权闭合子图。

建图：
    每个正权点向源点S连容量为权值的边，每个负权点向汇点T连容量为点权绝对值的边，有向图
原来的边容量全部为无限大。求它的最小割，割掉后，与源点s连通的点构成最大权闭合子图，权值
为（正权值之和-最小割）。

bzoj 1497
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 6e4 + 10; //
const int MAXM = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
typedef long long ll;
int n, m, a, b, p, c;

struct Edge{
    int to, next, cap, flow;  //容量  流量
}edge[8*MAXN];

int tol;   //边编号
int head[MAXN];
void init() {
    tol = 2;
    memset(head, -1, sizeof(head));
}

void add(int u, int v, int w, int rw = 0) {
    edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0;
    edge[tol].next = head[u]; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0;
    edge[tol].next = head[v]; head[v] = tol++;
}

int Q[MAXN];
int dep[MAXN], cur[MAXN], sta[MAXN];

bool bfs(int s, int t, int n) {   //分层
    int front = 0, tail = 0;
    memset(dep, -1, sizeof(dep[0])*(n+1));
    dep[s] = 0;
    Q[tail++] = s;
    while(front < tail)  {  //模拟队列
        int u = Q[front++];
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dep[v] == -1) {
                dep[v] = dep[u] + 1;
                if(v == t) return 1;
                Q[tail++] = v;
            }
        }
    }
    return 0;
}

int dinic(int s, int t, int n) {
    int maxflow = 0;
    while(bfs(s, t, n) ) {
        for(int i = 0; i < n; i++) cur[i] = head[i];
        int u = s, tail = 0;
        while(cur[s] != -1) {
            if(u == t) {
                int tp = INF;
                for(int i = tail -1; i >= 0; i--)
                    tp = min(tp, edge[sta[i]].cap - edge[sta[i]].flow);
                maxflow += tp;
                for(int i = tail - 1; i >= 0; i--) {
                    edge[sta[i]].flow += tp;
                    edge[sta[i]^1].flow -= tp;
                    if(edge[sta[i]].cap - edge[sta[i]].flow == 0)
                        tail = i;
                }

                u = edge[sta[tail]^1].to;

            }
            else if(cur[u] != -1 &&
                edge[cur[u]].cap > edge[cur[u]].flow &&
                 dep[u]+1 == dep[edge[cur[u]].to] ){
                sta[tail++] = cur[u];
                u = edge[cur[u]].to;

            }
            else {
                while(u != s && cur[u] == -1)
                    u = edge[sta[--tail]^1].to;
                cur[u] = edge[cur[u]].next;

            }
        }
    }
    return maxflow;
}

int main() {
    scanf("%d%d", &n, &m);
    int s = 0, t = n + m + 1;
    init();
    for(int i = m + 1; i <= n + m; ++i) {
        scanf("%d", &p);
        add(i, t, p);
    }
    int sum = 0;
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        sum += c;
        add(i, m + a, INF);
        add(i, m + b, INF);
        add(s, i, c);
    }
    cout << sum - dinic(s, t, n + m + 2) << endl;
    return 0;
}
