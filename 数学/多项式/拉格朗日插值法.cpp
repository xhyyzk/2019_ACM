2019南昌邀请赛B
对于形如
    f(x) = a0*x^0 + a1*x^1 + a2*x^2 + a3*x^3 +......+an*x^n,
    已知前n+1项，求：对于 i >= l && i <= r, f(i)的和，(mod 9999991)

   先由前n+1项插出第n+1的值，从而得到了前n+2项的前缀和。对于询问l和r，
插出sum(r)和sum(l-1)单点作差即可

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 9999991;
const int N = 1010;
int a[N],sum[N],pre[N],suf[N];
int fact[N],finv[N];

int quickpow(int a,int b,int n)
{
    int res = 1;
    while(b){
        if(b&1) res = 1ll*res*a%n;
        a = 1ll*a*a%n;
        b >>=1;
    }
    return res;
}
//fact阶乘，finv阶乘的逆元
void init()
{
    fact[0] = 1;
    for(int i=1;i<N;i++)
        fact[i] = 1ll*fact[i-1]*i%mod;
    finv[N-1] = quickpow(fact[N-1],mod-2,mod);
    for(int i=N-1;i>=1;i--)
        finv[i-1] = 1ll*finv[i]*i%mod;
}
//已知数组f[0]到f[n]，求f[x].  pre前缀积，suf后缀积
int cal(int *f,int n,int x)
{
    if(x<=n) return f[x];
    int ans = 0;
    pre[0] = suf[n] = 1;
    for(int i=1;i<=n;i++)
        pre[i] = 1ll*pre[i-1]*(x-(i-1))%mod;
    for(int i=n-1;i>=0;i--)
        suf[i] = 1ll*suf[i+1]*(x-(i+1))%mod;

    for(int i=0;i<=n;i++){
        int fu = (n-i)&1?-1:1;
        ans += 1ll*f[i]*fu*pre[i]%mod * suf[i]%mod * finv[i]%mod * finv[n-i]%mod;
        ans = (ans%mod + mod)%mod;
        //printf("%d !!!\n",ans);
    }
    return ans;
}

int main()
{
    init();
    int T; scanf("%d",&T);
    while(T--)
    {
        int m,n; scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++)
            scanf("%d",&a[i]);
        a[n+1] = cal(a,n,n+1);
        sum[0] = a[0];
        for(int i=1;i<=n+1;i++)
            sum[i] = (sum[i-1] + a[i])%mod;
        while(m--){
            int l,r; scanf("%d%d",&l,&r);
            int ans = cal(sum,n+1,r) - cal(sum,n+1,l-1);
            ans = (ans%mod + mod)%mod;
            printf("%d\n",ans);
        }
    }
    return 0;
}
