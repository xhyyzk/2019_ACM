Multi_Nim博弈
    一个单一游戏的后继可以为多个单一游戏
    规则与SG游戏相同
    仍然可以使用SG函数，后继为多个单一游戏，这个后继的SG值为多个单一游戏的SG值的异或和。

poj 3537
    在一个1×n的格子上画×，每次可以在空格子画×，当走完自己这一步后有连续的三个×，即为胜利
给出一个n,问先手输赢。
易知，当i画上×时，后手不能再前两格和后两格画×，所以sg(i-3)^sg(n-i-2).

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
int n;
int sg[2100];

int GetSg(int n) {
    if(n < 0) return 0;
    if(sg[n] >= 0) return sg[n];
    bool vis[2100] = {0};        //注意vis数组开在函数里，不能开全局
    for(int i = 1; i <= n; ++i)
        vis[GetSg(i - 3) ^ GetSg(n - i - 2)] = 1;  //分成两个单一游戏的，异或和
    for(int i = 0;; ++i) {
        if(vis[i] == 0) return sg[n] = i;
    }
}

int main() {
    memset(sg, -1, sizeof(sg));
    while(~scanf("%d", &n)) {
        if(GetSg(n)) cout << 1 << endl;
        else cout << 2 << endl;
    }
    return 0;
}


poj 2311
两个人轮流剪一张n*m的纸，先剪出1*1的纸的人赢。
可以知道一张i*j的纸，可以剪成k*j和(i-k)*j 或 i*k 和 i*(j-k)，所以异或起来就好了

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
int n, m;
int sg[210][210];
int vis[210];

int main() {
    sg[2][2] = sg[2][3] = sg[3][2] = sg[3][3] = 0;  //显然必输的点
    for(int i = 2; i <= 210; ++i) {
        for(int j = 2; j <= 210; ++j) {
            memset(vis, 0, sizeof(vis));
            for(int k = 2; k < i - 1; ++k) vis[sg[k][j] ^ sg[i - k][j]] = 1;
            for(int k = 2; k < j - 1; ++k) vis[sg[i][k] ^ sg[i][j - k]] = 1;
            for(int k = 0;;++k) {
                if(!vis[k]) {
                    sg[i][j] = k;
                    break;
                }
            }
        }
    }
    while(~scanf("%d%d", &n, &m)) {
        if(sg[n][m]) cout << "WIN" << endl;
        else cout << "LOSE" << endl;
    }
    return 0;
}
