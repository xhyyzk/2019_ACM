#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 10;
bool vis[MAXN];
int pri[MAXN]; //素数筛
int phi[MAXN]; //欧拉函数
int mu[MAXN]; //莫比乌斯函数
int tot;
int f[MAXN], g[MAXN]; //f表示i的约数和，g表示最小质因子的 p^1 + p^2 + p^3 +...+p^k

void init(int n) {
    memset(vis, 0, sizeof(vis));
    phi[1] = 1;
    tot = 0;
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) {
            pri[++tot] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= tot && i * pri[j] <= n; ++j) {
            vis[i* pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            }
            else  phi[i * pri[j]] = phi[i] * (pri[j] - 1);
        }
    }
}

//莫比乌斯函数
void pre() {
  mu[1] = 1;
  for (int i = 2; i <= 1e7; ++i) {
    if (!v[i]) mu[i] = -1, p[++tot] = i;
    for (int j = 1; j <= tot && i <= 1e7 / p[j]; ++j) {
      v[i * p[j]] = 1;
      if (i % p[j] == 0) {
        mu[i * p[j]] = 0;
        break;
      }
      mu[i * p[j]] = -mu[i];
    }
  }


  //约数和
  void pre() {
  g[1] = f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!v[i]) v[i] = 1, p[++tot] = i, g[i] = i + 1, f[i] = i + 1;
    for (int j = 1; j <= tot && i <= n / p[j]; ++j) {
      v[p[j] * i] = 1;
      if (i % p[j] == 0) {
        g[i * p[j]] = g[i] * p[j] + 1;
        f[i * p[j]] = f[i] / g[i] * g[i * p[j]];
        break;
      } else {
        f[i * p[j]] = f[i] * f[p[j]];
        g[i * p[j]] = 1 + p[j];
      }
    }
  }
  for (int i = 1; i <= n; ++i) f[i] = (f[i - 1] + f[i]) % Mod;
}
