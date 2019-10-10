#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
const ll INF = (1ll << 60);

int n , m , s , t;

struct Node {
    int d , pos;
    bool operator < (const Node &r) const {
        return d > r.d;
    }
};

struct Edge {
    int u , v , w;
};

int dis[MAXN];
int vis[MAXN];
vector <Edge> edge[MAXN];
priority_queue <Node> q;

void add(int u, int v, int w) {
    edge[u].push_back(Edge{u, v, w});

}

void Dijstra(int s) {
    while(!q.empty()) q.pop();
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i++) dis[i] = INF;
    dis[s] = 0;
    q.push(Node{0,s});
    while(!q.empty() ) {
        Node t = q.top();
        q.pop();
        int u = t.pos;
        if(vis[u]) continue;
        vis[u] = 1;
        int len = edge[u].size();
        for(int i = 0; i < len; i++) {
            Edge &e = edge[u][i];
            if(dis[e.v] > dis[u] + e.w) {
                dis[e.v] = dis[u] + e.w;
                q.push(Node {dis[e.v], e.v});
            }
        }
    }
}
