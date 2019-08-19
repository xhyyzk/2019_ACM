https://ac.nowcoder.com/acm/contest/881/H?&headNav=acm
题意：求n个数中子集内所有数异或为00的子集大小之和。
题解：可以求出每个数在子集中出现的次数之和。

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;
int n, r, tot;  //r表示线性基的大小
bool vis[MAXN];
vector<ll> vec;
ll a[MAXN], b[105], other[105], tmp[105];

ll qpow(ll x, int n) {
    ll res = 1;
    while(n) {
        if(n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

//构造线性基
bool ins(ll x, ll base[]) {
    for(int i = 63; i >= 0; --i) {
        if(x & (1ll << i)) {
            if(base[i]) x ^= base[i];
            else {
                base[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main() {
    while(~scanf("%d", &n)) {
        r = tot = 0;
        vec.clear();
        for(int i = 0; i <= 63; ++i) b[i] = other[i] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            vis[i] = 0;
            if(ins(a[i], b)) vis[i] = 1, ++r, vec.push_back(a[i]);
        }
        if(r == n) {
            printf("0\n");
            continue;
        }
        /*先枚举线性基之外的数，那么一共有2^(n-r-1)个集合，
           因为对于每个元素，先把它选走，剩下的不在R中的元素就可以随便选（也可以都不选），
           然后基R中一定能找出对应的元素组合把它们搞成0*/
        ll ans = qpow(2, n - r - 1) * (n - r) % mod;;
        for(int i = 1; i <= n; ++i) {
            if(vis[i]) continue;
            ins(a[i], other);
        }
        /*遍历R中的元素，把它拎出来，给剩下的n-1个元素建个基other
          如果被拎出来的元素还能插♂进基other，那就没救了，绝对异或不出0
          否则它对答案的贡献就是2^(n-|other|-1)，理由同上，
          不在other中的其他元素可以随便选，而从D中选子集的方案唯一*/
        for(int i = 0; i < vec.size(); ++i) {
            tot = 0;
            for(int j = 0; j <= 63; ++j) tmp[j] = 0;
            for(int j = 0; j < vec.size(); ++j) {
                if(i == j) continue;
                if(ins(vec[j], tmp)) ++tot;
            }

            /*求基other可以加速，给n个元素中没在基R里的元素建个基B
               然后每次把扔掉一个元素的基R和B合并*/
            for(int j = 0; j <= 63; ++j) {
                if(other[j] && ins(other[j], tmp)) ++tot;
            }
            if(!ins(vec[i], tmp)) {
                ans = (ans + qpow(2, n - tot - 1)) % mod;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
