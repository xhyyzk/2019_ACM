#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 10;
bool vis[MAXN];
int pri[MAXN]; //素数筛
int phi[MAXN]; //欧拉函数
int mu[MAXN]; //莫比乌斯函数
int tot;

void init(int n) {
    memset(vis, 0, sizeof(vis));
    phi[1] = 1;
    mu[1] = 1;
    tot = 0;
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) {
            pri[tot++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for(int j = 0; j < tot && i * pri[j] <= n; ++j) {
            vis[i* pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                mu[i * pri[j]] = 0;
                break;
            }
            else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
                mu[i + pri[j]] = -mu[i];
            }
        }
    }
}
